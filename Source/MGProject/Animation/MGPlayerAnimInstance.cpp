// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPlayerAnimInstance.h"
#include "../Character/MGPlayerCharacter.h"

UMGPlayerAnimInstance::UMGPlayerAnimInstance()
{
	ActionState = EPlayer_ActionState::Normal;

	QCurrentCount = 0;
	CharacterPrevAimYaw = 0.0f;
	RootBoneYaw = 0.0f;
}

void UMGPlayerAnimInstance::SetDamaged(bool Damaged)
{
	Super::SetDamaged(Damaged);

	if (Damaged)
		DamagedTimeAcc = 0.0f;
}

void UMGPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	MGUpdateRotate(DeltaSeconds);

	StateUpdate(DeltaSeconds);
}

void UMGPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UMGPlayerAnimInstance::MGUpdateRotate(float DeltaSeconds)
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

void UMGPlayerAnimInstance::StateUpdate(float DeltaSeconds)
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
