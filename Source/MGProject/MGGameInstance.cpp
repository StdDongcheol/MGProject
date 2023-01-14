// Fill out your copyright notice in the Description page of Project Settings.


#include "MGGameInstance.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"

UMGGameInstance::UMGGameInstance()
{
	{
		FString DataPath = TEXT("DataTable'/Game/Play/Data/EnemyStatusDataTable.EnemyStatusDataTable'");

		// ���ҽ��� �ε��ϴ� �뵵�� 
		// ���ҽ��� ������ ���ؿ��� �ε��ϴ� ���� �𸮾�d�� �̳༮�� ����Ѵٰ� ������.
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
