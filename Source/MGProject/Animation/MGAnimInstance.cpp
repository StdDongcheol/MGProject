// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimInstance.h"
#include "GameFramework/Character.h"

UMGAnimInstance::UMGAnimInstance()
{
}

void UMGAnimInstance::SetDamaged(bool Damaged)
{
	IsDamaged = Damaged;
}

void UMGAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMGAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

