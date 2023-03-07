// Fill out your copyright notice in the Description page of Project Settings.


#include "MGMissile.h"
#include "MGHitEffect.h"
#include "../Character/MGCharacter.h"
#include "../MGBlueprintFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

AMGMissile::AMGMissile() 
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = Mesh;

	DamageCollider = CreateDefaultSubobject<USphereComponent>(TEXT("DamageCollider"));
	DamageCollider->SetupAttachment(RootComponent);
	DamageCollider->SetNotifyRigidBodyCollision(true);
	DamageCollider->SetRelativeLocation(FVector(30.0f, 0.0f, 0.0f));
	DamageCollider->OnComponentBeginOverlap.AddDynamic(this, &AMGMissile::OnCollisionEnter);

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MissileNiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent, TEXT("skeleton_grpSocket"));

	ParticleLegacy->SetupAttachment(RootComponent);
	ProjectileComponent->SetUpdatedComponent(RootComponent);
}

void AMGMissile::SetStatus(FName _CollisionName, USceneComponent* _TargetComponent,
	float _Damage, float _BoostTime, float _ForgetTime)
{
	DamageCollider->SetCollisionProfileName(_CollisionName);
	
	Damage = _Damage;
	Target = _TargetComponent;
	BoostTime = _BoostTime;
	ForgetTime = _ForgetTime;

	if (_CollisionName == FName("PlayerAttack"))
	{
		SetForce(EObject_Force::Player);

		ProjectileComponent->InitialSpeed = 1000.f;
		ProjectileComponent->MaxSpeed = 1500.f;
		ProjectileComponent->HomingAccelerationMagnitude = 35000.f;
		ProjectileComponent->HomingTargetComponent = Target;
		ProjectileComponent->bIsHomingProjectile = true;

		const FMGBulletDataTable* BulletTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetBulletData(TEXT("Missile"));
		const FHitParticleDataTable* ParticleTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetParticleData(TEXT("MissileParticle"));

		if (BulletTable && ParticleTable)
		{
			switch (BulletTable->ParticleType)
			{
			case EParticle_Type::None:
				break;
			case EParticle_Type::CascadeParticle:
				ParticleLegacy->SetTemplate(BulletTable->ProjectileEffect);
				break;
			case EParticle_Type::NiagaraParticle:
				NiagaraComponent->SetAsset(BulletTable->NiagaraParticle);
				break;
			default:
				break;
			}

			switch (ParticleTable->ParticleType)
			{
			case EParticle_Type::None:
				break;
			case EParticle_Type::CascadeParticle:
				HitEffect = ParticleTable->CascadeParticle;
				break;
			case EParticle_Type::NiagaraParticle:
				break;
			default:
				break;
			}

			HitSound = ParticleTable->HitSound;
		}
	}

	else if (_CollisionName == FName("EnemyAttack"))
	{
		SetForce(EObject_Force::Enemy);

		ProjectileComponent->InitialSpeed = 500.f;
		ProjectileComponent->MaxSpeed = 5000.f;
		ProjectileComponent->HomingAccelerationMagnitude = 25000.f;

		const FMGBulletDataTable* BulletTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetBulletData(TEXT("Missile"));
		const FHitParticleDataTable* ParticleTable = UMGBlueprintFunctionLibrary::GetMGGameInstance()->GetParticleData(TEXT("MissileParticle"));

		if (BulletTable && ParticleTable)
		{
			switch (BulletTable->ParticleType)
			{
			case EParticle_Type::None:
				break;
			case EParticle_Type::CascadeParticle:
				ParticleLegacy->SetTemplate(BulletTable->ProjectileEffect);
				break;
			case EParticle_Type::NiagaraParticle:
				NiagaraComponent->SetAsset(BulletTable->NiagaraParticle);
				break;
			default:
				break;
			}

			switch (ParticleTable->ParticleType)
			{
			case EParticle_Type::None:
				break;
			case EParticle_Type::CascadeParticle:
				HitEffect = ParticleTable->CascadeParticle;
				break;
			case EParticle_Type::NiagaraParticle:
				break;
			default:
				break;
			}

			HitSound = ParticleTable->HitSound;
		}
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

		ProjectileComponent->HomingTargetComponent = Target;
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


	AMGCharacter* Character = Target->GetOwner<AMGCharacter>();

	if (!Character || !Character->IsValidLowLevel())
		return;

	if (Character->GetCurrentHP() <= 0.0f)
	{
		ProjectileComponent->HomingTargetComponent = nullptr;
		ProjectileComponent->bIsHomingProjectile = false;
		
		bool IsFinded = FindNearTarget();
	}

}

bool AMGMissile::FindNearTarget()
{
	TArray<TObjectPtr<AActor>> Actors;
	
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("Enemy")), Actors);

	for (AActor* TargetActor : Actors)
	{
		AMGCharacter* TargetCharacter = Cast<AMGCharacter>(TargetActor);
		
		if (!TargetCharacter || !TargetCharacter->IsValidLowLevel())
			continue;

		if (TargetCharacter->GetCurrentHP() <= 0.0f)
			continue;

		ProjectileComponent->HomingTargetComponent = TargetCharacter->GetRootComponent();
		ProjectileComponent->bIsHomingProjectile = true;

		return true;
	}

	return false;
}

void AMGMissile::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, 
	UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	FName OtherProfile = _OtherComp->GetCollisionProfileName();

	switch (Force)
	{
	case EObject_Force::Player:
	{
		if (OtherProfile == "PlayerAttack" || 
			OtherProfile == "Player")
			return;
		break;
	}
	case EObject_Force::Enemy:
		if (OtherProfile == "EnemyAttack" || 
			OtherProfile == "Enemy")
			return;
		break;
	}
	
	AMGHitEffect* Effect = GetWorld()->SpawnActor<AMGHitEffect>(GetActorLocation(), GetActorRotation());
	Effect->SetActorScale3D(FVector(3.0f, 3.0f, 3.0f));
	Effect->SetParticle(HitEffect);
	Effect->SetSound(HitSound);
	Effect->SetStatus(3.0f);


	AMGCharacter* OtherCharacter = Cast<AMGCharacter>(_pOtherActor);
	
	if (!OtherCharacter || !OtherCharacter->IsValidLowLevel())
	{
		Destroy();
		return;
	}

	bool IsWeakPoint = _OtherComp->ComponentHasTag(TEXT("WeakPoint")) ? true : false;

	OtherCharacter->SetStatus(ECharacter_Status::Damaged);
	OtherCharacter->SetDamage(-Damage, IsWeakPoint);
	
	Destroy();
}

