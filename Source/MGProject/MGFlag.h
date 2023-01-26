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
enum class EPlayer_ActionState : uint8
{
	None,
	Normal,
	Aiming,
	QAiming,
	EAiming,
};

UENUM()
enum class EPlayer_BodyAction : uint8
{
	None,
	Ready,
	NormalFire,
	QFire,
	EThrowing
};

UENUM()
enum class ECharacter_ActiveState : uint8
{
	None,
	Active,
	Dead
};

UENUM()
enum class EObject_Force : uint8
{
	None,
	Player, 
	Enemy,
	Neutural
};

UENUM()
enum class ECharacter_Status : uint8
{
	Normal = 0x0000,
	Status_Damaged = 0x0001,
	Status_Slow = 0x0010,
}; 

inline ECharacter_Status operator&(ECharacter_Status l, ECharacter_Status r)
{
	return (ECharacter_Status)((uint8)l & (uint8)r);
}

inline ECharacter_Status operator|(ECharacter_Status l, ECharacter_Status r)
{
	return (ECharacter_Status)((uint8)l | (uint8)r);
}