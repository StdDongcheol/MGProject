// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGUserWidget.h"
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
	class UProgressBar* MissileChargeBar;

	UPROPERTY()
	class UProgressBar* DroneChargeBar;
	
	UPROPERTY()
	class UTextBlock* MissileCountText;

private:
	class AMGPlayerCharacter* PlayerChacracter;

private:
	float	HPCurrent;
	float	HPMax;
	float	ETimeLeft;
	float	ECoolTime;
	float	QTimeLeft;
	float	QCoolTime;
	int		CurrentMissile;
	int		MissileMax;

public:
	void SetHPBar(float HP);
	void SetMissileBar(float HP);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void PlayerStatusUpdate(float Deltatime);
	
};