// Fill out your copyright notice in the Description page of Project Settings.


#include "MGInteraction.h"


AMGInteraction::AMGInteraction()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add(TEXT("Interaction"));

	DelayTime = 0.0f;
	DelayTimeAcc = 0.0f;
	IsActivate = false;
	IsComplete = false;
}

void AMGInteraction::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(InteractionTag);

	if (DelayTime > 0.0f)
		IsDelay = true;
}

void AMGInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsActivate && IsDelay)
	{
		DelayTimeAcc += DeltaTime;

		if (DelayTimeAcc >= DelayTime)
		{
			IsDelay = false;
		}
	}
}

void AMGInteraction::InteractionActivate()
{
	IsActivate = true;

	return;
}

void AMGInteraction::InteractionComplete()
{
	IsComplete = true;

	return;
}

