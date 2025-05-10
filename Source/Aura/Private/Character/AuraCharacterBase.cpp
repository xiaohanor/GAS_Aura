// Fill out your copyright notice in the Description page of Project Settings.


#include "Character//AuraCharacterBase.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);

	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAnimMontage* AAuraCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::InitAbilityInfo()
{
	// 由子类实现
}

void AAuraCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect>& EffectClass, const float Level) const
{
	check(IsValid(AbilitySystemComponent));
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this); // 添加源对象
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(EffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitializeDefaultAttribute() const
{
	// 由子类实现
}

void AAuraCharacterBase::AddCharacterAbilities()
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	AuraASC->AddCharacterAbilities(StartupAbilities);
}

void AAuraCharacterBase::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastDie();
}

void AAuraCharacterBase::Dissolve()
{
	if (IsValid(DissolveMaterialInstance) && IsValid(WeaponDissolveMaterialInstance))
	{
		TArray<UMaterialInstanceDynamic*> DynamicMIs;

		UMaterialInstanceDynamic* MatIns = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, MatIns);
		DynamicMIs.AddUnique(MatIns);

		UMaterialInstanceDynamic* WeaponMatIns = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		Weapon->SetMaterial(0, WeaponMatIns);
		DynamicMIs.AddUnique(WeaponMatIns);

		StartDissolveTimeline(DynamicMIs);
	}
}

void AAuraCharacterBase::MulticastDie_Implementation()
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Block);	
	//GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
}

FVector AAuraCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}


