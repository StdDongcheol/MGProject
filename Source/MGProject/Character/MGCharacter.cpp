// Fill out your copyright notice in the Description page of Project Settings.


#include "MGCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../MGBlueprintFunctionLibrary.h"

AMGCharacter::AMGCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	Capsule = FindComponentByClass<UCapsuleComponent>();
	SetRootComponent(Capsule);
}

void AMGCharacter::AdjustHP(float _HP)
{
	HP += _HP;

	if (HP <= 0.0f)
	{
		AnimInstance->SetDeath(true);
		return;
	}

	if (_HP < 0.0f)
	{
		AnimInstance->SetDamaged(true);
	}
}

AActor* AMGCharacter::FindTarget(FName _TargetTag, double _Range)
{
	TArray<AActor*> ActorsInLevel;

	UGameplayStatics::GetAllActorsWithTag(UMGBlueprintFunctionLibrary::GetCurrentWorld(), _TargetTag, ActorsInLevel);

	if (ActorsInLevel.IsEmpty())
	{
		return nullptr;
	}

	if (_Range <= 0.0f)
	{
		return ActorsInLevel[0];
	}

	FVector Location = GetActorLocation();

	for (size_t i = 0; i < ActorsInLevel.Num(); i++)
	{
		float Length = (Location - ActorsInLevel[i]->GetActorLocation()).Size();

		if (_Range > Length)
		{
			return ActorsInLevel[i];
		}
	}

	return nullptr;
}

FVector AMGCharacter::GetTargetDir(AActor* _Target)
{
	return _Target->GetActorLocation() - GetActorLocation();
}

FVector AMGCharacter::GetTargetDir(const FVector& _TargetLocation)
{
	return _TargetLocation - GetActorLocation();
}

void AMGCharacter::SetLookAt(AActor* _Target)
{
	SetActorRotation(GetTargetDir(_Target).GetSafeNormal().Rotation());
}

void AMGCharacter::AddMovement(FVector Dir, float Scale)
{
	AddMovementInput(Dir, Scale);
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