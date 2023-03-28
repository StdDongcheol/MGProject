// Fill out your copyright notice in the Description page of Project Settings.


#include "MGInteraction_Spawner.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Character/MGWarrior.h"
#include "../Character/MGSoldier.h"
#include "Kismet/GameplayStatics.h"

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
	float RandPosX = RandomStream.FRandRange(-250.0f, 250.0f);
	float RandPosY = RandomStream.FRandRange(-250.0f, 250.0f);

	FTransform SpawnTransform = GetActorTransform();
	float SpawnPosX = SpawnTransform.GetLocation().X + RandPosX;
	float SpawnPosY = SpawnTransform.GetLocation().Y + RandPosY;

	SpawnTransform.SetLocation(FVector(SpawnPosX, SpawnPosY, SpawnTransform.GetLocation().Z));

	GetWorld()->SpawnActor<AMGEnemyCharacter>(MonsterArray[Index], SpawnTransform);

	if (SpawningSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SpawningSound, GetActorLocation());
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
