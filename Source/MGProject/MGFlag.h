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
	Normal = 0b0000,
	Status_Damaged = 0b0001,
	Status_Slow = 0b0010,
}; 

inline ECharacter_Status operator&(ECharacter_Status l, ECharacter_Status r)
{
	return (ECharacter_Status)((uint8)l & (uint8)r);
}

inline ECharacter_Status operator|(ECharacter_Status l, ECharacter_Status r)
{
	return (ECharacter_Status)((uint8)l | (uint8)r);
}

UENUM()
enum class EAIAnimState : uint8
{
	Death = 0b0000,
	Idle = 0b0001,
	Rotate = 0b0010,
	Attack = 0b0100,
	Groggy = 0b1000,
};

inline EAIAnimState operator&(EAIAnimState l, EAIAnimState r)
{
	return (EAIAnimState)((uint8)l & (uint8)r);
}

inline EAIAnimState operator|(EAIAnimState l, EAIAnimState r)
{
	return (EAIAnimState)((uint8)l | (uint8)r);
}