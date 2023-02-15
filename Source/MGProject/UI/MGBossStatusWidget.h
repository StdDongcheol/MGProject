// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGUserWidget.h"
#include "MGBossStatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGBossStatusWidget : public UMGUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	class UProgressBar* HPBar;

private:
	class AMGEnemyBoss* BossPtr;

private:
	float	HPCurrent;
	float	HPMax;

public:
	void SetCharacter(class AMGEnemyBoss* Character);
	void SetHPBar(float HP);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	void BossStatusUpdate(float Deltatime);
};
