// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGEnemyCharacter.h"
#include "MGEnemyBoss.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API AMGEnemyBoss : public AMGEnemyCharacter
{
	GENERATED_BODY()

public:
	AMGEnemyBoss();

protected:
	class UMGBossStatusWidget* StatusWidget;

protected:
	UPROPERTY(EditAnywhere, Category = "Event Setting", meta = (AllowPrivateAccess = "true"))
	FName	EventInteractionTagName;

protected:
	double	CurrentStunGauge;
	double	MaxStunGauge;

public:
	virtual const FMGEnemyStatusDataTable* InitEnemyData();
	virtual void SetDamage(float _Damage, bool _IsWeakpoint = false);

public:
	void SetWeakpointEnable(bool bEnable);


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	bool FindTag(class AMGInteraction* Interaction);

};
