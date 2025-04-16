// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"


AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; // 角色朝向移动方向
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true; 
 
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// 为服务器端角色初始化能力系统
	InitAbilityInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// 为客户端角色初始化能力系统
	InitAbilityInfo();
}

void AAuraCharacter::InitAbilityInfo()
{
	AAuraPlayerState* PlayerState = Cast<AAuraPlayerState>(GetPlayerState());
	if (IsValid(PlayerState))
	{
		AbilitySystemComponent->InitAbilityActorInfo(PlayerState,this);
		AbilitySystemComponent = PlayerState->GetAbilitySystemComponent();
		AttributeSet = PlayerState->GetAttributeSet();
	}
}
