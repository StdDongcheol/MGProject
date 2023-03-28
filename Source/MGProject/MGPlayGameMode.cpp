// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPlayGameMode.h"
#include "MGBlueprintFunctionLibrary.h"
#include "MGGameInstance.h"
#include "Components/AudioComponent.h"

AMGPlayGameMode::AMGPlayGameMode()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMAudio"));
	RootComponent = AudioComponent;
	
	NextBGMSound = nullptr;
}

void AMGPlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	USoundBase* BGMSound = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetBGMData(TEXT("PlayNormal"));
	
	if (!BGMSound || !BGMSound->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("AMGPlayGameMode::BeginPlay() : BGMSound is null!"));
		return;
	}

	AudioComponent->SetSound(BGMSound);
	AudioComponent->FadeIn(3.0f, 1.0f, BGMPlayTime);
}

void AMGPlayGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!AudioComponent->IsPlaying() && NextBGMSound)
	{
		AudioComponent->SetSound(NextBGMSound);
		AudioComponent->FadeIn(3.0f, 1.0f, BGMPlayTime);

		NextBGMSound = nullptr;
	}
}

void AMGPlayGameMode::ChangeBGM(FName _BGMName, float _FadeDuration)
{
	USoundBase* BGMSound = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetBGMData(_BGMName);

	if (!BGMSound || !BGMSound->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("AMGPlayGameMode::ChangeBGM(FName) : BGMSound is null!"));
		return;
	}

	if (_FadeDuration == 0.0f)
	{
		AudioComponent->SetSound(BGMSound);
		AudioComponent->Play();
	}

	else
	{
		AudioComponent->FadeOut(_FadeDuration, 0.0f);

		if (UWorld* World = GetWorld())
		{
			BGMPlayTime = World->GetAudioTimeSeconds();
		}

		BGMPlayTime += _FadeDuration;
		NextBGMSound = BGMSound;
	}
}

void AMGPlayGameMode::BGMFadeOut()
{
	AudioComponent->FadeOut(3.0f, 0.0f);
}
