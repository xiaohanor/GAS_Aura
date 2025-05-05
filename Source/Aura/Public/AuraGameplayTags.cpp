#include "AuraGameplayTags.h"

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

namespace AuraGameplayTags::InputTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(LMB, "AuraGameplayTags.InputTags.LMB", "鼠标左键");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RMB, "AuraGameplayTags.InputTags.RMB", "鼠标右键");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MMB, "AuraGameplayTags.InputTags.MMB", "鼠标中键");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(one, "AuraGameplayTags.InputTags.1", "数字键1");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(two, "AuraGameplayTags.InputTags.2", "数字键2");
}

namespace AuraGameplayTags::Damage
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Damage, "Damage", "伤害");
}
