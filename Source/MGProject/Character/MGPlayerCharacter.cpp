// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPlayerCharacter.h"
#include "MGEnemyCharacter.h"
#include "../MGPlayerController.h"
#include "../Animation/MGPlayerAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Camera/CameraComponent.h"

AMGPlayerCharacter::AMGPlayerCharacter() :
	MissileMaxCount(10),
	MissileCount(10),
	MissileChargeTime(5.0f),
	MissileChargeTimeAcc(0.0f),
	DroneChargeTime(20.0f),
	DroneChargeTimeAcc(0.0f),
	DashChargeTime(1.0f),
	DashChargeTimeAcc(0.0f),
	ChargeShotGauge(300.0f),
	ChargeShotGaugeMax(300.0f)
{
	Tags.Add(TEXT("Player"));

	CapsuleComponent->SetCollisionProfileName(FName("Player"));
	CapsuleComponent->OnComponentHit.AddDynamic(this, &AMGPlayerCharacter::OnCollisionGroundHit);

	BoxRoot = CreateDefaultSubobject<USceneComponent>("QAimSceneComponent");
	BoxRoot->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("QBoxColliderComponent");
	BoxCollision->SetupAttachment(BoxRoot);
	BoxCollision->SetCollisionProfileName(FName("PlayerAttack"));
	BoxCollision->AddLocalOffset(FVector3d(-300.0f, 0.0f, 0.0f));
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DroneDeployParticle = CreateDefaultSubobject<UParticleSystemComponent>("DroneDeploy");
	DroneDeployParticle->SetupAttachment(RootComponent);
	DroneDeployParticle->SetRelativeRotation(FRotator3d(90.0f, 0.0f, 0.0f));
	
	ChargeParticle = CreateDefaultSubobject<UParticleSystemComponent>("ChargeParticle");
	ChargeParticle->SetupAttachment(GetMesh(), FName("Muzzle_01"));
	ChargeParticle->SetRelativeRotation(FRotator3d(90.0f, 0.0f, 0.0f));
	
	BackpackParticle = CreateDefaultSubobject<UParticleSystemComponent>("BackpackParticle");
	BackpackParticle->SetupAttachment(GetMesh(), FName("FX_piston_l"));
	BackpackParticle->SetRelativeRotation(FRotator3d(90.0f, 0.0f, 0.0f));

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AMGPlayerCharacter::QSkillOnCollisionEnter);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AMGPlayerCharacter::QSkillOnCollisionEnd);
}

void AMGPlayerCharacter::UseChargeShot()
{
	ChargeShotGauge = 0.0f;
	IsChargeReady = false;
	ChargeParticle->Deactivate();
	BackpackParticle->Deactivate();
}

void AMGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	ArmSpring = FindComponentByClass<USpringArmComponent>();
	BoxCollision = FindComponentByClass<UBoxComponent>();
	Camera = FindComponentByClass<UCameraComponent>();
	DroneDeployParticle = FindComponentByClass<UParticleSystemComponent>();

	BoxCollision->SetBoxExtent(FVector(3000.0f, 1000.0f, 128.0f));
	BoxCollision->AddRelativeLocation(FVector(-1500.0f, 0.0f, 0.0f));

	DroneDeployParticle->SetVisibility(false);

	ChargeParticle->Deactivate();
	BackpackParticle->Deactivate();

	SetQSkillCollision(false);

	// PlayerAnim setting start
	GetAnimInst<UMGPlayerAnimInstance>()->AddQAnimLoopCount(MissileCount);

	// Character status setting start
	HPMax = 100.0f;
	HP = HPMax;
	MinAttack = 10.0f;
	MaxAttack = 20.0f;
	MoveSpeed = 1.0f;
	IsDroneDeployable = true;
	IsDashReady = true;
	IsChargeReady = true;
}


void AMGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ActionStateUpdate(DeltaTime);
}

void AMGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

int AMGPlayerCharacter::GetMissileCount() const
{
	return MissileCount;
}

