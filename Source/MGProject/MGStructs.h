// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MGFlag.h"
#include "UObject/NoExportTypes.h"
#include "MGStructs.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGStructs : public UObject
{
	GENERATED_BODY()
	
};

USTRUCT(Atomic, BlueprintType)
struct FMGBulletTable : public FTableRowBase
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

USTRUCT(Atomic, BlueprintType)
struct FMGEnemyStatusDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double	MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double	MinAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double	MaxAttack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double	AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double	MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double	DetectionRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double	AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EObject_Force Force;

};