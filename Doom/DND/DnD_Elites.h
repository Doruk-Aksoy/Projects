#ifndef DND_ELITE_IN
#define DND_ELITE_IN

#define DND_MIN_ELITEMODS 2
#define DND_MAX_ELITEMODS 4
#define DND_ELITE_HPSCALE 15
#define DND_ELITE_DMGSCALE 0.02
#define DND_ELITE_EXTRASTRONG_BONUS 0.35
#define DND_ELITE_VITAL_SCALE 100
#define DND_ELITE_CREDITCHANCE_BONUS 0.1
#define DND_ELITE_EXP_BONUS 25
#define DND_ELITE_CREDIT_BONUS 25
#define DND_ELITE_FX_DENSITY 8
#define MAX_ELITE_FX_WAIT 60
#define DND_ELITE_FX_TID 900

#define DND_ELITE_RESOLUTION 10000
#define DND_ELITE_MIN_INCREMENT 25 // per level add 0.25
#define DND_ELITE_RESOLUTION_SCALE 100

#define DND_ELITE_BASEDROP 0.035

#define MAX_ELITE_TRIES 50
#define DND_MAX_ELITEIMMUNITIES 2

enum {
	// Traitset 1
	
	DND_MELEE_RESIST, // obsolete
	
	DND_ENERGY_WEAKNESS,
	DND_SILVER_WEAKNESS,
	DND_FIRE_WEAKNESS = DND_SILVER_WEAKNESS << 1,
	DND_ICE_WEAKNESS = DND_FIRE_WEAKNESS << 1,
	DND_MAGIC_WEAKNESS = DND_ICE_WEAKNESS << 1,
	
	DND_EXPLOSIVE_RESIST = DND_MAGIC_WEAKNESS << 1,
	DND_EXPLOSIVE_IMMUNE = DND_EXPLOSIVE_RESIST << 1,
	DND_EXPLOSIVE_NONE = DND_EXPLOSIVE_IMMUNE << 1,
	DND_BULLET_RESIST = DND_EXPLOSIVE_NONE << 1,
	DND_GHOST = DND_BULLET_RESIST << 1,
	DND_HARDENED_SKIN = DND_GHOST << 1,
	DND_REFLECTIVE = DND_HARDENED_SKIN << 1,
	DND_MINIONS = DND_REFLECTIVE << 1,
	DND_CURSE = DND_MINIONS << 1,
	DND_HEAL = DND_CURSE << 1,
	DND_BLOCK = DND_HEAL << 1,
	DND_SPLIT = DND_BLOCK << 1,
	DND_RAISE = DND_SPLIT << 1,
	DND_TELEPORT = DND_RAISE << 1,
	DND_RESURRECT = DND_TELEPORT << 1,
	DND_MOBILITY = DND_RESURRECT << 1,
	DND_HOMING = DND_MOBILITY << 1,
	DND_POISON = DND_HOMING << 1,
	DND_DEATH = DND_POISON << 1,
	DND_RAGE = DND_DEATH << 1,
	DND_PIERCE = DND_RAGE << 1,
	DND_AGGRESSIVE = DND_PIERCE << 1,
	DND_EXTRAFAST = DND_AGGRESSIVE << 1,
	DND_FASTREACTION = DND_EXTRAFAST << 1,
	DND_NOPAIN = DND_FASTREACTION << 1,
	
	// Traitset 2
	
	DND_BULLET_IMMUNE = 1,
	DND_ENERGY_RESIST = DND_BULLET_IMMUNE << 1,
	DND_ENERGY_IMMUNE = DND_ENERGY_RESIST << 1,
	DND_MAGIC_RESIST = DND_ENERGY_IMMUNE << 1,
	DND_MAGIC_IMMUNE = DND_MAGIC_RESIST	<< 1,
	DND_ELEMENTAL_RESIST = DND_MAGIC_IMMUNE << 1,
	DND_ELEMENTAL_IMMUNE = DND_ELEMENTAL_RESIST << 1,
	DND_EXTRASTRONG = DND_ELEMENTAL_IMMUNE << 1,
	DND_VITAL = DND_EXTRASTRONG << 1,
	DND_ARMORPEN = DND_VITAL << 1,
	
	DND_LEGENDARY = 1073741824
};

enum {
	DND_ENERGY_WEAKNESS_POW,
	DND_SILVER_WEAKNESS_POW,
	DND_FIRE_WEAKNESS_POW,
	DND_ICE_WEAKNESS_POW,
	DND_MAGIC_WEAKNESS_POW,
	
