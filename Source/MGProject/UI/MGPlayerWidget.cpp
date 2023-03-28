// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPlayerWidget.h"
#include "../MGPlayerController.h"
#include "Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/Slider.h"

void UMGPlayerWidget::SetHPBar(float HP)
{
	float Percent = HP / HPMax;

	HPBar->SetPercent(Percent);
	HPSlider->SetValue(Percent);
}

void UMGPlayerWidget::StageStart()
{
	PlayAnimation(FadeinAnimation);
}

void UMGPlayerWidget::StageEnd()
{
	PlayAnimation(FadeOutAnimation);
}

void UMGPlayerWidget::PlayChangeWeaponMode()
{
	if (!PlayerChacracter->IsChargeFireMode())
		PlayAnimation(NormalWeaponAnimation);

	else
		PlayAnimation(ChargeWeaponAnimation);
}

void UMGPlayerWidget::PlayChargeReady()
{
	PlayAnimation(ChargeReadyAnimation);
}

void UMGPlayerWidget::PlayChargeFire()
{
	PlayAnimation(ChargeFireAnimation);
}

void UMGPlayerWidget::SetPlayerDeathWidget()
{
	PlayAnimation(PlayerDeadAnimation);
}

void UMGPlayerWidget::SetPlayerStatus(const FMGPlayerDataTable* DataTable)
{
	HPCurrent = DataTable->HP;
	HPMax = DataTable->HPMax;
	ECoolTime = DataTable->mapSkill.Find(FName("ESkill"))->CoolTime;
	QCoolTime = DataTable->mapSkill.Find(FName("QSkill"))->CoolTime;
	DashCoolTime = DataTable->mapSkill.Find(FName("Dash"))->CoolTime;
	ChargeGaugeMax = DataTable->mapSkill.Find(FName("ChargeGauge"))->CoolTime;
	CurrentMissile = *DataTable->mapSkill.Find(FName("QSkill"))->AdditionalProperty.Find(FName("MaxMissile"));
	MissileMax = CurrentMissile;
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

	HPBar = Cast<UProgressBar>(WidgetTree->FindWidget(TEXT("HPProgressBar")));
	HPSlider = Cast<USlider>(WidgetTree->FindWidget(TEXT("S_Shine")));
	MissileChargeBar = Cast<UProgressBar>(WidgetTree->FindWidget(TEXT("MissileProgressBar")));
	DroneChargeBar = Cast<UProgressBar>(WidgetTree->FindWidget(TEXT("DroneProgressBar")));
	DashChargeBar = Cast<UProgressBar>(WidgetTree->FindWidget(TEXT("DashProgressBar")));
	WeaponChargeBar = Cast<UProgressBar>(WidgetTree->FindWidget(TEXT("ChargeWeaponBar")));
	MissileCountText = Cast<UTextBlock>(WidgetTree->FindWidget(TEXT("MissileCount")));
	Fade = Cast<UImage>(WidgetTree->FindWidget(TEXT("FadeImage")));
	TitleButton = Cast<UButton>(WidgetTree->FindWidget(TEXT("PlayBackButton")));

	AMGPlayerController* PlayerController = Cast<AMGPlayerController>(GetOwningPlayer());
	PlayerChacracter = Cast<AMGPlayerCharacter>(PlayerController->GetPlayerCharacter());

	MissileCountText->SetText(FText::FromString(FString::FromInt(CurrentMissile)));

	TitleButton->OnReleased.AddDynamic(this, &UMGPlayerWidget::BacktoTitleCallback);
		
	FadeOutDelegateEnd.BindDynamic(this, &UMGPlayerWidget::PlayStageEndCallback);
	PlayerDeadDelegateEnd.BindDynamic(this, &UMGPlayerWidget::PlayerDiedCallback);

	BindToAnimationFinished(FadeOutAnimation, FadeOutDelegateEnd);
	BindToAnimationFinished(PlayerDeadAnimation, PlayerDeadDelegateEnd);

	PlayAnimation(ShineLoopAnimation, 0.0f, 0);
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
	QTimeLeft = PlayerChacracter->GetMissileChargeTimeAcc();
	DashTimeLeft = PlayerChacracter->GetDashChargeTimeAcc();
	ChargeGauge = PlayerChacracter->GetChargeShotGauge();
	CurrentMissile = PlayerChacracter->GetMissileCount();

	SetHPBar(HPCurrent);

	MissileChargeBar->SetPercent(QTimeLeft / QCoolTime);
	DroneChargeBar->SetPercent(ETimeLeft / ECoolTime);
	DashChargeBar->SetPercent(DashTimeLeft / DashCoolTime);
	WeaponChargeBar->SetPercent(ChargeGauge / ChargeGaugeMax);
	MissileCountText->SetText(FText::FromString(FString::FromInt(CurrentMissile)));

	
	if (WeaponChargeBar->Percent >= 1.0f && !IsAnimationPlaying(ChargeReadyAnimation))
		PlayAnimation(ChargeReadyAnimation, 0.0f, 0);

	else if (WeaponChargeBar->Percent < 1.0f)
		StopAnimation(ChargeReadyAnimation);
}

void UMGPlayerWidget::PlayStageEndCallback()
{
	PlayerChacracter->SetLifeSpan(0.3f);

	AMGPlayerController* PlayerController = PlayerChacracter->GetController<AMGPlayerController>();

	if (!PlayerController || !PlayerController->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("UMGPlayerWidget::PlayStageEndCallback() : PlayerController is error!!"));
		return;
	}

	PlayerController->SetCursor(true);

	PlayAnimation(LevelEndAnimation);
}

void UMGPlayerWidget::BacktoTitleCallback()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("LobbyLevel")));
}

void UMGPlayerWidget::PlayerDiedCallback()
{
	AMGPlayerController* PlayerController = PlayerChacracter->GetController<AMGPlayerController>();

	if (PlayerController && PlayerController->IsValidLowLevel())
	{
		PlayerController->SetCursor(true);
	}
}
