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
#include "../Projectile/MGLaser.h"
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

		const FTransform SocketTransform = MeshComp->GetSocketTransform(SocketName);
		
		FTransform SpawnTransform = SocketTransform;
		SpawnTransform.SetLocation(SocketTransform.GetLocation() + SpawnOffset);

		FVector SpawnPosition = SocketTransform.GetLocation() + SpawnOffset;


		EPlayer_BodyAction BodyAction = PlayerCharacter->GetAnimInst<UMGPlayerAnimInstance>()->GetBodyActionState();

		switch (BodyAction)
		{
		case EPlayer_BodyAction::NormalFire:
		{
			FHitResult Result = PlayerCharacter->GetTrace(FVector::ZeroVector, 2000.0f, false);
			FVector3d HitPos = Result.ImpactPoint;

			FVector Dir = HitPos - SpawnPosition;
			FRotator Rot = Dir.Rotation();
			SpawnTransform.SetRotation(Rot.Quaternion());

			AMGLaser* Laser = MeshComp->GetWorld()->SpawnActorDeferred<AMGLaser>(TargetActor, SpawnTransform);

			if (!Laser || !Laser->IsValidLowLevel())
				return;

			Laser->SetProfile(TEXT("PlayerAttack"), PlayerCharacter->GetMaxAttack());
			Laser->FinishSpawning(SpawnTransform);

			PlayerCharacter->GetMesh()->SetScalarParameterValueOnMaterials(TEXT("EmissiveFresnelINT"), 0.2f);
			break;
		}
		case EPlayer_BodyAction::RapidFire:
		{			
			FHitResult Result = PlayerCharacter->GetTrace();
			FVector3d HitPos = Result.ImpactPoint;

			FVector Dir = HitPos - SpawnPosition;
			FRotator Rot = Dir.Rotation();

			AMGBullet* Bullet = MeshComp->GetWorld()->SpawnActor<AMGBullet>(TargetActor, SpawnPosition, Rot);

			if (!Bullet || !Bullet->IsValidLowLevel())
				return;

			Bullet->SetBulletProfile(TEXT("PlayerAttack"), 9000.0f, PlayerCharacter->GetMinAttack());
			break;
		}
		case EPlayer_BodyAction::QFire:
		{
			AMGMissile* Missile = MeshComp->GetWorld()->SpawnActorDeferred<AMGMissile>(AMGMissile::StaticClass(), SocketTransform);

			if (!Missile || !Missile->IsValidLowLevel())
				return;
			
			Missile->SetActorScale3D(Missile->GetActorScale3D() / 5.0f);
			Missile->SetStatus(TEXT("PlayerAttack"), PlayerCharacter->GetTarget(), 
				PlayerCharacter->GetMinAttack(), 0.0f, 8.f);

			Missile->FinishSpawning(SocketTransform);
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

		FTransform SpawnTransform = FTransform(SpawnRotation, MeshTransform.GetLocation() + SpawnOffset, FVector::One());

		AActor* PlayerActor = EnemyCharacter->FindTarget("Player", EnemyCharacter->GetDetectRange());
		
		if (PlayerActor)
		{
			FVector PlayerPos = PlayerActor->GetActorLocation();
			FVector Dir = PlayerPos - SpawnPosition;
			FRotator Rot = Dir.Rotation();

			if (TargetActor->IsChildOf(AMGMissile::StaticClass()))
			{
				AMGMissile* Missile = MeshComp->GetWorld()->SpawnActorDeferred<AMGMissile>(TargetActor, SpawnTransform);

				if (!Missile || !Missile->IsValidLowLevel())
					return;

				Missile->SetStatus(TEXT("EnemyAttack"), PlayerActor->GetRootComponent(), 
					EnemyCharacter->GetMinAttack(), 0.40f, 0.30f);
				Missile->FinishSpawning(SpawnTransform);
			}

			else if (TargetActor->IsChildOf(AMGBullet::StaticClass()))
			{
				AMGBullet* Bullet = MeshComp->GetWorld()->SpawnActor<AMGBullet>(TargetActor, SpawnPosition, Rot);

				if (!Bullet || !Bullet->IsValidLowLevel())
					return;

				Bullet->SetBulletProfile(TEXT("EnemyAttack"), 3500.0f, EnemyCharacter->GetMinAttack());
			}
		}
	}

}
