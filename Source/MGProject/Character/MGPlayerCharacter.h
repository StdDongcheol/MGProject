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

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

	void UseDroneReady()
	{
		IsDroneDeployable = false;
	}
	
	bool IsDroneReady() const
	{
		return IsDroneDeployable;
	}

public:
	int GetMissileCount() const;
	int GetMissileCount(int UsingCount);
	USceneComponent* GetTarget() const;
	FVector GetTrace(FVector Pos = FVector::ZeroVector, float TraceDistance = 10000.0f) const;

public:
	virtual void AdjustHP(float _HP);

protected:
	virtual void StateUpdate(float DeltaTime) override;
	virtual void ActionStateUpdate(float DeltaTime);

private:
	void ESkillTrace();

public:
	void SetQSkillCollision(bool bEnable);

public:
	void QFireEnd();

protected:
	UFUNCTION()
	void QSkillOnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp,
		int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit);

	UFUNCTION()
	void QSkillOnCollisionEnd(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp,
		int32 _OtherBodyIndex);


};
