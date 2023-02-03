// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotifyState_AddMove.h"
#include "../Character/MGCharacter.h"

UMGAnimNotifyState_AddMove::UMGAnimNotifyState_AddMove()
{
}

void UMGAnimNotifyState_AddMove::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	AActor* Owner = MeshComp->GetOwner();
	AMGCharacter* Character = Cast<AMGCharacter>(Owner);

	if (!Character || !Character->IsValidLowLevel())
	{
		return;
	}
	
	FVector FwdVector = Character->GetActorForwardVector();
	Character->AddActorWorldOffset(FwdVector * Speed * FrameDeltaTime);
}
