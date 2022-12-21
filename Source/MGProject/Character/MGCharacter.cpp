// Fill out your copyright notice in the Description page of Project Settings.


#include "MGCharacter.h"

AMGCharacter::AMGCharacter() :
	ActionState(ECharacter_ActionState::Idle),
	ActiveState(ECharacter_ActiveState::Active)
{
 	PrimaryActorTick.bCanEverTick = true;

}

void AMGCharacter::StateUpdate(float DeltaTime)
{
	FVector Velocity = GetVelocity();

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

	AnimInstance->SetCharacter(this);
}

void AMGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StateUpdate(DeltaTime);

}

void AMGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

