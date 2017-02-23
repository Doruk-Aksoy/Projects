#define MAXWEPS 64
#define MAXLEVELS 100
#define DND_MAX_MONSTERLVL MAXLEVELS
#define MAXWEPSLOTS 9

#define MGNUMID 709
#define BONUSBONUSID 708
#define SECRETBONUSID 707
#define ITEMBONUSID 706
#define KILLBONUSID 705
#define PERKID 704
#define CASHSPLITID 703
#define MENUUSEID 702

// RPG ELEMENTS
int Exp_ColorSet[8] = { 4, 16, 112, 160, 176, 196, 231, 251 };
#define EXP_NUMBER_TID 9000
#define EXP_NUMBER_TID_END 9500
#define MIN_CREDIT_GAIN 7
#define MIN_EXP_GAIN 10
#define STAT_BASE 0
#define STAT_MAX 100
#define PERK_MAX 10
#define BASE_WISDOM_GAIN 10
#define BASE_GREED_GAIN 10
#define PERK_MEDICBONUS 5
#define PERK_MEDICSTOREBONUS 15
#define ATTRIB_PER_LEVEL 2
#define DEFENSE_BONUS 2

#define SHARPSHOOTING_DAMAGE 5
#define ENDURANCE_RESIST 5
#define DND_BULKINESS_GAIN 0.005
#define DND_TALENT_INCREASE 7.5
#define DND_DEX_GAIN 0.1

global int 1: StatListOpened[];

#define MAX_MAP_DIFFICULTIES 5
global int 4: MapDifficulty;
str MapDifficultyLabel[MAX_MAP_DIFFICULTIES] = { "\cdVery Easy\c-", "\cqEasy\c-", "\cfMedium\c-", "\ckHard\c-", "\cgVery Hard\c-" };
global int 5: HardcoreSet;

int LogLookup[5] = { 0xAAAAAAAA, 0xCCCCCCCC, 0xF0F0F0F0, 0xFF00FF00, 0xFFFF0000 };
int LevelCurve[MAXLEVELS + 1] = { 100, 218, 392, 566, 740, 914, 1080, 1270, 1430, 1610, 1790, 1990, 2210, 2430, 2890, 3155, 3475, 3680, 3900, 4275, 4665, 4975, 5275, 5515, 5985, 6255, 6685, 7050, 7700, 8800, 10100, 11400, 13000, 14800, 16900, 19300, 21900, 25000, 28400, 32400, 36900, 41900, 48000, 54000, 62000, 71000, 81000, 92000, 104000, 120000, 136000, 154000, 177000, 200000, 229000, 261000, 297000, 338000, 385000, 437000, 500000, 570000, 650000, 730000, 850000, 960000, 1090000, 1240000, 1420000, 1620000, 1840000, 2090000, 2390000, 2720000, 3100000, 3530000, 4010000, 4500000, 5300000, 5900000, 6800000, 7700000, 8800000, 10000000, 11400000, 13000000, 14800000, 16800000, 19200000, 21900000, 24900000, 28400000, 32300000, 36900000, 41500000, 48000000, 54000000, 62000000, 71000000, 80000000, 80000000 };

int settings[4][2] = {
                        { BT_FORWARD,					0.00 	},
                        { BT_MOVELEFT | BT_LEFT,		0.25	},
                        { BT_BACK,						0.50	},
                        { BT_MOVERIGHT | BT_RIGHT,	    0.75	}
};

enum {	
		RES_STAT_DEX = 1,
		RES_PERK_SHARP = 2,
		RES_PERK_ENDURANCE = 4,
		RES_PERK_CHARISMA = 8,
		RES_PERK_MEDIC = 16
};

#define NANOCAP 150

enum {  
		WEAPON_NAME = 0,
		WEAPON_TAG,
		WEAPON_SLOT,
		WEAPON_AMMO1,
		WEAPON_AMMO2,
		WEAPON_GOT,
		WEAPON_ICON
};
	 
enum {
        RESET_LEVEL = 1,
        RESET_CREDIT = 2,
        RESET_STATS = 4,
        RESET_PERKS = 8
};
		 		 
enum {
	STAT_STR,
	STAT_DEX,
	STAT_BUL,
	STAT_CHR,
	STAT_VIT,
	
	STAT_SHRP,
	STAT_END,
	STAT_WIS,
	STAT_GRE,
	STAT_MED,
	STAT_MUN,
	
