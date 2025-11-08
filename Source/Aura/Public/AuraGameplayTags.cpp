#include "AuraGameplayTags.h"

namespace AuraGameplayTags::Attributes
{
	namespace Vital
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Health, "AuraGameplayTags.Attributes.Vital.Health", "生命值");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Mana, "AuraGameplayTags.Attributes.Vital.Mana", "法力值");
	}
	
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
	
	namespace Resilience
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Resilience, "AuraGameplayTags.Attributes.Resilience", "抗性");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Resilience_Fire, "AuraGameplayTags.Attributes.Resilience.Fire", "火焰抗性");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Resilience_Ice, "AuraGameplayTags.Attributes.Resilience.Ice", "冰霜抗性");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Resilience_Lightning, "AuraGameplayTags.Attributes.Resilience.Lightning", "闪电抗性");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Resilience_Physical, "AuraGameplayTags.Attributes.Resilience.Physical", "物理抗性");
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
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Damage, "AuraGameplayTags.Damage", "伤害");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Damage_Fire, "AuraGameplayTags.Damage.Fire", "火焰伤害");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Damage_Ice, "AuraGameplayTags.Damage.Ice", "冰霜伤害");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Damage_Lightning, "AuraGameplayTags.Damage.Lightning", "闪电伤害");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Damage_Physical, "AuraGameplayTags.Damage.Physical", "物理伤害");
}

namespace AuraGameplayTags::Effects
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "AuraGameplayTags.Effects.HitReact", "击中反应");
}

namespace AuraGameplayTags::Abilities
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack, "AuraGameplayTags.Abilities.Attack", "攻击");
}

namespace AuraGameplayTags::Montage
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Montage_Attack_1, "AuraGameplayTags.Montage.Attack.1", "攻击动作1");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Montage_Attack_2, "AuraGameplayTags.Montage.Attack.2", "攻击动作2");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Montage_Attack_3, "AuraGameplayTags.Montage.Attack.3", "攻击动作3");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Montage_Attack_4, "AuraGameplayTags.Montage.Attack.4", "攻击动作4");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Montage_FireBolt, "AuraGameplayTags.Montage.FireBolt", "发射火球动作");
}

namespace AuraGameplayTags::Socket
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(CombatSocket_Weapon, "AuraGameplayTags.CombatSocket.Weapon", "战斗武器插槽");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(CombatSocket_RightHand, "AuraGameplayTags.CombatSocket.RightHand", "战斗右手插槽");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(CombatSocket_LeftHand, "AuraGameplayTags.CombatSocket.LeftHand", "战斗左手插槽");
}

namespace GameplayCue
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(MeleeImpact, "GameplayCue.MeleeImpact", "近战冲击效果");
}
