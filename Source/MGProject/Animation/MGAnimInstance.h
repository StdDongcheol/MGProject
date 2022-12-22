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
	float	MovementYawValue;

	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FRotator	CharacterAimRotation;
	
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	CharacterPrevAimYaw;
	
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	RootBoneYaw;

	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECharacter_ActionState	ActionState;
	
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

	void SetActionState(ECharacter_ActionState State)
	{
		ActionState = State;
	}
	
public:
	ECharacter_ActionState GetActionState() const
	{
		return ActionState;
	}

private:
	void MGUpdateRotate(float DeltaSeconds);

public:
	void NativeUpdateAnimation(float DeltaSeconds) override;
	void NativeBeginPlay() override;

};
