// Fill out your copyright notice in the Description page of Project Settings.


#include "MGCrunch.h"
#include "../MGBossController.h"
#include "../MGBlueprintFunctionLibrary.h"
#include "../Projectile/MGHitEffect.h"
#include "../Projectile/MGProjectile.h"
#include "../UI/MGBossStatusWidget.h"
#include "../Animation/MGEnemyAnimInstance.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"

AMGCrunch::AMGCrunch()
{
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

	WeakBoxHead = CreateDefaultSubobject<UBoxComponent>(TEXT("WeakPointHead"));
	WeakBoxHead->SetupAttachment(GetMesh(), TEXT("FX_UltSteam_Back"));
	WeakBoxHead->SetCollisionProfileName(FName("Enemy"));
	WeakBoxHead->SetBoxExtent(FVector(30.0f, 25.0f, 25.0f));
	WeakBoxHead->SetGenerateOverlapEvents(true);

	WeakBoxBack = CreateDefaultSubobject<UBoxComponent>(TEXT("WeakPointBack"));
	WeakBoxBack->SetupAttachment(GetMesh(), TEXT("FX_Heads"));
	WeakBoxBack->SetCollisionProfileName(FName("Enemy"));
	WeakBoxBack->SetBoxExtent(FVector(40.0f, 25.0f, 25.0f));
	WeakBoxBack->SetGenerateOverlapEvents(true);
	
	WeakHeadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WeakHeadWidget"));
	WeakHeadWidget->SetupAttachment(GetMesh(), TEXT("head"));
	WeakHeadWidget->SetWidgetSpace(EWidgetSpace::Screen);
	
	WeakBackWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WeakBackWidget"));
	WeakBackWidget->SetupAttachment(GetMesh(), TEXT("FX_UltSteam_Back"));
	WeakBackWidget->SetWidgetSpace(EWidgetSpace::Screen);
	
	
	JetParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>("JetParticle");
	JetParticleComponent->SetupAttachment(GetMesh(), FName("FX_UltSteam_Back"));
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

	MaxStunGauge = 200.0f;

	return EnemyData;
}

void AMGCrunch::SetDamage(float _Damage, bool _IsWeakpoint)
{
	Super::SetDamage(_Damage, _IsWeakpoint);

	StatusWidget->SetHPBar(HP);

	if (_IsWeakpoint)
	{
		WeakpointHit(_Damage);
	}

	if (HP <= 0.0f)
	{
		JetParticleComponent->Deactivate();
		WeakHeadWidget->SetVisibility(false);
		WeakBackWidget->SetVisibility(false);
	}
}

void AMGCrunch::WeakpointHit(float _Damage)
{
	float HitDamage = FMath::Abs(_Damage);
	
	EAIAnimState CurrentState = GetAnimInst<UMGEnemyAnimInstance>()->GetAIAnimState();

	if (CurrentState & EAIAnimState::Groggy)
	{
		return;
	}

	CurrentStunGauge += HitDamage;

	if (CurrentStunGauge >= MaxStunGauge)
	{
		CurrentStunGauge -= CurrentStunGauge;
		
		if (!AnimInstance->IsDead())
			GetAnimInst<UMGEnemyAnimInstance>()->SetAIAnimState(EAIAnimState::Groggy);
	}
}

void AMGCrunch::BeginPlay()
{
	Super::BeginPlay();

	WeakBoxHead->ComponentTags.Add(TEXT("WeakPoint"));
	WeakBoxBack->ComponentTags.Add(TEXT("WeakPoint"));
	WeakHeadWidget->ComponentTags.Add(TEXT("WeakPoint"));
	WeakBackWidget->ComponentTags.Add(TEXT("WeakPoint"));

	WeakHeadWidget->SetVisibility(false);
	WeakBackWidget->SetVisibility(false);
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

	if (OtherCharacter->GetStatus() & ECharacter_Status::Dodge ||
		OtherCharacter->GetStatus() & ECharacter_Status::KnockOut)
		return;

	/// Melee Particle Start.
	FVector HitPos = _pOtherActor->GetActorLocation();

	const FHitParticleDataTable* ParticleTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetParticleData(TEXT("CrunchMelee"));

	AMGHitEffect* Effect = GetWorld()->SpawnActor<AMGHitEffect>(AMGHitEffect::StaticClass(), HitPos, GetActorRotation());
	Effect->SetStatus(2.0f, _pOtherActor->GetRootComponent());
	Effect->SetSound(ParticleTable->HitSound);

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

	OtherCharacter->AdjustHP(-MinAttack);

	if (OtherCharacter->GetCurrentHP() > 0.0f)
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
	}
}
