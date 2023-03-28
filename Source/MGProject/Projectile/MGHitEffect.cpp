// Fill out your copyright notice in the Description page of Project Settings.


#include "MGHitEffect.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"

AMGHitEffect::AMGHitEffect()
{
 	PrimaryActorTick.bCanEverTick = true;

	HitParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	RootComponent = HitParticle;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));
	AudioComponent->SetupAttachment(RootComponent);

	IsSoundPlayed = false;
}

void AMGHitEffect::SetStatus(float fLifetime, USceneComponent* AttachComponent)
{
	SetLifeSpan(fLifetime);

	if (AttachComponent != nullptr)
	{
		AttachToComponent(AttachComponent, FAttachmentTransformRules::KeepWorldTransform);
		AttachToOtherComponent = true;
	}
}

void AMGHitEffect::SetSound(USoundBase* SoundBase)
{
	AudioComponent->SetSound(SoundBase);
	
	if (SoundBase)
		AudioComponent->Play();
}

void AMGHitEffect::SetParticle(UParticleSystem* CascadeParticle)
{
	HitParticle->SetTemplate(CascadeParticle);
}

void AMGHitEffect::SetParticleNiagara(const UNiagaraSystem* NiagaraParticle)
{
	return;
}

void AMGHitEffect::BeginPlay()
{
	Super::BeginPlay();
}

void AMGHitEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

