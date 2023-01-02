// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGUserWidget.h"
#include "MGEnemyWidget.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGEnemyWidget : public UMGUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* TargetingAnimation;

private:
	bool IsLocked = false;

public:
	void SetTargetLock(bool bEnable)
	{
		IsLocked = bEnable;
	}

	bool IsTargetLocked() const
	{
		return IsLocked;
	}


private:
	FWidgetAnimationDynamicEvent TargetingEndDelegate;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UFUNCTION()
	void TargetingEnded();
};
