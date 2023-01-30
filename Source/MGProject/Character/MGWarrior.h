// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGEnemyCharacter.h"
#include "MGWarrior.generated.h"


UCLASS()
class MGPROJECT_API AMGWarrior : public AMGEnemyCharacter
{
	GENERATED_BODY()

public:
	AMGWarrior();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* DamageBoxLeft;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* DamageBoxRight;

protected:
	void BeginPlay() override;

public:
	virtual const FMGEnemyStatusDataTable* InitEnemyData() override;

protected:
	UFUNCTION()
	void OnDamageCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp,
	int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit);


};
