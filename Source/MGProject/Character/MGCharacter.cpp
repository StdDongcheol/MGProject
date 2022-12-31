// Fill out your copyright notice in the Description page of Project Settings.


#include "MGCharacter.h"
#include "Components/CapsuleComponent.h"

AMGCharacter::AMGCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	Capsule = FindComponentByClass<UCapsuleComponent>();
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