	STAT_EXP,
	STAT_LVLEXP,
	STAT_LVL,
	STAT_CRED,
	STAT_LVLCRED
};

str StatNames[STAT_LVLCRED + 1] = {
	"PSTAT_Strength",
	"PSTAT_Dexterity",
	"PSTAT_Bulkiness",
	"PSTAT_Charisma",
	"PSTAT_Vitality",
	
	"Perk_Sharpshooting",
	"Perk_Endurance",
	"Perk_Wisdom",
	"Perk_Greed",
	"Perk_Medic",
	"Perk_Munitionist",
	
	"Exp",
	"LevelExp",
	"Level",
	"Credit",
	"LevelCredit"
};

enum {
	TALENT_BULLET,
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

#define MAX_USER_VARIABLES 1
str Data_Variables[MAX_USER_VARIABLES] = {
    "P_Damage"
};
    
enum {
	WEPINFO_NAME,
	WEPINFO_TAG,
	WEPINFO_SLOT,
	WEPINFO_AMMO1,
	WEPINFO_AMMO2,
	WEPINFO_GOT,
	WEPINFO_ICON
};

str Weapons[MAXWEPS][7] = { 		     
			 { " Fists ",							"Fist",						"1",		" ",				" ",							"StartOnly",				"FISTICO"				},
			 { " Chainsaw ",						"Chainsaw",					"1",		" ",				" ",							"GotChainsaw",				"CSAWA0"				},
			 { "Upgraded Chainsaw",					"Dual Chainsaw",			"1",		" ",				" ",							"GotChainsaw",				"CSW2A0"				},
			 { "Sickle",							"Necromancer's Sickle", 	"1",		" ",				" ",							"GotChainsaw",				"SICKLICO"  			},
			 { "Excalibat",							"Excalibat",				"1",		"BatCharge",		"Souls",						"GotChainsaw",				"EBATICO"				},
			 { " Pistol ",							"Pistol",					"2",		"Clip",				" ",							"StartOnly",				"COLTICO"				},
			 { " Akimbo Pistols ",					"Dual Pistols",				"2",		"Clip",				" ",							"GotAkimbo",				"AKIMICO"				},
			 { "Magnum",							"Magnum",					"2",		"Clip",				"BulletSize_6",			        "GotMagnum",				"MAGNICO"			    },
			 { "Laser Pistol",						"Laser Pistol",				"2",		"LPistolCharge",	" ",							"GotLaserPistol",			"PBLTZ0" 				},
			 { "ScatterGun",						"Scatter Pistol",			"2",		"Clip",				" ",							"GotScatterPistol",			"SPPPA0" 				},
			 { "ResPistol1",						"Assault Rifle",			"2",		"Clip",				"MGClip5",					    "GotAR",					"4AFLA0"				},
			 { " Shotgun ",							"Shotgun",					"3",		"Shell",			"ShellSize_8N",			        "GotShotgun",				"SGN1ICO"				},
			 { "Upgraded Shotgun",					"H. Shotgun",				"3",		"Shell",			"ShellSize_8",			    	"GotShotgun",				"SGP2Z0"				},
			 { "Upgraded Shotgun2",					"Auto Shotgun",				"3",		"Shell",			"ShellSize_10",			        "GotShotgun",				"UASGICO"				},
			 { "ResShotgun1",						"Deadlock",					"3",		"Shell",			"ShellSize_12",			        "GotShotgun",				"RW01X0"				},
             { "ResShotgun2",                       "Nitrogen Crossbow",        "3",        "NitrogenCanister", " ",                            "GotShotgun",               "WBOWA0",               },
             { " Super Shotgun ",					"Super Shotgun",			"3",		"Shell",			" ",							"GotSSG",					"SHS1Z0"				},
			 { "Upgraded Super Shotgun",			"H. S. Shotgun",			"3",		"Shell",			" ",							"GotSSG",					"SSGPA0"				},
			 { "Upgraded Super Shotgun2",		    "Erasus",					"3",		"Shell",			"ShellSize_2",			    	"GotSSG",					"ERASICO"		   		},
			 { "ResSSG1",							"Plasma Cannon",			"3",		"PCanAmmo",			"PCanClip",				    	"GotSSG",					"RW02]0"				},
			 { "Silver Gun",						"Silver Gun",				"3",		"ExplodingShell",	" ",							"GotSilver",				"EXSGX0"				},
			 { "Slayer",							"Slayer",					"3",		"SlayerAmmo",		" ",							"GotSlayer",				"SLYPA0"				},
			 { " Machine gun ", 					"Machine Gun",				"4",		"Clip",				"MGClip",				    	"GotMG",					"WASGA0"				},
			 { "Upgraded Machine Gun",			    "H. Machine Gun",			"4",		"Clip",				"MGClip2",				    	"GotMG",					"WSG2ICO" 			    },
			 { "Upgraded Machine Gun2",			    "Lead Spitter",				"4",		"Clip",				"MGClip3",				    	"GotMG",					"QWOPA0"				},
			 { "ResMG1",							"Templar MG",				"4",		"Clip",				"MGClip4",				    	"GotMG",					"RW03X0"				},
			 { " Minigun ",							"Minigun",					"4",		"Clip",				" ",							"GotCG",					"CHNGX0"				},
			 { "Ebony Cannon",						"Ebony Cannon",				"4",		"EbonyAmmo",		"EbonyAmmoX",			        "GotEbony",					"EBONICO"				},
			 { "Rocket Launcher",					"R. Launcher",				"5",		"RocketAmmo",		" ",							"GotRL",					"LAUNICO"				},
			 { "Upgraded Rocket Launcher",		    "T. Launcher",				"5",		"RocketAmmo",		" ",							"GotRL",					"WPPKG0"				},
			 { "Upgraded Rocket Launcher2",		    "Merc. Launcher",			"5",		"RocketAmmo",		" ",							"GotRL",					"MERCICO"				},
			 { "ResRL1",							"Meteor Launcher",			"5",		"MeteorAmmo",		" ",							"GotRL",					"RW06X0"				},
			 { "Grenade Launcher",					"G. Launcher",				"5",		"Grenades",			" ",							"GotGL",					"NGLPA0"				},
			 { "Upgraded Grenade Launcher",		    "Rotary G. Launcher",		"5",		"Grenades",			" ",							"GotGL",					"RTGLICO"				},
			 { "Heavy Missile Launcher",			"H. M. Launcher",			"5",		"MISAmmo",			" ",							"GotHML",					"WMLNA0"				},
			 { "Plasma Rifle",						"Plasma Rifle",				"6",		"Cell",				" ",							"GotPL",					"NRAIE0"				},
			 { "Upgraded Plasma Rifle",				"Nuclear P. Rifle",			"6",		"Cell",				"PlasmaOverheat",		        "GotPL",					"QNPLX0"				},
			 { "Upgraded Plasma Rifle2",			"Turel Cannon", 			"6",		"Cell",				" ",							"GotPL",					"TURLX0"				},
			 { "ResPlasma1",						"Flamethrower",				"6",		"Fuel",				"FuelClip",					    "GotPL",					"RW05X0"				},
             { "ResPlasma2",                        "Lightning Gun",            "6",        "LightningCell",    "LightningStacks",              "GotPL",                    "LTGSA0"                },
             { "Nailgun",							"Nail Gun",					"6",		"Nail",				" ",							"GotNail",					"NAIGA0"				},
			 { "Basilisk",							"Basilisk",					"6",		"BasiliskAmmo",		"LoadedBasilisk",			    "GotBasilisk",				"BASICO"				},
			 { "BFG 9000",							"BFG 6000",					"7",		"Cell",				" ",							"GotBFG",					"PRDCX0"				},
			 { "Upgraded BFG 9000",					"BFG 32768",				"7",		"Cell",				" ",							"GotBFG",					"DEBFA0"				},
			 { "Devastator",						"Devastator 5000",			"7",		"Cell",				" ",							"GotBFG", 					"DEVAZ0"				},
			 { "MFG",								"Destruction Generator",	"7",		"Cell",				" ",							"GotBFG",					"BFGPA0"				},
			 { "ResBFG1",							"Ion Cannon",				"7",		"IonAmmo",			"IonOverHeat",			        "GotBFG",					"RW04X0"				},
			 { "Gauss Rifle",						"Gauss Rifle",				"7",		"GaussRound",		" ",							"GotBFG",					"GAUSZ0"				},
			 { "Rail gun",							"Rail Gun",					"7",		"Cell",				" ",							"GotRail",					"WRALA0"				},
			 { "Death Staff",						"Death Staff",				"8",		"Souls",			"Souls",						"GotDeath",					"LICICO"				},
			 { "Razorfang",						    "Razorfang",				"8",		"Souls",			"Souls",						"GotRazor",					"WRAZA0"				},
			 { "Sun Staff",							"Sun Staff",				"8",		"Souls",			"Souls",						"GotSun",					"SUNICO"				},
			 { "Soul Reaver",						"Soul Reaver",				"8",		"Souls",			" ",							"GotReaver",				"REAVICO"				},
			 
             { "Sawedoff",							"Sawedoff",					"9",		"SawedoffShell",	"SawedoffCounter",		        "GotSawedoff",				"SAWNICO"			    },
			 { "Soul Render",						"Soul Render",				"9",		"BladeCharge",		"BladeHits",				    "GotSoul",					"SWOICO"			    },
			 { "SMG",								"SMG",						"9",		"SMGAmmo",			" ",							"GotSMG",					"SMGICO"  			    },
			 { "Hellforge Cannon",				    "Hellforge Cannon",			"9",		"IronBalls",		"IronBalls",					"GotHell",					"WHFCA0"  			    },
			 { "Bloodfiend Spine",				    "Bloodfiend Spine",			"9",		"BloodAmmo",		"BloodAmmo",			        "GotGore",					"WGORA0"  			    },
			 { "Enforcer Rifle",					"Enforcer Rifle",			"9",		"LaserAmmo",		"LaserAmmo",			        "GotRifle",					"ENRPA0"  			    },
			 { "Venom",								"Venom",					"9",		"VenomAmmo",		"VenomAmmo",			        "GotVenom",					"VENOICO" 			    },
			 { "Demon Heart",						"Demon Heart",				"9",		"HeartAmmo",		" ",							"GotHeart",					"HARTICO" 			    },
             { "DarkServantGloves",                 "Dark Servant Gloves",      "9",        "DarkServantEnergy"," ",                            "GotGloves",                "DSGNTICO"              },
             { "Nailgun2",                          "Heavy Nailgun",            "9",        "BigNail",          " ",                            "GotNailgun2",              "NLCGF0"                },
             
             // free slots
			 
			 { "", "", "", "", "", "" }
};

enum {
	RES_RAREARMOR,
	RES_SUPERARMOR,
	RES_MEDKITSTORE,
	RES_ACCESSORY,
	
