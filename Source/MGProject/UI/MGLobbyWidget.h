// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGUserWidget.h"
#include "MGLobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGLobbyWidget : public UMGUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	
};
