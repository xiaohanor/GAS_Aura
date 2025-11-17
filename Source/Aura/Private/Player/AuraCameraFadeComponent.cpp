// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraCameraFadeComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"


UAuraCameraFadeComponent::UAuraCameraFadeComponent()
{
	CapsulePercentageForTrace = 1.0f;
	DebugLineTraces = true;
	IsOcclusionEnabled = true;
}

void UAuraCameraFadeComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningController = Cast<APlayerController>(GetOwner());
	checkf(OwningController.IsValid(), TEXT("需要一个玩家控制器作为拥有者"));
	if (!OwningController->IsLocalController()) return;

	APawn* Pawn = OwningController->GetPawn();
	if (IsValid(Pawn))
	{
		ActiveSpringArm = Pawn->FindComponentByClass<USpringArmComponent>();
		ActiveCamera  = Pawn->FindComponentByClass<UCameraComponent>();
		ActiveCapsuleComponent = Pawn->FindComponentByClass<UCapsuleComponent>();
	}

	SyncOccludedActors();
}

void UAuraCameraFadeComponent::SyncOccludedActors()
{
	if (!ShouldCheckCameraOcclusion()) return;
 
	// 摄像机当前发生碰撞，显示所有当前被遮挡的 Actor
	// 并且不再进行进一步的遮挡
	if (ActiveSpringArm->bDoCollisionTest)
	{
		ForceShowOccludedActors();
		return;
	}
 
	FVector Start = ActiveCamera->GetComponentLocation();
	FVector End = OwningController->GetPawn()->GetActorLocation();
 
	TArray<TEnumAsByte<EObjectTypeQuery>> CollisionObjectTypes;
	CollisionObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
 
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> OutHits;
 
	auto ShouldDebug = DebugLineTraces ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;
 
	bool bGotHits = UKismetSystemLibrary::CapsuleTraceMultiForObjects(
	  GetWorld(), Start, End, ActiveCapsuleComponent->GetScaledCapsuleRadius() * CapsulePercentageForTrace,
	  ActiveCapsuleComponent->GetScaledCapsuleHalfHeight() * CapsulePercentageForTrace, CollisionObjectTypes, true,
	  ActorsToIgnore,
	  ShouldDebug,
	  OutHits, true);
 
	if (bGotHits)
	{
		// 被线条追踪击中的Actor列表，这意味着他们被遮挡而无法看到
		TSet<AActor*> ActorsJustOccluded;
 
		// 隐藏被相机遮挡的Actor
		for (FHitResult Hit : OutHits)
		{
			AActor* HitActor = Hit.GetActor();
			HideOccludedActor(HitActor);
			ActorsJustOccluded.Add(HitActor);
		}
 
		// 显示目前被隐藏但不再被摄像机遮挡的Actor
		for (auto& Elem : OccludedActors)
		{
			if (!ActorsJustOccluded.Contains(Elem.Value.Actor) && Elem.Value.IsOccluded)
			{
				ShowOccludedActor(Elem.Value);
 
				if (DebugLineTraces)
				{
					UE_LOG(LogTemp, Warning,
						   TEXT("Actor %s was occluded, but it's not occluded anymore with the new hits."), *Elem.Value.Actor->GetName());
				}
			}
		}
	}
	else
	{
		ForceShowOccludedActors();
	}
}


bool UAuraCameraFadeComponent::HideOccludedActor(AActor* Actor)
{
	FCameraOccludedActor* ExistingOccludedActor = OccludedActors.Find(Actor);
 
	if (ExistingOccludedActor && ExistingOccludedActor->IsOccluded)
	{
		if (DebugLineTraces) UE_LOG(LogTemp, Warning, TEXT("Actor %s was already occluded. Ignoring."),
									*Actor->GetName());
		return false;
	}
 
	if (ExistingOccludedActor && IsValid(ExistingOccludedActor->Actor))
	{
		ExistingOccludedActor->IsOccluded = true;
		OnHideOccludedActor(*ExistingOccludedActor);
	}
	else
	{
		UStaticMeshComponent* StaticMesh = Actor->FindComponentByClass<UStaticMeshComponent>();
		if (!IsValid(StaticMesh)) return false;
 
		FCameraOccludedActor OccludedActor;
		OccludedActor.Actor = Actor;
		OccludedActor.StaticMesh = StaticMesh;
		OccludedActor.Materials = StaticMesh->GetMaterials();
		OccludedActor.IsOccluded = true;
		OccludedActors.Add(Actor, OccludedActor);
		OnHideOccludedActor(OccludedActor);

		if (DebugLineTraces) UE_LOG(LogTemp, Warning, TEXT("Actor %s does not exist, creating and occluding it now."), *Actor->GetName());
	}
 
	return true;
}

void UAuraCameraFadeComponent::OnHideOccludedActor(const FCameraOccludedActor& OccludedActor) const
{
	for (int i = 0; i < OccludedActor.StaticMesh->GetNumMaterials(); ++i)
	{
		OccludedActor.StaticMesh->SetMaterial(i, FadeMaterial);
	}
}

void UAuraCameraFadeComponent::ShowOccludedActor(FCameraOccludedActor& OccludedActor)
{
	if (!IsValid(OccludedActor.Actor))
	{
		OccludedActors.Remove(OccludedActor.Actor);
	}
 
	OccludedActor.IsOccluded = false;
	OnShowOccludedActor(OccludedActor);
}

void UAuraCameraFadeComponent::OnShowOccludedActor(const FCameraOccludedActor& OccludedActor) const
{
	for (int matIdx = 0; matIdx < OccludedActor.Materials.Num(); ++matIdx)
	{
		OccludedActor.StaticMesh->SetMaterial(matIdx, OccludedActor.Materials[matIdx]);
	}
}

void UAuraCameraFadeComponent::ForceShowOccludedActors()
{
	for (auto& Elem : OccludedActors)
	{
		if (Elem.Value.IsOccluded)
		{
			ShowOccludedActor(Elem.Value);
 
			if (DebugLineTraces) UE_LOG(LogTemp, Warning, TEXT("Actor %s was occluded, force to show again."), *Elem.Value.Actor->GetName());
		}
	}
}
