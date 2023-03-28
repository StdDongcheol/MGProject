// Fill out your copyright notice in the Description page of Project Settings.


#include "MGInteraction_Movement.h"

AMGInteraction_Movement::AMGInteraction_Movement()
{
	MovementMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Movement Mesh"));
	
	RootComponent = MovementMesh;
	MovementMesh->SetCollisionProfileName(TEXT("WorldObject"));
}

void AMGInteraction_Movement::BeginPlay()
{
	Super::BeginPlay();

	MoveDirection = MoveDirection.GetSafeNormal();
}

void AMGInteraction_Movement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsComplete && IsInteractionActivated())
	{
		MoveTimeAcc += DeltaTime;

		if (MoveTimeAcc >= MoveTime)
		{
			InteractionComplete();
		}

		MovementMesh->AddWorldOffset(MoveDirection * MovementSpeed * DeltaTime);
	}
}

void AMGInteraction_Movement::InteractionActivate()
{
	Super::InteractionActivate();
}

void AMGInteraction_Movement::InteractionComplete()
{
	Super::InteractionComplete();
}
