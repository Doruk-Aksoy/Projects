#ifndef DND_EXP_IN
#define DND_EXP_IN

#include "DnD_Quests.h"
#include "DnD_Common.h"

#define DND_BASE_PLAYERSPEED 1.0

#define SHARPSHOOTING_DAMAGE 5
#define ENDURANCE_RESIST 5
#define DND_BULKINESS_GAIN 0.0075
#define DND_TALENT_INCREASE 5.0
#define DND_DEX_GAIN 0.15
#define DND_INT_GAIN 0.15
#define DND_VIT_INCREASE 4
#define DND_STR_GAIN 0.9
#define DND_ARMOR_PER_STR 3
#define DND_CHR_GAIN 0.5
#define DND_LUCK_GAIN 0.015
#define DND_TALENTCAPSULE_DROPRATE 0.015
#define DND_TALENTPOINT_MARK 4

#define DND_STAT_FULLMAX 200
#define DND_BASE_ARMOR 200
#define DND_BASE_ARMORCAP 300
#define DND_PERK_MAX 10

// RPG ELEMENTS
int Exp_ColorSet[8] = { 4, 16, 112, 160, 176, 196, 231, 251 };
#define EXP_NUMBER_TID 9000
#define EXP_NUMBER_TID_END 9500

int LevelCurve[MAXLEVELS + 1] = { 100, 264, 480, 696, 912, 1128, 1340, 1560, 1780, 1990, 2210, 2420, 2640, 2860, 4200, 5800, 6100, 6600, 6900, 8350, 9900, 10300, 10900, 11400, 11800, 12300, 12800, 13300, 13800, 14300, 19000, 22700, 27000, 31900, 37900, 45000, 53300, 63000, 75000, 89000, 105000, 125000, 149000, 175000, 209000, 247000, 294000, 348000, 412000, 490000, 579000, 680000, 820000, 970000, 1150000, 1360000, 1610000, 1920000, 2270000, 2690000, 3200000, 3780000, 4490000, 5260000, 6300000, 7500000, 8900000, 10600000, 12500000, 14800000, 17500000, 20900000, 24700000, 29300000, 34800000, 41200000, 48900000, 57200000, 69000000, 82000000, 96000000, 115000000, 136000000, 161000000, 192000000, 227000000, 269000000, 319000000, 378000000, 449000000, 528000000, 630000000, 750000000, 890000000, 1050000000, 1250000000, 1480000000, 1750000000, 2090000000, 2147483647, 2147483647 };

int GetExpLimit() {
	return LevelCurve[GetStat(STAT_LVL) - 1];
}

enum {
	TALENT_BULLET = 0,
	TALENT_SHELL,
	TALENT_MELEE,
	TALENT_OCCULT,
	TALENT_EXPLOSIVE,
	TALENT_ENERGY,
    TALENT_ELEMENTAL
};

#define MAX_TALENTS TALENT_ELEMENTAL + 1
str TalentNames[MAX_TALENTS] = {
	"Talent_Bullet",
	"Talent_Shell",
	"Talent_Melee",
	"Talent_Occult",
	"Talent_Explosive",
	"Talent_Energy",
    "Talent_Elemental"
};

str TalentTypeNames[MAX_TALENTS] = {
	"Bullet",
	"Shell",
	"Melee",
	"Occult",
	"Explosive",
	"Energy",
    "Elemental"
};

typedef struct {
	int prosperity_orb_bonus;
	int fortitude_orb_bonus;
	
	int hp_flat_bonus;
	int armor_flat_bonus;
	
	int hp_percent_bonus;
	int armor_percent_bonus;
	
	int greed_percent_bonus;
	int wisdom_percent_bonus;
	
	int speed_bonus;
	int drop_chance;
	int holding;
	
	int damage_type_bonus[MAX_TALENTS];
} pstat_T;

global pstat_T 4: Player_Bonuses[MAXPLAYERS];

enum {
	STAT_STR,
	STAT_DEX,
	STAT_BUL,
	STAT_CHR,
	STAT_VIT,
	STAT_INT,
	
	STAT_SHRP,
	STAT_END,
	STAT_WIS,
	STAT_GRE,
	STAT_MED,
	STAT_MUN,
    STAT_DED,
	STAT_SAV,
	STAT_LUCK,
	
	STAT_EXP,
	STAT_LVLEXP,
	STAT_LVL,
	STAT_CRED,
	STAT_LVLCRED
};

