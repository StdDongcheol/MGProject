// Fill out your copyright notice in the Description page of Project Settings.


#include "MGTaskNode_TurnToTarget.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Animation/MGEnemyAnimInstance.h"

UMGTaskNode_TurnToTarget::UMGTaskNode_TurnToTarget()
{
	bNotifyTick = true;
	TurnAnimTimeAcc = 0.0f;
	PatternIndex = 0;
	LongRangePatternIndex = 0;
}

EBTNodeResult::Type UMGTaskNode_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMGEnemyController* EnemyController = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* EnemyCharacter = EnemyController->GetPawn<AMGEnemyCharacter>();
	UMGEnemyAnimInstance* AnimInst = EnemyCharacter->GetAnimInst<UMGEnemyAnimInstance>();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetObject"));

	AActor* ActorTarget = Cast<AActor>(Target);

	if (!ActorTarget)
	{
		TurnAnimTimeAcc = 0.0f;
		return EBTNodeResult::Succeeded;
	}

	int32 RotateStateIndex = AnimInst->GetInstanceAssetPlayerIndex(TEXT("Locomotion"), TEXT("Rotate"));
	float RotateLength = AnimInst->GetInstanceAssetPlayerLength(RotateStateIndex);

	if (AnimInst->GetAIAnimState() & EAIAnimState::Groggy)
	{
		TurnAnimTimeAcc -= TurnAnimTimeAcc;
		return EBTNodeResult::Failed;
	}

	if (RotateLength >= TurnAnimTimeAcc)
	{
		// keep progress turning.
		AnimInst->SetAIAnimState(EAIAnimState::Rotate);
		EnemyCharacter->SetLookAt(ActorTarget);

		return EBTNodeResult::InProgress;
	}

	else
	{
		// turning ended.
		TurnAnimTimeAcc -= TurnAnimTimeAcc;

		double TargetDist = FVector::Distance(EnemyCharacter->GetActorLocation(), 
			ActorTarget->GetActorLocation());
		
		if (TargetDist > SetLongRangeDistance)
		{
			AnimInst->SetAIAnimState(LongRangeAttackPattern[LongRangePatternIndex]);
			++LongRangePatternIndex;

			// Reset index
			if (LongRangePatternIndex > LongRangeAttackPattern.Num() - 1)
				LongRangePatternIndex -= LongRangePatternIndex;
		}

		else
		{
			AnimInst->SetAIAnimState(AttackPattern[PatternIndex]);
			++PatternIndex;

			// Reset index
			if (PatternIndex > AttackPattern.Num() - 1)
				PatternIndex -= PatternIndex;
		}

		return EBTNodeResult::Succeeded;
	}
}

void UMGTaskNode_TurnToTarget::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	FinishLatentTask(_OwnerComp, ExecuteTask(_OwnerComp, _pNodeMemory));

	AMGEnemyController* EnemyController = Cast<AMGEnemyController>(_OwnerComp.GetAIOwner());
	AMGEnemyCharacter* EnemyCharacter = EnemyController->GetPawn<AMGEnemyCharacter>();
	UMGEnemyAnimInstance* AnimInst = EnemyCharacter->GetAnimInst<UMGEnemyAnimInstance>();

	if (AnimInst->GetAIAnimState() == EAIAnimState::Rotate)
	{
		TurnAnimTimeAcc += _DeltaSeconds;
	}
}