	DND_EXPLOSIVE_RESIST_POW,
	DND_EXPLOSIVE_IMMUNE_POW,
	DND_EXPLOSIVE_NONE_POW,
	DND_BULLET_RESIST_POW,
	DND_GHOST_POW,
	DND_HARDENED_SKIN_POW,
	DND_REFLECTIVE_POW,
	DND_MINIONS_POW,
	DND_CURSE_POW,
	DND_HEAL_POW,
	DND_BLOCK_POW,
	DND_SPLIT_POW,
	DND_RAISE_POW,
	DND_TELEPORT_POW,
	DND_RESURRECT_POW,
	DND_MOBILITY_POW,
	DND_HOMING_POW,
	DND_POISON_POW,
	DND_DEATH_POW,
	DND_RAGE_POW,
	DND_PIERCE_POW,
	DND_AGGRESSIVE_POW,
	DND_EXTRAFAST_POW,
	DND_FASTREACTION_POW,
	DND_NOPAIN_POW,
	
	// Traitset 2
	
	DND_BULLET_IMMUNE_POW = 0,
	DND_ENERGY_RESIST_POW,
	DND_ENERGY_IMMUNE_POW,
	DND_MAGIC_RESIST_POW,
	DND_MAGIC_IMMUNE_POW,
	DND_ELEMENTAL_RESIST_POW,
	DND_ELEMENTAL_IMMUNE_POW,
	DND_EXTRASTRONG_POW,
	DND_VITAL_POW,
	DND_ARMORPEN_POW,
	
	DND_LEGENDARY_POW = 31
};

#define MAX_ROLLABLE_TRAITS 21
#define ELITE_FLAG2_BEGIN 11
// these are powers, not actual values
int EliteTraitNumbers[MAX_ROLLABLE_TRAITS] = {
	DND_EXPLOSIVE_RESIST_POW,
	DND_EXPLOSIVE_IMMUNE_POW,
	DND_EXPLOSIVE_NONE_POW,
	DND_BULLET_RESIST_POW,
	DND_GHOST_POW,
	DND_HARDENED_SKIN_POW,
	DND_REFLECTIVE_POW,
	DND_AGGRESSIVE_POW,
	DND_EXTRAFAST_POW,
	DND_FASTREACTION_POW,
	DND_NOPAIN_POW,
	
	// from here and onwards consider traits flag2
	DND_BULLET_IMMUNE_POW,
	DND_ENERGY_RESIST_POW,
	DND_ENERGY_IMMUNE_POW,
	DND_MAGIC_RESIST_POW,
	DND_MAGIC_IMMUNE_POW,
	DND_ELEMENTAL_RESIST_POW,
	DND_ELEMENTAL_IMMUNE_POW, 
	DND_EXTRASTRONG_POW,
	DND_VITAL_POW,
	DND_ARMORPEN_POW
};

int GetEliteBonusDamage() {
	return DND_ELITE_DMGSCALE * CheckInventory("MonsterLevel");
}

bool IsExtraStrong() {
	return IsSet(CheckInventory("MonsterTraits2"), DND_EXTRASTRONG_POW);
}

int GetRandomEliteTrait() {
	return random(0, MAX_ROLLABLE_TRAITS - 1);
}

bool RollEliteChance() {
	return random(1, DND_ELITE_RESOLUTION) <= Clamp_Between(GetCVar("dnd_elite_spawnchance"), 1, 100) * DND_ELITE_RESOLUTION_SCALE + max_level * DND_ELITE_MIN_INCREMENT;
}

