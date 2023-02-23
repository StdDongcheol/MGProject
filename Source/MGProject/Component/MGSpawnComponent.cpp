// Fill out your copyright notice in the Description page of Project Settings.


#include "MGSpawnComponent.h"
#include "../Interaction/MGInteraction.h"
#include "../Interaction/MGInteraction_Input.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UMGSpawnComponent::UMGSpawnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UMGSpawnComponent::GetInteracts(FName InteractionTag, TArray<TObjectPtr<AMGInteraction>>& InteractComponents, 
	FName WaveEndTag, TArray<TObjectPtr<AMGInteraction>>& WaveEndInteractComponents)
{
	for (AActor* InteractionActor : InteractionArray)
	{
		if (InteractionActor->ActorHasTag(InteractionTag))
		{
			AMGInteraction* TargetActor = Cast<AMGInteraction>(InteractionActor);
			InteractComponents.Add(TargetActor);
		}

		else if (InteractionActor->ActorHasTag(WaveEndTag))
		{
			AMGInteraction* TargetActor = Cast<AMGInteraction>(InteractionActor);
			WaveEndInteractComponents.Add(TargetActor);
		}
	}

	if (InteractComponents.IsEmpty() || WaveEndInteractComponents.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("InteractComponents or WaveEndInteractComponents is empty!! Check your Tags are blank."));
	}
}

// Called when the game starts
void UMGSpawnComponent::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Interaction"), InteractionArray);
	
	for (AActor* InteractActor : InteractionArray)
	{
		UBoxComponent* BoxTrigger = InteractActor->FindComponentByClass<UBoxComponent>();

		if (BoxTrigger && BoxTrigger->IsValidLowLevel())
		{
			AMGInteraction_Input* InputActor = Cast<AMGInteraction_Input>(InteractActor);
			InputActor->SetSpawnComponent(this);
			InputArray.Add(InputActor);
		}
	}
}


// Called every frame
void UMGSpawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

