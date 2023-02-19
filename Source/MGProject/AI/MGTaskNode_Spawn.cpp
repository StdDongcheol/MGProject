// Fill out your copyright notice in the Description page of Project Settings.


#include "MGTaskNode_Spawn.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Animation/MGEnemyAnimInstance.h"

UMGTaskNode_Spawn::UMGTaskNode_Spawn()
{
	bNotifyTick = true;
	SpawnedTimeAcc = 0.0f;
}

EBTNodeResult::Type UMGTaskNode_Spawn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMGEnemyController* Controller = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* Character = Cast<AMGEnemyCharacter>(Controller->GetPawn());
	UMGEnemyAnimInstance* AnimInst = Character->GetAnimInst<UMGEnemyAnimInstance>();

	if (AnimInst->IsSpawnCompleted())
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::InProgress;
}

void UMGTaskNode_Spawn::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	FinishLatentTask(_OwnerComp, ExecuteTask(_OwnerComp, _pNodeMemory));

	AMGEnemyController* Controller = Cast<AMGEnemyController>(_OwnerComp.GetAIOwner());
	AMGEnemyCharacter* Character = Cast<AMGEnemyCharacter>(Controller->GetPawn());
	UMGEnemyAnimInstance* AnimInst = Character->GetAnimInst<UMGEnemyAnimInstance>();

	int32 SpawnEndStateIndex = AnimInst->GetInstanceAssetPlayerIndex(TEXT("Locomotion"), TEXT("Start"));

	float SpawnLength = AnimInst->GetInstanceAssetPlayerLength(SpawnEndStateIndex);

	if (!AnimInst->IsSpawnCompleted())
	{
		SpawnedTimeAcc += _DeltaSeconds;

		if (SpawnedTimeAcc >= SpawnLength)
		{
			SpawnedTimeAcc -= SpawnedTimeAcc;
			AnimInst->SetAIAnimState(EAIAnimState::Idle);
			AnimInst->SetSpawned(true);
		}
	}
}
