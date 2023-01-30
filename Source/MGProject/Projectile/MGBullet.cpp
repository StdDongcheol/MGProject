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
	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AMGBullet::OnCollisionEnter);
}

void AMGBullet::BeginPlay()
{
	Super::BeginPlay();
}
	
void AMGBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMGBullet::SetBulletProfile(FName _Name)
{
	Mesh->SetCollisionProfileName(_Name);

	if (_Name == "PlayerAttack")
	{
		const FMGBulletDataTable* BulletTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetBulletData(TEXT("PlayerBullet"));

		if (BulletTable)
			ParticleLegacy->SetTemplate(BulletTable->ProjectileEffect);
	}

	else if (_Name == "EnemyAttack")
	{
		const FMGBulletDataTable* BulletTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetBulletData(TEXT("EnemyBullet"));

		if (BulletTable)
			ParticleLegacy->SetTemplate(BulletTable->ProjectileEffect);
	}
}

void AMGBullet::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, 
	UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	ProjectileComponent->StopSimulating(_Hit);
	
	AMGHitEffect* Effect = GetWorld()->SpawnActor<AMGHitEffect>(HitEffect, GetActorLocation(), GetActorRotation());
	Effect->SetStatus(3.0f);

	FName OtherProfile = _OtherComp->GetCollisionProfileName();


	AMGCharacter* OtherCharacter = Cast<AMGCharacter>(_pOtherActor);

	if (!OtherCharacter || !OtherCharacter->IsValidLowLevel())
	{
		Destroy();
		return;
	}

	if (OtherProfile == "Player")
	{
		OtherCharacter->AdjustHP(-10.0f);
	}

	else if (OtherProfile == "Enemy")
	{
		OtherCharacter->AdjustHP(-10.0f);
	}

	OtherCharacter->SetStatus(ECharacter_Status::Status_Damaged);

	Destroy();
}

