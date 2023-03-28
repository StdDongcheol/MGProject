

#include "MGWeakpointWidget.h"


void UMGWeakpointWidget::WeakPlayAnimation()
{
	PlayAnimation(WeakpointAnimation, 0.0f, 0);
}

void UMGWeakpointWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMGWeakpointWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UMGWeakpointWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMGWeakpointWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}