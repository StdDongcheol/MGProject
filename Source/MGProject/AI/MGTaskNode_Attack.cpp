// Fill out your copyright notice in the Description page of Project Settings.


#include "MGTaskNode_Attack.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"

UMGTaskNode_Attack::UMGTaskNode_Attack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UMGTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

	AMGEnemyController* EnemyController = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* EnemyCharacter = EnemyController->GetPawn<AMGEnemyCharacter>();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetObject"));

	AActor* ActorTarget = Cast<AActor>(Target);

	if (!ActorTarget)
	{
		return EBTNodeResult::Succeeded;
	}

	double AttackRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("AttackRange"));
	double Dist = (ActorTarget->GetActorLocation() - EnemyCharacter->GetActorLocation()).Length();
	
	// 거리가 AttackRange보다 멀어졌다면,
	if (Dist > AttackRange)
	{
		//if (공격 애니메이션 재생중이라면)
			return EBTNodeResult::InProgress;

		// 애니메이션 재생이 끝났다
		//else
		//	return EBTNodeResult::Succeeded;
	}

    return EBTNodeResult::Succeeded;
}

void UMGTaskNode_Attack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	FinishLatentTask(_OwnerComp, ExecuteTask(_OwnerComp, _pNodeMemory));
}
