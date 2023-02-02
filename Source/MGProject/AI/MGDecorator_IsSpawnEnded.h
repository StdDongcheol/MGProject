// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "MGDecorator_IsSpawnEnded.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGDecorator_IsSpawnEnded : public UBTDecorator
{
	GENERATED_BODY()

public:
	UMGDecorator_IsSpawnEnded();

private:
	float	SpawnedTimeAcc;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
