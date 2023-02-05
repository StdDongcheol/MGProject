// Fill out your copyright notice in the Description page of Project Settings.


#include "MGCrunch.h"
#include "../MGEnemyController.h"
#include "../MGBlueprintFunctionLibrary.h"
#include "Components/BoxComponent.h"

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
	OtherCharacter->SetStatus(ECharacter_Status::KnockOut);
}
