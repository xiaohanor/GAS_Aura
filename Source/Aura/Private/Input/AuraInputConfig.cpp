// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfig.h"


UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const auto& Action : InputActions)
	{
		if (Action.InputAction && Action.InputTag.MatchesTagExact(InputTag))
		{
			return Action.InputAction;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("找不到 [%s] 在 [%s] 中."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
