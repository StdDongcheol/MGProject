// Fill out your copyright notice in the Description page of Project Settings.


#include "MGBullet.h"
#include "MGHitEffect.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AMGBullet::AMGBullet()
{
	Mesh->SetCollisionProfileName(FName("PlayerAttack"));
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

void AMGBullet::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, 
	UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
	ProjectileComponent->StopSimulating(_Hit);
	
	AMGHitEffect* Effect = GetWorld()->SpawnActor<AMGHitEffect>(HitEffect, GetActorLocation(), GetActorRotation());

	Destroy();
}

