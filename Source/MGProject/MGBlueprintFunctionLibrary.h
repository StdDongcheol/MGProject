// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGGameInstance.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MGBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UWorld* GetCurrentWorld();
	static UMGGameInstance* GetMGGameInstance();
};
