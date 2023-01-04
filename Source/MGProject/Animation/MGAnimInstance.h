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

	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	IsQFire;
	
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	MovementYawValue;

	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	CharacterPrevAimYaw;
	
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	RootBoneYaw;
	
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int		QCurrentCount;
	
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int		QAnimLoopCount;

	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FRotator	CharacterAimRotation;

	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECharacter_ActionState	ActionState;

	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECharacter_BodyAction	BodyActionState;
	
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

	void SetActionState(ECharacter_ActionState State)
	{
		ActionState = State;
	}
	
	void SetBodyActionState(ECharacter_BodyAction State)
	{
		BodyActionState = State;
	}

public:
	FRotator GetAimRot() const
	{
		return CharacterAimRotation;
	}
	
public:
	ECharacter_ActionState GetActionState() const
	{
		return ActionState;
	}

	ECharacter_BodyAction GetBodyActionState() const
	{
		return BodyActionState;
	}

public:
	void AddQCount(int Count)
	{
		QCurrentCount += Count;
	}

	void AddQAnimLoopCount(int Count)
	{
		QAnimLoopCount += Count;
	}

private:
	void MGUpdateRotate(float DeltaSeconds);

public:
	void NativeUpdateAnimation(float DeltaSeconds) override;
	void NativeBeginPlay() override;

private:
	void StateUpdate(float DeltaTime);

};
