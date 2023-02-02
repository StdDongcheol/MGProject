// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotifyState_SetAIAnimState.h"
#include "../Character/MGEnemyCharacter.h"
#include "../MGBlueprintFunctionLibrary.h"
#include "MGEnemyAnimInstance.h"

void UMGAnimNotifyState_SetAIAnimState::NotifyBegin(USkeletalMeshComponent* MeshComp, 
	UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	
	AMGEnemyCharacter* EnemyCharacter = Cast<AMGEnemyCharacter>(MeshComp->GetOwner());

	if (!EnemyCharacter || !EnemyCharacter->IsValidLowLevel())
		return;

	UMGEnemyAnimInstance* AnimInst = EnemyCharacter->GetAnimInst<UMGEnemyAnimInstance>();

	if (!AnimInst || !AnimInst->IsValidLowLevel())
	{
		return;
	}

	AnimInst->SetAIAnimState(AnimState);
}
