// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void InitInputSystem() override;
	
private:
	void MoveFront(float Value);
	void MoveLeft(float Value);
	void MoveRight(float Value);
	void MoveBack(float Value);
	void MouseXMove(float Value);
	void MouseYMove(float Value);
};
