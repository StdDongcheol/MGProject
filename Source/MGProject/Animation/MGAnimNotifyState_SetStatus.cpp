// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotifyState_SetStatus.h"
#include "Components/CapsuleComponent.h"
#include "../Character/MGCharacter.h"

void UMGAnimNotifyState_SetStatus::NotifyBegin(USkeletalMeshComponent* MeshComp, 
	UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	UMGAnimInstance* AnimInst = Cast<UMGAnimInstance>(MeshComp->GetAnimInstance());

	if (!AnimInst || !AnimInst->IsValidLowLevel())
		return;

	if (CharacterStatus == ECharacter_Status::Normal)
	{
		AMGCharacter* Character = Cast<AMGCharacter>(MeshComp->GetOwner());
		Character->GetCapsuleComponent()->SetSimulatePhysics(false);
	}

	AnimInst->SetStatus(CharacterStatus);
}
