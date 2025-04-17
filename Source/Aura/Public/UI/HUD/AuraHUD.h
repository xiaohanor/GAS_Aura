﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> UserWidget;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAuraUserWidget> UserWidgetClass;
};
