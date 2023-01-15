// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAIController.h"
#include "Character/MGEnemyCharacter.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

void AMGAIController::OnPossess(APawn* _Mon)
{
	Super::OnPossess(_Mon);

	AMGEnemyCharacter* EnemyCharacter = Cast<AMGEnemyCharacter>(_Mon);

	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	UseBlackboard(EnemyCharacter->GetBlackboardData(), BlackboardComponent);
	RunBehaviorTree(EnemyCharacter->GetBehaviorTree());
}
