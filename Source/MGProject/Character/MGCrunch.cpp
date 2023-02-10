// Fill out your copyright notice in the Description page of Project Settings.


#include "MGCrunch.h"
#include "../MGEnemyController.h"
#include "../MGBlueprintFunctionLibrary.h"
#include "../Projectile/MGHitEffect.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

AMGCrunch::AMGCrunch()
{
	AIControllerClass = AMGEnemyController::StaticClass();

	DamageBoxLeft = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxLeft"));
	DamageBoxLeft->SetupAttachment(GetMesh(), TEXT("Muzzle_02"));
	DamageBoxLeft->SetCollisionProfileName(FName("EnemyAttack"));
	DamageBoxLeft->SetBoxExtent(FVector(80.0f, 50.0f, 50.0f));
	DamageBoxLeft->SetGenerateOverlapEvents(false);
	DamageBoxLeft->OnComponentBeginOverlap.AddDynamic(this, &AMGCrunch::OnDamageCollisionEnter);

	DamageBoxRight = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxRight"));
	DamageBoxRight->SetupAttachment(GetMesh(), TEXT("Muzzle_01"));
	DamageBoxRight->SetCollisionProfileName(FName("EnemyAttack"));
	DamageBoxRight->SetBoxExtent(FVector(80.0f, 50.0f, 50.0f));
	DamageBoxRight->SetGenerateOverlapEvents(false);
	DamageBoxRight->OnComponentBeginOverlap.AddDynamic(this, &AMGCrunch::OnDamageCollisionEnter);
}

const FMGEnemyStatusDataTable* AMGCrunch::InitEnemyData()
{
	EnemyData = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetEnemyData(TEXT("Crunch"));

	if (!EnemyData)
		return nullptr;

	SetAttackRange(EnemyData->AttackRange);
	SetDetectRange(EnemyData->DetectionRange);
	SetMaxHP(EnemyData->MaxHP);
	SetCurrentHP(EnemyData->MaxHP);
	SetMinAttack(EnemyData->MinAttack);
	SetMaxAttack(EnemyData->MaxAttack);
	SetAttackSpeed(EnemyData->AttackSpeed);
	SetMoveSpeed(EnemyData->MoveSpeed);

	return EnemyData;
}

void AMGCrunch::AdjustHP(float _HP)
{
	Super::AdjustHP(_HP);
}

void AMGCrunch::BeginPlay()
{
	Super::BeginPlay();
}

void AMGCrunch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMGCrunch::OnDamageCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, 
	UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex,
	bool _bFromSweep, const FHitResult& _Hit)
{
	FName OtherProfile = _OtherComp->GetCollisionProfileName();

	if (OtherProfile != "Player")
	{
		return;
	}

	AMGCharacter* OtherCharacter = Cast<AMGCharacter>(_pOtherActor);
	
	if (!OtherCharacter || !OtherCharacter->IsValidLowLevel())
		return;

	OtherCharacter->AdjustHP(-MinAttack);

	if (OtherCharacter->GetStatus() == ECharacter_Status::Normal)
	{

		/// Player Knockout Start.
		OtherCharacter->SetStatus(ECharacter_Status::KnockOut);

		FVector HandPos = _pComponent->GetComponentLocation() - FVector(0.0f, 0.0f, 250.f);
		
		// Debugging sphere
		DrawDebugSphere(GetWorld(), HandPos, 500.0f, 50, FColor::Red, false, 2.0f);

		OtherCharacter->GetCapsuleComponent()->SetSimulatePhysics(true);
		OtherCharacter->GetCapsuleComponent()->AddRadialImpulse(HandPos, 500.0f, 700.0f, ERadialImpulseFalloff::RIF_Constant, true);
		OtherCharacter->GetAnimInst()->SetFalling(true);
		/// Player Knockout End.

		/// Melee Particle Start.
		FVector HitPos = _pComponent->GetComponentLocation();

		const FHitParticleDataTable* ParticleTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetParticleData(TEXT("WarriorMelee"));

		AMGHitEffect* Effect = GetWorld()->SpawnActor<AMGHitEffect>(AMGHitEffect::StaticClass(), HitPos, GetActorRotation());
		Effect->SetStatus(2.0f);

		switch (ParticleTable->ParticleType)
		{
		case EParticle_Type::CascadeParticle:
		{
			Effect->SetParticle(ParticleTable->CascadeParticle);
			break;
		}
		case EParticle_Type::NiagaraParticle:
		{
			Effect->SetParticleNiagara(ParticleTable->NiagaraParticle);
			break;
		}
		default:
		{
			UE_LOG(LogTemp, Error, TEXT("Particle not selected type. Please select particle type."));
			break;
		}
		}
		/// Melee Particle End.

	}
}
