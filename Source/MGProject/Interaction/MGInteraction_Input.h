// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGInteraction.h"
#include "MGInteraction_Input.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGInteraction_Input : public AMGInteraction
{
	GENERATED_BODY()

public:
	AMGInteraction_Input();

public:
	UPROPERTY()
	TObjectPtr<class UBoxComponent>	TriggerBox;

private:
	TArray<TObjectPtr<AMGInteraction>>	InteractComponents;
	TArray<TObjectPtr<AMGInteraction>>	WaveEndInteractComponents;
	
	UPROPERTY(EditAnywhere, Category = "Interaction TagName", meta = (AllowPrivateAccess = "true"))
	FName	WaveEndTag;

private:
	UPROPERTY(EditAnywhere, Category = "Input Setting", meta = (AllowPrivateAccess = "true"))
	float	InputTime;
	float	InputTimeAcc;
		
	UPROPERTY(EditAnywhere, Category = "Input Setting", meta = (AllowPrivateAccess = "true"))
	float	WaveTime;
	float	WaveTimeAcc;

	bool	IsWaveStart;
	bool	IsEntered;
	float	Gauge;

	TObjectPtr<class UMGSpawnComponent>		SpawnComponent;

public:
	void SetSpawnComponent(class UMGSpawnComponent* Component);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void InteractionActivate() override;
	virtual void InteractionComplete() override;

protected:
	UFUNCTION()
	void OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp,
		int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit);

	UFUNCTION()
	void OnCollisionEnd(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, 
		UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex);
};