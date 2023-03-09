// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotify_PlaySound.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundWaveProcedural.h"
#include "Animation/AnimSequenceBase.h"


#if WITH_EDITOR
#include "Logging/MessageLog.h"
#include "Misc/UObjectToken.h"
#endif

UMGAnimNotify_PlaySound::UMGAnimNotify_PlaySound() :
	Super()
 { 
	IsPlayed = false;
}

void UMGAnimNotify_PlaySound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	PRAGMA_DISABLE_DEPRECATION_WARNINGS
	Super::Notify(MeshComp, Animation);
	PRAGMA_ENABLE_DEPRECATION_WARNINGS

	// Don't call super to avoid call back in to blueprints
	if (Sound && MeshComp)
	{
		if (!Sound->IsOneShot())
		{
			UE_LOG(LogAudio, Warning, TEXT("PlaySound notify: Anim %s tried to play a sound asset which is not a one-shot: '%s'. Spawning suppressed."), *GetNameSafe(Animation), *GetNameSafe(Sound));
			return;
		}

#if WITH_EDITORONLY_DATA
	  	UWorld* World = MeshComp->GetWorld();
	  	
	  	if (bPreviewIgnoreAttenuation && World && (World->WorldType == EWorldType::EditorPreview))
	  	{
	  		UGameplayStatics::PlaySound2D(World, Sound, VolumeMultiplier, PitchMultiplier);
	  	}
	  	else
#endif	
	  	{

			if (!IsPlayed && DoNotFirstPlay)
	  		{
				IsPlayed = true;
	  			return;
	  		}

	  		if (bFollow)
	  		{
	  			UGameplayStatics::SpawnSoundAttached(Sound, MeshComp, AttachName, FVector(ForceInit), EAttachLocation::SnapToTarget, false, VolumeMultiplier, PitchMultiplier);
	  		}
	  		else
	  		{
	  			UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), Sound, MeshComp->GetComponentLocation(), VolumeMultiplier, PitchMultiplier);
	  		}
	  	}
	  }
}
