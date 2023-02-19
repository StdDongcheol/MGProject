// Fill out your copyright notice in the Description page of Project Settings.


#include "MGDecorator_IsAlive.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Animation/MGEnemyAnimInstance.h"

UMGDecorator_IsAlive::UMGDecorator_IsAlive()
{
}

bool UMGDecorator_IsAlive::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AMGEnemyController* Controller = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* Character = Cast<AMGEnemyCharacter>(Controller->GetPawn());
	EAIAnimState State = Character->GetAnimInst<UMGEnemyAnimInstance>()->GetAIAnimState();
	

	if (Character->GetCurrentHP() <= 0.0f || 
		(State & EAIAnimState::Death) || 
		(State & EAIAnimState::Groggy))
	{
		return false;
	}

	return true;
}

