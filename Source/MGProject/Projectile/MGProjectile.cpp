// Fill out your copyright notice in the Description page of Project Settings.


#include "MGProjectile.h"
#include "Particles/ParticleSystemComponent.h"

AMGProjectile::AMGProjectile() :
	Speed(2400.f)
{
 	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(FName("Sphere"));
	RootComponent = Sphere;

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particle"));
	Particle->SetupAttachment(Sphere);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	
}

void AMGProjectile::BeginPlay()
{
	Super::BeginPlay(); 

	ProjectileComponent->ProjectileGravityScale = 0.0f;
	ProjectileComponent->Velocity = GetActorForwardVector() * Speed;
	ProjectileComponent->SetUpdatedComponent(Sphere);

	SetLifeSpan(8.0f);
}

void AMGProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

