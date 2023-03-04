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

void AMGEnemyBoss::SetDamage(float _Damage, bool _IsWeakpoint)
{
	Super::SetDamage(_Damage, _IsWeakpoint);
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

	if (HP <= 0.0f)
	{
		StatusWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
}
