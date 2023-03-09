// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify_PlaySound.h"
#include "MGAnimNotify_PlaySound.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGAnimNotify_PlaySound : public UAnimNotify_PlaySound
{
	GENERATED_BODY()

public:
	UMGAnimNotify_PlaySound();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool DoNotFirstPlay;
	bool IsPlayed;


public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
