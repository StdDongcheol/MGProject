// Fill out your copyright notice in the Description page of Project Settings.


#include "MGInteraction_Light.h"
#include "Components/LightComponent.h"

AMGInteraction_Light::AMGInteraction_Light()
{
}

void AMGInteraction_Light::BeginPlay()
{
	Super::BeginPlay();

	TInlineComponentArray<ULightComponent*> LightmComponents;

	GetComponents<ULightComponent>(LightmComponents);

	for (ULightComponent* LightComp : LightmComponents)
	{
		LightComp->SetVisibility(LightOnAtPlay);
		LightComponentArray.Add(LightComp);
	}
}

void AMGInteraction_Light::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMGInteraction_Light::InteractionActivate()
{
	Super::InteractionActivate();

	for (ULightComponent* LightComp : LightComponentArray)
	{
		LightComp->SetVisibility(IsActivateLightOn);
	}
}

void AMGInteraction_Light::InteractionComplete()
{
	Super::InteractionComplete();

	for (ULightComponent* LightComp : LightComponentArray)
	{
		LightComp->SetVisibility(!IsActivateLightOn);
	}
}
