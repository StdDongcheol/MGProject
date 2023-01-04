// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MGFlag.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MGAnimNotifyState_StateUpdate.generated.h"

/**
 * 
 */
UCLASS()
class MGPROJECT_API UMGAnimNotifyState_StateUpdate : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Category = "CharacterState", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECharacter_BodyAction State;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;


};
