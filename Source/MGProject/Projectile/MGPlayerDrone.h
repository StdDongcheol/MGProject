// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGProjectile.h"
#include "Components/AudioComponent.h"
#include "MGPlayerDrone.generated.h"

/**
 * 
 */

USTRUCT(Atomic, BlueprintType)
struct FMGParticleSoundEventInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EventTime;

	UPROPERTY(BlueprintReadWrite)
	bool IsPlayed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> Audio;
	
	FMGParticleSoundEventInfo() :
		EventTime(0.0f),
		IsPlayed(false)
	{
	}
};

UCLASS()
class MGPROJECT_API AMGPlayerDrone : public AMGProjectile
{
	GENERATED_BODY()

public:
	AMGPlayerDrone();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Drone")
	class USceneComponent* FloatingLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Drone")
	class UParticleSystemComponent* ActivateParticle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Drone")
	class UParticleSystemComponent* DeactivateParticle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Drone")
	class UParticleSystemComponent* HealParticle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Drone")
	class USphereComponent* HealSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "DroneEffect")
	TArray<FMGParticleSoundEventInfo> ParticleDatas;

private:
	FVector StartPos;
	FVector EndPos;
	class AActor* HealingTarget;
	float	ActivatedTime;
	float	ActivatedTimeAcc;
	bool	IsActivated;
	bool	IsHealActivated;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


protected:
	UFUNCTION()
	void OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp,
	int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit);
	
	UFUNCTION()
	void OnHealCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp,
	int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit);
	
	UFUNCTION()
	void OnHealCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
