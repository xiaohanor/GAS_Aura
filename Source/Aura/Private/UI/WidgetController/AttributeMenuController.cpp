// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Player/AuraPlayerState.h"

void UAttributeMenuController::BindCallbacksToDependencies()
{
	check(AttributeInfo);

	for (FAuraAttributeInfo& Info : AttributeInfo->AttributeInformation)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Info.AttributeGetter).AddLambda([this, Info](const FOnAttributeChangeData&){BroadcastAttributeInfo(Info);});
	}
	
	AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AuraPlayerState->OnAttributePointsChanged.AddLambda([this](const int32 Points){AttributePointsChanged.Broadcast(Points);});
}

void UAttributeMenuController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->UpgradeAttribute(AttributeTag);
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
	
	AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AttributePointsChanged.Broadcast(AuraPlayerState->GetAttributePoints());
}