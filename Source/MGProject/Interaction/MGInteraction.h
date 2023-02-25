// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGInteraction.generated.h"

UCLASS()
class MGPROJECT_API AMGInteraction : public AActor
{
	GENERATED_BODY()
	
public:	
	AMGInteraction();

public:
	UPROPERTY(EditAnywhere)
	float	DelayTime;
	float	DelayTimeAcc;

protected:
	UPROPERTY(EditAnywhere, Category = "Interaction TagName", meta = (AllowPrivateAccess = "true"))
	FName	InteractionTag;
	
	UPROPERTY(EditAnywhere, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USoundBase> ActivateSound;

protected:
	bool	IsDelay;
	bool	IsActivate;
	bool	IsComplete;

public:
	bool IsInteractionActivated() const
	{
		return (!IsDelay && IsActivate);
	}

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

/// <summary>
/// Activate -> Delay -> Tick -> Complete
/// </summary>
public:
	virtual void InteractionActivate();
	virtual void InteractionComplete();

};
