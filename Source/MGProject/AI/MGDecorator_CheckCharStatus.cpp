// Fill out your copyright notice in the Description page of Project Settings.


#include "MGDecorator_CheckCharStatus.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Animation/MGEnemyAnimInstance.h"

UMGDecorator_CheckCharStatus::UMGDecorator_CheckCharStatus()
{
}

bool UMGDecorator_CheckCharStatus::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AMGEnemyController* Controller = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* Character = Cast<AMGEnemyCharacter>(Controller->GetPawn());
	UMGEnemyAnimInstance* AnimInst = Character->GetAnimInst<UMGEnemyAnimInstance>();

	bool bCheck = (bool)(Character->GetStatus());

	// Is NormalState

	if (CheckStatus == ECharacter_Status::Normal)
	{
		if (!bCheck)
			return true;
	}

	if (CheckStatus & AnimInst->GetStatus())
		return true;

	return false;
}
