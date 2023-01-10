// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPlayerDrone.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AMGPlayerDrone::AMGPlayerDrone() :
	IsActivated(false),
	ActivatedTime(3.0f)
{
	Mesh->SetCollisionProfileName(TEXT("PlayerAttack"));
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AMGPlayerDrone::OnCollisionEnter);

	FloatingLocation = CreateDefaultSubobject<USceneComponent>(TEXT("FloatingLocation"));
	FloatingLocation->SetupAttachment(RootComponent);
	FloatingLocation->SetWorldLocation(FVector(0.0f, 0.0f, 150.f));

	ActivateParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ActivateParticle"));
	ActivateParticle->SetupAttachment(RootComponent);
	ActivateParticle->bAutoActivate = false;

	DeactivateParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DeactivateParticle"));
	DeactivateParticle->SetupAttachment(RootComponent);
	DeactivateParticle->bAutoActivate = false;
	
	ProjectileComponent->Velocity = FVector(1200.0f, 0.0f, 0.0f);
}

void AMGPlayerDrone::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(0.0f);
}

void AMGPlayerDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ProjectileComponent->bSimulationEnabled)
	{
		FVector RecentStartPos = RootComponent->GetComponentLocation();

		float Dist = FVector::Distance(RecentStartPos, EndPos);

		if (Dist > 10.0f)
		{
			FVector LerpPos = FMath::Lerp(RecentStartPos, EndPos, 0.7f);

			FVector MoveStartPos = FVector::UpVector * LerpPos;

			AddActorWorldOffset(MoveStartPos * DeltaTime);
		}

		else
		{
			if (!IsActivated && GetLifeSpan() == 0.0f)
			{
				IsActivated = true;
				ActivateParticle->ActivateSystem();
			}
		}
	}

	if (IsActivated)
	{
		ActivatedTimeAcc += DeltaTime;

		if (ActivatedTimeAcc > ActivatedTime && GetLifeSpan() == 0.0f)
		{
			IsActivated = false;

			ActivateParticle->DeactivateSystem();
			ParticleLegacy->DeactivateSystem();
			Mesh->SetVisibility(false);

			DeactivateParticle->ActivateSystem();
		
			SetLifeSpan(1.5f);
		}
	}

}

void AMGPlayerDrone::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, 
	UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	ProjectileComponent->bSimulationEnabled = false;

	StartPos = RootComponent->GetComponentLocation();
	EndPos = RootComponent->GetComponentLocation() + FVector(0.0f, 0.0f, 150.0f);
}
