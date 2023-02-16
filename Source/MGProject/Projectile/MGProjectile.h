// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MGFlag.h"
#include "MGProjectile.generated.h"

UCLASS()
class MGPROJECT_API AMGProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AMGProjectile();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
	class UParticleSystemComponent* ParticleLegacy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
	class UProjectileMovementComponent* ProjectileComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> HitEffect;

protected:
	EObject_Force Force;
	float		  Range;
	float		  Speed;
	float		  Damage;

public:
	void SetForce(EObject_Force _Force)
	{
		Force = _Force;
	}

public:
	EObject_Force GetForce() const
	{
		return Force;
	}
	
	float GetProjectileDamage() const
	{
		return Damage;
	}

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
