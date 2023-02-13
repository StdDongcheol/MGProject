// Fill out your copyright notice in the Description page of Project Settings.


#include "MGMissile.h"
#include "MGHitEffect.h"
#include "../Character/MGCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

AMGMissile::AMGMissile() 
{
	PrimaryActorTick.bCanEverTick = true;

	DamageCollider = CreateDefaultSubobject<USphereComponent>(TEXT("DamageCollider"));
	DamageCollider->SetupAttachment(RootComponent);
	DamageCollider->SetNotifyRigidBodyCollision(true);
	DamageCollider->SetRelativeLocation(FVector(30.0f, 0.0f, 0.0f));
	DamageCollider->OnComponentBeginOverlap.AddDynamic(this, &AMGMissile::OnCollisionEnter);
}

void AMGMissile::SetStatus(FName _CollisionName, USceneComponent* _TargetComponent,
	float _Damage, float _BoostTime, float _ForgetTime)
{
	DamageCollider->SetCollisionProfileName(_CollisionName);
	
	Damage = _Damage;
	target = _TargetComponent;
	BoostTime = _BoostTime;
	ForgetTime = _ForgetTime;

	if (_CollisionName == FName("PlayerAttack"))
	{
		ProjectileComponent->InitialSpeed = 1000.f;
		ProjectileComponent->MaxSpeed = 1500.f;
		ProjectileComponent->HomingAccelerationMagnitude = 35000.f;

		ProjectileComponent->HomingTargetComponent = target;
		ProjectileComponent->bIsHomingProjectile = true;
	}

	else if (_CollisionName == FName("EnemyAttack"))
	{
		ProjectileComponent->InitialSpeed = 500.f;
		ProjectileComponent->MaxSpeed = 5000.f;
		ProjectileComponent->HomingAccelerationMagnitude = 25000.f;
	}
}

void AMGMissile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileComponent->ProjectileGravityScale = 0.f;
	ProjectileComponent->bRotationFollowsVelocity = true;
	ProjectileComponent->bShouldBounce = true;

	MissileStateTimeAcc = 0.0f;
}

void AMGMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MissileStateTimeAcc += DeltaTime;

	if (!(MissileState & EMissile_State::Launch))
	{
		MissileState = MissileState | EMissile_State::Launch;

		ProjectileComponent->Velocity = RootComponent->GetForwardVector() * ProjectileComponent->InitialSpeed;
	}

	if (MissileStateTimeAcc >= BoostTime && !(MissileState & EMissile_State::Boost))
	{
		MissileStateTimeAcc -= MissileStateTimeAcc;

		MissileState = MissileState | EMissile_State::Boost;

		ProjectileComponent->HomingTargetComponent = target;
		ProjectileComponent->bIsHomingProjectile = true;
	}

	if (MissileStateTimeAcc >= ForgetTime &&
		(MissileState & EMissile_State::Boost) && 
		!(MissileState & EMissile_State::ForgetTarget))
	{
		MissileStateTimeAcc -= MissileStateTimeAcc;

		MissileState = MissileState | EMissile_State::ForgetTarget;

		ProjectileComponent->HomingTargetComponent = nullptr;
		ProjectileComponent->bIsHomingProjectile = false;
	}
}

void AMGMissile::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	FName OtherProfile = _OtherComp->GetCollisionProfileName();

	if (OtherProfile == "PlayerAttack" || OtherProfile == "EnemyAttack")
		return;

	AMGHitEffect* Effect = GetWorld()->SpawnActor<AMGHitEffect>(HitEffect, GetActorLocation(), GetActorRotation());
	Effect->SetStatus(3.0f);
	//
	AMGCharacter* OtherCharacter = Cast<AMGCharacter>(_pOtherActor);
	
	if (!OtherCharacter || !OtherCharacter->IsValidLowLevel())
	{
		Destroy();
		return;
	}
	
	OtherCharacter->AdjustHP(-Damage);
	OtherCharacter->SetStatus(ECharacter_Status::Damaged);
	
	Destroy();
}

