// Fill out your copyright notice in the Description page of Project Settings.


#include "MGMissile.h"
#include "MGHitEffect.h"
#include "../Character/MGCharacter.h"
#include "../Character/MGEnemyCharacter.h"
#include "../MGBlueprintFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

AMGMissile::AMGMissile() 
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = Mesh;

	HitCollider = CreateDefaultSubobject<USphereComponent>(TEXT("HitCollider"));
	HitCollider->SetupAttachment(RootComponent);
	HitCollider->SetNotifyRigidBodyCollision(true);
	HitCollider->SetRelativeLocation(FVector(30.0f, 0.0f, 0.0f));
	HitCollider->OnComponentBeginOverlap.AddDynamic(this, &AMGMissile::OnCollisionEnter);

	DamageCollider = CreateDefaultSubobject<USphereComponent>(TEXT("DamageCollider"));
	DamageCollider->SetupAttachment(RootComponent);
	DamageCollider->SetNotifyRigidBodyCollision(true);

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MissileNiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent, TEXT("skeleton_grpSocket"));

	ParticleLegacy->SetupAttachment(RootComponent);
	ProjectileComponent->SetUpdatedComponent(RootComponent);
}

void AMGMissile::SetStatus(FName _CollisionName, USceneComponent* _TargetComponent,
	float _Damage, float _BoostTime, float _ForgetTime)
{
	HitCollider->SetCollisionProfileName(_CollisionName);
	DamageCollider->SetCollisionProfileName(_CollisionName);
	Mesh->SetCollisionProfileName(_CollisionName);

	Damage = _Damage;
	Target = _TargetComponent;
	BoostTime = _BoostTime;
	ForgetTime = _ForgetTime;

	if (_CollisionName == FName("PlayerAttack"))
	{
		SetForce(EObject_Force::Player);

		DamageCollider->SetSphereRadius(1000.0f);

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
		
		HitCollider->SetSphereRadius(HitCollider->GetScaledSphereRadius() * 2.f);
		DamageCollider->SetSphereRadius(HitCollider->GetScaledSphereRadius() * 4.f);

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

	if (OtherCharacter->GetStatus() & ECharacter_Status::Dodge)
		return;

	TArray<TObjectPtr<AActor>> OverlappingActorArr;
	TArray<TObjectPtr<AActor>> OverlappingActorArr2;

	DamageCollider->GetOverlappingActors(OverlappingActorArr);

	FName CollisionProfile = _OtherComp->GetCollisionProfileName();

	for (AActor* TargetActor : OverlappingActorArr)
	{
		AMGCharacter* TargetEnemy = Cast<AMGCharacter>(TargetActor);
		
		if (!TargetEnemy || !TargetEnemy->IsValidLowLevel())
			continue;

		FName TargetProfileName = TargetEnemy->GetCapsuleComponent()->GetCollisionProfileName();

		if (TargetProfileName == CollisionProfile)
		{
			TArray<TObjectPtr<UActorComponent>> CollisionComponents;

			CollisionComponents = TargetEnemy->GetComponentsByTag(UPrimitiveComponent::StaticClass(), TEXT("WeakPoint"));

			bool IsWeakPoint = CollisionComponents.IsEmpty() ? false : true;

			TargetEnemy->SetStatus(ECharacter_Status::Damaged);
			TargetEnemy->SetDamage(-Damage, IsWeakPoint);
		}
	}

	Destroy();
}

