// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGAIController.h"
#include "MGEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGEnemyController : public AMGAIController
{
	GENERATED_BODY()

protected:
	void OnPossess(APawn* _Mon) override;
	
};
