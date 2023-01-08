// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimInstance.h"
#include "../Character/MGPlayerCharacter.h"
#include "GameFramework/Character.h"

UMGAnimInstance::UMGAnimInstance() :
	QCurrentCount(0)
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
		ActionState == ECharacter_ActionState::EAiming)
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

	StateUpdate(DeltaSeconds);
}

void UMGAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UMGAnimInstance::StateUpdate(float DeltaTime)
{
	switch (BodyActionState)
	{
	case ECharacter_BodyAction::None:
		break;
	case ECharacter_BodyAction::Ready:
		break;
	case ECharacter_BodyAction::NormalFire:
		break;
	case ECharacter_BodyAction::QFire:
	{
		if (QCurrentCount >= QAnimLoopCount)
		{
			AMGPlayerCharacter* PlayerCharacter = Cast<AMGPlayerCharacter>(GetOwningActor());

			QAnimLoopCount = PlayerCharacter->GetMissileCount(QCurrentCount);
			QCurrentCount = 0;

			SetActionState(ECharacter_ActionState::Normal);
			SetBodyActionState(ECharacter_BodyAction::Ready);
			PlayerCharacter->QFireEnd();
		}
	}
		break;
	case ECharacter_BodyAction::EThrowing:
		break;
	default:
		break;
	}
}
