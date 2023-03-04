// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGProjectile.h"
#include "MGLaser.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGLaser : public AMGProjectile
{
	GENERATED_BODY()

public:
	AMGLaser();

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Laser")
	class UBoxComponent* DamageCollider;

private:
	double	CollisionTime;
	double	CollisionTimeAcc;

protected:
	virtual void BeginPlay() override;

protected:
	virtual void Tick(float DeltaTime) override;

public:
	void SetProfile(FName _Name, float _Damage);

protected:
	UFUNCTION()
	void OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, 
		UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit);

};
