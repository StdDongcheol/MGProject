// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotifyState_ObjectCreate.h"
#include "UObject/Class.h"
#include "MGPlayerAnimInstance.h"
#include "BehaviorTree/BlackboardData.h"
#include "../Character/MGCharacter.h"
#include "../Character/MGPlayerCharacter.h"
#include "../Character/MGEnemyCharacter.h"
#include "../Projectile/MGProjectile.h"
#include "../Projectile/MGBullet.h"
#include "../Projectile/MGMissile.h"
#include "../Projectile/MGPlayerDrone.h"

void UMGAnimNotifyState_ObjectCreate::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AActor* Owner = MeshComp->GetOwner();

	AMGCharacter* Character = Cast<AMGCharacter>(Owner);

	if (!Character || !Character->IsValidLowLevel())
		return;
	
	if (Character->ActorHasTag(TEXT("Player")))
	{
		AMGPlayerCharacter* PlayerCharacter = Cast<AMGPlayerCharacter>(Character);
		float Pitch = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetAimRot().Pitch;

		const FTransform MeshTransform = MeshComp->GetSocketTransform(SocketName);

		FVector SpawnPosition = MeshTransform.GetLocation() + SpawnOffset;

		FRotator SpawnRotation = MeshTransform.Rotator();
		SpawnRotation.Pitch = Pitch;


		EPlayer_BodyAction BodyAction = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetBodyActionState();

		switch (BodyAction)
		{
		case EPlayer_BodyAction::NormalFire:
		{
			FVector HitPos = PlayerCharacter->GetTrace();

			FVector Dir = HitPos - SpawnPosition;
			FRotator Rot = Dir.Rotation();

			AMGBullet* Bullet = MeshComp->GetWorld()->SpawnActor<AMGBullet>(TargetActor, SpawnPosition, Rot);
			Bullet->SetBulletProfile(TEXT("PlayerAttack"));
			break;
		}
		case EPlayer_BodyAction::QFire:
		{
			AMGMissile* Missile = MeshComp->GetWorld()->SpawnActor<AMGMissile>(TargetActor, SpawnPosition, SpawnRotation);

			if (!Missile || !Missile->IsValidLowLevel())
				return;

			Missile->SetTarget(PlayerCharacter->GetTarget());
			break;
		}
		case EPlayer_BodyAction::EThrowing:
		{
			FVector DeployPos = PlayerCharacter->GetDroneDeployPosition();

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

	else if (Character->ActorHasTag(TEXT("Enemy")))
	{
		AMGEnemyCharacter* EnemyCharacter = Cast<AMGEnemyCharacter>(Character);

		const FTransform MeshTransform = MeshComp->GetSocketTransform(SocketName);

		FVector SpawnPosition = MeshTransform.GetLocation() + SpawnOffset;
		FRotator SpawnRotation = MeshTransform.Rotator();

		AActor* PlayerActor = EnemyCharacter->FindTarget("Player", EnemyCharacter->GetDetectRange());

		if (PlayerActor)
		{
			FVector PlayerPos = PlayerActor->GetActorLocation();
			FVector Dir = PlayerPos - SpawnPosition;
			FRotator Rot = Dir.Rotation();

			AMGBullet* Bullet = MeshComp->GetWorld()->SpawnActor<AMGBullet>(TargetActor, SpawnPosition, Rot);

			if (Bullet)
				Bullet->SetBulletProfile(TEXT("EnemyAttack"));
		}
	}

}
