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
	class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
	class UParticleSystemComponent* ParticleLegacy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
	class UNiagaraComponent* ParticleNiagara;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Projectile")
	class UProjectileMovementComponent* ProjectileComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> HitEffect;

private:
	EObject_Force Force;
	float		  Range;
	float		  Speed;

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
