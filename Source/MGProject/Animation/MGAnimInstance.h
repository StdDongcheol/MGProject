// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MGFlag.h"
#include "Animation/AnimInstance.h"
#include "MGAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMGAnimInstance();

protected:
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	IsMoving;
	
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	IsFire;
	
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	IsDamaged;
	
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	IsDeath;
	
public:
	void SetMoving(bool Moving)
	{
		IsMoving = Moving;
	}

	void SetFire(bool Fire)
	{
		IsFire = Fire;
	}
	
	void SetDeath(bool Death)
	{
		IsDeath = Death;
	}
	
public:
	virtual void SetDamaged(bool Damaged);

public:
	void NativeUpdateAnimation(float DeltaSeconds) override;
	void NativeBeginPlay() override;

};
