// Fill out your copyright notice in the Description page of Project Settings.


#include "MGTaskNode_TrackingTarget.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"

UMGTaskNode_TrackingTarget::UMGTaskNode_TrackingTarget()
{
}

EBTNodeResult::Type UMGTaskNode_TrackingTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMGEnemyController* EnemyController = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* EnemyCharacter = EnemyController->GetPawn<AMGEnemyCharacter>();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetObject"));

	AActor* ActorTarget = Cast<AActor>(Target);

	if (ActorTarget)
	{
		EnemyCharacter->SetLookAt(ActorTarget);

		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Succeeded;
}

void UMGTaskNode_TrackingTarget::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	FinishLatentTask(_OwnerComp, ExecuteTask(_OwnerComp, _pNodeMemory));
}
