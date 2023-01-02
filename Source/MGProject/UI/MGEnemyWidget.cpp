// Fill out your copyright notice in the Description page of Project Settings.


#include "MGEnemyWidget.h"

void UMGEnemyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMGEnemyWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UMGEnemyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TargetingEndDelegate.BindDynamic(this, &UMGEnemyWidget::TargetingEnded);

	BindToAnimationFinished(TargetingAnimation, TargetingEndDelegate);
}

void UMGEnemyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Visibility == ESlateVisibility::SelfHitTestInvisible)
	{
		if(!IsAnimationPlaying(TargetingAnimation) && !IsLocked)
			PlayAnimation(TargetingAnimation);
	}
}

void UMGEnemyWidget::TargetingEnded()
{
	IsLocked = true;
}
