﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressedFuncName, typename ReleasedFuncName, typename HeldFuncName>
	void BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncName PressedFunc, ReleasedFuncName ReleasedFunc, HeldFuncName HeldFunc);
};

template <class UserClass, typename PressedFuncName, typename ReleasedFuncName, typename HeldFuncName>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object,
	PressedFuncName PressedFunc, ReleasedFuncName ReleasedFunc, HeldFuncName HeldFunc)
{
	check(InputConfig);

	for (const FAuraInputAction& Action : InputConfig->InputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction,ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}

			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
}