#define DND_ATTRIB_BEGIN STAT_STR
#define DND_ATTRIB_END STAT_INT
#define DND_PERK_BEGIN STAT_SHRP
#define DND_PERK_END STAT_LUCK

enum {	
	RES_STAT_DEX = 1,
	RES_PERK_SHARP = 2,
	RES_PERK_ENDURANCE = 4,
	RES_PERK_CHARISMA = 8,
	RES_PERK_MEDIC = 16,
	RES_PERK_MUNITIONIST = 32,
	RES_PERK_DEADLINESS = 64,
	RES_PERK_SAVAGERY = 128,
	RES_PERK_LUCK = 256,
	RES_PLAYERSPEED = 512
};

#define DND_PERKS DND_PERK_END - DND_PERK_BEGIN + 1

str StatLabels[STAT_LVLCRED + 1] = {
	"Strength",
	"Dexterity",
	"Bulkiness",
	"Charisma",
	"Vitality",
	"Intellect",
	
	"Sharpshooting",
	"Endurance",
	"Wisdom",
	"Greed",
	"Medic",
	"Munitionist",
	"Deadliness",
	"Savagery",
	"Luck",
	
	"Experience",
	"Level Experience",
	"Level",
	"Credit",
	"Level Credit"
};

str StatNames[STAT_LVLCRED + 1] = {
	"PSTAT_Strength",
	"PSTAT_Dexterity",
	"PSTAT_Bulkiness",
	"PSTAT_Charisma",
	"PSTAT_Vitality",
	"PSTAT_Intellect",
	
	"Perk_Sharpshooting",
	"Perk_Endurance",
	"Perk_Wisdom",
	"Perk_Greed",
	"Perk_Medic",
	"Perk_Munitionist",
    "Perk_Deadliness",
	"Perk_Savagery",
	"Perk_Luck",
	
	"Exp",
	"LevelExp",
	"Level",
	"Credit",
	"LevelCredit"
};

enum {
	DND_ACCESSORY_TALISMANWISDOM = 1,
	DND_ACCESSORY_TALISMANGREED = 2,
	DND_ACCESSORY_DEMONBANE = 4,
	DND_ACCESSORY_AMULETHELLFIRE = 8,
	DND_ACCESSORY_ANGELICANKH = 16,
	DND_ACCESSORY_PENDANTREFLECTION = 32,
	DND_ACCESSORY_NETHERMASK = 64,
	DND_ACCESSORY_TALTOSRING = 128,
	DND_ACCESSORY_HATESHARD = 256,
	DND_ACCESSORY_HANDARTEMIS = 512,
	DND_ACCESSORY_AGAMOTTO = 1024,
	DND_ACCESSORY_GRYPHONBOOTS = 2048,
	DND_ACCESSORY_LICHARM = 4096,
	DND_ACCESSORY_SIGILELEMENTS = 8192
};
#define MAX_ACCESSORY 14
#define DND_ACCESSORY_BASELIMIT 2

enum {
	DND_ARMOR_BONUS,
	DND_ARMOR_GREEN,
	DND_ARMOR_YELLOW,
	DND_ARMOR_BLUE,
	DND_ARMOR_RED,
	
	DND_ARMOR_GUNSLINGER,
	DND_ARMOR_OCCULT,
	DND_ARMOR_DEMO,
	DND_ARMOR_ENERGY,
	DND_ARMOR_ELEMENTAL,
	
	DND_ARMOR_SUPER,
	DND_ARMOR_CYBERNETIC,
	DND_ARMOR_DUELIST,
	DND_ARMOR_NECRO,
	DND_ARMOR_KNIGHT,
	DND_ARMOR_RAVAGER
};
#define MAXARMORS DND_ARMOR_RAVAGER + 1

str ArmorTypes[MAXARMORS] = {
	"ArmorBonus",
	"NewGreenArmor",
	"YellowArmor",
	"NewBlueArmor",
	"TheRedArmor",
	
	"GunSlingerArmor",
	"OccultArmor",
	"DemoArmor",
	"EnergyArmor",
	"ElementalArmor",
	
	"SuperArmor",
	"CyberneticArmor",
	"DuelistArmor",
	"NecroArmor",
	"KnightArmor",
	"RavagerArmor"
};

int ArmorBaseAmounts[MAXARMORS] = {
	1,
	100,
	150,
	200,
	300,
	
	150,
	150,
	150,
	150,
	150,
	
	400,
	200,
	150,
	200,
	250,
	150
};

