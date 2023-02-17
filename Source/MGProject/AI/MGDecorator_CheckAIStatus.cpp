// Fill out your copyright notice in the Description page of Project Settings.


#include "MGDecorator_CheckAIStatus.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Animation/MGEnemyAnimInstance.h"

UMGDecorator_CheckAIStatus::UMGDecorator_CheckAIStatus()
{
}

bool UMGDecorator_CheckAIStatus::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AMGEnemyController* Controller = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* Character = Cast<AMGEnemyCharacter>(Controller->GetPawn());
	UMGEnemyAnimInstance* AnimInst = Character->GetAnimInst<UMGEnemyAnimInstance>();

	if (CheckStatus & AnimInst->GetAIAnimState())
		return false;

	return true;
}
