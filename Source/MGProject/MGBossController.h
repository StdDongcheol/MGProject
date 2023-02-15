// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGEnemyController.h"
#include "MGBossController.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGBossController : public AMGEnemyController
{
	GENERATED_BODY()

	AMGBossController();

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> StatusWBP;

	class UMGBossStatusWidget* StatusWidget;

public:
	class UMGBossStatusWidget* GetStatusWidget();

protected:
	virtual void OnPossess(APawn* _Mon) override;

public:
	virtual void BeginPlay() override;
};
