// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGEnemyBoss.h"
#include "MGCrunch.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGCrunch : public AMGEnemyBoss
{
	GENERATED_BODY()

public:
	AMGCrunch();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* DamageBoxLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* DamageBoxRight;
	

public:
	virtual const FMGEnemyStatusDataTable* InitEnemyData() override;
	virtual void AdjustHP(float _HP) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void OnDamageCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp,
	int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit);

};
