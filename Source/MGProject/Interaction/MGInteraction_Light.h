// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGInteraction.h"
#include "MGInteraction_Light.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGInteraction_Light : public AMGInteraction
{
	GENERATED_BODY()

public:
	AMGInteraction_Light();

private:
	TArray<TObjectPtr<class ULightComponent>>	LightComponentArray;

private:
	UPROPERTY(EditAnywhere)
	bool	LightOnAtPlay;
	UPROPERTY(EditAnywhere)
	bool	IsActivateLightOn;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
public:
	virtual void InteractionActivate() override;
	virtual void InteractionComplete() override;
};
