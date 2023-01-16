// Fill out your copyright notice in the Description page of Project Settings.


#include "MGWarrior.h"
#include "../MGEnemyController.h"
#include "../MGBlueprintFunctionLibrary.h"

AMGWarrior::AMGWarrior()
{
	AIControllerClass = AMGEnemyController::StaticClass();
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
