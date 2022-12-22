// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MGFlag.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGFlag : public UObject
{
	GENERATED_BODY()
	
};

UENUM()
enum class ECharacter_ActionState : uint8
{
	None,
	Normal,
	Aiming
};

UENUM()
enum class ECharacter_ActiveState
{
	None,
	Active,
	Dead
};