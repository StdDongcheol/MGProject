// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MGFlag.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MGProjectile.generated.h"

UCLASS()
class MGPROJECT_API AMGProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AMGProjectile();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
	class UStaticMeshComponent* Sphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
	class UParticleSystemComponent* Particle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
	class UProjectileMovementComponent* ProjectileComponent;

private:
	EObject_Force Force;
	float		  Range;

public:
	void SetForce(EObject_Force _Force)
	{
		Force = _Force;
	}

	EObject_Force GetForce() const
	{
		return Force;
	}

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
