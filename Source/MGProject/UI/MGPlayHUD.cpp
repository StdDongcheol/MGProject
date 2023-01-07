// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPlayHUD.h"
#include "MGUserWidget.h"
#include "MGAimWidget.h"
#include "../MGPlayerController.h"

void AMGPlayHUD::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<AMGPlayerController>(GetOwningPlayerController());

	if (!PlayerController || !PlayerController->IsValidLowLevel())
		return;
}

void AMGPlayHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
