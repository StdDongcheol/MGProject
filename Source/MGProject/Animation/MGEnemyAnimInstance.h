// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGAnimInstance.h"
#include "MGEnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGEnemyAnimInstance : public UMGAnimInstance
{
	GENERATED_BODY()

public:
	UMGEnemyAnimInstance();

protected:
	UPROPERTY(Category = "EnemyState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	IsAttacking;

	// Get Functions
public:
	bool GetCurrentAttacking() const
	{
		return IsAttacking;
	}

	// Set Functions
public:
	void SetCurrentAttacking(bool bEnable)
	{
		IsAttacking = bEnable;
	}

public:
	void NativeUpdateAnimation(float DeltaSeconds) override;
	void NativeBeginPlay() override;

};