int GetStat(int stat_id) {
	return CheckInventory(StatNames[stat_id]);
}

int GetActorStat(int tid, int stat_id) {
	return CheckActorInventory(tid, StatNames[stat_id]);
}

void GiveStat(int stat_id, int amt) {
	SetInventory(StatNames[stat_id], Clamp_Between(CheckInventory(StatNames[stat_id]) + amt, 0, DND_STAT_FULLMAX));
}

void GiveActorStat(int tid, int stat_id, int amt) {
	SetActorInventory(tid, StatNames[stat_id], Clamp_Between(CheckActorInventory(tid, StatNames[stat_id]) + amt, 0, DND_STAT_FULLMAX));
}

void GiveExp(int amt) {
	GiveInventory("Exp", amt);
	GiveInventory("ExpVisual", amt);
	GiveInventory("SpreeXP", amt);
	GiveInventory("LevelExp", amt);
}

void GiveActorExp(int tid, int amt) {
	GiveActorInventory(tid, "Exp", amt);
	GiveActorInventory(tid, "ExpVisual", amt);
	GiveActorInventory(tid, "SpreeXP", amt);
	GiveActorInventory(tid, "LevelExp", amt);
}

void GiveCredit(int amt) {
	GiveInventory("Credit", amt);
	GiveInventory("LevelCredit", amt);
}

void GiveBudget(int amt) {
	GiveInventory("Budget", amt);
}

void GiveActorCredit(int tid, int amt) {
	GiveActorInventory(tid, "Credit", amt);
	GiveActorInventory(tid, "LevelCredit", amt);
}

int GetBonusPlayerSpeed(int pnum) {
	int res = Player_Bonuses[pnum].speed_bonus;
	// add other stuff here
	return res;
}

int GetPlayerSpeed(int pnum) {
	return DND_BASE_PLAYERSPEED + GetBonusPlayerSpeed(pnum);
}

// Generic Player RPG Stat restore function
void RestoreRPGStat (int statflag) {
	if((statflag & RES_PERK_SHARP) && CheckInventory("Perk_Sharpshooting")) {
		GiveInventory(StrParam(s:"Damage_Perk_", d:CheckInventory("Perk_Sharpshooting") * SHARPSHOOTING_DAMAGE), 1);
	}
	if((statflag & RES_PERK_ENDURANCE) && CheckInventory("Perk_Endurance"))
		GiveInventory(StrParam(s:"Resist_Perk_", d:CheckInventory("Perk_Endurance") * ENDURANCE_RESIST), 1);
	if(IsAccessoryEquipped(ActivatorTID(), DND_ACCESSORY_AMULETHELLFIRE))
		GiveInventory("Accessory_FireProtection", 1);
	// can only intervene once per map
	if(IsAccessoryEquipped(ActivatorTID(), DND_ACCESSORY_ANGELICANKH) && !CheckInventory("Intervened")) {
		GiveInventory("CanIntervene", 1);
		SetPlayerProperty(0, 1, PROP_BUDDHA);
	}
	if(statflag & RES_PLAYERSPEED)
		SetActorProperty(0, APROP_SPEED, GetPlayerSpeed(PlayerNumber()));
	
	if(CheckInventory("HateCheck"))
		GiveInventory("PowerReflection", 1);
	if(CheckInventory("Ability_AntiPoison"))
		GiveInventory("PoisonImmunity", 1);
	/*if(CheckInventory("ArtemisCheck"))
		GiveInventory("ArtemisPower", 1);*/
	if(CheckInventory("GryphonCheck")) {
		GiveInventory("GryphonSpeed", 1);
		GiveInventory("CurseImmunity", 1);
	}
	if(CheckInventory("LichCheck"))
		GiveInventory("LichPower", 1);
	
	// So the player respawns with his actual new max hp
	SetActorProperty(0, APROP_SPAWNHEALTH, GetSpawnHealth());
}

int IsAccessoryEquipped(int tid, int acc) {
	if(tid)
		return CheckActorInventory(tid, "Accessory_Index") & acc;
	return CheckInventory("Accessory_Index") & acc;
}

bool ReachedAccessoryLimit() {
	// consider accessory limit enhancement here
	int baselimit = DND_ACCESSORY_BASELIMIT;
	int cur = CheckInventory("Accessory_Index");
	int count = 0;
	// counts bits of 1
	while(cur && count < baselimit) {
		if(cur & 1)
			++count;
		cur >>= 1;
	}
	return count >= baselimit;
}

