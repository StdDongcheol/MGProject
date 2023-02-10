// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotifyState_SetRagdoll.h"
#include "../Character/MGCharacter.h"

void UMGAnimNotifyState_SetRagdoll::NotifyBegin(USkeletalMeshComponent* MeshComp, 
	UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AMGCharacter* Character = Cast<AMGCharacter>(MeshComp->GetOwner());

	MeshComp->SetAllBodiesBelowSimulatePhysics(TEXT("root"), true);
	MeshComp->SetAllBodiesBelowPhysicsBlendWeight(TEXT("root"), 1.0f);
}
