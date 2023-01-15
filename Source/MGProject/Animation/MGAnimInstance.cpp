// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimInstance.h"
#include "../Character/MGPlayerCharacter.h"
#include "GameFramework/Character.h"

UMGAnimInstance::UMGAnimInstance() :
	QCurrentCount(0)
{
	ActionState = EPlayer_ActionState::Normal;
	CharacterPrevAimYaw = 0.0f;
	RootBoneYaw = 0.0f;
}

void UMGAnimInstance::MGUpdateRotate(float DeltaSeconds)
{
	if (IsMoving || 
		ActionState == EPlayer_ActionState::Aiming ||
		ActionState == EPlayer_ActionState::QAiming ||
		ActionState == EPlayer_ActionState::EAiming)
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
	case EPlayer_BodyAction::None:
		break;
	case EPlayer_BodyAction::Ready:
		break;
	case EPlayer_BodyAction::NormalFire:
		break;
	case EPlayer_BodyAction::QFire:
	{
		if (QCurrentCount >= QAnimLoopCount)
		{
			AMGPlayerCharacter* PlayerCharacter = Cast<AMGPlayerCharacter>(GetOwningActor());

			QAnimLoopCount = PlayerCharacter->GetMissileCount(QCurrentCount);
			QCurrentCount = 0;

			SetActionState(EPlayer_ActionState::Normal);
			SetBodyActionState(EPlayer_BodyAction::Ready);
			PlayerCharacter->QFireEnd();
		}
	}
		break;
	case EPlayer_BodyAction::EThrowing:
		break;
	default:
		break;
	}
}
