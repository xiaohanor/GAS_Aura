﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	if (UAuraUserWidget* Widget = CreateWidget<UAuraUserWidget>(GetWorld(), UserWidgetClass); IsValid(Widget))
	{
		Widget->AddToViewport();
	}
}
