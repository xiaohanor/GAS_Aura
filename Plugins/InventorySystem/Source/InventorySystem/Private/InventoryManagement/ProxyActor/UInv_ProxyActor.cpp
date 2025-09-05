// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManagement/ProxyActor/UInv_ProxyActor.h"

#include "GameFramework/Character.h"
#include "InventoryManagement/Component/Inv_EquipmentComponent.h"


AUInv_ProxyActor::AUInv_ProxyActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(false);

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("ProxyMesh");
	Mesh->SetupAttachment(RootComponent);

	EquipmentComponent = CreateDefaultSubobject<UInv_EquipmentComponent>("EquipmentComponent");
	EquipmentComponent->SetMesh(Mesh);
	EquipmentComponent->SetIsProxy(true);
}

void AUInv_ProxyActor::BeginPlay()
{
	Super::BeginPlay();

	DelayedInitialization();
}

void AUInv_ProxyActor::DelayedInitializeOwner()
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		DelayedInitialization();
		return;
	}

	APlayerController* PC = World->GetFirstPlayerController();
	if (!IsValid(PC))
	{
		DelayedInitialization();
		return;
	}

	ACharacter* Character = Cast<ACharacter>(PC->GetPawn());
	if (!IsValid(Character))
	{
		DelayedInitialization();
		return;
	}

	USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
	if (!IsValid(CharacterMesh))
	{
		DelayedInitialization();
		return;
	}

	SourceMesh = CharacterMesh;
	Mesh->SetSkeletalMesh(SourceMesh->GetSkeletalMeshAsset());
	Mesh->SetAnimInstanceClass(SourceMesh->GetAnimInstance()->GetClass());

	EquipmentComponent->InitializeOwner(PC);
}

void AUInv_ProxyActor::DelayedInitialization()
{
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &ThisClass::DelayedInitializeOwner);
	GetWorldTimerManager().SetTimerForNextTick(TimerDelegate);
}


