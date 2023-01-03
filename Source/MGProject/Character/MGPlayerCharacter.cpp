// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "MGEnemyCharacter.h"

AMGPlayerCharacter::AMGPlayerCharacter()
{
	Capsule->SetCollisionProfileName(FName("Player"));

	BoxRoot = CreateDefaultSubobject<USceneComponent>("QAimSceneComponent");
	BoxRoot->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("QBoxColliderComponent");
	BoxCollision->SetupAttachment(BoxRoot);
	BoxCollision->SetCollisionProfileName(FName("PlayerAttack"));
	BoxCollision->AddLocalOffset(FVector(-300.f, 0.f, 0.f));

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AMGPlayerCharacter::QSkillOnCollisionEnter);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AMGPlayerCharacter::QSkillOnCollisionEnd);
}


void AMGPlayerCharacter::StateUpdate(float DeltaTime)
{
	Super::StateUpdate(DeltaTime);

	FRotator CharacterRot = GetVelocity().Rotation();
	FRotator AimRot = GetBaseAimRotation();

	FRotator RotValue = AimRot - CharacterRot;
	RotValue.Normalize();

	GetAnimInst()->SetMovementYaw(RotValue.Yaw);
	GetAnimInst()->SetAimRotation(AimRot);

	// Set QDetectBox rotation to Yaw AimRotation.
	FRotator BoxRot = FRotator(0.0f, AimRot.Yaw, 0.0f);
	BoxRoot->SetRelativeRotation(BoxRot);

	// Debugging QDetectBox
	if (BoxCollision && BoxRoot)
		DrawDebugBox(GetWorld(), BoxCollision->GetComponentLocation(), BoxCollision->GetScaledBoxExtent(), BoxRoot->GetComponentRotation().Quaternion(), FColor::Green);
}

void AMGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	ArmSpring = FindComponentByClass<USpringArmComponent>();
	BoxCollision = FindComponentByClass<UBoxComponent>();
	ParticleQEffect = FindComponentByClass<UParticleSystemComponent>();

	BoxCollision->SetBoxExtent(FVector(256.0f, 128.0f, 128.0f));

	SetQSkillCollision(false);
}


void AMGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AMGPlayerCharacter::SetQSkillCollision(bool bEnable)
{
	if (!bEnable)
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	else
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AMGPlayerCharacter::QSkillOnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
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

		TargetArray.Add(TargetEnemy);
		TargetEnemy->SetLockonWidget(true);
	}
}

void AMGPlayerCharacter::QSkillOnCollisionEnd(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex)
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
