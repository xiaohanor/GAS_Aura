// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AuraCameraFadeComponent.generated.h"

class UCapsuleComponent;
class UCameraComponent;
class USpringArmComponent;

USTRUCT(BlueprintType)
struct FCameraOccludedActor
{
	GENERATED_USTRUCT_BODY()
 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> Actor;
 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
  
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UMaterialInterface*> Materials;
 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsOccluded = false;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class AURA_API UAuraCameraFadeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAuraCameraFadeComponent();

	UFUNCTION(BlueprintCallable)
	void SyncOccludedActors();

protected:
	virtual void BeginPlay() override;

	/** 在判定某个角色被遮挡之前，用于绘制直线轨迹的 Pawn 胶囊半径和高度应该是多少？
	 * 数值过低可能会导致摄像机穿过墙壁。
   */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Occlusion|Occlusion",
	  meta=(ClampMin="0.1", ClampMax="10.0") )
	float CapsulePercentageForTrace;
  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Occlusion|Materials")
	TObjectPtr<UMaterialInterface> FadeMaterial;
 
	UPROPERTY(BlueprintReadWrite, Category="Camera Occlusion|Components")
	TObjectPtr<USpringArmComponent> ActiveSpringArm;
 
	UPROPERTY(BlueprintReadWrite, Category="Camera Occlusion|Components")
	TObjectPtr<UCameraComponent> ActiveCamera;
 
	UPROPERTY(BlueprintReadWrite, Category="Camera Occlusion|Components")
	TObjectPtr<UCapsuleComponent> ActiveCapsuleComponent;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Occlusion")
	bool IsOcclusionEnabled;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera Occlusion|Occlusion")
	bool DebugLineTraces;

private:
	UPROPERTY()
	TMap<AActor*, FCameraOccludedActor> OccludedActors;

	UPROPERTY()
	TWeakObjectPtr<APlayerController> OwningController;
  
	bool HideOccludedActor(AActor* Actor);
	void OnHideOccludedActor(const FCameraOccludedActor& OccludedActor) const;
	void ShowOccludedActor(FCameraOccludedActor& OccludedActor);
	void OnShowOccludedActor(const FCameraOccludedActor& OccludedActor) const;
	void ForceShowOccludedActors();
 
	bool ShouldCheckCameraOcclusion() const
	{
		return IsOcclusionEnabled && FadeMaterial && ActiveCamera && ActiveCapsuleComponent;
	}
};
