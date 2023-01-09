// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotifyState_ObjectCreate.h"
#include "UObject/Class.h"
#include "../Character/MGCharacter.h"
#include "../Character/MGPlayerCharacter.h"
#include "../Projectile/MGProjectile.h"
#include "../Projectile/MGBullet.h"
#include "../Projectile/MGMissile.h"
#include "../Projectile/MGPlayerDrone.h"

void UMGAnimNotifyState_ObjectCreate::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AActor* Owner = MeshComp->GetOwner();

	AMGPlayerCharacter* Character = Cast<AMGPlayerCharacter>(Owner);

	if (!Character || !Character->IsValidLowLevel())
		return;
	
	float Pitch = Character->GetAnimInst()->GetAimRot().Pitch;

	const FTransform MeshTransform = MeshComp->GetSocketTransform(SocketName);

	FVector SpawnPosition = MeshTransform.GetLocation() + SpawnOffset;

	FRotator SpawnRotation = MeshTransform.Rotator();
	SpawnRotation.Pitch = Pitch;


	ECharacter_BodyAction BodyAction = Character->GetAnimInst()->GetBodyActionState();

	switch (BodyAction)
	{
	case ECharacter_BodyAction::NormalFire:
	{
		FVector HitPos = Character->GetTrace();
		
		FVector Dir = HitPos - SpawnPosition;
		FRotator Rot = Dir.Rotation();

		AMGBullet* Bullet = MeshComp->GetWorld()->SpawnActor<AMGBullet>(TargetActor, SpawnPosition, Rot);

		break;
	}
	case ECharacter_BodyAction::QFire:
	{	
		AMGMissile* Missile = MeshComp->GetWorld()->SpawnActor<AMGMissile>(TargetActor, SpawnPosition, SpawnRotation);

		if (!Missile || !Missile->IsValidLowLevel())
			return;
		
		Missile->SetTarget(Character->GetTarget());	
		break;
	}
	case ECharacter_BodyAction::EThrowing:
	{
		FVector DeployPos = Character->GetDroneDeployPosition();

		FVector Dir = DeployPos - SpawnPosition;
		FRotator Rot = Dir.Rotation();

		AMGPlayerDrone* Drone = MeshComp->GetWorld()->SpawnActor<AMGPlayerDrone>(TargetActor, SpawnPosition, Rot);

		if (!Drone || !Drone->IsValidLowLevel())
		{
			Drone->Destroy();
			return;
		}

		break;
	}
	default:
		break;
	}


}
