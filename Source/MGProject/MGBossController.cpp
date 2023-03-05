// Fill out your copyright notice in the Description page of Project Settings.


#include "MGBossController.h"
#include "UI/MGBossStatusWidget.h"

AMGBossController::AMGBossController()
{
}

UMGBossStatusWidget* AMGBossController::GetStatusWidget()
{
	if (!StatusWidget || !StatusWidget->IsValidLowLevel())
		return nullptr;

	return StatusWidget;
}

void AMGBossController::OnPossess(APawn* _Mon)
{
	Super::OnPossess(_Mon);
}

void AMGBossController::BeginPlay()
{
	Super::BeginPlay();
	
	if (StatusWBP)
	{
		StatusWidget = Cast<UMGBossStatusWidget>(CreateWidget(GetWorld(), StatusWBP));
		StatusWidget->AddToViewport(7);
		StatusWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
