// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MGAnimNotifyState_AddMove.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGAnimNotifyState_AddMove : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UMGAnimNotifyState_AddMove();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	Speed;

private:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
		float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

};
