// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
 
	check(AttributeInfo);
 
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AuraGameplayTags::Attributes::Primary::Strength);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeMenuController::BindCallbacksToDependencies()
{
	
}
