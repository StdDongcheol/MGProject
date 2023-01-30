// Fill out your copyright notice in the Description page of Project Settings.


#include "MGAnimNotifyState_SetCollision.h"

void UMGAnimNotifyState_SetCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, 
	UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	USceneComponent* RootComponent = MeshComp->GetAttachmentRoot();
	
	if (!RootComponent)
		return;

	TArray<USceneComponent*> Arrays;

	RootComponent->GetChildrenComponents(true, Arrays);

	TArray<USceneComponent*>::RangedForIteratorType iter1 = Arrays.begin();
	TArray<USceneComponent*>::RangedForIteratorType iter1End = Arrays.end();

	for (; iter1 != iter1End; ++iter1)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>((*iter1));
	
		if (PrimitiveComponent)
		{
			FName Name = PrimitiveComponent->GetCollisionProfileName();

			if (Name == "EnemyAttack")
				PrimitiveComponent->SetGenerateOverlapEvents(true);
		}
	}

}

void UMGAnimNotifyState_SetCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, 
	UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	USceneComponent* RootComponent = MeshComp->GetAttachmentRoot();

	if (!RootComponent)
		return;

	TArray<USceneComponent*> Arrays;

	RootComponent->GetChildrenComponents(true, Arrays);

	TArray<USceneComponent*>::RangedForIteratorType iter1 = Arrays.begin();
	TArray<USceneComponent*>::RangedForIteratorType iter1End = Arrays.end();

	for (; iter1 != iter1End; ++iter1)
	{
		UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>((*iter1));

		if (PrimitiveComponent)
		{
			FName Name = PrimitiveComponent->GetCollisionProfileName();

			if (Name == "EnemyAttack")
				PrimitiveComponent->SetGenerateOverlapEvents(false);
		}
	}
}
