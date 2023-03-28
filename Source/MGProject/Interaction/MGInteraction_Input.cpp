// Fill out your copyright notice in the Description page of Project Settings.


#include "MGInteraction_Input.h"
#include "../Character/MGPlayerCharacter.h"
#include "../Animation/MGPlayerAnimInstance.h"
#include "../Character/MGEnemyCharacter.h"
#include "../MGPlayerController.h"
#include "../MGPlayGameMode.h"
#include "../Component/MGSpawnComponent.h"
#include "../UI/MGInteractionWidget.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

AMGInteraction_Input::AMGInteraction_Input()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetCollisionProfileName(FName("Trigger"));
	TriggerBox->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	TriggerBox->SetGenerateOverlapEvents(true);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMGInteraction_Input::OnCollisionEnter);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AMGInteraction_Input::OnCollisionEnd);

	RootComponent = TriggerBox;

	InputMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	InputMesh->SetupAttachment(RootComponent);
	
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetupAttachment(RootComponent);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen); 

	IsLeftEnemyAllDeath = false;
}

void AMGInteraction_Input::SetForceEnter()
{
	ForceStart = true;
	IsEntered = true;
}

void AMGInteraction_Input::SetSpawnComponent(UMGSpawnComponent* Component)
{
	if (Component)
		SpawnComponent = Component;
}

void AMGInteraction_Input::SetProgressing(bool bEnable)
{
	IsPlayerPushed = bEnable;

	if (!bEnable && !InteractionPtr->IsCompleted())
	{
		InputTimeAcc = 0.0f;
		InteractionPtr->SetProgress(0.0f);

		if (InputMesh)
			InputMesh->SetScalarParameterValueOnMaterials(TEXT("EmssiveIntensity"), 1.0f);
	}
}

bool AMGInteraction_Input::FindEnemies()
{
	TArray<TObjectPtr<AActor>> OutActors;

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Enemy"), OutActors);

	if (OutActors.IsEmpty())
		return false;

	else
	{
		for (AActor* EnemyLeft : OutActors)
		{
			AMGEnemyCharacter* CastedEnemy = Cast<AMGEnemyCharacter>(EnemyLeft);

			WaveEndEnemiesArray.Add(CastedEnemy);
		}

		return true;
	}
}

void AMGInteraction_Input::BeginPlay()
{
	Super::BeginPlay();

	InteractionWidget->SetWidgetClass(InteractionWidgetClass);

	InteractionPtr = Cast<UMGInteractionWidget>(InteractionWidget->GetWidget());

	EmitFlickTime = 0.2f;
}

