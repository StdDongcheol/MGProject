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
	virtual void BeginPlay() override;

private:
	class AMGPlayerCharacter* PlayerCharacter = nullptr;

private:
	void MoveFront(float Value);
	void MoveLeft(float Value);
	void MoveRight(float Value);
	void MoveBack(float Value);
	void MouseXMove(float Value);
	void MouseYMove(float Value);
	void LeftMouseButtonClick();
	void RightMouseButtonClick();
	void RightMouseButtonAxis(float Value);
	void RightMouseButtonRelease();
};
