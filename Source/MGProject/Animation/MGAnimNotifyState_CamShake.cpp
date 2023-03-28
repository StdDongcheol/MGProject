// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotifyState_CamShake.h"
#include "Camera/CameraShakeSourceActor.h"
#include "Camera/CameraShakeSourceComponent.h"
#include "Camera/CameraShakeBase.h"

void UMGAnimNotifyState_CamShake::NotifyBegin(USkeletalMeshComponent* MeshComp, 
	UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AActor* Owner = MeshComp->GetOwner();

	if (!Owner || !Owner->IsValidLowLevel())
		return;

	const FTransform ActorTransform = Owner->GetActorTransform();

	if (!ShakeBase || !ShakeBase->IsValidLowLevel())
		return;
	
	float LifeTimer = ShakeBase.GetDefaultObject()->GetCameraShakeDuration().Get();
	
	ACameraShakeSourceActor* SpawnedShakeActor = MeshComp->GetWorld()->SpawnActorDeferred<ACameraShakeSourceActor>(ShakeActor, ActorTransform);
	
	UCameraShakeSourceComponent* ShakeComp = SpawnedShakeActor->GetCameraShakeSourceComponent();
	ShakeComp->CameraShake = ShakeBase;
	ShakeComp->bAutoStart = true;
	
	if (WorldShake)
	{
		ShakeComp->InnerAttenuationRadius = 99999.f;
		ShakeComp->OuterAttenuationRadius = 99999.f;
	}

	SpawnedShakeActor->SetLifeSpan(LifeTimer);

	SpawnedShakeActor->FinishSpawning(ActorTransform);

	if (AttactToActor)
		SpawnedShakeActor->AttachToActor(Owner, FAttachmentTransformRules::KeepWorldTransform, SocketName);

}
