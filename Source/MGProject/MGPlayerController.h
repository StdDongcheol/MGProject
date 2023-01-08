// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/MGAimWidget.h"
#include "Character/MGPlayerCharacter.h"
#include "MGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGPlayerController : public APlayerController
{
	GENERATED_BODY()

	friend class AMGPlayerCharacter;

private:
	class AMGPlayerCharacter* PlayerCharacter = nullptr;


	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerWidget;

	UMGAimWidget* PlayerAimWidget;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	bRightMouseButtonPress = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	bQButtonPress = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	bEButtonPress = false;

public:
	UFUNCTION()
	bool IsRightMouseButtonPressed() const
	{
		return bRightMouseButtonPress;
	}
	
	UFUNCTION()
	bool IsQButtonPressed() const
	{
		return bQButtonPress;
	}

	UFUNCTION()
	bool IsEButtonPressed() const
	{
		return bEButtonPress;
	}

	UFUNCTION()
	AMGPlayerCharacter* GetPlayerCharacter() const
	{
		return PlayerCharacter;
	}

public:
	virtual void InitInputSystem() override;
	virtual void BeginPlay() override;


private:
	void MoveFront(float Value);
	void MoveLeft(float Value);
	void MoveRight(float Value);
	void MoveBack(float Value);
	void MouseXMove(float Value);
	void MouseYMove(float Value);
	void LeftMouseButtonClick();
	void RightMouseButtonClick();
	void RightMouseButtonRelease();
	void QButtonPress();
	void QButtonRelease();
	void EButtonPress();
	void EButtonRelease();
};
