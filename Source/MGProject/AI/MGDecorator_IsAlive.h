// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "MGDecorator_IsAlive.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGDecorator_IsAlive : public UBTDecorator
{
	GENERATED_BODY()

public:
	UMGDecorator_IsAlive();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
