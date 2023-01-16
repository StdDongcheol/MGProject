// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MGTaskNode_Idle.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGTaskNode_Idle : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMGTaskNode_Idle();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;

};
