// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	//~ CombatInterface
	virtual int32 GetPlayerLevel() const override;
	//~ CombatInterface

protected:
	virtual void InitAbilityInfo() override;
	virtual void InitializeDefaultAttribute() const override;
};
