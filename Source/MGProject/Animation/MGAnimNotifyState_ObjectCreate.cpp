// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotifyState_ObjectCreate.h"

void UMGAnimNotifyState_ObjectCreate::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	const FTransform MeshTransform = MeshComp->GetSocketTransform(SocketName);
	FVector3d Vec3d = MeshTransform.GetLocation();
	FVector vector = Vec3d;

	AActor* Actor = MeshComp->GetWorld()->SpawnActor<AActor>(TargetActor, MeshTransform);
}
