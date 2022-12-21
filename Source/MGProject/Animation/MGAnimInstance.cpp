// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimInstance.h"
#include "GameFramework/Character.h"

UMGAnimInstance::UMGAnimInstance()
{
	CharacterAimYaw = 0.0f;
	CharacterPrevAimYaw = 0.0f;
	RootBoneYaw = 0.0f;
}

void UMGAnimInstance::MGUpdateRotate(float DeltaSeconds)
{
	if (IsMoving)
	{
		RootBoneYaw = CharacterAimYaw;
	}

	else
	{
		CharacterPrevAimYaw = CharacterAimYaw;

		RootBoneYaw -= (CharacterAimYaw - CharacterPrevAimYaw);
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
