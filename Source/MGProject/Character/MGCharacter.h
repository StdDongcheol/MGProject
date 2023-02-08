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

protected:
	UMGAnimInstance* AnimInstance;

protected:
	double		HP;
	double		HPMax;
	double		MinAttack;
	double		MaxAttack;
	double		AttackSpeed;
	double		MoveSpeed;

protected:
	class UCapsuleComponent* CapsuleComponent;

public:
	UMGAnimInstance* GetAnimInst() const
	{
		return AnimInstance;
	}
	
public:
	template<typename ClassType>
	ClassType* GetAnimInst() const
	{
		return Cast<ClassType>(AnimInstance);
	}

public:
	void SetCurrentHP(double _HP)
	{
		HP = _HP;
	}
	
	void SetMaxHP(double _MaxHP)
	{
		HPMax = _MaxHP;
	}
	
	void SetMinAttack(double _MinAttack)
	{
		MinAttack = _MinAttack;
	}
	
	void SetMaxAttack(double _MaxAttack)
	{
		MaxAttack = _MaxAttack;
	}
	
	void SetAttackSpeed(double _AttackSpeed)
	{
		AttackSpeed = _AttackSpeed;
	}
	
	void SetMoveSpeed(double _MoveSpeed)
	{
		MoveSpeed = _MoveSpeed;
	}
	
	void SetStatus(ECharacter_Status _Status)
	{
		AnimInstance->SetStatus(_Status);
	}

public:
	double GetCurrentHP() const
	{
		return HP;
	}

	double GetMaxHP() const
	{
		return HPMax;
	}
	
	double GetMinAttack() const
	{
		return MinAttack;
	}

	double GetMaxAttack() const
	{
		return MaxAttack;
	}
	
	double GetAttackSpeed() const
	{
		return AttackSpeed;
	}

	double GetMoveSpeed() const
	{
		return MoveSpeed;
	}

public:
	virtual void AdjustHP(float _HP);

public:
	AActor* FindTarget(FName _TargetTag, double _Range = 0.0f);
	FVector GetTargetDir(AActor* _Target);
	FVector GetTargetDir(const FVector& _TargetLocation);
	void SetLookAt(AActor* _Target);
	void AddMovement(FVector Dir, float Scale = 1.0f);

protected:
	virtual void StateUpdate(float DeltaTime);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
