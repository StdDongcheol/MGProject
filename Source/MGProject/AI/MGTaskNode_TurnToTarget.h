// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MGFlag.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MGTaskNode_TurnToTarget.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGTaskNode_TurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMGTaskNode_TurnToTarget();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<EAIAnimState> AttackPattern;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<EAIAnimState> LongRangeAttackPattern;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	double	SetLongRangeDistance;
	
private:
	int		PatternIndex;
	int		LongRangePatternIndex;
	double	TurnAnimTimeAcc;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;

};
