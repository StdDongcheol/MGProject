// Fill out your copyright notice in the Description page of Project Settings.


#include "MGNormalAimWidget.h"
#include "../MGPlayerController.h"
#include "../MGBossController.h"
#include "../Character/MGEnemyBoss.h"
#include "../Character/MGCrunch.h"
#include "../Animation/MGPlayerAnimInstance.h"
#include "Kismet/GameplayStatics.h"

void UMGNormalAimWidget::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);

	switch (InVisibility)
	{
	case ESlateVisibility::Visible:
	{
		if (!IsAimActivated)
		{
			IsAimActivated = true;
			PlayAnimation(ActivateAnim);
		}
		break;
	}
	case ESlateVisibility::Hidden:
	{
		if (IsAimActivated)
		{
			IsAimActivated = false;
		}

		SetBossWeakpointWidget(false);
		break;
	}
	default:
		break;
	}
}

void UMGNormalAimWidget::SwtichAimWidget(bool ToCharge)
{
	if (ToCharge)
		PlayAnimation(SwitchAnim);

	else
		PlayAnimationReverse(SwitchAnim);
}

void UMGNormalAimWidget::SetBossWeakpointWidget(bool bEnable)
{
	AActor* BossActor = UGameplayStatics::GetActorOfClass(GetWorld(), AMGEnemyBoss::StaticClass());

	if (!BossActor || !BossActor->IsValidLowLevel())
		return;

	AMGEnemyBoss* EnemyBoss = Cast<AMGEnemyBoss>(BossActor);
	
	EnemyBoss->SetWeakpointEnable(bEnable);
}

void UMGNormalAimWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMGNormalAimWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UMGNormalAimWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = Cast<AMGPlayerController>(GetOwningPlayer());

	ActivateAimStartDelegate.BindDynamic(this, &UMGNormalAimWidget::ActivateAimStart);
	RecoilAnimStartDelegate.BindDynamic(this, &UMGNormalAimWidget::RecoilAnimStart);

	BindToAnimationStarted(ActivateAnim, ActivateAimStartDelegate);
	BindToAnimationStarted(RecoilAnim, RecoilAnimStartDelegate);

	IsAimActivated = false;
	IsPlayingRecoil = false;
}

void UMGNormalAimWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	EPlayer_BodyAction State = PlayerController->GetPlayerCharacter()->GetAnimInst<UMGPlayerAnimInstance>()->GetBodyActionState();

	switch (State)
	{
	case EPlayer_BodyAction::Ready:
	{
		if (IsPlayingRecoil)
		{
			IsPlayingRecoil = false;
		}
		break;
	}
	case EPlayer_BodyAction::NormalFire:
	{
		if (!IsPlayingRecoil)
		{
			PlayAnimation(RecoilAnim);
			IsPlayingRecoil = true;
		}
		break;
	}
	default:
		break;
	}

}

void UMGNormalAimWidget::ActivateAimStart()
{
}

void UMGNormalAimWidget::RecoilAnimStart()
{
	// need Screen Recoil start.
}
