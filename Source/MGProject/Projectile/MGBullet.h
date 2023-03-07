// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGProjectile.h"
#include "../MGStructs.h"
#include "MGBullet.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGBullet : public AMGProjectile
{
	GENERATED_BODY()

public:
	AMGBullet();

private:
	const FHitParticleDataTable* ParticleTable;

protected:
	virtual void BeginPlay() override;

protected:
	virtual void Tick(float DeltaTime) override;

public:
	void SetBulletProfile(FName _Name, float _Speed, float _Damage);

protected:
	UFUNCTION()
	void OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp, 
		int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit);

};

