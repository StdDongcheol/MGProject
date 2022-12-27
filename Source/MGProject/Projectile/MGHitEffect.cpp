// Fill out your copyright notice in the Description page of Project Settings.


#include "MGHitEffect.h"
#include "Particles/ParticleSystemComponent.h"

AMGHitEffect::AMGHitEffect()
{
 	PrimaryActorTick.bCanEverTick = true;

	HitParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	RootComponent = HitParticle;
}

void AMGHitEffect::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(1.5f);
}

void AMGHitEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

