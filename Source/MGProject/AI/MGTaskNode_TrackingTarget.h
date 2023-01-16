// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MGTaskNode_TrackingTarget.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGTaskNode_TrackingTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMGTaskNode_TrackingTarget();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;

};
