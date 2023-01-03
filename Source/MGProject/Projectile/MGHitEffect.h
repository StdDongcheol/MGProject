// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGHitEffect.generated.h"

UCLASS()
class MGPROJECT_API AMGHitEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	AMGHitEffect();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Effect")
	class UParticleSystemComponent* HitParticle;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};