// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MGAnimNotifyState_ObjectCreate.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGAnimNotifyState_ObjectCreate : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector SpawnOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName	SocketName;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;


};
