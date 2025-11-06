// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AuraEvent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraEvent : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "AuraGameplayTags.Montage"))
	FGameplayTag EventTag;
	
};