void SetEliteFlag(int f, int flagside) {
	if(!flagside) {
		switch (f) {
			case DND_EXPLOSIVE_RESIST_POW:
				GiveInventory("MakeExplosiveResist", 1);
			break;
			case DND_EXPLOSIVE_IMMUNE_POW:
				GiveInventory("MakeExplosiveHighResist", 1);
			break;
			case DND_EXPLOSIVE_NONE_POW:
				GiveInventory("MakeExplosiveFullImmune", 1);
			break;
			case DND_BULLET_RESIST_POW:
				GiveInventory("MakePhysicalResist", 1);
			break;
			case DND_GHOST_POW:
				GiveInventory("MakeGhost", 1); // setactorflag didnt work...
				SetActorProperty(0, APROP_RENDERSTYLE, STYLE_TRANSLUCENT);
				SetActorProperty(0, APROP_ALPHA, 0.5);
			break;
			case DND_HARDENED_SKIN_POW:
				GiveInventory("MakeHardenedSkin", 1);
			break;
			case DND_REFLECTIVE_POW:
				GiveInventory("MakeReflective", 1);
			break;
			case DND_AGGRESSIVE_POW:
				GiveInventory("MakeAggressive", 1);
			break;
			case DND_EXTRAFAST_POW:
				GiveInventory("MakeFaster", 1);
			break;
			case DND_FASTREACTION_POW:
				GiveInventory("MakeRetaliate", 1);
			break;
			case DND_NOPAIN_POW:
				GiveInventory("MakeNoPain", 1);
			break;
		}
		SetInventory("MonsterTraits", CheckInventory("MonsterTraits") | (1 << f));
	}
	else {
		switch (f) {
			case DND_BULLET_IMMUNE_POW:
				if(IsSet(CheckInventory("MonsterTraits"), DND_SILVER_WEAKNESS_POW))
					SetInventory("MonsterTraits", ClearBit(CheckInventory("MonsterTraits"), DND_SILVER_WEAKNESS_POW));
				GiveInventory("MakePhysicalImmune", 1);
			break;
			case DND_ENERGY_RESIST_POW:
				SetInventory("MonsterTraits", ClearBit(CheckInventory("MonsterTraits"), DND_ENERGY_WEAKNESS_POW));
				GiveInventory("MakeEnergyResist", 1);
			break;
			case DND_ENERGY_IMMUNE_POW:
				SetInventory("MonsterTraits", ClearBit(CheckInventory("MonsterTraits"), DND_ENERGY_WEAKNESS_POW));
				GiveInventory("MakeEnergyImmune", 1);
			break;
			case DND_MAGIC_RESIST_POW:
				SetInventory("MonsterTraits", ClearBit(CheckInventory("MonsterTraits"), DND_MAGIC_WEAKNESS_POW));
				GiveInventory("MakeMagicResist", 1);
			break;
			case DND_MAGIC_IMMUNE_POW:
				SetInventory("MonsterTraits", ClearBit(CheckInventory("MonsterTraits"), DND_MAGIC_WEAKNESS_POW));
				GiveInventory("MakeMagicImmune", 1);
			break;
			case DND_ELEMENTAL_RESIST_POW:
				SetInventory("MonsterTraits", ClearBit(CheckInventory("MonsterTraits"), DND_FIRE_WEAKNESS_POW));
				SetInventory("MonsterTraits", ClearBit(CheckInventory("MonsterTraits"), DND_ICE_WEAKNESS_POW));
				GiveInventory("MakeElementalResist", 1);
			break;
			case DND_ELEMENTAL_IMMUNE_POW:
				SetInventory("MonsterTraits", ClearBit(CheckInventory("MonsterTraits"), DND_FIRE_WEAKNESS_POW));
				SetInventory("MonsterTraits", ClearBit(CheckInventory("MonsterTraits"), DND_ICE_WEAKNESS_POW));
				GiveInventory("MakeElementalImmune", 1);
			break;
			case DND_ARMORPEN:
				// if monster has pierce, remove it
				if(IsSet(CheckInventory("MonsterTraits"), DND_PIERCE_POW))
					SetInventory("MonsterTraits", ClearBit(CheckInventory("MonsterTraits"), DND_PIERCE_POW));
				GiveInventory("MakePierce", 1);
			break;
		}
		SetInventory("MonsterTraits2", CheckInventory("MonsterTraits2") | (1 << f));
	}
}

bool CheckEliteCvar(int t, int flagtype) {
	bool res = 0;
	if(GetCVar("dnd_no_immunity")) {
		res |= (!flagtype && ((t == DND_EXPLOSIVE_NONE_POW))) ||
			   (flagtype && ((t == DND_BULLET_IMMUNE_POW) | (t == DND_ENERGY_IMMUNE_POW) | (t == DND_MAGIC_IMMUNE_POW) | (t == DND_ELEMENTAL_IMMUNE_POW)));
	}
	if(GetCVar("dnd_no_reflect"))
		res |= !flagtype && t == DND_REFLECTIVE_POW;
	return res;
}

