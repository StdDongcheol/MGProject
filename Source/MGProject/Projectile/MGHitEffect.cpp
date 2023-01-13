// Fill out your copyright notice in the Description page of Project Settings.


#include "MGHitEffect.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"

AMGHitEffect::AMGHitEffect()
{
 	PrimaryActorTick.bCanEverTick = true;

	HitParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	RootComponent = HitParticle;

	Sound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));
	Sound->SetupAttachment(RootComponent); 
}

void AMGHitEffect::SetStatus(float fLifetime, USceneComponent* Component)
{
	SetLifeSpan(fLifetime);

	if (Component != nullptr)
		AttachToComponent(Component, FAttachmentTransformRules::KeepRelativeTransform);
}

void AMGHitEffect::BeginPlay()
{
	Super::BeginPlay();

	if (Sound->GetSound())
		Sound->Play();
}

void AMGHitEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

