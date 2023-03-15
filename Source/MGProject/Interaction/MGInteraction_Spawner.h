// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGInteraction.h"
#include "MGInteraction_Spawner.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGInteraction_Spawner : public AMGInteraction
{
	GENERATED_BODY()

public:
	AMGInteraction_Spawner();

private:
	UPROPERTY(EditAnywhere, Category = "Spawner Setting", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class AMGEnemyCharacter>> MonsterArray;

	UPROPERTY(EditAnywhere, Category = "Spawner Setting", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USoundBase> SpawningSound;
	
	FRandomStream RandomStream; 

	UPROPERTY(EditAnywhere, Category = "Spawner Setting", meta = (AllowPrivateAccess = "true"))
	float	SpawnCycleTime;
	float	CycleTimeAcc;

	UPROPERTY(EditAnywhere, Category = "Spawner Setting", meta = (AllowPrivateAccess = "true"))
	int		SpawnCount;
	int		CurrentSpawnCount;
	bool	IsMonsterAllSpawned;


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void Spawn();

public:
	virtual void InteractionActivate() override;
	virtual void InteractionComplete() override;
};
