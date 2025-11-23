// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "GameFramework/PlayerState.h"
#include "Interaction/ModifierDependencyInterface.h"
#include "AuraPlayerState.generated.h"

class ULevelUpInfo;
class UAttributeSet;
class UAuraAttributeSet;
class UAuraAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatusChanged, int32 /*NewValue*/);
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface, public IModifierDependencyInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	ULevelUpInfo* GetLevelUpInfo() const { return LevelUpInfo; }
	
	//~ ModifierDependencyInterface
	virtual FOnExternalGameplayModifierDependencyChange* GetOnModifierDependencyChanged() override { return &OnModifierDependencyChanged; }
	//~ ModifierDependencyInterface

	FOnPlayerStatusChanged OnXPChanged;
	FOnPlayerStatusChanged OnLevelChanged;
	FOnPlayerStatusChanged OnAttributePointsChanged;
	FOnPlayerStatusChanged OnSpellPointsChanged;
	
	int32 GetPlayerLevel() const { return Level; }
	int32 GetXP() const { return XP; }
	int32 GetAttributePoints() const { return AttributePoints; }
	int32 GetSpellPoints() const { return SpellPoints; }
	
	void SetXP(int32 NewXP);
	void SetLevel(int32 NewLevel);
	
	void AddToXP(int32 DeltaXP);
	void AddToLevel(int32 DeltaLevel);
	void AddToAttributePoints(int32 InPoints);
	void AddToSpellPoints(int32 InPoints);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;
	
	FOnExternalGameplayModifierDependencyChange OnModifierDependencyChanged;
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_XP)
	int32 XP = 1;
	
	UFUNCTION()
	void OnRep_XP(int32 OldXP);
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_AttributePoints)
	int32 AttributePoints = 0;
	
	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributePoints);
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_SpellPoints)
	int32 SpellPoints = 1;
	
	UFUNCTION()
	void OnRep_SpellPoints(int32 OldSpellPoints);
};
