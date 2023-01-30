// Fill out your copyright notice in the Description page of Project Settings.


#include "MGMissile.h"
#include "MGHitEffect.h"
#include "../Character/MGCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

AMGMissile::AMGMissile() 
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(RootComponent);
	SphereCollider->SetCollisionProfileName(TEXT("PlayerAttack"));
	SphereCollider->SetNotifyRigidBodyCollision(true);
	SphereCollider->SetRelativeLocation(FVector(30.0f, 0.0f, 0.0f));
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AMGMissile::OnCollisionEnter);
}

void AMGMissile::SetTarget(USceneComponent* TargetComponent)
{
	ProjectileComponent->HomingTargetComponent = TargetComponent;
	ProjectileComponent->bIsHomingProjectile = true;
}

void AMGMissile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileComponent->InitialSpeed = 1000.f;
	ProjectileComponent->MaxSpeed = 4000.f;
	ProjectileComponent->bRotationFollowsVelocity = true;
	ProjectileComponent->HomingAccelerationMagnitude = 3500.f;
	ProjectileComponent->ProjectileGravityScale = 0.f;
	ProjectileComponent->bShouldBounce = true;
}

void AMGMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMGMissile::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	ProjectileComponent->StopSimulating(_Hit);

	AMGHitEffect* Effect = GetWorld()->SpawnActor<AMGHitEffect>(HitEffect, GetActorLocation(), GetActorRotation());
	Effect->SetStatus(3.0f);

	FName OtherProfile = _OtherComp->GetCollisionProfileName();

	AMGCharacter* OtherCharacter = Cast<AMGCharacter>(_pOtherActor);

	if (!OtherCharacter || !OtherCharacter->IsValidLowLevel())
	{
		Destroy();
		return;
	}

	if (OtherProfile == "Enemy")
	{
		OtherCharacter->AdjustHP(-10.0f);
	}

	OtherCharacter->SetStatus(ECharacter_Status::Status_Damaged);

	Destroy();
}
