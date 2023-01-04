// Fill out your copyright notice in the Description page of Project Settings.


#include "MGProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
//#include "NiagaraComponent.h"

AMGProjectile::AMGProjectile() :
	Speed(2400.f)
{
 	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	RootComponent = Mesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	Sphere->SetupAttachment(Mesh);

	ParticleLegacy = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particle"));
	ParticleLegacy->SetupAttachment(Mesh);

	//ParticleNiagara = CreateDefaultSubobject<UNiagaraComponent>(FName("Particle"));
	//ParticleNiagara->SetupAttachment(Mesh);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));

}

void AMGProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileComponent->ProjectileGravityScale = 0.0f;
	ProjectileComponent->Velocity = GetActorForwardVector() * Speed;
	ProjectileComponent->InitialSpeed = 0.0f;
	ProjectileComponent->MaxSpeed = 0.0f;
	ProjectileComponent->Bounciness = 0.0f;
	ProjectileComponent->SetUpdatedComponent(Mesh);

	SetLifeSpan(8.0f);
}

void AMGProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