	RES_FLECHETTE,
	RES_PIERCING,
	RES_ELECTRIC,
	
	RES_SONICGRENADE,
	RES_HEGRENADE,
	
	RES_DOUBLESPECIALCAP,
	
	RES_SLOT1OCCULT,
	RES_SLOT2LUXURY,
	RES_SLOT3LUXURY,
	RES_SLOT4LUXURY,
	RES_SLOT5LUXURY,
	RES_SLOT6LUXURY,
	RES_SLOT7LUXURY,
	
	RES_SLOT2UPG1,
	RES_SLOT3UPG1,
    RES_SLOT3UPG2,
	RES_SLOT3SSGUPG1,
	RES_SLOT4UPG1,
	RES_SLOT5UPG1,
	RES_SLOT5GL,
	RES_SLOT6UPG1,
    RES_SLOT6UPG2,
	RES_SLOT7UPG1,
	
	RES_OCCULTABILITY,
	RES_SLOT8REVEAL,
	RES_NANOTECH,
	RES_OCCULTARTIFACT,
};

#define MAX_RESEARCHES RES_OCCULTARTIFACT + 1
str ResearchPrefix = "\ccResearch Item : \c[Y5]Discovered ";
str Research_List[MAX_RESEARCHES] = {
	"RareArmors",
	"SuperArmor",
	"MedkitStore",
	"AccessoryTap",

	"FlechetteShell",
	"PiercingShell",
	"ElectricShell",

	"HEGrenade",
	"SonicGrenade",
	
	"DoubleSpecialCap",

	"Slot1Occult",
	"Slot2Luxury",
	"Slot3Luxury",
	"Slot4Luxury",
	"Slot5Luxury",
	"Slot6Luxury",
	"Slot7Luxury",

	"Slot2Upgrade1",
	"Slot3Upgrade1",
    "Slot3Upgrade2",
	"Slot3SSGUpgrade1",
	"Slot4Upgrade1",
	"Slot5Upgrade1",
	"Slot5GL",
	"Slot6Upgrade1",
    "Slot6Upgrade2",
	"Slot7Upgrade1",

	"OccultAbility",
	"Slot8Reveal",
	"NanoTech",
	"OccultArtifact"
};

str Research_Label[MAX_RESEARCHES] = {
    "Rare Armors",
    "Super Armor",
    "Medikit Storing",
    "Accessory Tap",
   
    "Flechette Shells",
    "Magnum Shells",
    "Electric Shells",
    
    "High Explosive Grenades",
    "Sonic Grenades",
    
    "Special Ammo Holding",
    
    "Slot 1 Occult Weapons",
    "Slot 2 Luxury Weapons",
    "Slot 3 Luxury Weapons",
    "Slot 4 Luxury Weapons",
    "Slot 5 Luxury Weapons",
    "Slot 6 Luxury Weapons",
    "Slot 7 Luxury Weapons",
    
    "Assault Rifle (2)",
    "Deadlock Shotgun (3)",
    "Nitrogen Crossbow (3)",
    "Plasma Cannon (3)",
    "Templar Machine Gun (4)",
    "Meteor Launcher (5)",
    "Grenade Launcher (5)",
    "Flamethrower (6)",
    "Lightning Gun (6)",
    "Ion Cannon (7)",
    
    "Occult Abilities",
    "Slot 8 Weapons",
    "Nano Technology",
    "Occult Artifacts"
};
											
function int IsButtonPressed (int input, int oldInput, int mask) {
	return (input & ~oldInput) & mask;
}
	 
function int IsAccessoryEquipped(int tid, int acc) {
	if(!acc)
		return 0;
	return CheckActorInventory(tid, "Accessory_Top_Index") == acc || CheckActorInventory(tid, "Accessory_Bot_Index") == acc;
}

// Generic Player RPG Stat restore function
function void RestoreRPGStat (int statflag) {
	if((statflag & RES_PERK_SHARP) && CheckInventory("Perk_Sharpshooting")) {
		GiveInventory(StrParam(s:"Damage_Perk_", d:CheckInventory("Perk_Sharpshooting") * SHARPSHOOTING_DAMAGE), 1);
	}
	if((statflag & RES_PERK_ENDURANCE) && CheckInventory("Perk_Endurance"))
		GiveInventory(StrParam(s:"Resist_Perk_", d:CheckInventory("Perk_Endurance") * ENDURANCE_RESIST), 1);
	if(IsAccessoryEquipped(ActivatorTID(), ACC_FIRE))
		GiveInventory("Accessory_FireProtection", 1);
	// can only intervene once per map
	if(IsAccessoryEquipped(ActivatorTID(), ACC_ANGELIC) && !CheckInventory("Intervened")) {
		GiveInventory("CanIntervene", 1);
		SetPlayerProperty(0, 1, PROP_BUDDHA);
	}
	if(CheckInventory("HateCheck"))
		GiveInventory("PowerReflection", 1);
	if(CheckInventory("Ability_AntiPoison"))
		GiveInventory("PoisonImmunity", 1);
	if(CheckInventory("ArtemisCheck"))
		GiveInventory("ArtemisPower", 1);
	if(CheckInventory("GryphonCheck")) {
		GiveInventory("GryphonSpeed", 1);
		GiveInventory("CurseImmunity", 1);
	}
	if(CheckInventory("LichCheck"))
		GiveInventory("LichPower", 1);
}

function int CheckSuperWeaponPickup (void) {
	if(CheckInventory("Death Staff") || CheckInventory("Razorfang") || 
	   CheckInventory("Sun Staff")  || CheckInventory("Soul Reaver"))
		  return 1;
	return 0;
}

// Copied from ZDWiki.
// Fixed-point version, only works up to 30,000 or so:
function int fsqrt(int number) 
{ 
  int samples = 15; // Samples for accuracy

  if (number == 1.0) return 1.0; 
  if (number <= 0) return 0;
  int val = samples<<17 + samples<<19; // x*10 = x<<1 + x<<3
  for (int i=0; i<samples; ++i) 
    val = (val + FixedDiv(number, val)) >> 1;

  return val; 
}

function int sqrt_z(int number)
{
	if(number <= 3)
	{
		if(number > 0)
		{
			return 1;
		}
		return 0;
	}
	
	int oldAns = number >> 1,                     
	    newAns = (oldAns + number / oldAns) >> 1; 
	
	while(newAns < oldAns)
	{
		oldAns = newAns;
		newAns = (oldAns + number / oldAns) >> 1;
	}

	return oldAns;
}

function int Min(int x, int y) {
	if(x < y)
		return x;
	return y;
}

function int magnitudeThree(int x, int y, int z)
{
    return sqrt_z(x*x + y*y + z*z);
}

function int GetCurrentWeaponID (void) {
	int res = 0;
	for(int i = 0; i < MAXWEPS; ++i) {
		if(CheckWeapon(Weapons[i][WEAPON_NAME])) {
			res = i;
			break;
		}
	}
	return res;
}

function str GetWeaponAmmoType (int wepid, int which) {
	if(!which)
		return Weapons[wepid][WEAPON_AMMO1];
	else
		return Weapons[wepid][WEAPON_AMMO2];
}

function int log2 (int num) {
	int r = (num & LogLookup[0]) != 0;
	for (int i = 4; i > 0; i--) {
	    r |= ((num & LogLookup[i]) != 0) << i;
	}
	return r;
}

function int GetPlayerNumber() {
	return CheckInventory("PNum");
}

struct p_stat {
	int strn; // strength: melee damage
	int dex; // dexterity: talent bonus
	int bul; // bulkiness: armor efficiency
	int chr; // charisma: reduces shop prices
	int vit; // vitality: health capacity increase
	
