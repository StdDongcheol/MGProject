// Fill out your copyright notice in the Description page of Project Settings.


#include "MGBlueprintFunctionLibrary.h"

UWorld* UMGBlueprintFunctionLibrary::GetCurrentWorld()
{
	UWorld* PIE = nullptr;
	UWorld* GamePreview = nullptr;

	for (FWorldContext Context : GEngine->GetWorldContexts())
	{
		switch (Context.WorldType)
		{
		case EWorldType::PIE:
		case EWorldType::Game:
			PIE = Context.World();
			break;
		case EWorldType::GamePreview:
			GamePreview = Context.World();
			break;
		default:
			break;
		}
	}

	UWorld* CurrentWorld = nullptr;

	if (nullptr != PIE)
	{
		CurrentWorld = PIE;
	}

	else if (nullptr != GamePreview)
	{
		CurrentWorld = GamePreview;
	}

	return CurrentWorld;
}

UMGGameInstance* UMGBlueprintFunctionLibrary::GetMGGameInstance()
{
	UMGGameInstance* MGGameInst = GetCurrentWorld()->GetGameInstance<UMGGameInstance>();

	if (!MGGameInst)
	{
		UE_LOG(LogTemp, Error, TEXT("MGGameInst is null !"));

		return nullptr;
	}

	return MGGameInst;
}
