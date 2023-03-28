// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "MGDecorator_IsAlive.generated.h"

/**
 * 
 */

struct UMGDecorator_IsAlive_Memory
{
	bool BeforeData;
};

typedef UMGDecorator_IsAlive_Memory TNodeInstanceMemory;

UCLASS()
class MGPROJECT_API UMGDecorator_IsAlive : public UBTDecorator
{
	GENERATED_BODY()

public:
	UMGDecorator_IsAlive();

	uint16 GetInstanceMemorySize() const
	{
		return sizeof(TNodeInstanceMemory);
	}

protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
