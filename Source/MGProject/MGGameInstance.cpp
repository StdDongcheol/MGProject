// Fill out your copyright notice in the Description page of Project Settings.


#include "MGGameInstance.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"

UMGGameInstance::UMGGameInstance()
{
	{
		FString DataPath = TEXT("DataTable'/Game/Play/Data/EnemyStatusDataTable.EnemyStatusDataTable'");

		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			EnemyDataTable = DataTable.Object;
		}
	}

	{
		FString DataPath = TEXT("DataTable'/Game/Play/Data/BulletDataTable.BulletDataTable'");

		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			BulletDataTable = DataTable.Object;
		}
	}

	{
		FString DataPath = TEXT("DataTable'/Game/Play/Data/HitParticleDataTable.HitParticleDataTable'");

		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			ParticleDataTable = DataTable.Object;
		}
	}

	{
		FString DataPath = TEXT("DataTable'/Game/Play/Data/BGMDataTable.BGMDataTable'");

		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

		if (DataTable.Succeeded())
		{
			BGMDataTable = DataTable.Object;
		}
	}
}

const FMGEnemyStatusDataTable* UMGGameInstance::GetEnemyData(FName _Name) const
{
	if (!EnemyDataTable)
		return nullptr;

	FMGEnemyStatusDataTable* EnemyDataInfo = EnemyDataTable->FindRow<FMGEnemyStatusDataTable>(_Name, _Name.ToString());

	if (!EnemyDataInfo)
		return nullptr;

	return EnemyDataInfo;
}

const FMGBulletDataTable* UMGGameInstance::GetBulletData(FName _Name) const
{
	if (!BulletDataTable)
		return nullptr;

	FMGBulletDataTable* BulletDataInfo = BulletDataTable->FindRow<FMGBulletDataTable>(_Name, _Name.ToString());

	if (!BulletDataInfo)
		return nullptr;

	return BulletDataInfo;
}

const FHitParticleDataTable* UMGGameInstance::GetParticleData(FName _Name) const
{
	if (!ParticleDataTable)
		return nullptr;

	FHitParticleDataTable* ParticleDataInfo = ParticleDataTable->FindRow<FHitParticleDataTable>(_Name, _Name.ToString());

	if (!ParticleDataInfo)
		return nullptr;

	return ParticleDataInfo;
}

USoundBase* UMGGameInstance::GetBGMData(FName _Name) const
{
	if (!ParticleDataTable)
		return nullptr;

	FMGBGMDataTable* BGMData = BGMDataTable->FindRow<FMGBGMDataTable>(_Name, _Name.ToString());

	if (!BGMData || !BGMData->BGM)
	{
		UE_LOG(LogTemp, Error, TEXT("BGMData is null!"));
		return nullptr;
	}

	return BGMData->BGM;
}