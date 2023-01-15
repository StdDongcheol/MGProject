// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGCharacter.h"
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

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProperty", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyProperty", meta = (AllowPrivateAccess = "true"))
	class UBlackboardData* BlackboardData;

private:
	class UMGEnemyWidget* EnemyWidget;

private:
	bool IsTargetLock;

public:
	bool IsTargetLocked() const
	{
		return IsTargetLock;
	}

	class UBehaviorTree* GetBehaviorTree() const;
	class UBlackboardData* GetBlackboardData() const;

public:
	void SetLockonWidget(bool bEnable);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


};
