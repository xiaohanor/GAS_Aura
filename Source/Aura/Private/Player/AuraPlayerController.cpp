// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
	if (CursorHit.bBlockingHit)
	{
		/**
	  * Line trace from cursor. There are several scenarios:
	  *  A. LastActor is null && ThisActor is null
	  *		- Do nothing
	  *	B. LastActor is null && ThisActor is valid
	  *		- Highlight ThisActor
	  *	C. LastActor is valid && ThisActor is null
	  *		- UnHighlight LastActor
	  *	D. Both actors are valid, but LastActor != ThisActor
	  *		- UnHighlight LastActor, and Highlight ThisActor
	  *	E. Both actors are valid, and are the same actor
	  *		- Do nothing
	  */
 
		if (LastActor == nullptr)
		{
			if (ThisActor != nullptr)
			{
				// Case B
				ThisActor->HighlightActor();
			}
			else
			{
				// Case A - both are null, do nothing
			}
		}
		else // LastActor is valid
		{
			if (ThisActor == nullptr)
			{
				// Case C
				LastActor->UnHighlightActor();
			}
			else // both actors are valid
			{
				if (LastActor != ThisActor)
				{
					// Case D
					LastActor->UnHighlightActor();
					ThisActor->HighlightActor();
				}
				else
				{
					// Case E - do nothing
				}
			}
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default; // 鼠标光标类型为默认

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 不锁定鼠标
	InputMode.SetHideCursorDuringCapture(false); // 鼠标不隐藏
	SetInputMode(InputMode);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
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
		// 使用Y值控制前后移动（向前/向后）
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
        
		// 使用X值控制左右移动
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
