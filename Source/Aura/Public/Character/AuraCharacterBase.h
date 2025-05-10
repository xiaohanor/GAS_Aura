// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AuraCharacterBase.generated.h"

enum class ECharacterClass : uint8;
class UAuraAttributeSet;
class UAuraAbilitySystemComponent;
class UGameplayEffect;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	FName WeaponTipSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
	
	virtual FVector GetCombatSocketLocation() override;
	
	virtual void InitAbilityInfo();
 
	void ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& EffectClass, float Level) const;
	virtual void InitializeDefaultAttribute() const;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	void AddCharacterAbilities();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass;

	virtual void Die() override;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastDie();

	/* 溶解效果 */

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(const TArray<UMaterialInstanceDynamic*>& DynamicMaterialInstance);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;
};
