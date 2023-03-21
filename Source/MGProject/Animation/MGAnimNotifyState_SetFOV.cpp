// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotifyState_SetFOV.h"
#include "Camera/CameraComponent.h"

UMGAnimNotifyState_SetFOV::UMGAnimNotifyState_SetFOV()
{
}

void UMGAnimNotifyState_SetFOV::NotifyBegin(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}


void UMGAnimNotifyState_SetFOV::NotifyTick(USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	AActor* Owner = MeshComp->GetOwner();

	if (!Owner || !Owner->IsValidLowLevel())
		return;

	UCameraComponent* CamComponent = Owner->FindComponentByClass<UCameraComponent>();
	
	if (!CamComponent || !CamComponent->IsValidLowLevel())
		return;
	
	float DeltaFOV = FMath::FInterpTo(CamComponent->FieldOfView, TargetFOVValue, FrameDeltaTime, FOVSpeed);

	CamComponent->SetFieldOfView(DeltaFOV);
}

void UMGAnimNotifyState_SetFOV::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ResetFOV)
	{
		AActor* Owner = MeshComp->GetOwner();

		if (!Owner || !Owner->IsValidLowLevel())
			return;

		UCameraComponent* CamComponent = Owner->FindComponentByClass<UCameraComponent>();

		if (!CamComponent || !CamComponent->IsValidLowLevel())
			return;

		CamComponent->SetFieldOfView(90.0f);
	}
}
