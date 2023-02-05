// Fill out your copyright notice in the Description page of Project Settings.


#include "MGWarrior.h"
#include "../MGEnemyController.h"
#include "../MGBlueprintFunctionLibrary.h"
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
	
	OtherCharacter->AdjustHP(-MinAttack);
	OtherCharacter->SetStatus(ECharacter_Status::Damaged);
}
