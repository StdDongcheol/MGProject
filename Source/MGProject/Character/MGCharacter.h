// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Animation/MGAnimInstance.h"
#include "../MGFlag.h"
#include "GameFramework/Character.h"
#include "MGCharacter.generated.h"

UCLASS()
class MGPROJECT_API AMGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMGCharacter();

private:
	UMGAnimInstance* AnimInstance;

protected:
	float		HP;
	float		HPMax;

protected:
	class UCapsuleComponent* Capsule;

public:
	UMGAnimInstance* GetAnimInst() const
	{
		return AnimInstance;
	}

public:
	float GetCurrentHP() const
	{
		return HP;
	}

	float GetMaxHP() const
	{
		return HPMax;
	}

public:
	void AdjustHP(float _HP);

protected:
	virtual void StateUpdate(float DeltaTime);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
