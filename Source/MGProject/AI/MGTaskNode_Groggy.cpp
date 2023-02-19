// Fill out your copyright notice in the Description page of Project Settings.


#include "MGTaskNode_Groggy.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Animation/MGEnemyAnimInstance.h"

UMGTaskNode_Groggy::UMGTaskNode_Groggy()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UMGTaskNode_Groggy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMGEnemyController* EnemyController = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* EnemyCharacter = EnemyController->GetPawn<AMGEnemyCharacter>();
	UMGEnemyAnimInstance* AnimInst = EnemyCharacter->GetAnimInst<UMGEnemyAnimInstance>();

	if (EnemyCharacter->GetCurrentHP() <= 0.0f)
	{
		TimeAcc -= TimeAcc;
		return EBTNodeResult::Failed;
	}
	
	if (TimeAcc >= GroggyTime)
	{
		TimeAcc -= TimeAcc;
		AnimInst->SetAIAnimState(EAIAnimState::Idle);
		return EBTNodeResult::Succeeded;
	}
	
	else
		return EBTNodeResult::InProgress;
}	

void UMGTaskNode_Groggy::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	TimeAcc += _DeltaSeconds;

	FinishLatentTask(_OwnerComp, ExecuteTask(_OwnerComp, _pNodeMemory));
}
