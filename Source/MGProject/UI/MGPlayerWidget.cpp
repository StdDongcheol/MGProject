// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPlayerWidget.h"
#include "../MGPlayerController.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMGPlayerWidget::SetHPBar(float HP)
{
	float Percent = HP / HPMax;

	HPBar->SetPercent(Percent);
}

void UMGPlayerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMGPlayerWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UMGPlayerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AMGPlayerController* PlayerController = Cast<AMGPlayerController>(GetOwningPlayer());
	PlayerChacracter = Cast<AMGPlayerCharacter>(PlayerController->GetPlayerCharacter());

	HPBar = Cast<UProgressBar>(WidgetTree->FindWidget(TEXT("HPProgressBar")));
	MissileChargeBar = Cast<UProgressBar>(WidgetTree->FindWidget(TEXT("MissileProgressBar")));
	DroneChargeBar = Cast<UProgressBar>(WidgetTree->FindWidget(TEXT("DroneProgressBar")));
	MissileCountText = Cast<UTextBlock>(WidgetTree->FindWidget(TEXT("MissileCount")));

	HPCurrent = PlayerChacracter->GetCurrentHP();
	HPMax = PlayerChacracter->GetMaxHP();
	ETimeLeft = PlayerChacracter->GetDroneChargeTimeAcc();
	ECoolTime = PlayerChacracter->GetDroneChargeTime();
	QTimeLeft = PlayerChacracter->GetMissileChargeTimeAcc();
	QCoolTime = PlayerChacracter->GetMissileChargeTime();
	CurrentMissile = PlayerChacracter->GetMissileCount();
	MissileMax = PlayerChacracter->GetMissileMax();

	MissileCountText->SetText(FText::FromString(FString::FromInt(CurrentMissile)));
}

void UMGPlayerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	PlayerStatusUpdate(InDeltaTime);
}

void UMGPlayerWidget::PlayerStatusUpdate(float Deltatime)
{
	HPCurrent = PlayerChacracter->GetCurrentHP();
	HPMax = PlayerChacracter->GetMaxHP();
	ETimeLeft = PlayerChacracter->GetDroneChargeTimeAcc();
	ECoolTime = PlayerChacracter->GetDroneChargeTime();
	QTimeLeft = PlayerChacracter->GetMissileChargeTimeAcc();
	QCoolTime = PlayerChacracter->GetMissileChargeTime();
	CurrentMissile = PlayerChacracter->GetMissileCount();
	MissileMax = PlayerChacracter->GetMissileMax();

	SetHPBar(HPCurrent);

	MissileChargeBar->SetPercent(QTimeLeft / QCoolTime);
	DroneChargeBar->SetPercent(ETimeLeft / ECoolTime);
	MissileCountText->SetText(FText::FromString(FString::FromInt(CurrentMissile)));
}
