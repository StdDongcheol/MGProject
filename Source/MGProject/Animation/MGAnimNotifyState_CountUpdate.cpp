// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotifyState_CountUpdate.h"
#include "../Character/MGPlayerCharacter.h"

void UMGAnimNotifyState_CountUpdate::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AActor* Owner = MeshComp->GetOwner();

	AMGPlayerCharacter* PlayerCharacter = Cast<AMGPlayerCharacter>(Owner);

	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;

	PlayerCharacter->GetAnimInst()->AddQCount(1);
}
