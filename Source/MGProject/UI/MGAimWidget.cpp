

#include "MGAimWidget.h"

void UMGAimWidget::NativeOnInitialized()
{
	
}

void UMGAimWidget::NativePreConstruct()
{
}

void UMGAimWidget::NativeConstruct()
{
	ActivateScopeStartDelegate.BindDynamic(this, &UMGAimWidget::ScopeActivateStart);

	BindToAnimationStarted(ActivateScope, ActivateScopeStartDelegate);

	PlayAnimation(DecoAnimLoop_1, 0.0f, 0);
	PlayAnimation(DecoAnimLoop_2, 0.0f, 0);
}

void UMGAimWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Visibility == ESlateVisibility::Visible)
	{
		if (!ScopeActivated)
			PlayAnimation(ActivateScope);
	}
}

void UMGAimWidget::ScopeActivateStart()
{
	SetScopeActivate(true);
}
