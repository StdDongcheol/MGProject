// Fill out your copyright notice in the Description page of Project Settings.


#include "MGTaskNode_Attack.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Animation/MGEnemyAnimInstance.h"

UMGTaskNode_Attack::UMGTaskNode_Attack()
{
	bNotifyTick = true;

	AttackAnimTimeAcc = 0.0f;
}

EBTNodeResult::Type UMGTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

	AMGEnemyController* EnemyController = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* EnemyCharacter = EnemyController->GetPawn<AMGEnemyCharacter>();
	UMGEnemyAnimInstance* AnimInst = EnemyCharacter->GetAnimInst<UMGEnemyAnimInstance>();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetObject"));

	AActor* ActorTarget = Cast<AActor>(Target);

	if (!ActorTarget)
	{
		AnimInst->SetCurrentAttacking(false);
		AttackAnimTimeAcc = 0.0f;

		return EBTNodeResult::Succeeded;
	}

	int32 AttStateIndex = AnimInst->GetInstanceAssetPlayerIndex(TEXT("Locomotion"), TEXT("Attack"));

	float AttackLength = AnimInst->GetInstanceAssetPlayerLength(AttStateIndex);

	double AttackRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("AttackRange"));
	double Dist = (ActorTarget->GetActorLocation() - EnemyCharacter->GetActorLocation()).Length();


	// 타겟이 범위 안에 존재할 경우
	if (Dist <= AttackRange)
	{
		// 공격 애니메이션을 재생하도록 SetAttacking.
		if (!AnimInst->GetCurrentAttacking())
		{
			AnimInst->SetCurrentAttacking(true);
		}

		if (AttackAnimTimeAcc >= AttackLength)
		{
			AnimInst->SetCurrentAttacking(false);
			AttackAnimTimeAcc = 0.0f;

			FVector Dir = (ActorTarget->GetActorLocation() - EnemyCharacter->GetActorLocation()).GetSafeNormal();
			EnemyCharacter->SetLookAt(ActorTarget);
		}

		if (EnemyCharacter->GetCurrentHP() > 0.0f)
			return EBTNodeResult::Succeeded;
		
	}

	// 타겟이 바깥으로 나갔을 경우
	else
	{
		// is attacking?
		if (AnimInst->GetCurrentAttacking())
		{
			AttackAnimTimeAcc = 0.0f;
			AnimInst->SetCurrentAttacking(false);
		}
	}

	return EBTNodeResult::Succeeded;
}

void UMGTaskNode_Attack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	FinishLatentTask(_OwnerComp, ExecuteTask(_OwnerComp, _pNodeMemory));

	AMGEnemyController* EnemyController = Cast<AMGEnemyController>(_OwnerComp.GetAIOwner());
	AMGEnemyCharacter* EnemyCharacter = EnemyController->GetPawn<AMGEnemyCharacter>();
	UMGEnemyAnimInstance* AnimInst = EnemyCharacter->GetAnimInst<UMGEnemyAnimInstance>();

	if (AnimInst->GetCurrentAttacking())
	{
		AttackAnimTimeAcc += _DeltaSeconds;
	}
}
