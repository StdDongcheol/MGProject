// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MGProjectile.generated.h"

UCLASS()
class MGPROJECT_API AMGProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AMGProjectile();

private:
	UMeshComponent* MeshComponent;
	UProjectileMovementComponent* ProjectileComponent;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
