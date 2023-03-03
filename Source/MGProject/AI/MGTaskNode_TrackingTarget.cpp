// Fill out your copyright notice in the Description page of Project Settings.


#include "MGTaskNode_TrackingTarget.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Animation/MGEnemyAnimInstance.h"

UMGTaskNode_TrackingTarget::UMGTaskNode_TrackingTarget()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UMGTaskNode_TrackingTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMGEnemyController* EnemyController = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* EnemyCharacter = EnemyController->GetPawn<AMGEnemyCharacter>();
	UMGEnemyAnimInstance* AnimInst = EnemyCharacter->GetAnimInst<UMGEnemyAnimInstance>();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetObject"));

	AActor* ActorTarget = Cast<AActor>(Target);

	if (ActorTarget)
	{ 
		double Dist = (ActorTarget->GetActorLocation() - EnemyCharacter->GetActorLocation()).Length();
		FVector Dir = (ActorTarget->GetActorLocation() - EnemyCharacter->GetActorLocation()).GetSafeNormal();
		EnemyCharacter->SetLookAt(ActorTarget);
		EnemyCharacter->AddMovement(Dir);

		double AttackRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("AttackRange"));


		// Transition to Attack_TaskNode
		if (AttackRange > Dist)
			return EBTNodeResult::Succeeded;
		
		else
		{
			// Is not death && Is character status not damaged
			if (EnemyCharacter->GetCurrentHP() > 0.0f && 
				!(ECharacter_Status::Damaged & AnimInst->GetStatus()))
			{
				AnimInst->SetCurrentAttacking(false);

				return EBTNodeResult::InProgress;
			}
		}
	}

	return EBTNodeResult::Failed;
}

void UMGTaskNode_TrackingTarget::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	FinishLatentTask(_OwnerComp, ExecuteTask(_OwnerComp, _pNodeMemory));
}
