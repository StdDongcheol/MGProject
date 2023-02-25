// Fill out your copyright notice in the Description page of Project Settings.


#include "MGInteraction_Input.h"
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

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetupAttachment(RootComponent);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);
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
	}
}

void AMGInteraction_Input::BeginPlay()
{
	Super::BeginPlay();

	InteractionWidget->SetWidgetClass(InteractionWidgetClass);

	InteractionPtr = Cast<UMGInteractionWidget>(InteractionWidget->GetWidget());

	Gauge = 0.0f;
	InputTime = 3.0f;
}

void AMGInteraction_Input::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsEntered && !IsWaveStart)
	{
		TArray<AActor*> OutActors;
		TriggerBox->GetOverlappingActors(OutActors);

		for (AActor* OutActor : OutActors)
		{
			if (OutActor->ActorHasTag(TEXT("Player")))
			{
				if (IsPlayerPushed)
				{
					InputTimeAcc += DeltaTime;
					InteractionPtr->SetProgress(InputTimeAcc / InputTime);
				}

				if (InputTimeAcc >= InputTime)
				{
					UE_LOG(LogTemp, Error, TEXT("Input Complete!"));

					SpawnComponent->GetInteracts(InteractionTag, InteractComponents, 
						WaveEndTag, WaveEndInteractComponents);

					for (TObjectPtr<AMGInteraction> InteractTarget : InteractComponents)
					{
						InteractTarget->InteractionActivate();
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
}

void AMGInteraction_Input::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, 
	UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	FName OtherProfile = _OtherComp->GetCollisionProfileName();

	if (OtherProfile != "Player")
	{
		return;
	}

	if (InteractionPtr)
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

	if (InteractionPtr)
	{
		InteractionPtr->SetPlayerOn(false);
	}

	InputTimeAcc = 0.0f;
}
