// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGCharacter.h"
#include "../MGStructs.h"
#include "MGEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGEnemyCharacter : public AMGCharacter
{
	GENERATED_BODY()

public:
	AMGEnemyCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProperty")
	class UWidgetComponent* TargetingWidgetComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProperty", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProperty", meta = (AllowPrivateAccess = "true"))
	class UBlackboardData* BlackboardData;

	class UMGEnemyWidget* EnemyWidget;

protected:
	const struct FMGEnemyStatusDataTable* EnemyData;

public:
	const FMGEnemyStatusDataTable* GetEnemyData()
	{
		return EnemyData;
	}

protected:
	bool	IsTargetLock;
	double	DetectRange;
	double	AttackRange;

public:
	bool IsTargetLocked() const
	{
		return IsTargetLock;
	}

	void SetDetectRange(float _Range)
	{
		DetectRange = _Range;
	}

	void SetAttackRange(float _Range)
	{
		AttackRange = _Range;
	}

public:
	double GetDetectRange() const
	{
		return DetectRange;
	}

	double GetAttackRange() const
	{
		return AttackRange;
	}

	class UBehaviorTree* GetBehaviorTree() const;
	class UBlackboardData* GetBlackboardData() const;

public:
	void SetLockonWidget(bool bEnable);

public:
	virtual const FMGEnemyStatusDataTable* InitEnemyData();
	virtual void AdjustHP(float _HP);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


};
