// Fill out your copyright notice in the Description page of Project Settings.


#include "MGEnemyController.h"
#include "Character/MGEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void AMGEnemyController::OnPossess(APawn* _Mon)
{
	Super::OnPossess(_Mon);
	
	AMGEnemyCharacter* EnemyCharacter = Cast<AMGEnemyCharacter>(_Mon);
	const struct FMGEnemyStatusDataTable* EnemyData = EnemyCharacter->InitEnemyData();

	if (EnemyData)
	{
		GetBlackboardComponent()->SetValueAsFloat(TEXT("DetectionRange"), EnemyData->DetectionRange);
		GetBlackboardComponent()->SetValueAsFloat(TEXT("AttackRange"), EnemyData->AttackRange);
	}

}
