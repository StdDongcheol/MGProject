// Fill out your copyright notice in the Description page of Project Settings.


#include "MGWarrior.h"
#include "../MGEnemyController.h"
#include "../MGBlueprintFunctionLibrary.h"
#include "../Projectile/MGHitEffect.h"
#include "Components/BoxComponent.h"

AMGWarrior::AMGWarrior()
{
	AIControllerClass = AMGEnemyController::StaticClass();

	DamageBoxLeft = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxLeft"));
	DamageBoxLeft->SetupAttachment(GetMesh(), TEXT("FX_Trail_02_L"));
	DamageBoxLeft->SetCollisionProfileName(FName("EnemyAttack"));
	DamageBoxLeft->SetBoxExtent(FVector(20.0f, 70.0f, 10.0f));
	DamageBoxLeft->AddLocalOffset(FVector(-15.0f, 50.0f, 0.0f));
	DamageBoxLeft->SetGenerateOverlapEvents(false);
	DamageBoxLeft->OnComponentBeginOverlap.AddDynamic(this, &AMGWarrior::OnDamageCollisionEnter);
	
	DamageBoxRight = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxRight"));
	DamageBoxRight->SetupAttachment(GetMesh(), TEXT("FX_Trail_02_R"));
	DamageBoxRight->SetCollisionProfileName(FName("EnemyAttack"));
	DamageBoxRight->SetBoxExtent(FVector(20.0f, 70.0f, 10.0f));
	DamageBoxRight->AddLocalOffset(FVector(-15.0f, 50.0f, 0.0f));
	DamageBoxRight->SetGenerateOverlapEvents(false);
	DamageBoxRight->OnComponentBeginOverlap.AddDynamic(this, &AMGWarrior::OnDamageCollisionEnter);
}

void AMGWarrior::BeginPlay()
{
	Super::BeginPlay();
}

const FMGEnemyStatusDataTable* AMGWarrior::InitEnemyData()
{
	EnemyData = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetEnemyData(TEXT("Warrior"));
	
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

void AMGWarrior::OnDamageCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, 
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
	
	if (OtherCharacter->GetStatus() & ECharacter_Status::Dodge)
		return;

	OtherCharacter->SetStatus(ECharacter_Status::Damaged);
	OtherCharacter->AdjustHP(-MinAttack);

	FVector HitPos = _pComponent->GetComponentLocation();

	const FHitParticleDataTable* ParticleTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetParticleData(TEXT("WarriorMelee"));

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
}
