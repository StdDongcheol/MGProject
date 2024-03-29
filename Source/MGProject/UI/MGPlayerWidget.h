// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGUserWidget.h"
#include "../MGStructs.h"
#include "MGPlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGPlayerWidget : public UMGUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class UProgressBar* HPBar;

	UPROPERTY()
	class USlider*	HPSlider;

	UPROPERTY()
	class UProgressBar* MissileChargeBar;

	UPROPERTY()
	class UProgressBar* DroneChargeBar;

	UPROPERTY()
	class UProgressBar* DashChargeBar;
	
	UPROPERTY()
	class UProgressBar* WeaponChargeBar;
	
	UPROPERTY()
	class UTextBlock* MissileCountText;


	UPROPERTY()
	class UImage* Fade;

	UPROPERTY()
	class UButton* TitleButton;


public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ShineLoopAnimation;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeOutAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeinAnimation;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* LevelEndAnimation;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* PlayerDeadAnimation;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* NormalWeaponAnimation;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ChargeWeaponAnimation;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ChargeReadyAnimation;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ChargeFireAnimation;

private:
	FWidgetAnimationDynamicEvent FadeOutDelegateStart;
	FWidgetAnimationDynamicEvent FadeOutDelegateEnd;
	FWidgetAnimationDynamicEvent FadeinDelegateStart;
	FWidgetAnimationDynamicEvent PlayerDeadDelegateEnd;

private:
	class AMGPlayerCharacter* PlayerChacracter;

private:
	float	HPCurrent;
	float	HPMax;
	float	ETimeLeft;
	float	ECoolTime;
	float	QTimeLeft;
	float	QCoolTime;
	float	DashTimeLeft;
	float	DashCoolTime;
	float	ChargeGauge;
	float	ChargeGaugeMax;
	int		CurrentMissile;
	int		MissileMax;

	// Callable functions.
public:
	void SetHPBar(float HP);
	void StageStart();
	void StageEnd();
	void PlayChangeWeaponMode();
	void PlayChargeReady();
	void PlayChargeFire();
	void SetPlayerDeathWidget();
	void SetPlayerStatus(const FMGPlayerDataTable* DataTable);


protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void PlayerStatusUpdate(float Deltatime);

private:
	UFUNCTION()
	void PlayStageEndCallback();

	UFUNCTION()
	void BacktoTitleCallback();

	UFUNCTION()
	void PlayerDiedCallback();
};
