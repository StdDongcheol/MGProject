// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimInstance.h"
#include "GameFramework/Character.h"

UMGAnimInstance::UMGAnimInstance()
{
	ActionState = ECharacter_ActionState::Normal;
	CharacterPrevAimYaw = 0.0f;
	RootBoneYaw = 0.0f;
}

void UMGAnimInstance::MGUpdateRotate(float DeltaSeconds)
{
	if (IsMoving || 
		ActionState == ECharacter_ActionState::Aiming ||
		ActionState == ECharacter_ActionState::QAiming ||
		ActionState == ECharacter_ActionState::RAiming)
	{
		RootBoneYaw = CharacterAimRotation.Yaw;
	}

	else
	{
		CharacterPrevAimYaw = CharacterAimRotation.Yaw;

		RootBoneYaw -= (CharacterAimRotation.Yaw - CharacterPrevAimYaw);
	}
}

void UMGAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	MGUpdateRotate(DeltaSeconds);

	
}

void UMGAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}
