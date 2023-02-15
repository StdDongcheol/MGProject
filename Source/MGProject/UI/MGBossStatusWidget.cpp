// Fill out your copyright notice in the Description page of Project Settings.


#include "MGBossStatusWidget.h"
#include "../Character/MGEnemyBoss.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMGBossStatusWidget::SetCharacter(AMGEnemyBoss* Character)
{
	if (!Character || !Character->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("UMGBossStatusWidget SetCharacter initialize failed!"));
		return;
	}

	HPMax = Character->GetMaxHP();
	HPCurrent = Character->GetCurrentHP();
	
	SetHPBar(HPCurrent);

	BossPtr = Character;
}

void UMGBossStatusWidget::SetHPBar(float HP)
{
	float Percent = HP / HPMax;

	HPBar->SetPercent(Percent);
}

void UMGBossStatusWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMGBossStatusWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UMGBossStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPBar = Cast<UProgressBar>(WidgetTree->FindWidget(TEXT("HPProgressBar")));
}

void UMGBossStatusWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMGBossStatusWidget::BossStatusUpdate(float Deltatime)
{
}
