// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MGAIController.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGAIController : public AAIController
{
	GENERATED_BODY()

protected:
	void OnPossess(APawn* _Mon) override;

private:
	UBehaviorTree*		BehaviorTree;
	UBlackboardData*	BlackboardData;
};
