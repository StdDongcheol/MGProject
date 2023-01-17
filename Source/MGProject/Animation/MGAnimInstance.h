// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MGFlag.h"
#include "Animation/AnimInstance.h"
#include "MGAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMGAnimInstance();

private:
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	IsMoving;
	
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	IsFire;

	// Player
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	IsQFire;

	// Player
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	MovementYawValue;

	// Player
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	CharacterPrevAimYaw;

	// Player
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	RootBoneYaw;

	// Player
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int		QCurrentCount;

	// Player
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int		QAnimLoopCount;

	// Player
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FRotator	CharacterAimRotation;

	// Player
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayer_ActionState	ActionState;

	// Player
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
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

	void SetMoving(bool Moving)
	{
		IsMoving = Moving;
	}
	
	void SetFire(bool Fire)
	{
		IsFire = Fire;
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

public:
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
	void NativeUpdateAnimation(float DeltaSeconds) override;
	void NativeBeginPlay() override;

private:
	void MGUpdateRotate(float DeltaSeconds);
	void StateUpdate(float DeltaSeconds);


};
