// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGUserWidget.h"
#include "MGInteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGInteractionWidget : public UMGUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<class UProgressBar> InputProgressBar;
	
private:
	bool	IsProgressBarStart;
	bool	IsProgressCompleted;
	
public:
	bool IsCompleted() const
	{
		return IsProgressCompleted;
	}

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* PlayerOnAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* PlayerOffAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* PushingAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* CompleteAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USoundBase> CompletedSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USoundBase> PushingSound;

private:
	FWidgetAnimationDynamicEvent PlayerOnAnimStartDelegate;
	FWidgetAnimationDynamicEvent PlayerOffAnimStartDelegate;
	FWidgetAnimationDynamicEvent KeyPushingAnimStartDelegate;
	FWidgetAnimationDynamicEvent CompleteAnimStartDelegate;

public:

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void SetProgress(float Percent);
	void SetPlayerOn(bool IsOnPlayer);

};
