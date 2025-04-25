// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuController::BindCallbacksToDependencies()
{
	check(AttributeInfo);

	for (FAuraAttributeInfo& Info : AttributeInfo->AttributeInformation)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Info.AttributeGetter).AddLambda([this, Info](const FOnAttributeChangeData&){BroadcastAttributeInfo(Info);});
	}
}

void UAttributeMenuController::BroadcastAttributeInfo(const FAuraAttributeInfo& Info) const
{
	FAuraAttributeInfo NewInfo = Info;
	NewInfo.AttributeValue = Info.AttributeGetter.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(NewInfo);
}

void UAttributeMenuController::BroadcastInitialValues()
{
	check(AttributeInfo);
 
	for (FAuraAttributeInfo& Info : AttributeInfo->AttributeInformation)
	{
		BroadcastAttributeInfo(Info);
	}
}