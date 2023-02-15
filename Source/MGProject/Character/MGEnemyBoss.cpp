// Fill out your copyright notice in the Description page of Project Settings.


#include "MGEnemyBoss.h"
#include "../MGBossController.h"
#include "../UI/MGBossStatusWidget.h"
#include "Components/WidgetComponent.h"

AMGEnemyBoss::AMGEnemyBoss()
{
	AIControllerClass = AMGBossController::StaticClass();
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
	
	AMGBossController* BossController = GetController<AMGBossController>();

	if (BossController)
	{
		StatusWidget = BossController->GetStatusWidget();
		StatusWidget->SetCharacter(this);
	}
}

void AMGEnemyBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
