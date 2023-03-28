// Fill out your copyright notice in the Description page of Project Settings.


#include "MGEnemyBoss.h"
#include "../MGPlayGameMode.h"
#include "../MGBossController.h"
#include "../UI/MGBossStatusWidget.h"
#include "../UI/MGWeakpointWidget.h"
#include "../Interaction/MGInteraction.h"
#include "../Interaction/MGInteraction_Input.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"

AMGEnemyBoss::AMGEnemyBoss()
{
	AIControllerClass = AMGBossController::StaticClass();
}

const FMGEnemyStatusDataTable* AMGEnemyBoss::InitEnemyData()
{
	return nullptr;
}

void AMGEnemyBoss::SetDamage(float _Damage, bool _IsWeakpoint)
{
	Super::SetDamage(_Damage, _IsWeakpoint);

	if (HP <= 0.0f)
	{
		TObjectPtr<AMGInteraction> Interaction = nullptr;

		AMGPlayGameMode* GameMode = Cast<AMGPlayGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->ChangeBGM(FName("PlayNormal"), 3.0f);

		FindTag(Interaction);
		SetLifeSpan(9.0f);
	}
}

void AMGEnemyBoss::SetWeakpointEnable(bool bEnable)
{
	TArray<UActorComponent*> ComponentsArray = GetComponentsByTag(UWidgetComponent::StaticClass(), FName("WeakPoint"));

	for (UActorComponent* WeakComponent : ComponentsArray)
	{
		UWidgetComponent* WidgetComp = Cast<UWidgetComponent>(WeakComponent);
		UMGWeakpointWidget* WidgetClass = Cast<UMGWeakpointWidget>(WidgetComp->GetWidget());

		if (bEnable)
		{
			WidgetComp->SetVisibility(true);
			WidgetClass->SetVisibility(ESlateVisibility::Visible);
			WidgetClass->WeakPlayAnimation();
		}

		else
		{
			WidgetComp->SetVisibility(false);
			WidgetClass->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AMGEnemyBoss::BeginPlay()
{
	Super::BeginPlay();
	
	AMGBossController* BossController = GetController<AMGBossController>();

	if (BossController)
	{
		StatusWidget = BossController->GetStatusWidget();
		StatusWidget->SetCharacter(this);
	}

	AMGPlayGameMode* GameMode = Cast<AMGPlayGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->ChangeBGM(FName("PlayBoss"));
}

void AMGEnemyBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HP <= 0.0f)
	{
		StatusWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool AMGEnemyBoss::FindTag(AMGInteraction* Interaction)
{
	TArray<TObjectPtr<AActor>>	InteractionArray;

	if (EventInteractionTagName == NAME_None)
		return false;

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), EventInteractionTagName, InteractionArray);

	for (AActor* TargetInteraction : InteractionArray)
	{
		AMGInteraction_Input* InputActor = Cast<AMGInteraction_Input>(TargetInteraction);

		if (InputActor && InputActor->IsValidLowLevel())
		{
			InputActor->SetForceEnter();
			Interaction = InputActor;
			return true;
		}
	}

	return false;
}
