// Fill out your copyright notice in the Description page of Project Settings.


#include "MGDecorator_IsSpawnEnded.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Animation/MGEnemyAnimInstance.h"

UMGDecorator_IsSpawnEnded::UMGDecorator_IsSpawnEnded()
{
	SpawnedTimeAcc = 0.0f;
}

bool UMGDecorator_IsSpawnEnded::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AMGEnemyController* Controller = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* Character = Cast<AMGEnemyCharacter>(Controller->GetPawn());
	UMGEnemyAnimInstance* AnimInst = Character->GetAnimInst<UMGEnemyAnimInstance>();
	
	int32 SpawnEndStateIndex = AnimInst->GetInstanceAssetPlayerIndex(TEXT("Locomotion"), TEXT("Start"));

	float SpawnLength = AnimInst->GetInstanceAssetPlayerLength(SpawnEndStateIndex);

	if (AnimInst->IsSpawnCompleted())
	{
		return true;
	}

	return false;
}
