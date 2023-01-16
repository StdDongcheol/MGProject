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