int AMGPlayerCharacter::GetMissileCount(int UsingCount)
{
	if (MissileCount - UsingCount < 0)
		return 0;

	else
	{
		MissileCount -= UsingCount;

		return MissileCount;
	}
}

USceneComponent* AMGPlayerCharacter::GetTarget() const
{
	int Index = GetAnimInst<UMGPlayerAnimInstance>()->GetCurrentQCount() % TargetArray.Num();
	
	return TargetArray[Index]->GetRootComponent();
}

FHitResult AMGPlayerCharacter::GetTrace(FVector Pos, float TraceDistance, bool GetHitResult) const
{
	FHitResult Result;

	bool bHit = false;

	// 카메라 위치에서 Trace.
	if (Pos == FVector::ZeroVector)
	{
		FTransform CameraTransform = Camera->GetComponentTransform();
		
		FVector CameraPos = CameraTransform.GetLocation();
		
		FVector CameraForwardPos = CameraPos + (Camera->GetForwardVector() * TraceDistance);
		
		//DrawDebugLine(GetWorld(), CameraPos, CameraForwardPos, FColor::Red, false, 10.f, 0U, 2.f);

		bHit = GetWorld()->LineTraceSingleByChannel(Result, CameraPos, CameraForwardPos, ECollisionChannel::ECC_WorldDynamic);
		
		// Hit일 경우
		if (bHit && GetHitResult)
		{
			// Debugging log print start.
			AActor* HitActor = Result.GetActor(); 
			UE_LOG(LogTemp, Log, TEXT("Hit Target : %s"), *HitActor->GetName());
			// Debugging log print end.
		}

		// false의 경우, CameraForwardPos 위치를 반환.
		else
		{
			Result.ImpactPoint = CameraForwardPos;
		}
	}

	// 지정받은 위치에서 Trace
	else 
	{
		FVector TargetForwardPos = Pos + (Camera->GetForwardVector() * TraceDistance);

		//Debugging Line
		//DrawDebugLine(GetWorld(), CameraPos, CameraForwardPos, FColor::Red, false, 10.f, 0U, 2.f);

		bHit = GetWorld()->LineTraceSingleByChannel(Result, Pos, TargetForwardPos, ECollisionChannel::ECC_WorldDynamic);

		// Trace가 Hit일 경우
		if (bHit && GetHitResult)
		{
			// Debugging log print start.
			AActor* HitActor = Result.GetActor();
			UE_LOG(LogTemp, Log, TEXT("Hit Target : %s"), *HitActor->GetName());
			// Debugging log print end.
		}

		// false의 경우, CameraForwardPos 위치를 반환.
		else
		{
			Result.ImpactPoint = TargetForwardPos;
		}
	}

	
	return Result;
}

void AMGPlayerCharacter::AdjustHP(float _HP)
{
	Super::AdjustHP(_HP);

	if (HP <= 0.0f)
		GetController<AMGPlayerController>()->PlayerDeath();
}

void AMGPlayerCharacter::StateUpdate(float DeltaTime)
{
	Super::StateUpdate(DeltaTime);

	FRotator CharacterRot = GetVelocity().Rotation();
	FRotator AimRot = GetBaseAimRotation();

	FRotator RotValue = AimRot - CharacterRot;
	RotValue.Normalize();

	GetAnimInst<UMGPlayerAnimInstance>()->SetMovementYaw(RotValue.Yaw);
	GetAnimInst<UMGPlayerAnimInstance>()->SetAimRotation(AimRot);

	// Set QDetectBox rotation to Yaw AimRotation.
	FRotator BoxRot = FRotator(0.0f, AimRot.Yaw, 0.0f);
	BoxRoot->SetRelativeRotation(BoxRot);

	// Debugging QDetectBox
	//if (BoxCollision && BoxRoot)
	//	DrawDebugBox(GetWorld(), BoxCollision->GetComponentLocation(), BoxCollision->GetScaledBoxExtent(), BoxRoot->GetComponentRotation().Quaternion(), FColor::Green);

	// Missile Charge Start
	if (MissileCount < MissileMaxCount)
	{
		MissileChargeTimeAcc += DeltaTime;

		if (MissileChargeTimeAcc > MissileChargeTime)
		{
			MissileChargeTimeAcc -= MissileChargeTimeAcc;
			++MissileCount;

			// AnimInst 업데이트
			GetAnimInst<UMGPlayerAnimInstance>()->AddQAnimLoopCount(1);
		}
	}
	// Missile Charge End

	// Drone Charge start
	if (!IsDroneDeployable)
	{
		DroneChargeTimeAcc += DeltaTime;

		if (DroneChargeTimeAcc > DroneChargeTime)
		{
			DroneChargeTimeAcc -= DroneChargeTimeAcc;

			IsDroneDeployable = true;
		}
	}
	// Drone Charge end
	
	// Dash Charge start
	if (!IsDashReady)
	{
		DashChargeTimeAcc += DeltaTime;

		if (DashChargeTimeAcc > DashChargeTime)
		{
			DashChargeTimeAcc -= DashChargeTimeAcc;

			IsDashReady = true;
		}
	}
	// Drone Charge end


}

