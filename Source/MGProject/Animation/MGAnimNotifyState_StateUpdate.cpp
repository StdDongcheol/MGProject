// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotifyState_StateUpdate.h"
#include "../Character/MGCharacter.h"

void UMGAnimNotifyState_StateUpdate::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AMGCharacter* PlayerCharacter = MeshComp->GetOwner<AMGCharacter>();

	if (!PlayerCharacter || !PlayerCharacter->IsValidLowLevel())
		return;

	PlayerCharacter->GetAnimInst()->SetFire(false);
	
	return;
}
