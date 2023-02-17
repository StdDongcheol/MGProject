// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MGFlag.h"
#include "BehaviorTree/BTDecorator.h"
#include "MGDecorator_CheckAIStatus.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGDecorator_CheckAIStatus : public UBTDecorator
{
	GENERATED_BODY()

public:
	UMGDecorator_CheckAIStatus();

private:
	UPROPERTY(EditAnywhere)
	EAIAnimState	CheckStatus;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
