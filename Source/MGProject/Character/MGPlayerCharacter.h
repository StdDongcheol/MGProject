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
	USpringArmComponent* ArmSpring;

private:
	TArray<AActor*> TargetArray;
	int		MissileCount;
	float	MissileChargeTime;
	float	MissileChargeTimeAcc;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USceneComponent* BoxRoot;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* ParticleQEffect;

public:
	USpringArmComponent* GetSpringArmComponent() const
	{
		return ArmSpring;
	}
	
	UParticleSystemComponent* GetQEffect() const
	{
		return ParticleQEffect;
	}

public:
	bool IsTargetEmpty() const
	{
		return TargetArray.IsEmpty();
	}

	int GetMissileCount() const;
	int GetMissileCount(int UsingCount);

public:
	USceneComponent* GetTarget() const;

protected:
	virtual void StateUpdate(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
