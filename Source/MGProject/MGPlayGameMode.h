// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MGPlayGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGPlayGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMGPlayGameMode();

private:
	UPROPERTY(EditAnywhere, Category = "Event Setting", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAudioComponent>	AudioComponent;

private:
	float	BGMPlayTime;
	TObjectPtr<class USoundBase> NextBGMSound;

public:
	UAudioComponent* GetBGMAudioComponent() const
	{
		return AudioComponent;
	}

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
public:
	void ChangeBGM(FName _BGMName, float _FadeDuration = 0.0f);
	void BGMFadeOut();
};
