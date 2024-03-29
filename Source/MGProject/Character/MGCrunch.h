// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGEnemyBoss.h"
#include "../Component/MGWeakComponent.h"
#include "MGCrunch.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGCrunch : public AMGEnemyBoss
{
	GENERATED_BODY()

public:
	AMGCrunch();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* DamageBoxLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* DamageBoxRight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* WeakBoxHead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* WeakBoxBack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* WeakHeadWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* WeakBackWidget;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* JetParticleComponent;

public:
	virtual const FMGEnemyStatusDataTable* InitEnemyData() override;
	virtual void SetDamage(float _Damage, bool _IsWeakpoint = false) override;

private:
	void WeakpointHit(float _Damage);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void OnDamageCollisionEnter(UPrimitiveComponent* _pComponent, AActor* _pOtherActor, UPrimitiveComponent* _OtherComp,
	int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _Hit);

};
