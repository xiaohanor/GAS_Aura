// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraEnemy.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widget/AuraUserWidget.h"


AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block); //用于后处理材质描边
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal); // Minimal 模式用于 AI 控制的角色

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void AAuraEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);

}

int32 AAuraEnemy::GetPlayerLevel() const
{
	return Level;
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityInfo();
	BindToHealthBar();

	UAuraAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);
	AbilitySystemComponent->RegisterGameplayTagEvent(AuraGameplayTags::Effects::HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&AAuraEnemy::HitReactTagChanged
		);
}

void AAuraEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
}

void AAuraEnemy::InitAbilityInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	InitializeDefaultAttribute();
}

void AAuraEnemy::InitializeDefaultAttribute() const
{
	UAuraAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void AAuraEnemy::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}

void AAuraEnemy::BindToHealthBar()
{
	if (UAuraUserWidget* AuraWidget = Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject()); IsValid(AuraWidget))
	{
		AuraWidget->SetWidgetController(this);
	}

	if (const UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AttributeSet); IsValid(AuraAS))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnHealthChanged.Broadcast(Data.NewValue);});
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnMaxHealthChanged.Broadcast(Data.NewValue);});
		
		OnHealthChanged.Broadcast(AuraAS->GetHealth());
		OnMaxHealthChanged.Broadcast(AuraAS->GetMaxHealth());
	}
}
