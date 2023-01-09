// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGProjectile.h"
#include "MGPlayerDrone.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGPlayerDrone : public AMGProjectile
{
	GENERATED_BODY()

public:
	AMGPlayerDrone();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Drone")
	class UParticleSystemComponent* ActivateParticle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Drone")
	class UParticleSystemComponent* DeactivateParticle;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


protected:
	UFUNCTION()
	void OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp,
	int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit);

};