void AMGPlayerCharacter::ActionStateUpdate(float DeltaTime)
{
	EPlayer_ActionState CurrentState = GetAnimInst<UMGPlayerAnimInstance>()->GetActionState();

	switch (CurrentState)
	{
	case EPlayer_ActionState::None:
		break;
	case EPlayer_ActionState::Normal:
	{
		if (ChargeParticle->IsActive())
		{
			ChargeParticle->Deactivate(); 
			BackpackParticle->Deactivate();

			GetMesh()->SetScalarParameterValueOnMaterials(TEXT("EmissiveFresnelINT"), 0.2f);
		}
	}
		break;
	case EPlayer_ActionState::Aiming:
	{
		if (!ChargeParticle->IsActive() && IsChargeReady && ChargeFireMode)
		{
			ChargeParticle->Activate();
			BackpackParticle->Activate();
			GetMesh()->SetScalarParameterValueOnMaterials(TEXT("EmissiveFresnelINT"), 100.0f);
		}

		else if (!ChargeFireMode)
		{
			ChargeParticle->Deactivate();
			BackpackParticle->Deactivate();
			GetMesh()->SetScalarParameterValueOnMaterials(TEXT("EmissiveFresnelINT"), 0.2f);
		}
	}
		break;
	case EPlayer_ActionState::QAiming:
		break;
	case EPlayer_ActionState::EAiming:
	{
		ESkillTrace();
		break;
	}
	default:
		break;
	}
}

void AMGPlayerCharacter::ESkillTrace()
{
	FHitResult Result = GetTrace(FVector3d::ZeroVector, 1200.0f);

	if (Result.bStartPenetrating)
	{
		FVector3d HitPos = Result.ImpactPoint;
	
		HitPos += FVector3d(0.0f, 0.0f, 50.0f);

		DronePos = HitPos;
		DroneDeployParticle->SetWorldLocation(HitPos);
	}

	else
	{
		FVector3d NonHitPos = Result.ImpactPoint;
		FVector3d GroundPos = NonHitPos - FVector3d(0.0f, 0.0f, 1200.0f);

		FHitResult SecondHitResult;

		bool bSecondHit = GetWorld()->LineTraceSingleByChannel(SecondHitResult, NonHitPos, GroundPos, ECollisionChannel::ECC_WorldDynamic);

		if (bSecondHit)
		{
			NonHitPos.Z = SecondHitResult.ImpactPoint.Z + 50.0f;
			DronePos = NonHitPos;
			DroneDeployParticle->SetWorldLocation(NonHitPos);
		}

		else
		{
			DronePos = GroundPos;
			DroneDeployParticle->SetWorldLocation(GroundPos);
		}
	}
}

