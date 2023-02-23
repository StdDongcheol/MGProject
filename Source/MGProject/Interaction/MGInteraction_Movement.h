// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGInteraction.h"
#include "MGInteraction_Movement.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGInteraction_Movement : public AMGInteraction
{
	GENERATED_BODY()

public:
	AMGInteraction_Movement();
	
public:
	UPROPERTY(EditAnywhere, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent>	MovementMesh;

private:
	UPROPERTY(EditAnywhere, Category = "Movement Setting", meta = (AllowPrivateAccess = "true"))
	float	MovementSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement Setting", meta = (AllowPrivateAccess = "true"))
	float	MoveTime;
	float	MoveTimeAcc;
	
	UPROPERTY(EditAnywhere, Category = "Movement Setting", meta = (AllowPrivateAccess = "true"))
	FVector	MoveDirection;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void InteractionActivate() override;
	virtual void InteractionComplete() override;

};
