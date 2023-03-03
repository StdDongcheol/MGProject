// Fill out your copyright notice in the Description page of Project Settings.


#include "MGBullet.h"
#include "MGHitEffect.h"
#include "../MGBlueprintFunctionLibrary.h"
#include "../Character/MGCharacter.h"
#include "Components/SphereComponent.h"
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

		if (BulletTable)
		{
			ParticleLegacy->SetTemplate(BulletTable->ProjectileEffect);
			HitEffect = BulletTable->HitEffect;
		}
	}

	else if (_Name == "EnemyAttack")
	{
		const FMGBulletDataTable* BulletTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetBulletData(TEXT("EnemyBullet"));

		if (BulletTable)
		{
			ParticleLegacy->SetTemplate(BulletTable->ProjectileEffect);
			HitEffect = BulletTable->HitEffect;
		}
	}
}

void AMGBullet::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, 
	UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	FName OtherProfile = _OtherComp->GetCollisionProfileName();

	if (OtherProfile == "PlayerAttack" || OtherProfile == "EnemyAttack")
		return;

	ProjectileComponent->StopSimulating(_Hit);
	
	AMGHitEffect* Effect = GetWorld()->SpawnActor<AMGHitEffect>(GetActorLocation(), GetActorRotation());
	Effect->SetActorScale3D(FVector(3.0f, 3.0f, 3.0f));
	Effect->SetParticle(HitEffect);
	Effect->SetStatus(3.0f);

	AMGCharacter* OtherCharacter = Cast<AMGCharacter>(_pOtherActor);

	if (!OtherCharacter || !OtherCharacter->IsValidLowLevel())
	{
		Destroy();
		return;
	}

	bool IsWeakPoint = _OtherComp->ComponentHasTag(TEXT("WeakPoint")) ? true : false;

	OtherCharacter->SetDamage(-Damage, IsWeakPoint);
	OtherCharacter->SetStatus(ECharacter_Status::Damaged);

	Destroy();
}

