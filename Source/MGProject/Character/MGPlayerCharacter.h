// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "MGPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGPlayerCharacter : public AMGCharacter
{
	GENERATED_BODY()

	friend class UMGAnimInstance;

public:
	AMGPlayerCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USpringArmComponent* ArmSpring;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USceneComponent* BoxRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* DroneDeployParticle;
	
	class UCameraComponent* Camera;

private:
	TArray<AActor*> TargetArray;
	FVector3d		DronePos;
	int				MissileMaxCount;
	int				MissileCount;
	float			MissileChargeTime;
	float			MissileChargeTimeAcc;
	float			DroneChargeTime;
	float			DroneChargeTimeAcc;
	bool			IsDroneDeployable;
	bool			ChargeFireMode;


public:
	USpringArmComponent* GetSpringArmComponent() const
	{
		return ArmSpring;
	}

	UParticleSystemComponent* GetDroneParticleSystem() const
	{
		return DroneDeployParticle;
	}

public:
	bool IsTargetEmpty() const
	{
		return TargetArray.IsEmpty();
	}

	FVector3d GetDroneDeployPosition() const
	{
		return DronePos;
	}

	float GetDroneChargeTime() const
	{
		return DroneChargeTime;
	}
	
	float GetDroneChargeTimeAcc() const
	{
		return DroneChargeTimeAcc;
	}
	
	float GetMissileMax() const
	{
		return MissileMaxCount;
	}
	
	float GetMissileChargeTime() const
	{
		return MissileChargeTime;
	}
	
	float GetMissileChargeTimeAcc() const
	{
		return MissileChargeTimeAcc;
	}

	bool IsDroneReady() const
	{
		return IsDroneDeployable;
	}
	
	bool IsChargeFireMode() const
	{
		return ChargeFireMode;
	}

	ECharacter_Status GetStatus() const
	{
		return AnimInstance->GetStatus();
	}

public:
	void UseDroneReady()
	{
		IsDroneDeployable = false;
	}

	void SetChargeFireMode(bool bEnable)
	{
		ChargeFireMode = bEnable;
	}


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	int GetMissileCount() const;
	int GetMissileCount(int UsingCount);
	USceneComponent* GetTarget() const;
	FVector GetTrace(FVector Pos = FVector::ZeroVector, float TraceDistance = 10000.0f) const;
	void SetQSkillCollision(bool bEnable);
	void QFireEnd();

private:
	void ESkillTrace();

public:
	virtual void AdjustHP(float _HP);

protected:
	virtual void StateUpdate(float DeltaTime) override;
	virtual void ActionStateUpdate(float DeltaTime);

protected:
	UFUNCTION()
	void QSkillOnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp,
		int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit);

	UFUNCTION()
	void QSkillOnCollisionEnd(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp,
		int32 _OtherBodyIndex);

	UFUNCTION()
	void OnCollisionGroundHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, const FHitResult& Hit);


};
