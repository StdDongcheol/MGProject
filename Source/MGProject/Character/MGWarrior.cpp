// Fill out your copyright notice in the Description page of Project Settings.


#include "MGWarrior.h"
#include "../MGAIController.h"

AMGWarrior::AMGWarrior()
{
	AIControllerClass = AMGAIController::StaticClass();
}

void AMGWarrior::BeginPlay()
{
	Super::BeginPlay();
}
