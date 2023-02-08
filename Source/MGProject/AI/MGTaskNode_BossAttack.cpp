// Fill out your copyright notice in the Description page of Project Settings.


#include "MGTaskNode_BossAttack.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Animation/MGEnemyAnimInstance.h"

UMGTaskNode_BossAttack::UMGTaskNode_BossAttack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UMGTaskNode_BossAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMGEnemyController* EnemyController = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* EnemyCharacter = EnemyController->GetPawn<AMGEnemyCharacter>();
	UMGEnemyAnimInstance* AnimInst = EnemyCharacter->GetAnimInst<UMGEnemyAnimInstance>();

	// attacking now...
	if (AnimInst->GetAIAnimState() == EAIAnimState::Attack)
		return EBTNodeResult::InProgress;

	// attack ended
	else
	{
		return EBTNodeResult::Succeeded;
	}
}

void UMGTaskNode_BossAttack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	FinishLatentTask(_OwnerComp, ExecuteTask(_OwnerComp, _pNodeMemory));
}
