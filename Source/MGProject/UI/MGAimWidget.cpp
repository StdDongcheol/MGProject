

#include "MGAimWidget.h"
#include "../MGPlayerController.h"

void UMGAimWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMGAimWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UMGAimWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = Cast<AMGPlayerController>(GetOwningPlayer());

	ActivateScopeStartDelegate.BindDynamic(this, &UMGAimWidget::ScopeActivateStart);
	ActivateScopeEndDelegate.BindDynamic(this, &UMGAimWidget::ScopeActivateEnd);

	BindToAnimationStarted(ActivateScope, ActivateScopeStartDelegate);
	BindToAnimationFinished(ActivateScope, ActivateScopeEndDelegate);

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

void UMGAimWidget::ScopeActivateEnd()
{
	if (PlayerController)
		PlayerController->GetPlayerCharacter()->SetQSkillCollision(true);
}
