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

public:
	AMGPlayerCharacter();

private:
	USpringArmComponent* ArmSpring;

private:
	TArray<AActor*> TargetArray;

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
	
public:
	UParticleSystemComponent* GetQEffect() const
	{
		return ParticleQEffect;
	}

protected:
	virtual void StateUpdate(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	UFUNCTION()
	void OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp,
		int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit);

	UFUNCTION()
	void OnCollisionEnd(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp,
		int32 _OtherBodyIndex);


};
