#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace AuraGameplayTags::Attributes
{
	namespace Vital
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Health);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Mana);
	}
	
	namespace Primary
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Strength);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Intelligence);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resilience);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Vigor);
	}

	namespace Secondary
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Armor);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ArmorPenetration);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(BlockChance);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(CriticalHitChance);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(CriticalHitDamage);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(CriticalHitResistance);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(HealthRegeneration);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ManaRegeneration);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(MaxHealth);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(MaxMana);
	}
	
	namespace Resilience
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resilience);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resilience_Fire);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resilience_Lightning);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resilience_Ice);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Resilience_Physical);
	}
}

namespace AuraGameplayTags::InputTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(LMB);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(RMB);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(MMB);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(one);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(two);
}

namespace AuraGameplayTags::Damage
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Fire);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Lightning);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Ice);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Physical);
}

namespace AuraGameplayTags::Effects  
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact);
}

namespace AuraGameplayTags::Abilities
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attack);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Summon);
}

namespace AuraGameplayTags::Montage
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_Attack_1);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_Attack_2);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_Attack_3);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_Attack_4);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Montage_FireBolt);
}

namespace AuraGameplayTags::Socket
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(CombatSocket_Weapon);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(CombatSocket_RightHand);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(CombatSocket_LeftHand);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(CombatSocket_Tail);
}

namespace GameplayCue
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(MeleeImpact);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GroundSummon)
}
