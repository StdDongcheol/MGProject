// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGEnemyCharacter.h"
#include "MGSoldier.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGSoldier : public AMGEnemyCharacter
{
	GENERATED_BODY()

public:
	AMGSoldier();

protected:
	virtual void BeginPlay() override;

public:
	virtual const FMGEnemyStatusDataTable* InitEnemyData() override;


};
