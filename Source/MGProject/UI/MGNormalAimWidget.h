// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGUserWidget.h"
#include "MGNormalAimWidget.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGNormalAimWidget : public UMGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ActivateAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* RecoilAnim;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* SwitchAnim;

private:
	FWidgetAnimationDynamicEvent ActivateAimStartDelegate;
	FWidgetAnimationDynamicEvent RecoilAnimStartDelegate;

private:
	bool		IsAimActivated;
	bool		IsPlayingRecoil;

private:
	class AMGPlayerController* PlayerController;

public:
	virtual void SetVisibility(ESlateVisibility InVisibility) override;
	void SwtichAimWidget(bool ToCharge);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UFUNCTION()
	void ActivateAimStart();
	
	UFUNCTION()
	void RecoilAnimStart();

};
