// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Character/MGPlayerCharacter.h"
#include "UI/MGPlayerWidget.h"
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

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerNormalAimWBP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerStatusWBP;

	class UMGAimWidget* PlayerQAimWidget;
	class UMGNormalAimWidget* PlayerNormalAimWidget;
	class UMGPlayerWidget* PlayerStatusWidget;

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
	
	UFUNCTION()
	UMGPlayerWidget* GetPlayerStatusWidget() const
	{
		return PlayerStatusWidget;
	}

public:
	virtual void InitInputSystem() override;
	virtual void BeginPlay() override;

public:
	void WidgetStart();
	void WidgetEnd();
	void PlayerDeath();
	void SetCursor(bool bEnable);

private:
	void MoveFront(float Value);
	void MoveLeft(float Value);
	void MoveRight(float Value);
	void MoveBack(float Value);
	void MouseXMove(float Value);
	void MouseYMove(float Value);
	void LeftMouseButtonAxis(float Value);
	void LeftMouseButtonClick();
	void RightMouseButtonClick();
	void RightMouseButtonRelease();
	void QButtonPress();
	void QButtonRelease();
	void EButtonPress();
	void EButtonRelease();
	void FButtonPress();
	void FButtonRelease();
	void RButtonPress();
	void ShiftButtonPress();
	void CheatKeyPress();
};
