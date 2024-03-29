// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MGFlag.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MGAnimNotifyState_SetAction.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGAnimNotifyState_SetAction : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayer_ActionState	PlayerAction;

private:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
};