void EquipAccessory(int acc) {
	SetInventory("Accessory_Index", CheckInventory("Accessory_Index") | acc);
	DecideAccessories();
}

void UnequipAccessory(int acc) {
	SetInventory("Accessory_Index", CheckInventory("Accessory_Index") & ~acc);
	DecideAccessories();
}

int CalculateHealthCapBonuses() {
	// consider quest bonuses
	int res = 0;
	res += CheckInventory("DnD_QuestReward_100BonusCap") * DND_QUEST_PRECIOUSLIFE_BONUS;
	res += CheckInventory("DnD_QuestReward_HealingAndCapIncrease") * DND_QUEST_SKINOTEETH_BONUS;
	// consider charms
	res += Player_Bonuses[PlayerNumber()].hp_flat_bonus;
	// consider orb effects
	res += Player_Bonuses[PlayerNumber()].prosperity_orb_bonus;
	
	return res;
}

int GetSpawnHealth() {
	int res = CalculateHealthCapBonuses() + DND_BASE_HEALTH + DND_VIT_INCREASE * CheckInventory("PSTAT_Vitality");
	// consider percent bonuses
	res += (res * (Player_Bonuses[PlayerNumber()].fortitude_orb_bonus) + DND_TORRASQUE_BOOST * CheckInventory("DnD_QuestReward_TorrasqueBonus")) / 100;
	if(IsAccessoryEquipped(ActivatorTID(), DND_ACCESSORY_ANGELICANKH))
		res >>= 1;
	if(res < DND_BASE_HEALTH)
		res = DND_BASE_HEALTH;
	return res;
}

int CalculateArmorCapBonuses() {
	int res = CheckInventory("DnD_QuestReward_ArmorCapIncrease") * DND_QUEST_ARMORBONUS;
	
	// consider orb effects
	res += Player_Bonuses[PlayerNumber()].prosperity_orb_bonus;
	
	return res;
}

// used for displaying to hud
int GetArmorCap() {
	int res = CalculateArmorCapBonuses() + DND_BASE_ARMOR + DND_ARMOR_PER_STR * CheckInventory("PSTAT_Strength");
	res += (res * (Player_Bonuses[PlayerNumber()].fortitude_orb_bonus) + DND_TORRASQUE_BOOST * CheckInventory("DnD_QuestReward_TorrasqueBonus")) / 100;
	return res;
}

// used for deciding armor pickup values
int GetArmorSpecificCap(int amt) {
	if(amt != 1) { // exception for armor bonus
		amt += CalculateArmorCapBonuses() + DND_ARMOR_PER_STR * CheckInventory("PSTAT_Strength");
		amt += (amt * Player_Bonuses[PlayerNumber()].fortitude_orb_bonus) / 100;
	}
	else
		amt = GetArmorCap();
	return amt;
}

// compare armor types t1 and t2, check if t1 is of higher tier than t2
// tier only matters for armors green to red, rest from menu replace whatever you have either way
int IsArmorTierHigher(int t1, int t2) {
	return ArmorBaseAmounts[t1] > ArmorBaseAmounts[t2];
}

void HandleArmorPickup(int armor_type, int amount) {
	int armor = CheckInventory("Armor"), cap = 0;
	if(armor_type == DND_ARMOR_BONUS) {
		// if we had no armor
		if(!armor) {
			SetInventory("DnD_ArmorType", armor_type + 1);
			cap = GetArmorCap();
		}
		else
			cap = GetArmorSpecificCap(ArmorBaseAmounts[CheckInventory("DnD_ArmorType") - 1]) << 1;
		// just add 1 to current armor if meets requirements
		if(CheckInventory("Armor") < cap)
			GiveInventory("DnD_ArmorBonus", 1);
	}
	else {
		// only give the actual armor if my tier is higher!
		if(IsArmorTierHigher(armor_type, CheckInventory("DnD_ArmorType") - 1)) {
			// gross hacks
			SetInventory("Armor", 0);
			GiveInventory(ArmorTypes[armor_type], 1);
			// prevent armor downgrades
			GiveInventory("DnD_ArmorBonus", armor - 1);
			SetInventory("DnD_ArmorType", armor_type + 1);
		}
		
		/*if(armor) // if we had armor, retain it
			GiveInventory("DnD_ArmorBonus", armor - 1);*/
			
		armor = CheckInventory("Armor");
		// respect the cap of the currently equipped armor
		cap = GetArmorSpecificCap(ArmorBaseAmounts[CheckInventory("DnD_ArmorType") - 1]);
		// set armor count
		if(armor + amount > cap)
			GiveInventory("DnD_ArmorBonus", cap - armor);
		else
			GiveInventory("DnD_ArmorBonus", amount);
	}
}

