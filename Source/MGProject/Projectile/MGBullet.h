// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGProjectile.h"
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

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp, 
		int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit);

public:
	virtual void Tick(float DeltaTime) override;
	
	
};

