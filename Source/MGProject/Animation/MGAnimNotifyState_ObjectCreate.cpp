// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotifyState_ObjectCreate.h"
#include "UObject/Class.h"
#include "../Character/MGCharacter.h"
#include "../Character/MGPlayerCharacter.h"
#include "../Projectile/MGProjectile.h"
#include "../Projectile/MGBullet.h"
#include "../Projectile/MGMissile.h"

void UMGAnimNotifyState_ObjectCreate::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AActor* Owner = MeshComp->GetOwner();

	AMGPlayerCharacter* Character = Cast<AMGPlayerCharacter>(Owner);

	if (!Character || !Character->IsValidLowLevel())
		return;
	
	float Pitch = Character->GetAnimInst()->GetAimRot().Pitch;

	const FTransform MeshTransform = MeshComp->GetSocketTransform(SocketName);

	FVector Vector = MeshTransform.GetLocation() + SpawnOffset;
	FRotator Rotator = MeshTransform.Rotator();

	Rotator.Pitch = Pitch;

	
	ECharacter_BodyAction BodyAction = Character->GetAnimInst()->GetBodyActionState();

	switch (BodyAction)
	{
	case ECharacter_BodyAction::NormalFire:
	{
		AActor* Actor = MeshComp->GetWorld()->SpawnActor<AActor>(TargetActor, Vector, Rotator);
		break;
	}
	case ECharacter_BodyAction::QFire:
	{	
		AMGProjectile* Actor = MeshComp->GetWorld()->SpawnActor<AMGProjectile>(TargetActor, Vector, Rotator);
		AMGMissile* Missile = Cast<AMGMissile>(Actor);

		if (!Missile || !Missile->IsValidLowLevel())
			return;
		
		Missile->SetTarget(Character->GetTarget());	
		break;
	}
	case ECharacter_BodyAction::RThrowing:
		break;
	default:
		break;
	}


}
