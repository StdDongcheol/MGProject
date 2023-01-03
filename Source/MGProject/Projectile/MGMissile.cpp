// Fill out your copyright notice in the Description page of Project Settings.


#include "MGMissile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AMGMissile::AMGMissile()
{
	Mesh->SetCollisionProfileName(FName("PlayerAttack"));
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AMGMissile::OnCollisionEnter);
}

void AMGMissile::BeginPlay()
{
	Super::BeginPlay();
}

void AMGMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMGMissile::OnCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit)
{
}