int Calculate_Stats() {
	int res = 0;
	for(int i = DND_ATTRIB_BEGIN; i <= DND_ATTRIB_END; ++i)
		res += CheckInventory(StatNames[i]);
	return res;
}

int Calculate_Perks() {
	int res = 0;
	for(int i = DND_PERK_BEGIN; i <= DND_PERK_END; ++i)
		res += CheckInventory(StatNames[i]);
	return res;
}

int GetDropChance(int pnum, bool isElite) {
	int base = Player_Bonuses[pnum].drop_chance + DND_LUCK_GAIN * CheckActorInventory(pnum + P_TIDSTART, "Perk_Luck");
	if(isElite) {
		if(CheckActorInventory(pnum + P_TIDSTART, "DnD_QuestReward_EliteDropBonus"))
			base += DND_ELITEDROP_GAIN;
	}
	return base;
}

bool RunDefaultDropChance(int pnum, bool isElite, int basechance) {
	return RunDropChance(pnum, isElite, basechance, 0, 1.0);
}

bool RunDropChance(int pnum, bool isElite, int basechance, int low, int high) {
	return GetDropChance(pnum, isElite) + basechance >= random(low, high);
}

void DecideAccessories() {
	int this = ActivatorTID();
	if(IsAccessoryEquipped(this, DND_ACCESSORY_AMULETHELLFIRE))
		GiveInventory("Accessory_FireProtection", 1);
	else
		TakeInventory("Accessory_FireProtection", 1);
		
	if(IsAccessoryEquipped(this, DND_ACCESSORY_ANGELICANKH)) {
		if(!CheckInventory("Intervened")) {
			SetPlayerProperty(0, 1, PROP_BUDDHA);
			GiveInventory("CanIntervene", 1);
		}
	}
	else {
		SetPlayerProperty(0, 0, PROP_BUDDHA);
		TakeInventory("CanIntervene", 1);
	}
	
	if(IsAccessoryEquipped(this, DND_ACCESSORY_DEMONBANE))
		GiveInventory("DemonBaneReduction", 1);
	else
		TakeInventory("DemonBaneReduction", 1);
	
	if(IsAccessoryEquipped(this, DND_ACCESSORY_PENDANTREFLECTION))
		GiveInventory("CanDeflect", 1);
	else
		TakeInventory("CanDeflect", 1);
		
	if(IsAccessoryEquipped(this, DND_ACCESSORY_NETHERMASK)) {
		GiveInventory("NetherCheck", 1);
		GiveInventory("NetherWeaken", 1);
	}
	else {
		TakeInventory("NetherCheck", 1);
		TakeInventory("NetherWeaken", 1);
	}
		
	if(IsAccessoryEquipped(this, DND_ACCESSORY_TALTOSRING)) {
		GiveInventory("TaltosEffect", 1);
		GiveInventory("TaltosUp", 1);
	}
	else {
		GiveInventory("TaltosUnsetEffect", 1);
		TakeInventory("TaltosUp", 1);
	}
	
	if(IsAccessoryEquipped(this, DND_ACCESSORY_HATESHARD)) {
		GiveInventory("HateCheck", 1);
		GiveInventory("PowerReflection", 1);
		GiveInventory("HateReduction", 1);
	}
	else {
		TakeInventory("PowerReflection", 1);
		TakeInventory("HateCheck", 1);
		TakeInventory("HateReduction", 1);
	}
	
	if(IsAccessoryEquipped(this, DND_ACCESSORY_HANDARTEMIS)) {
		GiveInventory("ArtemisPower", 1);
		GiveInventory("ArtemisCheck", 1);
		GiveInventory("ArtemisReduction", 1);
	}
	else {
		TakeInventory("ArtemisPower", 1);
		TakeInventory("ArtemisCheck", 1);
		TakeInventory("ArtemisReduction", 1);
	}
	
	if(IsAccessoryEquipped(this, DND_ACCESSORY_AGAMOTTO))
		GiveInventory("AgamottoCheck", 1);
	else
		TakeInventory("AgamottoCheck", 1);
	
	if(IsAccessoryEquipped(this, DND_ACCESSORY_GRYPHONBOOTS)) {
		GiveInventory("CurseImmunity", 1);
		GiveInventory("GryphonCheck", 1);
		GiveInventory("GryphonSpeed", 1);
	}
	else {
		TakeInventory("CurseImmunity", 1);
		TakeInventory("GryphonCheck", 1);
		TakeInventory("GryphonSpeed", 1);
	}
	
	if(IsAccessoryEquipped(this, DND_ACCESSORY_LICHARM)) {
		GiveInventory("LichCheck", 1);
		GiveInventory("LichPower", 1);
		SetAmmoCapacity("Souls", 150);
	}
	else {
		TakeInventory("LichCheck", 1);
		TakeInventory("LichPower", 1);
		if(CheckInventory("Souls") > 75) // yea this is bad but o well
			SetInventory("Souls", 75);
		SetAmmoCapacity("Souls", 75);
	}
	
	// sigil order: 1 = fire, 2 = ice, 3 = lightning, 4 = poison
	if(IsAccessoryEquipped(this, DND_ACCESSORY_SIGILELEMENTS))
		SetInventory("SigilCheck", 1);
	else {
		SetInventory("SigilCheck", 0);
		TakeInventory("ElementPower_Fire", 1);
		TakeInventory("ElementPower_Ice", 1);
		TakeInventory("ElementPower_Lightning", 1);
		TakeInventory("ElementPower_Earth", 1);
	}
}

