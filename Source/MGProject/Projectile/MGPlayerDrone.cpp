// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPlayerDrone.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AMGPlayerDrone::AMGPlayerDrone()
{
	Mesh->SetCollisionProfileName(TEXT("PlayerAttack"));

	ActivateParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ActivateParticle"));
	ActivateParticle->SetupAttachment(RootComponent);

	DeactivateParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DeactivateParticle"));
	DeactivateParticle->SetupAttachment(RootComponent);

	ActivateParticle->SetVisibility(false);
	DeactivateParticle->SetVisibility(false);

	ProjectileComponent->Velocity = FVector(1200.0f, 0.0f, 0.0f);

	RootComponent->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
}

void AMGPlayerDrone::BeginPlay()
{
	Super::BeginPlay();
}

void AMGPlayerDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMGPlayerDrone::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	Mesh->SetSimulatePhysics(false);
}