	int shrp;
	int end;
	int wisdom;
	int greed;
	int medic;
	int munitionist;
};

struct p_info {
	int exp;
	int level_exp;
	int level;
	int credit;
	int level_credit;
	struct p_stat stat_info;
};

function int GetStat(int stat_id) {
	return CheckInventory(StatNames[stat_id]);
}

function int GetActorStat(int tid, int stat_id) {
	return CheckActorInventory(tid, StatNames[stat_id]);
}

function void GiveActorExp(int tid, int amt) {
	GiveActorInventory(tid, "Exp", amt);
	GiveActorInventory(tid, "ExpVisual", amt);
	GiveActorInventory(tid, "SpreeXP", amt);
	GiveActorInventory(tid, "LevelExp", amt);
}

function void GiveActorCredit(int tid, int amt) {
	GiveActorInventory(tid, "Credit", amt);
	GiveActorInventory(tid, "LevelCredit", amt);
}

function int IsHardcore() {
	return HardcoreSet;
}

enum {
	RES_NA,
	RES_KNOWN,
	RES_DONE
};

// 0 for NA, 1 for found, 2 for researched
function int CheckResearchStatus(int res_id) {
	if(CheckInventory(StrParam(s:"Done_", s:Research_List[res_id])))
		return RES_DONE;
	if(CheckInventory(StrParam(s:"Research_", s:Research_List[res_id])))
		return RES_KNOWN;
	return RES_NA;
}

function void GiveResearch(int res_id) {
	GiveInventory(StrParam(s:"Research_", s:Research_List[res_id]), 1);
}

function void CompleteResearch(int res_id) {
	GiveInventory(StrParam(s:"Done_", s:Research_List[res_id]), 1);
}

function void GiveAndDoAllResearch() {
	for(int i = 0; i < MAX_RESEARCHES; ++i) {
		GiveResearch(i);
		CompleteResearch(i);
	}
	GiveInventory("MedkitItem", 1);
	DoubleSpecialAmmoCapacity();
}

enum {
	SSAM_FLECHETTE,
	SSAM_MAGNUM,
	SSAM_SHOCK,
	
	SSAM_40MMHE,
	SSAM_40MMSONIC
};

#define MAX_SPECIAL_AMMOS SSAM_40MMSONIC + 1
str SuperSpecialAmmos[MAX_SPECIAL_AMMOS] = {
	"FlechetteShell", 
	"PiercingShell",
	"ElectricShell",
	
	"A40mmSonicGrenade",
	"A40mmHEGrenade"
};

function void DoubleSpecialAmmoCapacity() {
	for(int i = 0; i < MAX_SPECIAL_AMMOS; ++i)
		SetAmmoCapacity(SuperSpecialAmmos[i], GetAmmoCapacity(SuperSpecialAmmos[i]) * 2);
}