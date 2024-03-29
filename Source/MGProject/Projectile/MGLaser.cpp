// Fill out your copyright notice in the Description page of Project Settings.


#include "MGLaser.h"
#include "MGHitEffect.h"
#include "../Character/MGCharacter.h"
#include "../MGBlueprintFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"


AMGLaser::AMGLaser()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = Mesh;

	DamageCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageCollider"));

	DamageCollider->SetGenerateOverlapEvents(true);
	DamageCollider->SetBoxExtent(FVector(1000.0f, 30.0f, 30.0f));
	DamageCollider->OnComponentBeginOverlap.AddDynamic(this, &AMGLaser::OnCollisionEnter);
	DamageCollider->SetCollisionProfileName(TEXT("PlayerAttack"));

	DamageCollider->SetupAttachment(RootComponent);
	ParticleLegacy->SetupAttachment(RootComponent);
}

void AMGLaser::BeginPlay()
{
	Super::BeginPlay();

	const FMGBulletDataTable* BulletTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetBulletData(TEXT("PlayerSnipe"));
	const FHitParticleDataTable* ParticleTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetParticleData(TEXT("PlayerCharge"));

	if (BulletTable && ParticleTable)
	{
		ParticleLegacy->SetTemplate(BulletTable->ProjectileEffect);

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

	HitSound = ParticleTable->HitSound;

	SetLifeSpan(1.0f);
	CollisionTime = 0.3f;
	CollisionTimeAcc = 0.0f;
}

void AMGLaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CollisionTimeAcc += DeltaTime;
}

void AMGLaser::SetProfile(FName _Name, float _Damage)
{
	DrawDebugBox(GetWorld(), DamageCollider->GetComponentLocation(), DamageCollider->GetScaledBoxExtent(), DamageCollider->GetComponentRotation().Quaternion(), FColor::Red, false, 2.0f, (uint8)0U, 1.0f);

	Mesh->SetCollisionProfileName(_Name);
	Damage = _Damage;
}

void AMGLaser::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor,
	UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	if (CollisionTimeAcc >= CollisionTime)
		return;

	FName OtherProfile = _OtherComp->GetCollisionProfileName();

	if (OtherProfile == "PlayerAttack" || 
		OtherProfile == "EnemyAttack" || 
		OtherProfile == "WorldObject")
		return;
	
	AMGHitEffect* Effect = GetWorld()->SpawnActor<AMGHitEffect>(_pOtherActor->GetActorLocation(), _pOtherActor->GetActorRotation());
	Effect->SetActorScale3D(FVector(3.0f, 3.0f, 3.0f));
	Effect->SetStatus(2.0f);
	Effect->SetSound(HitSound);
	Effect->SetParticle(HitEffect);
	//Effect->SetSound(HitEffect);

	AMGCharacter* OtherCharacter = Cast<AMGCharacter>(_pOtherActor);

	if (!OtherCharacter || !OtherCharacter->IsValidLowLevel())
		return;

	bool IsWeakPoint = _OtherComp->ComponentHasTag(TEXT("WeakPoint")) ? true : false;

	OtherCharacter->SetStatus(ECharacter_Status::Damaged);
	OtherCharacter->SetDamage(-Damage, IsWeakPoint);
}

