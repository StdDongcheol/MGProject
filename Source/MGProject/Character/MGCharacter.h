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

public:
	UMGAnimInstance* GetAnimInst() const
	{
		return AnimInstance;
	}

protected:
	virtual void StateUpdate(float DeltaTime);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
