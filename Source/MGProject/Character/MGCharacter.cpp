// Fill out your copyright notice in the Description page of Project Settings.


#include "MGCharacter.h"
#include "../MGBlueprintFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

AMGCharacter::AMGCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = FindComponentByClass<UCapsuleComponent>();
	SetRootComponent(CapsuleComponent);
}

void AMGCharacter::AdjustHP(float _HP)
{
	HP += _HP;

	if (HP <= 0.0f)
	{
		AnimInstance->SetDeath(true);

		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		CapsuleComponent->SetCollisionProfileName(TEXT("Ragdoll"));
		SetLifeSpan(5.0f);
		return;
	}

	if (_HP < 0.0f)
	{
		AnimInstance->SetDamaged(true);
	}
}

void AMGCharacter::SetDamage(float _Damage, bool _IsWeakpoint)
{
	AdjustHP(_Damage);
}

AActor* AMGCharacter::FindTarget(FName _TargetTag, double _Range)
{
	TArray<TObjectPtr<AActor>> ActorsInLevel;

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

	if (AnimInstance->GetStatus() == ECharacter_Status::Normal)
	{
		if (Velocity.Length() > 0.f)
		{
			AnimInstance->SetMoving(true);
		}
	
		else
		{
			AnimInstance->SetMoving(false);
		}
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