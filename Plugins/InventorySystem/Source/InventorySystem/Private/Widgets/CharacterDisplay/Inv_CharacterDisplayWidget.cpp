// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/CharacterDisplay/Inv_CharacterDisplayWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "InventoryManagement/ProxyActor/UInv_ProxyActor.h"
#include "Kismet/GameplayStatics.h"

FReply UInv_CharacterDisplayWidget::NativeOnMouseButtonDown(const FGeometry& MyGeometry,
                                                            const FPointerEvent& MouseEvent)
{
	CurrentPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetOwningPlayer());
	LastPosition = CurrentPosition;
	
	bIsDragging = true;
	return FReply::Handled();
}

FReply UInv_CharacterDisplayWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	bIsDragging = false;
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void UInv_CharacterDisplayWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	bIsDragging = false;
}

void UInv_CharacterDisplayWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, AUInv_ProxyActor::StaticClass(), Actors);

	if (!Actors.IsValidIndex(0)) return;

	AUInv_ProxyActor* ProxyMesh = Cast<AUInv_ProxyActor>(Actors[0]);
	if (!IsValid(ProxyMesh)) return;

	Mesh = ProxyMesh->GetMesh();
}

void UInv_CharacterDisplayWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!bIsDragging) return;

	LastPosition = CurrentPosition;
	CurrentPosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetOwningPlayer());
	const float HorizontalDelta  = LastPosition.X - CurrentPosition.X;
	if (Mesh.IsValid())
	{
		Mesh->AddRelativeRotation(FRotator(0.f, HorizontalDelta, 0.f));
	}
}
