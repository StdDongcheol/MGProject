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
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent>	InputMesh;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent>	TriggerBox;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UWidgetComponent>	InteractionWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget>	InteractionWidgetClass;

	TObjectPtr<class UMGInteractionWidget> InteractionPtr;

	TObjectPtr<class UMGSpawnComponent>		SpawnComponent;

private:
	TArray<TObjectPtr<AMGInteraction>>	InteractComponents;
	TArray<TObjectPtr<AMGInteraction>>	WaveEndInteractComponents;
	
private:
	TArray<TObjectPtr<class AMGEnemyCharacter>> WaveEndEnemiesArray;
	
	
	UPROPERTY(EditAnywhere, Category = "Interaction TagName", meta = (AllowPrivateAccess = "true"))
	FName	WaveEndTag;

private:
	UPROPERTY(EditAnywhere, Category = "Input Setting", meta = (AllowPrivateAccess = "true"))
	float	InputTime;
	float	InputTimeAcc;
		
	UPROPERTY(EditAnywhere, Category = "Input Setting", meta = (AllowPrivateAccess = "true"))
	float	WaveTime;
	float	WaveTimeAcc;

	float	EmitFlickTime;
	float	EmitFlickTimeAcc;
	bool	bEmitFlipper;


	UPROPERTY(EditAnywhere, Category = "Input Setting", meta = (AllowPrivateAccess = "true"))
	bool	IsFinalInput;
	
	UPROPERTY(EditAnywhere, Category = "Input Setting", meta = (AllowPrivateAccess = "true"))
	bool	IsIncomingWave;
	bool	IsLeftEnemyAllDeath;

	UPROPERTY(EditAnywhere, Category = "Input Setting", meta = (AllowPrivateAccess = "true"))
	bool	IsTriggerOnly;
	
	UPROPERTY(EditAnywhere, Category = "Input Setting", meta = (AllowPrivateAccess = "true"))
	bool	SetBGMFadeOut;
	
	bool	IsWaveStart;
	bool	IsEntered;
	bool	ForceStart;
	bool	IsPlayerPushed;

public:
	bool IsPlayerEntered() const
	{
		return IsEntered;
	}

public:
	void SetForceEnter();

public:
	void SetSpawnComponent(class UMGSpawnComponent* Component);
	void SetProgressing(bool bEnable);

private:
	bool FindEnemies();

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
