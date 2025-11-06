// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/AuraEvent.h"

#include "AbilitySystemBlueprintLibrary.h"

void UAuraEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                        const FAnimNotifyEventReference& EventReference)
{
	if (!IsValid(MeshComp)) return;

	if (AActor* Owner = MeshComp->GetOwner(); IsValid(Owner))
	{
		FGameplayEventData Payload;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Owner, EventTag,Payload);
	}
	Super::Notify(MeshComp, Animation, EventReference);
}
