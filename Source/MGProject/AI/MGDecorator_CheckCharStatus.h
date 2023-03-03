// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MGFlag.h"
#include "BehaviorTree/BTDecorator.h"
#include "MGDecorator_CheckCharStatus.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGDecorator_CheckCharStatus : public UBTDecorator
{
	GENERATED_BODY()

public:
	UMGDecorator_CheckCharStatus();

private:
	UPROPERTY(EditAnywhere)
	ECharacter_Status	CheckStatus;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
