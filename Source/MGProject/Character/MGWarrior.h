// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGEnemyCharacter.h"
#include "MGWarrior.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGWarrior : public AMGEnemyCharacter
{
	GENERATED_BODY()

public:
	AMGWarrior();

private:
	const struct FMGEnemyStatusDataTable* EnemyData;

public:
	const FMGEnemyStatusDataTable* GetEnemyData()
	{
		return EnemyData;
	}

protected:
	void BeginPlay() override;

public:
	virtual const FMGEnemyStatusDataTable* InitEnemyData() override;


};
