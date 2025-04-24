#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

namespace AuraGameplayTags::Attributes
{
	namespace Primary
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Strength, "AuraGameplayTags.Attributes.Primary.Strength", "力量");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Intelligence, "AuraGameplayTags.Attributes.Primary.Intelligence", "智力");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Resilience, "AuraGameplayTags.Attributes.Primary.Resilience", "韧性");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Vigor, "AuraGameplayTags.Attributes.Primary.Vigor", "活力");
	}

	namespace Secondary
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Armor, "AuraGameplayTags.Attributes.Secondary.Armor", "护甲");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ArmorPenetration, "AuraGameplayTags.Attributes.Secondary.ArmorPenetration", "护甲穿透");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(BlockChance, "AuraGameplayTags.Attributes.Secondary.BlockChance", "格挡几率");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(CriticalHitChance, "AuraGameplayTags.Attributes.Secondary.CriticalHitChance", "暴击几率");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(CriticalHitDamage, "AuraGameplayTags.Attributes.Secondary.CriticalHitDamage", "暴击伤害");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(CriticalHitResistance, "AuraGameplayTags.Attributes.Secondary.CriticalHitResistance", "暴击抗性");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(HealthRegeneration, "AuraGameplayTags.Attributes.Secondary.HealthRegeneration", "生命回复");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ManaRegeneration, "AuraGameplayTags.Attributes.Secondary.ManaRegeneration", "法力回复");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(MaxHealth, "AuraGameplayTags.Attributes.Secondary.MaxHealth", "最大生命值");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(MaxMana, "AuraGameplayTags.Attributes.Secondary.MaxMana", "最大法力值");
	}
}