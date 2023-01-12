// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPlayerDrone.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

AMGPlayerDrone::AMGPlayerDrone() :
	IsActivated(false),
	IsHealActivated(false),
	ActivatedTime(10.0f)
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
	
	HealParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HealParticle"));
	HealParticle->SetupAttachment(RootComponent);
	HealParticle->bAutoActivate = false;
	
	HealSphere = CreateDefaultSubobject<USphereComponent>(TEXT("HealSphere"));
	HealSphere->SetupAttachment(RootComponent);
	HealSphere->SetNotifyRigidBodyCollision(true);
	HealSphere->SetCollisionProfileName(TEXT("PlayerHeal"));
	HealSphere->SetSphereRadius(1000.f);
	HealSphere->SetGenerateOverlapEvents(false);
	HealSphere->OnComponentBeginOverlap.AddDynamic(this, &AMGPlayerDrone::OnHealCollisionEnter);
	HealSphere->OnComponentEndOverlap.AddDynamic(this, &AMGPlayerDrone::OnHealCollisionEnd);

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

	//UE_LOG(LogTemp, Log, TEXT("AccumTickTime : %f"), ActivateParticle->AccumTickTime);

	if (ParticleDatas.Num() > 0)
	{
		for (FMGParticleSoundEventInfo& ParticleEventData : ParticleDatas)
		{
			if (!ParticleEventData.IsPlayed &&
				ActivateParticle->AccumTickTime > ParticleEventData.EventTime )
			{
				ParticleEventData.IsPlayed = true;
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), ParticleEventData.Audio, GetActorLocation());
			}
		}
	}

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
				HealSphere->SetGenerateOverlapEvents(true);
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

			// Heal off
			IsHealActivated = !IsHealActivated;
			HealParticle->KillParticlesForced();
			HealParticle->DeactivateSystem();
			
			// Particle off
			ActivateParticle->DeactivateSystem();
			ParticleLegacy->DeactivateSystem();
			Mesh->SetVisibility(false);

			DeactivateParticle->ActivateSystem();
		
			SetLifeSpan(1.5f);
		}
	}

	if (IsHealActivated)
	{
		if (HealingTarget && HealingTarget->IsValidLowLevel())
		{
			FVector Pos = HealingTarget->GetActorLocation() + FVector(0.0f, 0.0f, -100.0f);

			HealParticle->SetWorldLocation(Pos);
		}
	}
}

void AMGPlayerDrone::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, 
	UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	FName CollisionName = _OtherComp->GetCollisionProfileName();

	if (CollisionName != FName("PlayerHeal"))
	{
		ProjectileComponent->bSimulationEnabled = false;

		StartPos = RootComponent->GetComponentLocation();
		EndPos = RootComponent->GetComponentLocation() + FVector(0.0f, 0.0f, 150.0f);
	}
}

void AMGPlayerDrone::OnHealCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, 
	UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	FName CollisionName = _OtherComp->GetCollisionProfileName();

	if (CollisionName == FName("Player"))
	{
		HealingTarget = _pOtherActor;

		IsHealActivated = !IsHealActivated;

		// heal effect 시작.
		HealParticle->ActivateSystem();

		// Player 도트 heal 시작.
		 
		
	}
}

void AMGPlayerDrone::OnHealCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	FName CollisionName = OtherComp->GetCollisionProfileName();

	if (CollisionName == FName("Player"))
	{
		HealingTarget = nullptr;

		IsHealActivated = !IsHealActivated;

		// heal effect 정지.
		HealParticle->DeactivateSystem();

		// Player 도트 heal 정지.


	}
}
