// Fill out your copyright notice in the Description page of Project Settings.


#include "MGEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "../UI/MGEnemyWidget.h"
#include "../Animation/MGEnemyAnimInstance.h"

AMGEnemyCharacter::AMGEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Tags.Add("Enemy");

	CapsuleComponent->SetCollisionProfileName(FName("Enemy"));

	TargetingWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Lockon Widget"));
	TargetingWidgetComponent->SetupAttachment(RootComponent);
	TargetingWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	IsTargetLock = false;
}

UBehaviorTree* AMGEnemyCharacter::GetBehaviorTree() const
{
	return BehaviorTree;
}

UBlackboardData* AMGEnemyCharacter::GetBlackboardData() const
{
	return BlackboardData;
}
	
void AMGEnemyCharacter::SetLockonWidget(bool bEnable)
{	
	TargetingWidgetComponent->SetVisibility(bEnable);

	if (!bEnable)
	{
		if (EnemyWidget || EnemyWidget->IsValidLowLevel())
			EnemyWidget->SetTargetLock(false);
	}
}

const FMGEnemyStatusDataTable* AMGEnemyCharacter::InitEnemyData()
{
	return nullptr;
}

void AMGEnemyCharacter::SetDamage(float _Damage, bool _IsWeakpoint)
{
	Super::SetDamage(_Damage, _IsWeakpoint);

	if (HP <= 0.0f)
	{
		SetLifeSpan(5.0f);
		GetAnimInst<UMGEnemyAnimInstance>()->SetAIAnimState(EAIAnimState::Death);
	}
}

void AMGEnemyCharacter::SetAppearance(float _DeltaTime)
{
	AppearanceTimeAcc -= _DeltaTime;

	const float AppearanceValue = AppearanceTimeAcc / AppearanceTime;
	
	GetMesh()->SetScalarParameterValueOnMaterials(TEXT("Appearance"), AppearanceValue);
}

void AMGEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	EnemyWidget = Cast<UMGEnemyWidget>(TargetingWidgetComponent->GetWidget());
	
	TargetingWidgetComponent->SetVisibility(false);
	AppearanceTimeAcc = AppearanceTime;
}

void AMGEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnemyWidget)
		IsTargetLock = EnemyWidget->IsTargetLocked();

	if (GetAnimInst()->IsDead())
	{
		SetAppearance(DeltaTime);
	}
}
