// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGCharacter.h"
#include "Camera/CameraComponent.h"
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
	friend class AMGPlayerController;

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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* ChargeParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* BackpackParticle;
	
	TObjectPtr<UCameraComponent> Camera;

private:
	TArray<AActor*> TargetArray;
	FVector3d		DronePos;
	int				MissileMaxCount;
	int				MissileCount;
	float			MissileChargeTime;
	float			MissileChargeTimeAcc;
	float			DroneChargeTime;
	float			DroneChargeTimeAcc;
	float			DashChargeTime;
	float			DashChargeTimeAcc;
	float			ChargeShotGauge;
	float			ChargeShotGaugeMax;
	bool			IsDashReady;
	bool			IsDroneDeployable;
	bool			ChargeFireMode;
	bool			IsChargeReady;


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
	
	float GetDashChargeTime() const
	{
		return DashChargeTime;
	}
	
	float GetDashChargeTimeAcc() const
	{
		return DashChargeTimeAcc;
	}

	bool IsDroneReady() const
	{
		return IsDroneDeployable;
	}
	
	bool IsChargeFireMode() const
	{
		return ChargeFireMode;
	}
	
	bool IsChargeEnable() const
	{
		return IsChargeReady;
	}

	bool IsDashCharged() const
	{
		return IsDashReady;
	}

	ECharacter_Status GetStatus() const
	{
		return AnimInstance->GetStatus();
	}
	
	UCameraComponent* GetCameraComponent() const
	{
		return Camera;
	}

public:
	void UseDroneReady()
	{
		IsDroneDeployable = false;
	}
	
	void UseDash()
	{
		IsDashReady = false;
	}
	
	void UseChargeShot();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	int GetMissileCount() const;
	int GetMissileCount(int UsingCount);
	USceneComponent* GetTarget() const;
	FHitResult GetTrace(FVector Pos = FVector::ZeroVector, float TraceDistance = 10000.0f, bool GetHitResult = true) const;
	void SetQSkillCollision(bool bEnable);
	void QFireEnd();
	void SetChargeFireMode(bool bEnable);
	void AddAttackCharge(float ChargeValue);

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
