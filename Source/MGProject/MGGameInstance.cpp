// Fill out your copyright notice in the Description page of Project Settings.


#include "MGGameInstance.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"

UMGGameInstance::UMGGameInstance()
{
	{
		FString DataPath = TEXT("DataTable'/Game/Play/Data/EnemyStatusDataTable.EnemyStatusDataTable'");

		// 리소스를 로드하는 용도고 
		// 리소스를 생성자 수준에서 로드하는 순간 언리얼d은 이녀석을 사용한다고 생각함.
		ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);
		//
		//if (DataTable.Succeeded())
		//{
		//	EnemyDataTable = DataTable.Object;
		//}
		//
		//else
		//{
		//	UE_LOG(LogTemp, Error, TEXT("EnemyDataTable is null!!!"));
		//}
	}
}
