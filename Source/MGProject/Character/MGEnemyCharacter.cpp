// Fill out your copyright notice in the Description page of Project Settings.


#include "MGEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "../UI/MGEnemyWidget.h"

AMGEnemyCharacter::AMGEnemyCharacter()
{
	Capsule->SetCollisionProfileName(FName("Enemy"));

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Lockon Widget"));
	Widget->SetupAttachment(RootComponent);

	LockedByPlayer = false;
}

void AMGEnemyCharacter::SetLockonWidget(bool bEnable)
{	
	Widget->SetVisibility(bEnable);

	if (!bEnable)
	{
		if (EnemyHUD && EnemyHUD->IsValidLowLevel())
			EnemyHUD->SetTargetLock(false);
	}
}

void AMGEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	EnemyHUD = Cast<UMGEnemyWidget>(Widget->GetWidget());

	Widget->SetVisibility(false);
}

void AMGEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LockedByPlayer = EnemyHUD->IsTargetLocked();
}
