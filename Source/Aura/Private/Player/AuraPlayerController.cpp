// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/Aura.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()); IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default; // 鼠标光标类型为默认

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 不锁定鼠标
	InputMode.SetHideCursorDuringCapture(false); // 鼠标不隐藏
	SetInputMode(InputMode);

	NavSys = UNavigationSystemV1::GetCurrent(GetWorld()); // 获取导航系统
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	AutoRun();
}

void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		// 找到角色在预先计算好的路径曲线上的最近投影点
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		// 获取该点的前进方向（切线方向）
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);
		
		// 获取路径的终点位置（曲线的最后一个点）
		const FVector LastPoint = Spline->GetLocationAtSplinePoint(Spline->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World);
		// 计算角色当前曲线投影位置到终点的距离
		const float DistanceToDestination = (LocationOnSpline - LastPoint).Length();
		// 当距离小于接受半径时，停止自动寻路
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void AAuraPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
	if (CursorHit.bBlockingHit)
	{
		if (LastActor != ThisActor)
		{
			if (LastActor) LastActor->UnHighlightActor();
			if (ThisActor) ThisActor->HighlightActor();
		}
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(AuraGameplayTags::InputTags::LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AAuraPlayerController::CreatPathSpline()
{
	const APawn* ControlledPawn = GetPawn();
	// 只有短按且有控制的角色时才执行
	if (FollowTime <= ShortPressThreshold && ControlledPawn)
	{
		// 使用导航专用碰撞通道检测鼠标点击位置
		FHitResult NavChannelHit;
		GetHitResultUnderCursor(ECC_Nav, false, NavChannelHit);
		if (NavChannelHit.bBlockingHit)
		{
			// 将点击位置投影到导航网格上的可行走位置
			// QueryingExtent 为查询范围比默认值大
			FNavLocation NavImpactLocation;
			const FVector QueryingExtent = FVector(400.f, 400.f, 250.f);
			const FNavAgentProperties& NavPros = GetNavAgentPropertiesRef();
			const bool bNavLocationFound = NavSys->ProjectPointToNavigation(NavChannelHit.ImpactPoint, NavImpactLocation, QueryingExtent, &NavPros);
			if (bNavLocationFound)
			{
				// 同步计算从角色位置到目标点的路径
				UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), ControlledPawn->GetActorLocation(), NavImpactLocation);
				if (NavPath && NavPath->PathPoints.Num() > 0)
				{
					Spline->ClearSplinePoints();
					for (const FVector& PathPoint : NavPath->PathPoints)
					{
						Spline->AddSplinePoint(PathPoint, ESplineCoordinateSpace::World);
						DrawDebugSphere(GetWorld(), PathPoint, 8.f, 8, FColor::Green, false, 5.f);
					}
					bAutoRunning = true;
				}
			}
		}
	}
	FollowTime = 0.f;
	bTargeting = false;
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(AuraGameplayTags::InputTags::LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}

	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		CreatPathSpline();
	}
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(AuraGameplayTags::InputTags::LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}

	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds(); // 获取光标跟随时间
		
		if (GetHitResultUnderCursor(ECC_Visibility, false, CursorHit))
		{
			CachedDestination = CursorHit.ImpactPoint; // 缓存鼠标点击位置
		}
		
		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal(); // 获取移动方向
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return  AuraAbilitySystemComponent;
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputValue)
{
	// 从输入值中提取二维向量（X表示左右移动，Y表示前后移动）
	const FVector2D InputAxisVector = InputValue.Get<FVector2D>();
    
	// 获取控制器当前的旋转角度（即摄像机朝向）
	const FRotator Rotation = GetControlRotation();
    
	// 创建一个只保留水平旋转(Yaw)的旋转器，忽略俯仰和翻滚
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// 根据摄像机的水平朝向计算前进方向向量
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X);
    
	// 计算右侧方向向量（垂直于前进方向）
	const FVector RightDirection = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);

	// 获取当前控制的Pawn，并添加移动输入
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		bAutoRunning = false;
		// 使用Y值控制前后移动（向前/向后）
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
        
		// 使用X值控制左右移动
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
