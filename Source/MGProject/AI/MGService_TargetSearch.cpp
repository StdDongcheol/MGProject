// Fill out your copyright notice in the Description page of Project Settings.


#include "MGService_TargetSearch.h"
#include "../MGEnemyController.h"
#include "../Character/MGEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UMGService_TargetSearch::UMGService_TargetSearch()
{
	NodeName = TEXT("Search Target");

	Interval = 0.1f;
}

void UMGService_TargetSearch::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AMGEnemyController* EnemyController = Cast<AMGEnemyController>(OwnerComp.GetAIOwner());
	AMGEnemyCharacter* EnemyCharacter = EnemyController->GetPawn<AMGEnemyCharacter>();

	float SeeRange = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(FName("DetectionRange"));

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetObject"));

	if (nullptr == Target)
	{
		// Target finded.
		Target = EnemyCharacter->FindTarget(FName(TEXT("Player")), SeeRange);

		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("TargetObject"), Target);
	}

	else
	{
		AActor* TargetActor = Cast<AActor>(Target);

		if (SeeRange < (TargetActor->GetActorLocation() - EnemyCharacter->GetActorLocation()).Size())
		{
			// Target is lost.
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("TargetObject"), nullptr);
		}
	}
}