bool HasTraitExceptions(int t, int flagtype) {
	if(!flagtype)
		return ((t == DND_EXPLOSIVE_RESIST_POW && IsSet(CheckInventory("MonsterTraits"), DND_EXPLOSIVE_IMMUNE_POW)) || (t == DND_EXPLOSIVE_IMMUNE_POW && IsSet(CheckInventory("MonsterTraits"), DND_EXPLOSIVE_RESIST_POW))) ||
			   ((t == DND_EXPLOSIVE_IMMUNE_POW && IsSet(CheckInventory("MonsterTraits"), DND_EXPLOSIVE_NONE_POW)) || (t == DND_EXPLOSIVE_NONE_POW && IsSet(CheckInventory("MonsterTraits"), DND_EXPLOSIVE_IMMUNE_POW))) ||
			   ((t == DND_EXPLOSIVE_RESIST_POW && IsSet(CheckInventory("MonsterTraits"), DND_EXPLOSIVE_NONE_POW)) || (t == DND_EXPLOSIVE_NONE_POW && IsSet(CheckInventory("MonsterTraits"), DND_EXPLOSIVE_RESIST_POW))) ||
			   ((t == DND_BULLET_RESIST_POW && IsSet(CheckInventory("MonsterTraits2"), DND_BULLET_IMMUNE_POW))) || CheckEliteCvar(t, flagtype);
	else
		return ((t == DND_ENERGY_RESIST_POW && IsSet(CheckInventory("MonsterTraits2"), DND_ENERGY_IMMUNE_POW)) || (t == DND_ENERGY_IMMUNE_POW && IsSet(CheckInventory("MonsterTraits2"), DND_ENERGY_RESIST_POW))) ||
			   ((t == DND_MAGIC_RESIST_POW && IsSet(CheckInventory("MonsterTraits2"), DND_MAGIC_IMMUNE_POW)) || (t == DND_MAGIC_IMMUNE_POW && IsSet(CheckInventory("MonsterTraits2"), DND_MAGIC_RESIST_POW))) ||
			   ((t == DND_ELEMENTAL_RESIST_POW && IsSet(CheckInventory("MonsterTraits2"), DND_ELEMENTAL_IMMUNE_POW))) || ((t == DND_ELEMENTAL_IMMUNE_POW && IsSet(CheckInventory("MonsterTraits2"), DND_ELEMENTAL_RESIST_POW))) ||
			   ((t == DND_BULLET_IMMUNE_POW && IsSet(CheckInventory("MonsterTraits"), DND_BULLET_RESIST_POW))) || CheckEliteCvar(t, flagtype);
}

bool HasMaxImmunes() {
	return !!IsSet("MonsterTraits", DND_EXPLOSIVE_NONE_POW) + 
		   !!IsSet("MonsterTraits2", DND_BULLET_IMMUNE_POW) + 
		   !!IsSet("MonsterTraits2", DND_ENERGY_IMMUNE_POW) +
		   !!IsSet("MonsterTraits2", DND_MAGIC_IMMUNE_POW) +
		   !!IsSet("MonsterTraits2", DND_ELEMENTAL_IMMUNE_POW) >= DND_MAX_ELITEIMMUNITIES;
}

bool IsImmunityFlag(int flag, int flagside) {
	return (!flagside && flag == DND_EXPLOSIVE_NONE_POW) || (flagside && (flag == DND_BULLET_IMMUNE_POW || flag == DND_ENERGY_IMMUNE_POW || flag == DND_MAGIC_IMMUNE_POW || flag == DND_ELEMENTAL_IMMUNE_POW));
}

bool CheckImmunityFlagStatus(int try_trait, int flagside) {
	return !(IsImmunityFlag(try_trait, flagside) && HasMaxImmunes());
}

void DecideEliteTraits(int count) {
	int tries = 0;
	// Run the elite special fx script on this monster
	GiveInventory("RunEliteFXScript", 1);
	while(tries < MAX_ELITE_TRIES && count) {
		str tocheck = "MonsterTraits";
		int flagside = 0;
		int try_trait = GetRandomEliteTrait();
		
		if(try_trait >= ELITE_FLAG2_BEGIN) {
			tocheck = "MonsterTraits2";
			flagside = 1;
		}

		if(!IsSet(CheckInventory(tocheck), EliteTraitNumbers[try_trait])) {
			// dont give explosive immunity with resist etc
			if(!HasTraitExceptions(EliteTraitNumbers[try_trait], flagside) && CheckImmunityFlagStatus(try_trait, flagside)) {
				SetEliteFlag(EliteTraitNumbers[try_trait], flagside);
				--count;
			}
		}
		++tries;
	}
}

#endif