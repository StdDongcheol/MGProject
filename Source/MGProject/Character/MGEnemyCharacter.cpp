// Fill out your copyright notice in the Description page of Project Settings.


#include "MGEnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "../UI/MGEnemyWidget.h"

AMGEnemyCharacter::AMGEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Tags.Add("Enemy");

	Capsule->SetCollisionProfileName(FName("Enemy"));

	TargetingWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Lockon Widget"));
	TargetingWidgetComponent->SetupAttachment(RootComponent);

	TargetingWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FObjectFinder<UBlueprint> BPObject(TEXT("WidgetBlueprint'/Game/Play/UI/Enemy/WBP_EnemyWidget.WBP_EnemyWidget'")); // PATH is blueprint object path

	if (BPObject.Object)
	{
		TSubclassOf<UUserWidget> BPClass = BPObject.Object->GeneratedClass;

		TargetingWidgetComponent->SetWidgetClass(BPClass);
	}

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

const FMGEnemyStatusDataTable* AMGEnemyCharacter::InitEnemyData()
{
	return nullptr;
}

void AMGEnemyCharacter::AdjustHP(float _HP)
{
	Super::AdjustHP(_HP);
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

	if (EnemyWidget)
		IsTargetLock = EnemyWidget->IsTargetLocked();
}
