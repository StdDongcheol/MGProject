// Fill out your copyright notice in the Description page of Project Settings.


#include "MGDecorator_IsAlive.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Animation/MGEnemyAnimInstance.h"

UMGDecorator_IsAlive::UMGDecorator_IsAlive()
{
	bNotifyTick = true;
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

void UMGDecorator_IsAlive::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	
	TNodeInstanceMemory* DecoratorMemory = CastInstanceNodeMemory<TNodeInstanceMemory>(NodeMemory);
	DecoratorMemory->BeforeData = CalculateRawConditionValue(OwnerComp, NodeMemory);
}

void UMGDecorator_IsAlive::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	TNodeInstanceMemory* DecoratorMemory = CastInstanceNodeMemory<TNodeInstanceMemory>(NodeMemory);
	
	bool bCondition = CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (bCondition != DecoratorMemory->BeforeData)
	{
		DecoratorMemory->BeforeData = bCondition;
		OwnerComp.RequestExecution(this);
	}
}