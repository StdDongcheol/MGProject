// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotifyState_SetAction.h"
#include "Components/CapsuleComponent.h"
#include "MGPlayerAnimInstance.h"
#include "../Character/MGPlayerCharacter.h"

void UMGAnimNotifyState_SetAction::NotifyBegin(USkeletalMeshComponent* MeshComp, 
	UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	UMGPlayerAnimInstance* AnimInst = Cast<UMGPlayerAnimInstance>(MeshComp->GetAnimInstance());

	if (!AnimInst || !AnimInst->IsValidLowLevel())
		return;

	AnimInst->SetActionState(PlayerAction);
}
