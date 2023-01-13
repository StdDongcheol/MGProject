// Fill out your copyright notice in the Description page of Project Settings.


#include "MGCharacter.h"
#include "Components/CapsuleComponent.h"

AMGCharacter::AMGCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	Capsule = FindComponentByClass<UCapsuleComponent>();
}

void AMGCharacter::AdjustHP(float _HP)
{
	if (_HP < 0.0f)
	{
		HP -= _HP;
	}

	else
	{
		if (HP < HPMax)
			HP += _HP;
	}
}

void AMGCharacter::StateUpdate(float DeltaTime)
{
	FVector Velocity = GetVelocity();

	if (!AnimInstance || !AnimInstance->IsValidLowLevel())
		return;

	if (Velocity.Length() > 0.f)
	{
		AnimInstance->SetMoving(true);
	}
	
	else
	{
		AnimInstance->SetMoving(false);
	}
}

void AMGCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance = Cast<UMGAnimInstance>(GetMesh()->GetAnimInstance());
}

void AMGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StateUpdate(DeltaTime);

}