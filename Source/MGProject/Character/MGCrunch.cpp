// Fill out your copyright notice in the Description page of Project Settings.


#include "MGCrunch.h"
#include "../MGEnemyController.h"
#include "../MGBlueprintFunctionLibrary.h"

AMGCrunch::AMGCrunch()
{
	AIControllerClass = AMGEnemyController::StaticClass();
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
