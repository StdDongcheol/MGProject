// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGHUD.h"
#include "MGPlayHUD.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGPlayHUD : public AMGHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
