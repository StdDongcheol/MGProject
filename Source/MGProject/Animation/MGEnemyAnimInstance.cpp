// Fill out your copyright notice in the Description page of Project Settings.


#include "MGEnemyAnimInstance.h"

UMGEnemyAnimInstance::UMGEnemyAnimInstance()
{
	IsAttacking = false;

	AnimState = EAIAnimState::Idle;
}

void UMGEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMGEnemyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}
