// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGProjectile.h"
#include "MGMissile.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGMissile : public AMGProjectile
{
	GENERATED_BODY()

public:
	AMGMissile();

protected:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Missile")
	class USkeletalMesh* SkeletalMesh;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Missile")
	class USphereComponent* DamageCollider;


public:
	void SetTarget(USceneComponent* TargetComponent);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp,
	int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit);

};
