// Fill out your copyright notice in the Description page of Project Settings.


#include "MGProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Actor.h"

AMGProjectile::AMGProjectile() :
	Speed(2400.f)
{
 	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));

	ParticleLegacy = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particle"));

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	ProjectileComponent->ProjectileGravityScale = 0.0f;
}

void AMGProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(8.0f);
}

void AMGProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

