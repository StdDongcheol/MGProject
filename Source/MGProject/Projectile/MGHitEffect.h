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

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Effect")
	class UParticleSystemComponent* HitParticle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Effect")
	class UAudioComponent* AudioComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Effect")
	bool	AttachToOtherComponent = false;

private:
	bool	IsSoundPlayed;

public:
	void SetStatus(float fLifetime = 1.0f, USceneComponent* AttachComponent = nullptr);
	void SetParticle(class UParticleSystem* CascadeParticle);
	void SetParticleNiagara(const class UNiagaraSystem* NiagaraParticle);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
