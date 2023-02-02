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

	UPROPERTY(Category = "EnemyState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	IsSpawned;
	
	UPROPERTY(Category = "EnemyState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	IsStunned;
	
	UPROPERTY(Category = "EnemyState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	IsTurning;

	UPROPERTY(Category = "EnemyState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAIAnimState	AnimState;
	
	UPROPERTY(Category = "EnemyState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	TurnTo;

	// Get Functions
public:
	bool GetCurrentAttacking() const
	{
		return IsAttacking;
	}

	EAIAnimState GetAIAnimState() const
	{
		return AnimState;
	}

	bool IsStunning() const
	{
		return IsStunned;
	}
	
	bool IsSpawnCompleted() const
	{
		return IsSpawned;
	}
	

	// Set Functions
public:
	void SetCurrentAttacking(bool bEnable)
	{
		IsAttacking = bEnable;
	}

	void SetStun(bool bEnable)
	{
		IsStunned = bEnable;
	}

	// True : To right
	// False : To reft
	void SetTurning(bool bEnable)
	{
		IsTurning = bEnable;
	}

	void SetTurnTo(bool bEnable)
	{
		TurnTo = bEnable;
	}

	void SetSpawned(bool bEnable)
	{
		IsSpawned = bEnable;
	}

	void SetAIAnimState(EAIAnimState State)
	{
		AnimState = State;
	}

public:
	void NativeUpdateAnimation(float DeltaSeconds) override;
	void NativeBeginPlay() override;

};
