// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGAnimInstance.h"
#include "MGPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGPlayerAnimInstance : public UMGAnimInstance
{
	GENERATED_BODY()

public:
	UMGPlayerAnimInstance();

private:
	UPROPERTY(Category = "PlayerState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	IsQFire;

	UPROPERTY(Category = "PlayerState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	MovementYawValue;

	UPROPERTY(Category = "PlayerState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	CharacterPrevAimYaw;

	UPROPERTY(Category = "PlayerState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	RootBoneYaw;
	
	UPROPERTY(Category = "PlayerState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	DamagedTimeAcc;

	UPROPERTY(Category = "PlayerState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int		QCurrentCount;

	UPROPERTY(Category = "PlayerState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int		QAnimLoopCount;

	UPROPERTY(Category = "PlayerState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FRotator	CharacterAimRotation;

	UPROPERTY(Category = "PlayerState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayer_ActionState	ActionState;

	UPROPERTY(Category = "PlayerState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayer_BodyAction	BodyActionState;

public:
	void SetMovementYaw(float Value)
	{
		MovementYawValue = Value;
	}

	void SetAimRotation(FRotator Rot)
	{
		CharacterAimRotation = Rot;
	}

	void SetQFire(bool Fire)
	{
		IsQFire = Fire;
	}

	void SetActionState(EPlayer_ActionState State)
	{
		ActionState = State;
	}

	void SetBodyActionState(EPlayer_BodyAction State)
	{
		BodyActionState = State;
	}

	void AddQCount(int Count)
	{
		QCurrentCount += Count;
	}

	void AddQAnimLoopCount(int Count)
	{
		QAnimLoopCount += Count;
	}

	FRotator GetAimRot() const
	{
		return CharacterAimRotation;
	}

	EPlayer_ActionState GetActionState() const
	{
		return ActionState;
	}

	EPlayer_BodyAction GetBodyActionState() const
	{
		return BodyActionState;
	}

	int GetCurrentQCount() const
	{
		return QCurrentCount;
	}


public:
	virtual void SetDamaged(bool Damaged) override;

public:
	void NativeUpdateAnimation(float DeltaSeconds) override;
	void NativeBeginPlay() override;

private:
	void MGUpdateRotate(float DeltaSeconds);
	void StateUpdate(float DeltaSeconds);
};
