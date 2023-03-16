// Fill out your copyright notice in the Description page of Project Settings.


#include "MGBullet.h"
#include "MGHitEffect.h"
#include "../MGBlueprintFunctionLibrary.h"
#include "../Character/MGCharacter.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AMGBullet::AMGBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = Mesh;
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AMGBullet::OnCollisionEnter);

	ParticleLegacy->SetupAttachment(RootComponent);
	ProjectileComponent->SetUpdatedComponent(RootComponent);
}

void AMGBullet::BeginPlay()
{
	Super::BeginPlay();
}
	
void AMGBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMGBullet::SetBulletProfile(FName _Name, float _Speed, float _Damage)
{
	Mesh->SetCollisionProfileName(_Name);
	Speed = _Speed;
	Damage = _Damage;

	ProjectileComponent->Velocity = GetActorForwardVector() * Speed;

	if (_Name == "PlayerAttack")
	{
		const FMGBulletDataTable* BulletTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetBulletData(TEXT("PlayerBullet"));
		ParticleTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetParticleData(TEXT("PlayerNormal"));

		if (BulletTable && ParticleTable)
		{
			switch (BulletTable->ParticleType)
			{
			case EParticle_Type::None:
				break;
			case EParticle_Type::CascadeParticle:
				ParticleLegacy->SetTemplate(BulletTable->ProjectileEffect);
				break;
			case EParticle_Type::NiagaraParticle:
				UNiagaraFunctionLibrary::SpawnSystemAttached(BulletTable->NiagaraParticle, GetRootComponent(), 
					NAME_None, GetActorLocation(), GetActorRotation(), EAttachLocation::KeepRelativeOffset, true);
				break;
			default:
				break;
			}

			switch (ParticleTable->ParticleType)
			{
			case EParticle_Type::None:
				break;
			case EParticle_Type::CascadeParticle:
				HitEffect = ParticleTable->CascadeParticle;
				break;
			case EParticle_Type::NiagaraParticle:
				break;
			default:
				break;
			}
		}
	}

	else if (_Name == "EnemyAttack")
	{
		const FMGBulletDataTable* BulletTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetBulletData(TEXT("EnemyBullet"));
		ParticleTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetParticleData(TEXT("SoldierParticle"));

		if (BulletTable && ParticleTable)
		{
			switch (BulletTable->ParticleType)
			{
			case EParticle_Type::None:
				break;
			case EParticle_Type::CascadeParticle:
				ParticleLegacy->SetTemplate(BulletTable->ProjectileEffect);
				break;
			case EParticle_Type::NiagaraParticle:
				break;
			default:
				break;
			}

			switch (ParticleTable->ParticleType)
			{
			case EParticle_Type::None:
				break;
			case EParticle_Type::CascadeParticle:
				HitEffect = ParticleTable->CascadeParticle;
				break;
			case EParticle_Type::NiagaraParticle:
				break;
			default:
				break;
			}
		}
	}

	HitSound = ParticleTable->HitSound;
}

void AMGBullet::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, 
	UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	FName OtherProfile = _OtherComp->GetCollisionProfileName();

	if (OtherProfile == "PlayerAttack" || OtherProfile == "EnemyAttack")
		return;

	AMGCharacter* OtherCharacter = Cast<AMGCharacter>(_pOtherActor);

	ProjectileComponent->StopSimulating(_Hit);

	AMGHitEffect* Effect = GetWorld()->SpawnActor<AMGHitEffect>(GetActorLocation(), GetActorRotation());
	Effect->SetActorScale3D(FVector(3.0f, 3.0f, 3.0f));
	Effect->SetParticle(HitEffect);
	Effect->SetSound(HitSound);
	Effect->SetStatus(3.0f);


	if (!OtherCharacter || !OtherCharacter->IsValidLowLevel())
	{
		Destroy();
		return;
	}

	if (OtherCharacter->GetStatus() & ECharacter_Status::Dodge)
		return;

	bool IsWeakPoint = _OtherComp->ComponentHasTag(TEXT("WeakPoint")) ? true : false;

	OtherCharacter->SetStatus(ECharacter_Status::Damaged);
	OtherCharacter->SetDamage(-Damage, IsWeakPoint);

	Destroy();
}

