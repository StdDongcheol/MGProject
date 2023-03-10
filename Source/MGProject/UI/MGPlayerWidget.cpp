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

void UMGPlayerWidget::SetPlayerDeathWidget()
{
	PlayAnimation(PlayerDeadAnimation);
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
	HPSlider = Cast<USlider>(WidgetTree->FindWidget(TEXT("S_Shine")));
	MissileChargeBar = Cast<UProgressBar>(WidgetTree->FindWidget(TEXT("MissileProgressBar")));
	DroneChargeBar = Cast<UProgressBar>(WidgetTree->FindWidget(TEXT("DroneProgressBar")));
	MissileCountText = Cast<UTextBlock>(WidgetTree->FindWidget(TEXT("MissileCount")));
	Fade = Cast<UImage>(WidgetTree->FindWidget(TEXT("FadeImage")));
	TitleButton = Cast<UButton>(WidgetTree->FindWidget(TEXT("PlayBackButton")));

	HPCurrent = PlayerChacracter->GetCurrentHP();
	HPMax = PlayerChacracter->GetMaxHP();
	ETimeLeft = PlayerChacracter->GetDroneChargeTimeAcc();
	ECoolTime = PlayerChacracter->GetDroneChargeTime();
	QTimeLeft = PlayerChacracter->GetMissileChargeTimeAcc();
	QCoolTime = PlayerChacracter->GetMissileChargeTime();
	CurrentMissile = PlayerChacracter->GetMissileCount();
	MissileMax = PlayerChacracter->GetMissileMax();

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
