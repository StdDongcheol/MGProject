// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGUserWidget.h"
#include "MGWeakpointWidget.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGWeakpointWidget : public UMGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* WeakpointAnimation;

public:
	void WeakPlayAnimation();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
