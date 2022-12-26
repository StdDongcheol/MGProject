// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotifyState_ObjectCreate.h"
#include "UObject/Class.h"
#include "../Character/MGCharacter.h"

void UMGAnimNotifyState_ObjectCreate::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AActor* Owner = MeshComp->GetOwner();


	AMGCharacter* Character = Cast<AMGCharacter>(Owner);

	if (!Character || !Character->IsValidLowLevel())
		return;
	
	float Pitch = Character->GetAnimInst()->GetAimRot().Pitch;

	const FTransform MeshTransform = MeshComp->GetSocketTransform(SocketName);

	FVector Vector = MeshTransform.GetLocation();
	FRotator Rotator = MeshTransform.Rotator();

	Rotator.Pitch = Pitch;

	AActor* Actor = MeshComp->GetWorld()->SpawnActor<AActor>(TargetActor, Vector, Rotator);
}
