

#pragma once

#include "CoreMinimal.h"
#include "MGUserWidget.h"
#include "MGAimWidget.generated.h"


UCLASS()
class MGPROJECT_API UMGAimWidget : public UMGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* ActivateScope;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* DecoAnimLoop_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* DecoAnimLoop_2;

private:
	FWidgetAnimationDynamicEvent ActivateScopeStartDelegate;

private:
	bool	ScopeActivated;

public:
	void SetScopeActivate(bool bEnable)
	{
		ScopeActivated = bEnable;
	}

	bool IsScopeActivated() const
	{
		return ScopeActivated;
	}

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UFUNCTION()
	void ScopeActivateStart();
};
