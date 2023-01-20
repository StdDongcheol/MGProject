// Fill out your copyright notice in the Description page of Project Settings.


#include "MGSoldier.h"
#include "../MGEnemyController.h"
#include "../MGBlueprintFunctionLibrary.h"

AMGSoldier::AMGSoldier()
{
	AIControllerClass = AMGEnemyController::StaticClass();
}

void AMGSoldier::BeginPlay()
{
	Super::BeginPlay();
}

const FMGEnemyStatusDataTable* AMGSoldier::InitEnemyData()
{
	EnemyData = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetEnemyData(TEXT("Soldier"));

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
