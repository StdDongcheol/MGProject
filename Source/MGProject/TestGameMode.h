// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API ATestGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMGAimWidget* AimWidget;

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
};
