// Fill out your copyright notice in the Description page of Project Settings.


#include "MGProjectile.h"
#include "Particles/ParticleSystemComponent.h"

AMGProjectile::AMGProjectile()
{
 	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(FName("Sphere"));
	RootComponent = Sphere;

	Particle = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particle"));
	
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));

}

void AMGProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMGProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

