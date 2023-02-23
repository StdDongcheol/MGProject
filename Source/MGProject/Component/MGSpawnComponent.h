// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MGSpawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MGPROJECT_API UMGSpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMGSpawnComponent();

private:
	TArray<TObjectPtr<AActor>>		InteractionArray;
	TArray<TObjectPtr<class AMGInteraction_Input>>	InputArray;

public:
	void GetInteracts(FName InteractionTag, TArray<TObjectPtr<class AMGInteraction>>& InteractComponents,
		FName WaveEndTag, TArray<TObjectPtr<class AMGInteraction>>& WaveEndInteractComponents);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
