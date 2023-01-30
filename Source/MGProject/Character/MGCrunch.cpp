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
	return nullptr;
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
