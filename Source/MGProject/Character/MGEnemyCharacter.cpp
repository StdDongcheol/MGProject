// Fill out your copyright notice in the Description page of Project Settings.


#include "MGEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "../UI/MGEnemyWidget.h"

AMGEnemyCharacter::AMGEnemyCharacter()
{
	Capsule->SetCollisionProfileName(FName("Enemy"));

	TargetingWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Lockon Widget"));
	TargetingWidgetComponent->SetupAttachment(RootComponent);

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
		if (EnemyWidget && EnemyWidget->IsValidLowLevel())
			EnemyWidget->SetTargetLock(false);
	}
}

void AMGEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	EnemyWidget = Cast<UMGEnemyWidget>(TargetingWidgetComponent->GetWidget());
	
	TargetingWidgetComponent->SetVisibility(false);
}

void AMGEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	IsTargetLock = EnemyWidget->IsTargetLocked();
}
