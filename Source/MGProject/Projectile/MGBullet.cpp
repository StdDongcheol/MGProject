// Fill out your copyright notice in the Description page of Project Settings.


#include "MGBullet.h"
#include "MGHitEffect.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AMGBullet::AMGBullet()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AMGBullet::OnCollisionEnter);
}

void AMGBullet::BeginPlay()
{
	Super::BeginPlay();
}
	
void AMGBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMGBullet::SetCollisionProfile(FName _Name)
{
	Mesh->SetCollisionProfileName(_Name);
}

void AMGBullet::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, 
	UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	ProjectileComponent->StopSimulating(_Hit);
	
	AMGHitEffect* Effect = GetWorld()->SpawnActor<AMGHitEffect>(HitEffect, GetActorLocation(), GetActorRotation());
	Effect->SetStatus(3.0f);

	Destroy();
}

