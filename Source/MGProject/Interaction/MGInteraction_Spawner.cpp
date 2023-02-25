// Fill out your copyright notice in the Description page of Project Settings.


#include "MGInteraction_Spawner.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Character/MGWarrior.h"
#include "../Character/MGSoldier.h"

AMGInteraction_Spawner::AMGInteraction_Spawner()
{
	RandomStream = FDateTime::Now().GetTicks();
}

void AMGInteraction_Spawner::BeginPlay()
{
	Super::BeginPlay();
}

void AMGInteraction_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsInteractionActivated() && !IsMonsterAllSpawned)
	{
		CycleTimeAcc += DeltaTime;

		if (CycleTimeAcc >= SpawnCycleTime)
		{
			CycleTimeAcc -= CycleTimeAcc;

			Spawn();
			CurrentSpawnCount++;
			
			if (CurrentSpawnCount >= SpawnCount)
			{
				InteractionComplete();
			}
		}
	}
}

void AMGInteraction_Spawner::Spawn()
{
	int Index = static_cast<int>(RandomStream.FRandRange(0, MonsterArray.Num()));

	FTransform SpawnTransform = FTransform(GetActorLocation());

	GetWorld()->SpawnActor<AMGEnemyCharacter>(MonsterArray[Index], SpawnTransform);	
}

void AMGInteraction_Spawner::InteractionActivate()
{
	Super::InteractionActivate();
}

void AMGInteraction_Spawner::InteractionComplete()
{
	Super::InteractionComplete();

	IsMonsterAllSpawned = true;
}