void AMGPlayerCharacter::SetQSkillCollision(bool bEnable)
{
	if (!bEnable)
	{
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	else
	{
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BoxCollision->SetCollisionProfileName(FName("PlayerAttack"));
	}
}

void AMGPlayerCharacter::QFireEnd()
{
	auto	iter = TargetArray.begin();
	auto	iterEnd = TargetArray.end();

	for (; iter != iterEnd; ++iter)
	{
		AMGEnemyCharacter* Enemy = Cast<AMGEnemyCharacter>(*iter);
		Enemy->SetLockonWidget(false);
	}

	// CameraArm Length 및 SocketOffset 조정
	ArmSpring->TargetArmLength = 250.0f;
	ArmSpring->SocketOffset = FVector(0.0f, 0.0f, 0.0f);

	TargetArray.Empty();
}

void AMGPlayerCharacter::SetChargeFireMode(bool bEnable)
{
	ChargeFireMode = bEnable;

	GetAnimInst<UMGPlayerAnimInstance>()->SetChargeMode(bEnable);
}

void AMGPlayerCharacter::AddAttackCharge(float ChargeValue)
{
	ChargeShotGauge += ChargeValue;

	if (ChargeShotGauge >= ChargeShotGaugeMax)
	{
		ChargeShotGauge = ChargeShotGaugeMax;

		IsChargeReady = true;
	}
}

void AMGPlayerCharacter::QSkillOnCollisionEnter(UPrimitiveComponent* _pComponent, 
	AActor* _pOtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, 
	bool _bFromSweep, const FHitResult& _Hit)
{
	UCapsuleComponent* Component = _pOtherActor->FindComponentByClass<UCapsuleComponent>();
	
	if (!Component || !Component->IsValidLowLevel())
		return;

	FName CollisionName = Component->GetCollisionProfileName();

	// Target acquired
	if (CollisionName == TEXT("Enemy"))
	{
		AMGEnemyCharacter* TargetEnemy = Cast<AMGEnemyCharacter>(_pOtherActor);

		if (!TargetEnemy || !TargetEnemy->IsValidLowLevel())
			return;

		else if (TargetEnemy->GetCurrentHP() <= 0.0f)
			return;

		TargetArray.Add(TargetEnemy);
		TargetEnemy->SetLockonWidget(true);
	}
}

void AMGPlayerCharacter::QSkillOnCollisionEnd(UPrimitiveComponent* _pComponent, 
	AActor* _pOtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex)
{
	UCapsuleComponent* Component = _pOtherActor->FindComponentByClass<UCapsuleComponent>();

	if (!Component || !Component->IsValidLowLevel())
		return;

	FName CollisionName = Component->GetCollisionProfileName();

	if (CollisionName == TEXT("Enemy"))
	{
		AMGEnemyCharacter* TargetEnemy = Cast<AMGEnemyCharacter>(_pOtherActor);

		if (!TargetEnemy || !TargetEnemy->IsValidLowLevel())
			return;

		EPlayer_BodyAction BodyState = GetAnimInst<UMGPlayerAnimInstance>()->GetBodyActionState();

		if (!(BodyState == EPlayer_BodyAction::QFire))
		{
			auto	iter = TargetArray.begin();
			auto	iterEnd = TargetArray.end();

			for (; iter != iterEnd; ++iter)
			{
				if ((*iter) == TargetEnemy)
				{
					TargetEnemy->SetLockonWidget(false);
					TargetArray.RemoveSingle(*iter);
					break;
				}
			}
		}
	}
	
}

void AMGPlayerCharacter::OnCollisionGroundHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FName OtherProfileName = OtherComp->GetCollisionProfileName();

	if (OtherProfileName == TEXT("WorldObject") || 
		OtherProfileName == TEXT("BlockAll"))
	{
		if (GetAnimInst()->GetStatus() & ECharacter_Status::KnockOut ||
			GetAnimInst<UMGPlayerAnimInstance>()->GetActionState() == EPlayer_ActionState::Dash)
		{
			GetAnimInst()->SetFalling(false);

			if (GetAnimInst<UMGPlayerAnimInstance>()->GetActionState() == EPlayer_ActionState::Dash)
			{
				GetAnimInst<UMGPlayerAnimInstance>()->SetActionState(EPlayer_ActionState::Normal);
				GetAnimInst()->SetStatus(ECharacter_Status::Normal);
				GetCapsuleComponent()->SetSimulatePhysics(false);

				GetMesh()->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
			}
		}
	}
}
