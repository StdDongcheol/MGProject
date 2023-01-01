// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGCharacter.h"
#include "MGEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGEnemyCharacter : public AMGCharacter
{
	GENERATED_BODY()

public:
	AMGEnemyCharacter();

protected:
	UPROPERTY(Category = "Enemy Property", EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* Widget;

public:
	void SetLockonWidget(bool bEnable);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


};
