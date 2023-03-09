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
struct FHitParticleDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EParticle_Type ParticleType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UParticleSystem> CascadeParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UNiagaraSystem> NiagaraParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USoundBase> HitSound;
};

USTRUCT(Atomic, BlueprintType)
struct FMGBulletDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EParticle_Type ParticleType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UParticleSystem> ProjectileEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UNiagaraSystem> NiagaraParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UParticleSystem> HitEffect;

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

USTRUCT(Atomic, BlueprintType)
struct FMGBGMDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USoundBase> BGM;
};