bool HasNoSigilPower() {
	return !CheckInventory("ElementPower_Fire") && !CheckInventory("ElementPower_Ice") && !CheckInventory("ElementPower_Lightning") && !CheckInventory("ElementPower_Earth");
}

void ResetPlayerBonuses(int pnum) {
	Player_Bonuses[pnum].prosperity_orb_bonus = 0;
	Player_Bonuses[pnum].fortitude_orb_bonus = 0;
	
	Player_Bonuses[pnum].hp_flat_bonus = 0;
	Player_Bonuses[pnum].armor_flat_bonus = 0;
	
	Player_Bonuses[pnum].hp_percent_bonus = 0;
	Player_Bonuses[pnum].armor_percent_bonus = 0;
	
	Player_Bonuses[pnum].greed_percent_bonus = 0;
	Player_Bonuses[pnum].wisdom_percent_bonus = 0;
	
	Player_Bonuses[pnum].speed_bonus = 0;
	Player_Bonuses[pnum].drop_chance = 0;
	Player_Bonuses[pnum].holding = 0;
	
	for(int i = 0; i < MAX_TALENTS; ++i)
		Player_Bonuses[pnum].damage_type_bonus[i] = 0;
}

// Takes a stat from the player, also removing effects of it
void TakeStat(int stat_id, int amt) {
	TakeInventory(StatNames[stat_id], amt);
}

void UpdatePerkStuff() {
	if(CheckInventory("Perk_SharpShooting") > 1) // Take previous powerup so they don't stack
		TakeInventory(StrParam(s:"Damage_Perk_", d:(CheckInventory("Perk_Sharpshooting") - 1) * 5), 1);
	if(CheckInventory("Perk_Endurance") > 1) // Take previous powerup so they don't stack
		TakeInventory(StrParam(s:"Resist_Perk_", d:(CheckInventory("Perk_Endurance") - 1) * 5), 1);
	RestoreRPGStat(RES_PERK_SHARP | RES_PERK_ENDURANCE);
	SetAmmoCapacity("StoredMedkit", GetAmmoCapacity("StoredMedkit") + 15 * CheckInventory("Perk_Medic"));
}

enum {
	SF_FREEZE = 1
};

void SlowPlayer(int amt, int mode, int pnum) {
	if(!pnum)
		pnum = PlayerNumber();
	if(mode & SF_FREEZE) {
		SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
		SetActorProperty(0, APROP_SPEED, 0.0);
		GiveInventory("P_Frozen", 1);
	}
	else
		SetActorProperty(P_TIDSTART + pnum, APROP_SPEED, GetPlayerSpeed(pnum) - amt);
}

bool HasKilledLegendary(int id) {
	return IsSet(CheckInventory("LegendaryKills"), id);
}

void UpdateLegendaryKill(int pnum, int mon_id) {
	SetActorInventory(pnum + P_TIDSTART, "LegendaryKills", CheckActorInventory(pnum + P_TIDSTART, "LegendaryKills") | (1 << mon_id));
}

#endif