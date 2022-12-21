// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPlayerCharacter.h"

AMGPlayerCharacter::AMGPlayerCharacter()
{
}

void AMGPlayerCharacter::StateUpdate(float DeltaTime)
{
	Super::StateUpdate(DeltaTime);

	FRotator3d CharacterRot = GetVelocity().Rotation();
	FRotator3d AimRot = GetBaseAimRotation();

	FRotator3d RotValue = AimRot - CharacterRot;
	RotValue.Normalize();

	GetAnimInst()->SetMovementYaw(RotValue.Yaw);
	GetAnimInst()->SetAimYaw(AimRot.Yaw);

}

void AMGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	ArmSpring = FindComponentByClass<USpringArmComponent>();
}

void AMGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
