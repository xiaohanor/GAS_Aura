// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AsyncTasks/AuraWaitCooldownChange.h"

#include "AbilitySystemComponent.h"

UAuraWaitCooldownChange* UAuraWaitCooldownChange::WaitForCooldownChange(
	UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& InCooldownTag)
{
	if (!IsValid(AbilitySystemComponent) || !InCooldownTag.IsValid()) return nullptr;
	
	UAuraWaitCooldownChange* WaitTask = NewObject<UAuraWaitCooldownChange>();
	WaitTask->ASC = AbilitySystemComponent;
	WaitTask->CooldownTag = InCooldownTag;
	
	// 知道冷却何时结束
	AbilitySystemComponent->RegisterGameplayTagEvent(InCooldownTag, EGameplayTagEventType::NewOrRemoved).AddUObject(WaitTask, &UAuraWaitCooldownChange::CooldownTagChanged);

	// 知道冷却何时开始
	AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(WaitTask, &UAuraWaitCooldownChange::OnActiveEffectAdded);
	
	return WaitTask;
}

void UAuraWaitCooldownChange::EndTask()
{
	if (!IsValid(ASC)) return;
	
	ASC->RegisterGameplayTagEvent(CooldownTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
	ASC->OnActiveGameplayEffectAddedDelegateToSelf.RemoveAll(this);
}

void UAuraWaitCooldownChange::CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount)
{
	if (NewCount == 0)
	{
		OnCooldownEnd.Broadcast(0.f);
	}
}

void UAuraWaitCooldownChange::OnActiveEffectAdded(UAbilitySystemComponent* TargetASC,
	const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer AssetTags;
	SpecApplied.GetAllAssetTags(AssetTags);
	
	FGameplayTagContainer GrantedTags;
	SpecApplied.GetAllGrantedTags(GrantedTags);
	
	if (AssetTags.HasTagExact(CooldownTag) || GrantedTags.HasTagExact(CooldownTag))
	{
		const FGameplayEffectQuery Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTag.GetSingleTagContainer());
		const TArray<float> ReamingTimes = TargetASC->GetActiveEffectsTimeRemaining(Query);
		const float ReamingTime = FMath::Max(ReamingTimes);
		OnCooldownStart.Broadcast(ReamingTime);
	}
}
