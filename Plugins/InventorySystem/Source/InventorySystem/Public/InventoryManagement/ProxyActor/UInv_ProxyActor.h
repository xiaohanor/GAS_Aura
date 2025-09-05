// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UInv_ProxyActor.generated.h"

class UInv_EquipmentComponent;

UCLASS()
class INVENTORYSYSTEM_API AUInv_ProxyActor : public AActor
{
	GENERATED_BODY()

public:
	AUInv_ProxyActor();

	USkeletalMeshComponent* GetMesh() const { return Mesh; }

protected:
	virtual void BeginPlay() override;

private:
	// This is the mesh on the player-controlled Character.
	TWeakObjectPtr<USkeletalMeshComponent> SourceMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInv_EquipmentComponent> EquipmentComponent;

	// This is the proxy mesh we will see in the Inventory Menu.
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh;

	void DelayedInitializeOwner();
	void DelayedInitialization();
};
