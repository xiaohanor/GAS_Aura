﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}

		if (bLogNotFound)
		{
			UE_LOG(LogTemp, Error, TEXT("找不到 [%s] 在 [%s] 中."), *AttributeTag.ToString(),*GetNameSafe(this));
		}
	}
	return FAuraAttributeInfo();
}
