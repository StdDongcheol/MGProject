// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGStructs.h"
#include "Engine/GameInstance.h"
#include "MGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMGGameInstance();

private:
	UPROPERTY()
	TSoftObjectPtr<class UDataTable>	EnemyDataTable;

	UPROPERTY()
	TSoftObjectPtr<class UDataTable>	BulletDataTable;

public:
	const FMGEnemyStatusDataTable* GetEnemyData(FName _Name) const;
	const FMGBulletDataTable* GetBulletData(FName _Name) const;
};
