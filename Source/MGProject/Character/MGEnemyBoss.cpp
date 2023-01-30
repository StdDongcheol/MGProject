// Fill out your copyright notice in the Description page of Project Settings.


#include "MGEnemyBoss.h"

AMGEnemyBoss::AMGEnemyBoss()
{
}

const FMGEnemyStatusDataTable* AMGEnemyBoss::InitEnemyData()
{
	return nullptr;
}

void AMGEnemyBoss::AdjustHP(float _HP)
{
	Super::AdjustHP(_HP);
}

void AMGEnemyBoss::BeginPlay()
{
	Super::BeginPlay();
}

void AMGEnemyBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
