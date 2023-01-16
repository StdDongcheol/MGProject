// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MGService_TargetSearch.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGService_TargetSearch : public UBTService
{
	GENERATED_BODY()

public:
	UMGService_TargetSearch();

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

};
