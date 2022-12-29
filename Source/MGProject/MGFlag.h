// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
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
	Aiming,
	QAiming,
	RAiming
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

USTRUCT(Atomic, BlueprintType)
struct FBulletTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* ProjectileEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* HitEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EObject_Force Force;

};