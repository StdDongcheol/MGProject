// Fill out your copyright notice in the Description page of Project Settings.


#include "MGInteractionWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ProgressBar.h"
#include "Components/Slider.h"

void UMGInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	BindToAnimationStarted(PlayerOnAnimation, PlayerOnAnimStartDelegate);
	BindToAnimationStarted(PlayerOffAnimation, PlayerOffAnimStartDelegate);
	BindToAnimationStarted(PushingAnimation, KeyPushingAnimStartDelegate);
	BindToAnimationStarted(CompleteAnimation, CompleteAnimStartDelegate);

	InputProgressBar = Cast<UProgressBar>(WidgetTree->FindWidget(TEXT("PB_Base")));
	InputProgressSlider = Cast<USlider>(WidgetTree->FindWidget(TEXT("S_Shine")));
	IsProgressBarStart = false;
}

void UMGInteractionWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (InputProgressBar->Percent >= 1.0f && !IsProgressCompleted)
	{
		IsProgressCompleted = true;
		PlaySound(CompletedSound);
		PlayAnimation(CompleteAnimation);
	}
}

void UMGInteractionWidget::SetProgress(float Percent)
{
	InputProgressBar->SetPercent(Percent);
	InputProgressSlider->SetValue(Percent);

	if (IsProgressCompleted)
		return;

	if (Percent > 0.0f)
	{
		if (!IsProgressBarStart)
		{
			PlayAnimation(PushingAnimation);
			PlaySound(CalculatingSound);
			IsProgressBarStart = true;
		}
	}

	else if (Percent <= 0.0f) 
	{
		if (IsProgressBarStart)
		{
			PlayAnimation(PlayerOnAnimation);
			IsProgressBarStart = false;
		}
	}
}

void UMGInteractionWidget::SetPlayerOn(bool IsOnPlayer)
{
	if (IsProgressCompleted)
		return;
	
	if (IsOnPlayer)
		PlayAnimation(PlayerOnAnimation);

	else
		PlayAnimation(PlayerOffAnimation);
}
