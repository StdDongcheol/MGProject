// Fill out your copyright notice in the Description page of Project Settings.


#include "MGEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

AMGEnemyCharacter::AMGEnemyCharacter()
{
	Capsule->SetCollisionProfileName(FName("Enemy"));

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Lockon Widget"));
}

void AMGEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Widget->SetVisibility(false);
}

void AMGEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
