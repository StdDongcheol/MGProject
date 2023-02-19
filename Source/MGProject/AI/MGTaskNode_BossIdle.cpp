// Fill out your copyright notice in the Description page of Project Settings.


#include "MGTaskNode_BossIdle.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Animation/MGEnemyAnimInstance.h"

UMGTaskNode_BossIdle::UMGTaskNode_BossIdle()
{
	bNotifyTick = true;
	TimeAcc = 0.0f;
}

EBTNodeResult::Type UMGTaskNode_BossIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMGEnemyController* EnemyController = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* EnemyCharacter = EnemyController->GetPawn<AMGEnemyCharacter>();
	UMGEnemyAnimInstance* AnimInst = EnemyCharacter->GetAnimInst<UMGEnemyAnimInstance>();

	if (AnimInst->GetAIAnimState() & EAIAnimState::Groggy)
	{
		TimeAcc -= TimeAcc;
		return EBTNodeResult::Failed;
	}

	if (TimeAcc >= IdleTime)
	{
		TimeAcc -= TimeAcc;
		AnimInst->SetAIAnimState(EAIAnimState::Rotate);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::InProgress;
}

void UMGTaskNode_BossIdle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	TimeAcc += _DeltaSeconds;

	FinishLatentTask(_OwnerComp, ExecuteTask(_OwnerComp, _pNodeMemory));
}
