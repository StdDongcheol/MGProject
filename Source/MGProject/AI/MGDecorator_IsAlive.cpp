// Fill out your copyright notice in the Description page of Project Settings.


#include "MGDecorator_IsAlive.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"

UMGDecorator_IsAlive::UMGDecorator_IsAlive()
{
}

bool UMGDecorator_IsAlive::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AMGEnemyController* Controller = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* Character = Cast<AMGEnemyCharacter>(Controller->GetPawn());
	
	if (Character->GetCurrentHP() <= 0.0f)
	{
		return false;
	}

	return true;
}