void AMGInteraction_Input::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsEntered && !IsWaveStart)
	{
		TArray<AActor*> OutActors;
		TriggerBox->GetOverlappingActors(OutActors);

		if (ForceStart)
		{
			IsWaveStart = true;

			SpawnComponent->GetInteracts(InteractionTag, InteractComponents,
				WaveEndTag, WaveEndInteractComponents);
		}

		for (AActor* OutActor : OutActors)
		{
			if (OutActor->ActorHasTag(TEXT("Player")))
			{
				if (IsPlayerPushed)
				{
					InputTimeAcc += DeltaTime;
					EmitFlickTimeAcc += DeltaTime;

					if (InputMesh)
					{
						if (EmitFlickTimeAcc >= EmitFlickTime)
						{
							bEmitFlipper = !bEmitFlipper;
							EmitFlickTimeAcc -= EmitFlickTimeAcc;
						}

						if (bEmitFlipper)
							InputMesh->SetScalarParameterValueOnMaterials(TEXT("EmssiveIntensity"), 100.0f);
						else
							InputMesh->SetScalarParameterValueOnMaterials(TEXT("EmssiveIntensity"), 1.0f);
					}
					
					InteractionPtr->SetProgress(InputTimeAcc / InputTime);
				}

				if (InputTimeAcc >= InputTime)
				{
					UE_LOG(LogTemp, Error, TEXT("Input Complete!"));

					AMGPlayerCharacter* Player = Cast<AMGPlayerCharacter>(OutActor);

					if (!Player || !Player->IsValidLowLevel())
					{
						UE_LOG(LogTemp, Error, TEXT("Player doesn't executed !!"));
						return;
					}

					Player->GetAnimInst<UMGPlayerAnimInstance>()->SetActionState(EPlayer_ActionState::Normal);
						
					SpawnComponent->GetInteracts(InteractionTag, InteractComponents, 
						WaveEndTag, WaveEndInteractComponents);

					if (IsIncomingWave)
					{
						AMGPlayGameMode* GameMode = Cast<AMGPlayGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
						GameMode->ChangeBGM(FName("PlayWave"), 0.2f);
					}

					for (TObjectPtr<AMGInteraction> InteractTarget : InteractComponents)
					{
						InteractTarget->InteractionActivate();
					}

					if (SetBGMFadeOut)
					{
						AMGPlayGameMode* GameMode = Cast<AMGPlayGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
						GameMode->BGMFadeOut();
					}

					IsWaveStart = true;
				}
			}
		}
	}	

	if (IsWaveStart && !IsComplete)
	{
		WaveTimeAcc += DeltaTime;

		if (WaveTimeAcc >= WaveTime)
		{
			InteractionComplete();
		}
	}

	if (IsComplete && !IsLeftEnemyAllDeath)
	{
		for (AMGEnemyCharacter* EnemyLeft : WaveEndEnemiesArray)
		{
			IsLeftEnemyAllDeath = true;

			if (EnemyLeft->GetCurrentHP() > 0.0f)
			{
				IsLeftEnemyAllDeath = false;
				break;
			}
		}

		if (IsLeftEnemyAllDeath)
		{
			AMGPlayGameMode* GameMode = Cast<AMGPlayGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			GameMode->ChangeBGM(FName("PlayNormal"), 2.0f);
		}
	}
}

void AMGInteraction_Input::InteractionActivate()
{
	Super::InteractionActivate();
}

void AMGInteraction_Input::InteractionComplete()
{
	Super::InteractionComplete();

	for (AMGInteraction* InteractTarget : WaveEndInteractComponents)
	{
		InteractTarget->InteractionActivate();
	}

	if (IsIncomingWave)
	{
		if (!FindEnemies())
		{
			AMGPlayGameMode* GameMode = Cast<AMGPlayGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			GameMode->ChangeBGM(FName("PlayNormal"), 0.2f);
		}
	}
}

void AMGInteraction_Input::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, 
	UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	FName OtherProfile = _OtherComp->GetCollisionProfileName();

	if (OtherProfile != "Player")
	{
		return;
	}

	if (IsFinalInput)
	{
		// Final Setting;
		AMGPlayerCharacter* Player = Cast<AMGPlayerCharacter>(_pOtherActor);

		if (!Player || !Player->IsValidLowLevel())
		{
			UE_LOG(LogTemp, Error, TEXT("Player doesn't executed !!"));
			return;
		}

		AMGPlayerController* PlayerController = Player->GetController<AMGPlayerController>();

		if (!PlayerController || !PlayerController->IsValidLowLevel())
		{
			UE_LOG(LogTemp, Error, TEXT("PlayerController doesn't executed !!"));
			return;
		}

		AMGPlayGameMode* GameMode = Cast<AMGPlayGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->ChangeBGM(FName("StageClear"), 3.0f);

		PlayerController->WidgetEnd();
		return;
	}

	if (InteractionPtr && !IsTriggerOnly)
	{
		InteractionPtr->SetPlayerOn(true);
	}

	IsEntered = true;

}

void AMGInteraction_Input::OnCollisionEnd(UPrimitiveComponent* _pComponent, AActor* _pOtherActor,
	UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex)
{
	FName OtherProfile = _OtherComp->GetCollisionProfileName();

	if (OtherProfile != "Player")
	{
		return;
	}

	IsEntered = false;
	IsPlayerPushed = false;

	if (InteractionPtr && !IsTriggerOnly)
	{
		InteractionPtr->SetPlayerOn(false);
	}

	InputTimeAcc = 0.0f;

	if (InputMesh)
		InputMesh->SetScalarParameterValueOnMaterials(TEXT("EmssiveIntensity"), 1.0f);
}
