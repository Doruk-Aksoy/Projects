#include "DnD_Defs.h"

#define PRICE_CHARISMAREDUCE 1
#define STR_GAIN 4
#define SHOP_SCALE_MAX 10

#define CHARISMA_PERCENT 5 // percentage
#define CHARISMA_DIV 10 // for fractional
#define CHARISMA_REDUCE CHARISMA_DIV / CHARISMA_PERCENT

#define TALENT_CAP 100

// Input Listener Flags
enum { 
	   LISTEN_LEFT = 1,
	   LISTEN_RIGHT = 2,
	   LISTEN_UP = 4,
	   LISTEN_DOWN = 8,
	   LIF_FIXATMAX_Y = 16,
	   LIF_USEMAIN_Y = 32
	 };

// Object definitions for shop
enum { 
	   OBJ_WEP = 1,
	   OBJ_AMMO = 2,
	   OBJ_ABILITY = 4,
	   OBJ_ARTI = 8,
	   OBJ_TALENT = 16,
	   OBJ_ARMOR = 32, // color those that can only be had 1 in a category as a different color
	   OBJ_HASCHOICE = 64,
	   OBJ_RESEARCH = 128 // requires some research to be available
	 };

// Trade options
enum {
		TRADE_BUY = 1,
		TRADE_SELL = 2,
		TRADE_WEAPON = 4,
		TRADE_AMMO = 8,
		TRADE_ABILITY = 16,
		TRADE_ARTIFACT = 32,
		TRADE_TALENT = 64,
		TRADE_ARMOR = 128
	 };

// Popup Definitions
enum {
		POPUP_ERROR,
		POPUP_SELL
	 };
	 
 // MENU IDS
#define RPGMENUID 701
#define RPGMENULISTID 700
#define RPGMENUINFOID 691
#define RPGMENUHELPID 690
#define RPGMENUNAMEID 689
#define RPGMENUHELPCORNERID 688
#define RPGMENUITEMID 687
#define RPGMENUITEMIDEND 500
	 
enum {
	TYPE_WEAPON,
	TYPE_AMMO,
	TYPE_ABILITY,
	TYPE_TALENT,
	TYPE_ARTI,
	TYPE_ARMOR
};

// These are moved from menu to here because now, the limits are varying. We will update this array size depending on researches
// Page definitions
enum { 
			MENU_NULL,
			MENU_STAT1,
			MENU_STAT2,
			MENU_PERK,
			MENU_LOAD,
			MENU_LOAD2,
			MENU_LOAD3,
			MENU_LOAD4,
			MENU_SHOP,
			MENU_SHOP_WEAPON,
			MENU_SHOP_WEAPON1,
			MENU_SHOP_WEAPON2,
			MENU_SHOP_WEAPON3,
			MENU_SHOP_WEAPON4,
			MENU_SHOP_WEAPON5,
			MENU_SHOP_WEAPON6,
			MENU_SHOP_WEAPON7,
			MENU_SHOP_WEAPON8,
			MENU_SHOP_AMMO1,
			MENU_SHOP_AMMO2,
			MENU_SHOP_AMMO3,
            MENU_SHOP_AMMO_SPECIAL1,
			MENU_SHOP_ABILITY,
			MENU_SHOP_ARTIFACT,
			MENU_SHOP_TALENT,
			MENU_SHOP_ARMOR1,
			MENU_SHOP_ARMOR2,
			MENU_RESEARCH,
			MENU_MAIN,
			MENU_HELP,
			MENU_ABILITY
		};
		
struct coord {
	int x;
	int y;
};

// for drawtoggledimage func
struct draw_info {
	int flags;
	int res_id;
};

// Holds the players' current maximum page visit indexes
#define MENUMAXPAGES MENU_ABILITY + 1
struct coord MenuListenMax[MENUMAXPAGES] = {
			{ 0, 0 }, // empty record due to enum
			{ 1, 3 },
			{ 1, 0 },
			{ 0, 6 },
			{ 1, 0 },
			{ 2, 0 },
			{ 2, 0 },
			{ 0x7FFFFFFF, 2}, // load4 -- accessories
			{ 0, 6 }, // shop
			{ 0, 8 }, // weaps
			{ 0, 3 }, // slot 1
			{ 0, 5 }, // slot 2
			{ 0, 8 }, // slot 3
			{ 0, 5 }, // slot 4
			{ 0, 6 }, // slot 5
			{ 0, 5 }, // slot 6
			{ 0, 6 }, // slot 7
			{ 0, 4 }, // slot 8
			{ 1, 4 }, // shop ammo 1
			{ 2, 9 }, // shop ammo 2
            { 2, 4 }, // shop ammo 3
			{ 1, 5 }, // shop ammo special 1
			{ 0, 11 }, // shop ability
			{ 0, 10 }, // shop artifact
			{ 0, 6 }, // shop talent
			{ 1, 4 }, // shop armor1
			{ 1, 9 }, // shop armor2
			{ 27, 1 }, // research menu
			{ 0, 6 }, // main
			{ 0, 1 }, // help
			{ 0, 12 } // menu ability help
};
	
enum {
       SHOP_WEP_CSAW = 0,
	   SHOP_WEP_SICKLE,
	   SHOP_WEP_EXCALIBAT,
	   
	   SHOP_WEP_AKIMBOPISTOL,
	   SHOP_WEP_MAGNUM,
	   SHOP_WEP_LASERPISTOL,
	   SHOP_WEP_SCATTERPISTOL,
	   SHOP_WEP_RESPIS1,
	   
	   SHOP_WEP_PURIFIER,
	   SHOP_WEP_AUTOSG,
	   SHOP_WEP_RESSG1,
	   SHOP_WEP_HSSG,
	   SHOP_WEP_ERASUS,
	   SHOP_WEP_RESSSG1,
	   SHOP_WEP_SILVER,
	   SHOP_WEP_SLAYER,
	   
	   SHOP_WEP_HMG,
	   SHOP_WEP_LEAD,
	   SHOP_WEP_RESMG1,
	   SHOP_WEP_MINIGUN,
	   SHOP_WEP_EBONY,
	   
	   SHOP_WEP_TORPEDO,
	   SHOP_WEP_MERC,
	   SHOP_WEP_RESRL1,
	   SHOP_WEP_GRENADE,
	   SHOP_WEP_ROTARYGL,
	   SHOP_WEP_HEAVYML,
	   
	   SHOP_WEP_NUCLEARPL,
	   SHOP_WEP_TUREL,
	   SHOP_WEP_RESPL1,
	   SHOP_WEP_NAIL,
	   SHOP_WEP_BASILISK,
	   
	   SHOP_WEP_BFG,
	   SHOP_WEP_DEVA,
	   SHOP_WEP_MFG,
	   SHOP_WEP_RESBFG1,
	   SHOP_WEP_GAUSS,
	   SHOP_WEP_RAIL,
	   
	   SHOP_WEP_DEATHSTAFF,
	   SHOP_WEP_RAZOR,
	   SHOP_WEP_SUN,
	   SHOP_WEP_REAVER,
	   
	   SHOP_AMMO_CLIP,
	   SHOP_AMMO_SHELL,
	   SHOP_AMMO_ROCKET,
	   SHOP_AMMO_CELL,
	   
	   SHOP_AMMO_EXPSHELL,
	   SHOP_AMMO_EBONY,
	   SHOP_AMMO_EBONYX,
	   SHOP_AMMO_MIS,
	   SHOP_AMMO_GL,
	   SHOP_AMMO_NAIL,
	   SHOP_AMMO_BASILISK,
	   SHOP_AMMO_GAUSS,
	   SHOP_AMMO_SLAYER,
       
       SHOP_AMMO_PCAN,
       SHOP_AMMO_METEOR,
       SHOP_AMMO_FUEL,
       SHOP_AMMO_ION,
	   
	   SHOP_AMMO_FLECHETTE,
	   SHOP_AMMO_PIERCING,
	   SHOP_AMMO_ELECTRIC,
	   SHOP_AMMO_SONICGRENADE,
	   SHOP_AMMO_HEGRENADE,
	   
	   SHOP_ABILITY_KICK,
	   SHOP_ABILITY_RELOAD,
	   SHOP_ABILITY_DASH,
	   SHOP_ABILITY_ARCANE,
	   SHOP_ABILITY_POISON,
	   SHOP_ABILITY_EXPLOSION,
	   SHOP_ABILITY_HEART,
	   SHOP_ABILITY_REGEN,
	   SHOP_ABILITY_TEMPORAL,
	   SHOP_ABILITY_SOUL,
	   SHOP_ABILITY_MONSTERINFO,
	   
	   SHOP_TALENTBULLET,
	   SHOP_TALENTSHELL,
	   SHOP_TALENTMELEE,
	   SHOP_TALENTOCCULT,
	   SHOP_TALENTEXPLOSIVE,
	   SHOP_TALENTENERGY,
	   
	   SHOP_ARMOR_GREEN,
	   SHOP_ARMOR_YELLOW,
	   SHOP_ARMOR_BLUE,
	   SHOP_ARMOR_RED,
	   SHOP_ARMOR_CYBERNETIC,
	   SHOP_ARMOR_DUELIST,
	   SHOP_ARMOR_NECRO,
	   SHOP_ARMOR_KNIGHT,
	   SHOP_ARMOR_RAVAGER,
	   SHOP_ARMOR_GUNSLINGER,
	   SHOP_ARMOR_OCCULT,
	   SHOP_ARMOR_DEMO,
	   SHOP_ARMOR_ENERGY,
	   
	   SHOP_ARTI_KIT,
	   SHOP_ARTI_SALVATE,
	   SHOP_ARTI_SHIELD,
	   SHOP_ARTI_BLOOD,
	   SHOP_ARTI_TRIPLE,
	   SHOP_ARTI_VORTEX,
	   SHOP_ARTI_BOOK,
	   SHOP_ARTI_MAP,
	   SHOP_ARTI_BACKPACK,
	   SHOP_ARTI_RESET
};

#define MAXSHOPITEMS SHOP_ARTI_RESET + 1

#define SHOP_FIRSTARMOR_INDEX SHOP_ARMOR_GREEN
#define SHOP_FIRSTARMOR2_INDEX SHOP_ARMOR_CYBERNETIC
#define SHOP_FIRSTAMMO_INDEX SHOP_AMMO_CLIP
#define SHOP_FIRSTAMMO2_INDEX SHOP_AMMO_EXPSHELL
#define SHOP_FIRSTAMMO3_INDEX SHOP_AMMO_PCAN
#define SHOP_FIRSTAMMOSPECIAL_INDEX SHOP_AMMO_FLECHETTE
#define SHOP_FIRSTARTI_INDEX SHOP_ARTI_KIT
#define SHOP_ABILITY_BEGIN SHOP_ABILITY_KICK
#define SHOP_TALENT_BEGIN SHOP_TALENTBULLET

#define SHOP_WEAPON_BEGIN SHOP_WEP_CSAW
#define SHOP_WEAPON_SLOT1END SHOP_WEP_EXCALIBAT
#define SHOP_WEAPON_SLOT2END SHOP_WEP_RESPIS1
#define SHOP_WEAPON_SLOT3END SHOP_WEP_SLAYER
#define SHOP_WEAPON_SLOT4END SHOP_WEP_EBONY
#define SHOP_WEAPON_SLOT5END SHOP_WEP_HEAVYML
#define SHOP_WEAPON_SLOT6END SHOP_WEP_BASILISK
#define SHOP_WEAPON_SLOT7END SHOP_WEP_RAIL
#define SHOP_WEAPON_SLOT8END SHOP_WEP_REAVER

#define SHOP_LASTAMMO_INDEX SHOP_AMMO_SLAYER
#define SHOP_LASTAMMO_SPECIALINDEX SHOP_AMMO_HEGRENADE
#define SHOP_LASTWEP_INDEX SHOP_WEP_REAVER
#define SHOP_LASTABILITY_INDEX SHOP_ABILITY_MONSTERINFO
#define SHOP_LASTTALENT_INDEX SHOP_TALENTENERGY
#define SHOP_LASTARMOR_INDEX SHOP_ARMOR_ENERGY
#define SHOP_LASTARTI_INDEX SHOP_ARTI_RESET

#define SHOPINFO_PRICE 0
#define SHOPINFO_MAX 1
int ShopInfo[MAXSHOPITEMS][2] = 
	{
		// Weapons
		// 1
		{ 2750,	 1 },
		{ 2800,  1 },
		{ 3500,  1 },
		
		// 2
		{ 1500,  1 },
		{ 2750,  1 },
		{ 2850,  1 },
		{ 2500,  1 },
		{ 3250,	 1 },
		
		// 3
		{ 4000,  1 },
		{ 4500,  1 },
		{ 4350,  1 },
		{ 5000,  1 },
		{ 5250,  1 },
		{ 5500,  1 },
		{ 5250,  1 },
		{ 5250,  1 },
		
		// 4
		{ 4000,  1 },
		{ 4500,  1 },
		{ 5750,  1 },
		{ 5250,	 1 },
		{ 4800,  1 },
		
		// 5
		{ 3500,  1 },
		{ 4800,  1 },
		{ 5500,  1 },
		{ 800,   1 },
		{ 4000,  1 },
		{ 5000,  1 },
		
		// 6
		{ 4000,  1 },
		{ 4500,  1 },
		{ 4800,  1 },
		{ 5000,  1 },
		{ 5500,  1 },
		
		// 7
		{ 7750,  1 },
		{ 7750,	 1 },
		{ 8000,  1 },
		{ 8500,  1 },
		{ 6500,  1 },
		{ 6500,  1 },
		
		// 8
		{ 25000, 1 },
		{ 25000, 1 },
		{ 25000, 1 },
		{ 25000, 1 },
		
		// Ammunition
		// Basic Ammunition
		{ 20,		 1 },
		{ 30,		 1 },
		{ 40,		 1 },
		{ 50,		 1 },
		
		// Rare Ammunition
		{ 80,       1 },
		{ 50,       1 },
		{ 100,      1 },
		{ 100,      1 },
		{ 25,       1 },
		{ 65,       1 },
		{ 100,      1 },
		{ 100,      1 },
		{ 90,       1 },
        
        // Page 2 of rare
        { 65,       1 },
        { 105,      1 },
        { 80,       1 },
        { 150,      1 },
		
		// Special Ammunition
		{ 550,	    1 },
		{ 900,	    1 },
		{ 1250,	    1 },
		{ 1250,     1 },
		{ 2000,	    1 },
		
		
		// Abilities
		{ 6000,  1 },
		{ 6000,  1 },
		{ 8500,  1 },
		{ 7250,  1 },
		{ 6000,  1 },
		{ 6000,  1 },
		{ 7000,  1 },
		{ 8500,  1 },
		{ 7000,  1 },
		{ 9750,  1 },
		{ 2000,  1 },
		
		// Talent costs
		{ 800,	 1 },
		{ 800,	 1 },
		{ 800,	 1 },
		{ 800,	 1 },
		{ 800,	 1 },
		{ 800,	 1 },
		
		// Armor costs
		{ 4500,	 1 },
		{ 9000,  1 },
		{ 13500, 1 },
		{ 18000, 1 },
		{ 16500, 1 },
		{ 8000,  1 },
		{ 15000, 1 },
		{ 17000, 1 },
		{ 12000, 1 },
		{ 12000, 1 },
		{ 12000, 1 },
		{ 12000, 1 },
		{ 12000, 1 },

		// Artifacts, here for convenience. Index = MAXSHOPITEMS - MAXARTIFACTS
		{ 500,          FIELDKITMAX  		},
		{ 8000,         SOLVEMAX     		},
		{ 4500,         STASISMAX    		},
		{ 6000,         BLOODRUNEMAX 	    },
		{ 6000,         TRIPLEMAX   		},
		{ 6000,         VORTEXMAX   		},
		{ 5500,	        BOOKMAX      		},
		{ 27500,        1			   		},
		{ 50000,        1					},
		{ 10000,        RESETMAX 			}
	};

#define SHOPNAME_ITEM 0
#define SHOPNAME_TAG 1
#define SHOPNAME_CONDITION 2
#define SHOPNAME_TYPE 3
str ShopItemNames[MAXSHOPITEMS][4] = {
										{ "Upgraded Chainsaw",					"Dual Chainsaw",					"P_Slot1Replaced",		"0"  	    },
										{ "Sickle",								"Necro's Sickle",					"P_Slot1Replaced",		"0"		    },
										{ "Excalibat",							"Excalibat",						"P_Slot1Replaced",		"0"		    },
										
										{ " Akimbo Pistols ",					"Akimbo Longslides",				"P_Slot2Replaced",		"0"  	    },
										{ "Magnum", 							"Magnum",							"P_Slot2Replaced",		"0"  	    },
										{ "Laser Pistol",						"Laser Pistol",						"P_Slot2Replaced",		"0"		    },
										{ "ScatterGun",							"Scatter Pistol",					"P_Slot2Luxury",		"1"		    },
										{ "ResPistol1",							"Assault Rifle",					"P_Slot2Replaced",		"0"		    },
										
										{ "Upgraded Shotgun",					"Purifier",							"P_Slot3Replaced",		"0"  		},
										{ "Upgraded Shotgun2", 					"Auto Shotgun",						"P_Slot3Replaced",		"0" 		},
										{ "ResShotgun1",						"Deadlock",							"P_Slot3Replaced",		"0"		    },
										{ "Upgraded Super Shotgun",			    "Heavy SSG",						"P_Slot3XReplaced",	    "0" 		},
										{ "Upgraded Super Shotgun2",		    "Erasus",							"P_Slot3XReplaced",	    "0" 		},
										{ "ResSSG1",							"Plasma Cannon",					"P_Slot3XReplaced",	    "0"		    },
										{ "Silver Gun",						    "Silver Gun",						"P_Slot3Luxury",		"1"	        },
										{ "Slayer",								"Slayer",							"P_Slot3Luxury",		"1"		    },
											
										{ "Upgraded Machine Gun",				"Heavy Machine Gun",				"P_Slot4Replaced",  	"0"     	},
										{ "Upgraded Machine Gun2",			    "Lead Spitter",						"P_Slot4Replaced", 		"0"		    },
										{ "ResMG1",								"Templar MG",						"P_Slot4Replaced",		"0"		    },
										{ " Minigun ",							"Minigun",							"P_Slot4Luxury",   		"1"		    },
										{ "Ebony Cannon",						"Ebony Cannon",						"P_Slot4Luxury",   		"1"		    },
										
										{ "Upgraded Rocket Launcher",		    "Torpedo Launcher",				    "P_Slot5Replaced",  	"0"		    },
										{ "Upgraded Rocket Launcher2",		    "Mercury Launcher",				    "P_Slot5Replaced",  	"0"		    },
										{ "ResRL1",								"Meteor Launcher",					"P_Slot5Replaced",		"0"		    },
										{ "Grenade Launcher",					"Grenade Launcher",				    "P_Slot5Luxury",    	"1"		    },
										{ "Upgraded Grenade Launcher",		    "Rotary G. Launcher",				"P_Slot5Luxury",  		"1"		    },
										{ "Heavy Missile Launcher",				"H. Missile Launcher",				"P_Slot5Luxury",   		"1"		    },
										
										{ "Upgraded Plasma Rifle",				"Nuclear P. R.",					"P_Slot6Replaced", 		"0"		    },
										{ "Upgraded Plasma Rifle2",				"Turel Cannon",						"P_Slot6Replaced",		"0"		    },
										{ "ResPlasma1",							"Flamethrower",						"P_Slot6Replaced",		"0"		    },
										{ "Nailgun",							"Nailgun",							"P_Slot6Luxury",		"1"	        },
										{ "Basilisk",							"Basilisk",							"P_Slot6Luxury",		"1"	        },
										
										{ "Upgraded BFG 9000",					"BFG 32768",						"P_Slot7Replaced",		"0"		    },
										{ "Devastator",							"Devastator 5000",					"P_Slot7Replaced",		"0"     	},
										{ "MFG",								"Destr. Generator",					"P_Slot7Replaced",		"0"		    },
										{ "ResBFG1",							"Ion Cannon",						"P_Slot7Replaced",		"0"		    },
										{ "Gauss Rifle",						"Gauss Rifle",						"P_Slot7Luxury",		"1"     	},
										{ "Rail Gun",							"Railgun",							"P_Slot7Luxury",		"1"     	},
										
										{ "Death Staff",						"Death Staff",						"P_Slot8Luxury",		"1"		    },
										{ "RazorFang",							"Razorfang",						"P_Slot8Luxury",		"1"    	    },
										{ "Sun Staff",							"Sun Staff",						"P_Slot8Luxury",		"1"     	},
										{ "Soul Reaver",						"Soul Reaver",						"P_Slot8Luxury",		"1"     	},
										
										{ "Clip",								"Bullets",							"",						"0"		    },
										{ "Shell",								"Shells",							"",						"0"		    },
										{ "RocketAmmo",							"Rockets",							"",						"0"		    },
										{ "Cell",								"Cells",							"",						"0"		    },
										
										{ "ExplodingShell",						"Explosive Shells",					"",						"0"	        },
										{ "EbonyAmmo",							"Cannon Balls",						"",						"0"	        },
										{ "EbonyAmmoX",							"Shrapnel Balls",					"",						"0"	        },
										{ "MISAmmo",							"Heavy Missile",					"",						"0"	        },
										{ "Grenades",							"Grenades",							"",						"0"	        },
										{ "Nail",								"Nails",							"",						"0"	        },
										{ "BasiliskAmmo",						"Lava Cell",						"",						"0"	        },
										{ "GaussRound",							"Gauss Rounds",						"",						"0"	        },
										{ "SlayerAmmo",							"Slayer Essence",					"",						"0"		    },
                                        
                                        { "PCanAmmo",                           "Plasma Battery",                   "",                     "0"         },
                                        { "MeteorAmmo",                         "Meteor Sphere",                    "",                     "0"         },
                                        { "Fuel",                               "Fuel Tank"                         "",                     "0"         },
                                        { "IonAmmo",                            "Ion Cell",                         "",                     "0"         },
										
										{ "FlechetteShell",					    "Flechette Shells",					"",						"0"		    },
										{ "PiercingShell",						"Magnum Shells",					"",						"0"		    },
										{ "ElectricShell",						"Shock Shells",						"",						"0"		    },
										{ "A40mmSonicGrenade",				    "Sonic Grenades",					"",						"0"		    },
										{ "A40mmHEGrenade",					    "HE Grenades",						"",						"0"		    },
										
										{ "Ability_Kick",						"Close Combat Mastery",			    "",						"0"	        },
										{ "Ability_Reloader",					"Reloading Mastery",				"",						"0"	        },
										{ "Ability_Dash",						"Mobility Mastery",					"",						"0"	        },
										{ "Ability_Arcanery",					"Arcane Mastery",					"",						"0"	        },
										{ "Ability_AntiPoison",					"Poison Mastery",					"",						"0"	        },
										{ "Ability_ExplosionMastery",			"Explosion Mastery",				"",						"0"	        },
										{ "Ability_HeartSeeker",				"Heart Seeker Mastery",			    "",						"0"	        },
										{ "Ability_Regeneration",				"Regeneration Mastery",			    "",						"0"	        },
										{ "Ability_Temporal",					"Temporal Mastery",				    "",						"0"	        },
										{ "Ability_SoulStealer",				"Soul Stealer Mastery",			    "",						"0"	        },
										{ "Ability_MonsterInfo",				"Monster Mastery",					"",						"0"		    },
										
										{ "Talent_Bullet",						"Bullet Talent",					"",						"0"		    },
										{ "Talent_Shell",						"Shell Talent",						"",						"0"		    },
										{ "Talent_Melee",						"Melee Talent",						"",						"0"		    },
										{ "Talent_Occult",						"Occult Talent",					"",						"0"		    },
										{ "Talent_Explosive",					"Explosive Talent",					"",						"0"		    },
										{ "Talent_Energy",						"Energy Talent",					"",						"0"		    },
										
										{ "NewGreenArmor",						"Green Armor",						"",						"0"		    },
										{ "YellowArmor",						"Yellow Armor",						"",						"0"		    },
										{ "NewBlueArmor",					    "Blue Armor",						"",						"0"		    },
										{ "TheRedArmor",						"Red Armor",						"",						"0"		    },
										{ "CyberneticArmor",					"Cybernetic Armor",				    "",						"0"		    },
										{ "DuelistArmor",						"Duelist Armor",					"",						"0"		    },
										{ "NecroArmor",							"Necro Armor",						"",						"0"		    },
										{ "KnightArmor",						"Knight Armor",						"",						"0"		    },
										{ "RavagerArmor",						"Ravager Armor",					"",						"0"		    },
										{ "GunSlingerArmor",					"Gunslinger Armor",				    "",						"0"		    },
										{ "OccultArmor",						"Occult Armor",						"",						"0"		    },
										{ "DemoArmor",							"Demo Armor",						"",						"0"		    },
										{ "EnergyArmor",						"Energy Armor",						"",						"0"		    },
									
										{ "FieldKit",							"Field Kit",						"",						"0"		    },
										{ "SalvationSphere",					"Salvation Sphere",					"",						"0"		    },
										{ "PortableShield",						"Portable Shield",					"",						"0"		    },
										{ "BloodRune",							"Blood Rune",						"",						"0"		    },
										{ "TripleDamage",						"Triple Damage",					"",						"0"    	    },
										{ "BladeVortex",						"Blade Vortex",						"",						"0"		    },
										{ "BookOfTheDead",						"Book of the Dead",				    "",						"0"		    },
										{ "AllmapGiver",						"Auto Map",							"",						"0"		    },
										{ "NewBackPack",						"Back Pack",						"",						"0"		    },
										{ "StatReset",							"Stat Reset",						"",						"0"		    }
										
									 };

#define MAX_RESEARCH_REQUIREMENTS 3
// Basis for multi-research requiring stuff is here
int ItemResearchRequirements[MAXSHOPITEMS][MAX_RESEARCH_REQUIREMENTS] = {
	{ -1, -1, -1 },
	{ RES_SLOT1OCCULT, -1, -1 },
	{ RES_SLOT1OCCULT, -1, -1 },
	
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ RES_SLOT2UPG1, -1, -1 },
	
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ RES_SLOT3UPG1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ RES_SLOT3SSGUPG1, -1, -1 },
	{ RES_SLOT3LUXURY, -1, -1 },
	{ RES_SLOT3LUXURY, -1, -1 },
	
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ RES_SLOT4UPG1, -1, -1 },
	{ RES_SLOT4LUXURY, -1, -1 },
	{ RES_SLOT4LUXURY, -1, -1 },
	
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ RES_SLOT5UPG1, -1, -1 },
	{ RES_SLOT5GL, -1, -1 },
	{ RES_SLOT5LUXURY, -1, -1 },
	{ RES_SLOT5LUXURY, -1, -1 },
	
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ RES_SLOT6UPG1, -1, -1 },
	{ RES_SLOT6LUXURY, -1, -1 },
	{ RES_SLOT6LUXURY, -1, -1 },
	
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ RES_SLOT7UPG1, -1, -1 },
	{ RES_SLOT7LUXURY, -1, -1 },
	{ RES_SLOT7LUXURY, -1, -1 },
	
	{ RES_SLOT8REVEAL, -1, -1 },
	{ RES_SLOT8REVEAL, -1, -1 },
	{ RES_SLOT8REVEAL, -1, -1 },
	{ RES_SLOT8REVEAL, -1, -1 },
	
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	
	{ RES_SLOT3LUXURY, -1, -1 },
	{ RES_SLOT4LUXURY, -1, -1 },
	{ RES_SLOT4LUXURY, -1, -1 },
	{ RES_SLOT5LUXURY, -1, -1 },
	{ RES_SLOT5GL, -1, -1 },
	{ RES_SLOT6LUXURY, -1, -1 },
	{ RES_SLOT6LUXURY, -1, -1 },
	{ RES_SLOT7LUXURY, -1, -1 },
	{ RES_SLOT3LUXURY, -1, -1 },
    
    { RES_SLOT3SSGUPG1, -1, -1 },
    { RES_SLOT5UPG1, -1, -1 },
    { RES_SLOT6UPG1, -1, -1 },
    { RES_SLOT7UPG1, -1, -1 },
	
	{ RES_FLECHETTE, -1, -1 },
	{ RES_PIERCING, -1, -1 },
	{ RES_ELECTRIC, -1, -1 },
	
	{ RES_SONICGRENADE, -1, -1 },
	{ RES_HEGRENADE, -1, -1 },
	
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ RES_OCCULTABILITY, -1, -1 },
	{ RES_NANOTECH, -1, -1 },
	{ RES_NANOTECH, -1, -1 },
	{ RES_OCCULTABILITY, -1, -1 },
	{ RES_NANOTECH, -1, -1 },
	{ RES_OCCULTABILITY, -1, -1 },
	{ RES_OCCULTABILITY, -1, -1 },
	{ -1, -1, -1 },
	
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	
	{ RES_RAREARMOR, -1, -1 },
	{ RES_RAREARMOR, -1, -1 },
	{ RES_RAREARMOR, -1, -1 },
	{ RES_RAREARMOR, -1, -1 },
	{ RES_RAREARMOR, -1, -1 },
	{ RES_RAREARMOR, -1, -1 },
	{ RES_RAREARMOR, -1, -1 },
	{ RES_RAREARMOR, -1, -1 },
	{ RES_RAREARMOR, -1, -1 },
	
	{ -1, -1, -1 },
	{ RES_OCCULTARTIFACT, -1, -1 },
	{ -1, -1, -1 },
	{ RES_OCCULTARTIFACT, -1, -1 },
	{ RES_OCCULTARTIFACT, -1, -1 },
	{ RES_OCCULTARTIFACT, -1, -1 },
	{ RES_OCCULTARTIFACT, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 },
	{ -1, -1, -1 }
};

#define TALENT_COST_INCREASE 800
		
#define MAXABILITIES 11
str AbilityInfo[MAXABILITIES] = 
							{
								"Ability_Kick",
								"Ability_Reloader",
								"Ability_Dash",
								"Ability_Arcanery",
								"Ability_AntiPoison",
								"Ability_ExplosionMastery",
								"Ability_HeartSeeker",
								"Ability_Regeneration",
								"Ability_Temporal",
								"Ability_SoulStealer",
								"Ability_MonsterInfo"
							};
							
enum {
		ARTI_FIELDKIT = 1,
		ARTI_SALVATION,
		ARTI_SHIELD,
		ARTI_BLOODRUNE,
		ARTI_TRIPLE,
		ARTI_BLADE,
		ARTI_BOOK,
		ARTI_MAP,
		ARTI_BACKPACK,
		ARTI_RESET,
	 };
	 
#define VORTEXMAX 1
#define TRIPLEMAX 1
#define BLOODRUNEMAX 1
#define BOOKMAX 1
#define SOLVEMAX 1
#define STASISMAX 3
#define FIELDKITMAX 3
#define RESETMAX 1

#define ARTI_ICON 0
#define ARTI_NAME 1
#define MAXARTIFACTS SHOP_LASTARTI_INDEX - SHOP_FIRSTARTI_INDEX + 1
str ArtifactInfo[MAXARTIFACTS][2] = 
							{ 
							   { "FKITD0",				"FieldKit"				},	
							   { "SALVRICO",			"SalvationSphere"		},
							   { "SHIELICO",			"PortableShield"		},
							   { "BRUNICO",			    "BloodRune"				},
							   { "DMGICO",			    "TripleDamage"			},
							   { "SHRUA0",			    "BladeVortex"			},
							   { "BOTDICO",			    "BookOfTheDead"		    },
							   { "PMAPA0",			    "AllMapOnlyOnce"		},
							   { "BPAKA0",			    "NewBackPack"			},
							   { "RESETICO",            "StatReset"             }
							};
							
str ArtifactExplanation[MAXARTIFACTS] = {
												"Portable medikits, can carry 3.",
												"Teleports you to start, heals\nfor 100 health.",
												"Invulnerability on use for 5\nseconds. Duration stacks.",
												"Steal life from damage done\nfor 30 seconds.",
												"Triples damage dealt for 15\nseconds.",
												"Creates a ring of blades for\n20 seconds, granting 50% damage\nresistance. Blades damage on\ncollision.",
												"Unleashes power of the\ndead, granting souls for demon\nkills.",
												"Reveals the current map\nto you.",
												"Increases ammo capacity.",
												"Resets your stats back to\nzero. You can reassign."
										};

struct draw_info ArtifactDrawInfo[MAXARTIFACTS] = {
	{ OBJ_ARTI | OBJ_HASCHOICE, 					        -1 										    },
	{ OBJ_ARTI | OBJ_HASCHOICE | OBJ_RESEARCH, 		        SHOP_ARTI_SALVATE				            },
	{ OBJ_ARTI | OBJ_HASCHOICE,								-1											},
	{ OBJ_ARTI | OBJ_HASCHOICE | OBJ_RESEARCH,		        SHOP_ARTI_BLOOD				                },
	{ OBJ_ARTI | OBJ_HASCHOICE | OBJ_RESEARCH,		        SHOP_ARTI_TRIPLE					        },
	{ OBJ_ARTI | OBJ_HASCHOICE | OBJ_RESEARCH,		        SHOP_ARTI_VORTEX				            },
	{ OBJ_ARTI | OBJ_HASCHOICE | OBJ_RESEARCH,		        SHOP_ARTI_BOOK					            },
	{ OBJ_ARTI | OBJ_HASCHOICE,								-1											},
	{ OBJ_ARTI | OBJ_HASCHOICE,								-1											},
	{ OBJ_ARTI | OBJ_HASCHOICE,								-1											}
};
	 
str AccessoryNames[MAX_ACCESSORY + 1] = { 
	"None", 
	"Wisdom Talisman", 
	"Greed Talisman", 
	"Demon Bane", 
	"Amulet of Hellfire", 
	"Angelic Ankh", 
	"Reflection Pendant", 
	"Nether Mask", 
	"Taltos Ring", 
	"Hate Shard",
	"Hand of Artemis",
	"Scroll of Agamotto",
	"Gryphon Boots",
	"Lich Arm"
};

// make this automated later
str AccessoryImages[MAX_ACCESSORY + 1] = { 
	"TNT1A0", 
	"ACC1B0", 
	"ACC2B0", 
	"ACC3B0", 
	"ACC4B0", 
	"ACC5B0", 
	"ACC6B0", 
	"ACC7B0", 
	"ACC8B0", 
	"ACC9B0",
	"AC10B0",
	"AC11B0",
	"AC12B0",
	"AC13B0"
}; 

str AccessoryExplanation[MAX_ACCESSORY + 1] = {
												"", 
												"Increases experience gain by 50%.",
												"Increases credit gain by 50%.",
												"Increases damage of occult\nweapons by 100%.",
												"Protects from all fire damage\nand hazards by 75%.",
												"When about to die, the ankh will\nintervene, making you invulnerable\nfor 8 seconds. Works once every map.",
												"When hit, 20% chance to go\ninvulnerable and reflective\nfor 5 seconds. Can happen only\n5 times every map.",
												"All your weapons can hit gho-\nsts and do irreducable damage.",
												"Recover health from melee\nattacks and become a ghost.\nHealth items are unpickable. Only\nMegasphere or Berserk can be\npicked that give health.",
												"Reflect damage back to enemies.\nAttackers take x2 more damage\nfor 5 seconds.",
												"Your weapons do not require\nany ammo. Does not affect \cstempo-\n\csrary\c- weapons.",
												"Grants 30% damage reduction\nwhile moving and 150% more\ndamage while standing.",
												"Gives 25% movement speed,\nimmunity to curses and fall damage.",
												"Soul capacity becomes 150 and ultimate\nweapons do x2.5 damage."
											  };

#define MAXSHOPAMMOS 22
#define AMMO_ICON 0
#define AMMO_NAME 1	
#define AMMO_PAGE2_BEGIN SHOP_FIRSTAMMO2_INDEX - SHOP_FIRSTAMMO_INDEX
#define AMMO_PAGE3_BEGIN SHOP_FIRSTAMMO3_INDEX - SHOP_FIRSTAMMO_INDEX
#define AMMO_PAGESPECIAL_BEGIN SHOP_FIRSTAMMOSPECIAL_INDEX - SHOP_FIRSTAMMO_INDEX
str AmmoInfo[MAXSHOPAMMOS][2] = {
									{ "CLIPA0",			"Clip"								},
									{ "SHELA0",			"Shell"								},
									{ "ROCKA0",			"RocketAmmo"						},
									{ "CELLA0",			"Cell"								},

									{ "ESHAA0",			"ExplodingShell"					},
									{ "EBOPA0",			"EbonyAmmo"						    },
									{ "EBOPE0",			"EbonyAmmoX"						},
									{ "AHRLA0",			"MISAmmo"							},
									{ "GBUNA0",			"Grenades" 							},
									{ "NPAKA0",			"Nail"								},
									{ "BASIA01",		"BasiliskAmmo"						},
									{ "GAUSICO",		"GaussRound"						},
									{ "SLAYAM01",		"SlayerAmmo"						},
                                    
                                    { "PCNIC1",         "PCanAmmo"                          },
                                    { "LAAM1",          "MeteorAmmo"                        },
                                    { "FUAMA0",         "Fuel"                              },
                                    { "IONAMM1",        "IonAmmo"                           },
								
									{ "SAM1A0",			"FlechetteShell"				    },
									{ "SAM3A0",			"PiercingShell"						},
									{ "SAM2A0",			"ElectricShell"						},
									{ "GAM1A0",			"A40MMSonicGrenade"			        },
									{ "GAM2A0",			"A40MMHEGrenade"				    },
								};
								
int AmmoCounts[MAXSHOPAMMOS] = {
	25,
	10,
	5,
	40,
	
	8,
	8,
	4,
	4,
	5,
	15,
	20,
	5,
	6,
    
    4,
    5,
    30,
    18,
	
	8,
	8,
	8,
	
	5,
	5
};
					
str AmmoExplanation[MAXSHOPAMMOS] = {
										"clips.",
										"shells.",
										"rockets.",
										"cells.",
										
										"explosive shells for\nthe Silver Gun.",
										"cannon balls for the\nEbony Cannon.",
										"shrapnel balls for\nthe Ebony Cannon.",
										"heavy missiles for the\nHeavy Missile Launcher.",
										"grenades for the\nGrenade Launcher.",
										"nails for the Nail\nGun.",
										"lava ammo for the\nBasilisk.",
										"gauss rounds for the\nGauss Rifle.",
										"slayer essences for\nthe Slayer.",
                                        
                                        "plasma charge for\nthe Plasma Cannon.",
                                        "meteors for the\nMeteor Launcher.",
                                        "fuel for the Flame\nThrower.",
                                        "ion cells for the Ion\nCannon.",
										
										"flechette shells.",
										"magnum shells.",
										"electric shells.",
										"sonic grenades.",
										"high-ex grenades."
									};
									
#define MAXARMORS 13
#define CLASSIC_ARMOR_COUNT 4
str ArmorImages[MAXARMORS] = { 
	"ARM1A0", 
	"ARM3A0", 
	"ARM2A0", 
	"QRARA0",
	"ARM4A1",
	"ARM5A0",
	"ARM6A0",
	"ARM7A0",
	"ARM8A0",
	"ARM9A0",
	"AR10A0",
	"AR11A0",
	"AR12A1"
};

int ArmorCapacities[MAXARMORS] = {
	100,
	150,
	200,
	300,
	200,
	150,
	200,
	250,
	150,
	150,
	150,
	150,
	150
};

str ArmorExplanation[MAXARMORS] = {
	"33% protection, 100 armor.",
	"41.6% protection, 150 armor.",
	"50% protection, 200 armor.",
	"75% protection, 300 armor.",
	"45% protection, 200 armor. If\nnot damaged for 3 seconds, res-\ntores armor slowly.",
	"33% protection, 150 armor.\nExtra 60% hitscan resist.",
	"45% protection, 200 armor.\n33% chance on hit to release\nspikes around doing 60 - 100 dam-\nage. Scales from occult talents and bulkiness.",
	"35% protection, 250 armor.\nIf a melee weapon is held\nextra 35% protection is bestowed.",
	"25% protection, 150 armor.\nOn a kill spree, gain 35% extra\ndamage. If a killing spree is met\nrestore armor completely.",
	"25% protection, 150 armor.\nExtra 50% hitscan damage.",
	"25% protection, 150 armor.\nExtra 50% magic damage.",
	"25% protection, 150 armor.\nExtra 50% explosives damage.",
	"25% protection, 150 armor.\nExtra 50% energy damage."
};

struct draw_info ArmorDrawInfo[MAXARMORS] = {
	{ OBJ_ARMOR, 								-1 															},
	{ OBJ_ARMOR, 								-1 															},
	{ OBJ_ARMOR, 								-1 															},
	{ OBJ_ARMOR, 								-1 															},
	{ OBJ_ARMOR | OBJ_RESEARCH, 		SHOP_ARMOR_CYBERNETIC		 					},
	{ OBJ_ARMOR | OBJ_RESEARCH, 		SHOP_ARMOR_DUELIST	 							},
	{ OBJ_ARMOR | OBJ_RESEARCH, 		SHOP_ARMOR_NECRO		 							},
	{ OBJ_ARMOR | OBJ_RESEARCH, 		SHOP_ARMOR_KNIGHT	 							},
	{ OBJ_ARMOR | OBJ_RESEARCH, 		SHOP_ARMOR_RAVAGER		 						},
	{ OBJ_ARMOR | OBJ_RESEARCH, 		SHOP_ARMOR_GUNSLINGER	 					},
	{ OBJ_ARMOR | OBJ_RESEARCH, 		SHOP_ARMOR_OCCULT	 							},
	{ OBJ_ARMOR | OBJ_RESEARCH, 		SHOP_ARMOR_DEMO	 								},
	{ OBJ_ARMOR | OBJ_RESEARCH, 		SHOP_ARMOR_ENERGY	 							}
};
						 
str WeaponExplanation[SHOP_WEP_REAVER + 1] = 
						{
							"Double the blade, double the\nfun! Twice as much damage, same\nfiring rate.",
							"Sickle steals life from enemies\non hit. Does 35 - 50 damage 3\ntimes. Alt fire swings for irredu-\ncable 60 - 80 damage 3 times. Alt\nfire requires Close Combat Mas-\ntery.",
							"Does 100 - 150 damage per\nswing. Alt fire charges and\nreleases 17 baseballs each doing\n30 - 45 on impact and 64 damage\nin a 96 unit radius. Alt fire\nrequires Close Combat Mastery.",
							"Akimbo longslides. Does 35\ndamage per shot in a 1.25 by 0.5\nspread.",
							"Magnum is a true classic. Each\nbullet does 170 - 230 damage.\nHas a capacity of 6. Alt fire\nreloads. \cfIgnores shields.",
							"Laser Pistol is the fresh inven-\ntion of UAC. Shoots lasers doing\n15 - 30 damage in a 2.0 by 1.25\nspread. Alt fire charges to do\nup to a x5 damage rail. Doesn't\nuse ammo. \cfIgnores shields.",
							"Scatter Pistol shoots 3 pellets\neach doing 8 - 16 damage. Pellets\nscatter to 5 tiny pellets doing\n2- 8 damage. Alt fire shoots one\npellet. \cfIgnores shields.\c- Irredu-\ncable.",
							"Assault Rifle does 18 damage\nper bullet in a 3.6 by 2.4 spread.\nMagazine capacity of 31. Alt fire\nzooms, allowing more precise\nshots.",
							"Purifier shoots 15 pellets\neach doing 15 damage in a 3.6 by\n3.6 and a shell capacity of 8.",
							"Killstorm is an automatic\nshotgun, shooting 10 pellets\neach doing 15 damage in a\n7.2 by 5.2 spread. Has a shell\ncapacity of 10.",
							"Deadlocks fires 16 pellets\ndoing 15 damage in a 4.8 by 3.6\nspread. Has a shell capacity\nof 12. Can use \cialternate\c- ammo.",
							"Heavy Super Shotgun shoots\n24 pellets doing 15 damage in a\n9.6 by 5.8 spread. 8 of these rip\nthrough targets.",
							"Erasus shotgun shoots highly\nballistic shells with 16 pellets\neach doing 15 damage. Has to\nreload after shooting twice.\nAlt fire shoots both shells\nin the chamber, or reloads.",
							"Fires 24 plasma balls in a cir-\ncular fashion, each doing\n20 damage. Does irreducable\ndamage. Has a clip size of 5.",
							"Silver Gun fires 9 pellets each\ndoing 15 on hit. Each pellet also\ndoes 32 - 48 explosion damage\nin a small area. Does self\ndamage. \cfIgnores shields.",
							"Slayer creates 6 blades each\ndoing 9 damage and rip through.\nAlt fire detonates blades at will\nfor 90 damage in a 96 unit radius.\nBlades return to you after tra-\nvelling a bit. Can't hit \cughosts.",
							"Finest machine guns UAC has to\noffer. Bullets do 25 damage in a\n1.6 by 0.8 spread. Has a clip size\nof 60. Can zoom.",
							"Lead Spitter is a super sonic\nbullet shooter shooting 2\nbullets doing 18 damage in a 6.4\nby 4.8 spread. Clip size is 75.\n\cfIgnores shields.",
							"Templar fires silver bullets\ndoing 20 damage in a 4.4 by 2.8\nspread. Bullets deal x3 damage\nto undead and magical enemies.\nClip size of 40. Can use \cigrenades\c-.",
							"Stronger, faster and better\nthan ever! Poor accuracy, shoots\ntracers that do 16 - 28 damage\neach. Alt fire to spin.\nCan't hit \cughosts.",
							"The ebony cannon shoots boun-\ncing balls of death. 16 - 40 dama-\nge with 48 explosion damage in\n64 units. Alt fire shoots scatter\nbombs. \cfIgnores shields.",
							"The Torpedo Launcher shoots\nfast torpedos each doing\n180 - 220 damage on impact and\n224 damage in a 128 unit radius.\nCan't hit \cughosts",
							"Mercury Launcher fires accele-\nrating and heat seeking mercury\nmissiles doing 256 - 320 damage\non hit and 192 damage in a 160\nunit radius over 2 seconds.\nCan't hit \cughosts.",
							"Fires a meteor doing 200 onimp-\nact and 192 in a 192 unit ra-\ndius. The meteor then splits into\nsmaller pieces, and those pieces\nas well. Main meteor \cfignores\n\cfshields\c-.",
							"Useful for when you can't re-\nach around corners. Does 80 dam-\nage on impact and 128 damage in\na 144 unit radius.\nCan't hit \cughosts",
							"The Rotary Grenade Launcher\ndoes 192 damage on impact and\n192 damage on a 192 unit radius.\nCan't hit \cughosts",
							"Top of the food chain for rock-\nets. Shoots two homing rockets\neach doing 160 damage both on\nimpact and explosion. Can't hit\n\cughosts.",
							"Improved with a nuclear react-\nor. Does 36 - 60 on hit and 10 - 30\nexplosion damage in a 48 unit ra-\ndius. Can \cgoverheat\c-. Does self da-\nmage.",
							"Turel Cannon fires highly ion-\nized particles doing 125 damage\nripping through everything. Cont-\ninuous fire is less accurate and\ndoes 80 damage. Has a range\nof 768 units.",
							"Flamethrower does what it says\nand throws flames doing 1 - 8\ndamage. When they hit, they leave\na trail of flame doing 5 damage\nevery 2 tics. Fuel size of 75.",
							"Shoots nails which do 8 - 16\ndamage and rips through. Alt fire\nshoots explosive lava nails that\n\cfignores shields.\c- Can't hit \cughosts.",
							"Shoots fire balls doing 5 - 40\ndamage. If loaded, shoots meteors\ndoing 60 - 120 on impact and 96\nexplosion damage. \cfIgnores shields.",
							"The newest BFG model 32768\ndevastates with 600 - 900 damage\non impact and 384 damage in a 160\nunit radius. Shoots 64 tracers.\n\cfIgnores shields.",
							"Devastator launches three mini\nrockets each doing 32 to 80 with\n32 radius damage in 72 units.\nCan't hit \cughosts.\c- \cfIgnores shields.",
							"Fires a destructive orb doing\n400 - 600 damage on impact and\n384 damage in a 768 unit radius.\nCreates 6 smaller explosions\ndoing 384 damage in a 256 unit\nradius. \cfIgnores shields.",
							"Fires ionized energy doing\n100 impact and 96 area damage in\n160 unit radius. Can \cgoverheat\c-.\n\cfIngores shields\c-. Can't hit \cughosts\c-.",
							"Gauss Rifle fires a magnetic\npulse dealing 100 on hit and 192\nradius damage in a 96 unit radius.\nAlt fire zooms, amplifying the\ndamage for each zoom. Can't hit\n\cughosts.\c- \cfIgnores shields.",
							"This baby can rip through conc-\nrete with ease. Each shot does\nmultiples of 92 damage. Alt fire\ncharges up the next shot, up to 2\ntimes. \cfIgnores shields.",
							"Fires meteors of magic bursting\non impact. Alt fire fires three\ncolumns of fire on the floor and\nceiling that travel and explode\nin flames. \cfIgnores shields.",
							"Fires magical bone shards that\nrip through. Alt fire switches\nthe mode to shoot three demon\nshredders that seek demons.",
							"Fires sun beams to burn enemies.\nAlt fire channels the very ess-\nence of sun causing a massive\nmeltdown. \cfIgnores shields\c-.",
							"Creates portals that lead to\nhungry ghosts to devour your\nenemies. Hold to gain a deflective\nshield. \cfIgnores shields."
						};

// + 2 because dash toggle is an exception
str AbilityHelpText[MAXABILITIES + 2] = {
						"Melee\nweapons\ngain\naltfires",
						"Reload\ntwice\nas fast",
						"Gain\ndodge\nmoves\n(tap the\nmove keys)",
						"Artifact\npower\nincreases\nby 50%",
						"Poison\nimmunity",
						"Your\nexplosives\nhurt 50%\nless",
						"Demons\ndrop their\nhearts\n10% of\nthe time.\nUse as\ntemporary\nweapons",
						"Heal till\n20 + twi-\nce VIT\neach se-\ncond",
						"Temporary\nweapons\ngive 50%\nmore ammo.\nAlso gives\ntemporal\nsphere\neach map.",
						"Demons\ngive souls\non kill",
						"Can see\nMonster\nInfo",
						"Toggles\ndashing",
						"Returns\nto Shop\nMenu"
					  };
									 
str ShopWeaponTake[SHOP_WEP_REAVER + 1] = {
								" Chainsaw ",
								" Chainsaw ",
								" Chainsaw ",
								
								" Pistol ",
								" Pistol ",
								" Pistol ",
								" Pistol ",
								" Pistol ",
								
								" Shotgun ",
								" Shotgun ",
								" Shotgun ",
								" Super Shotgun ",
								" Super Shotgun ",
								" Super Shotgun ",
								" ",
								" ",
								
								" Machine Gun ",
								" Machine Gun ",
								" Machine Gun ",
								" ",
								" ",
								
								"Rocket Launcher",
								"Rocket Launcher",
								"Rocket Launcher",
								" ",
								" ",
								" ",
								
								"Plasma Rifle",
								"Plasma Rifle",
								"Plasma Rifle",
								" ",
								" ",
								
								"BFG 9000",
								"BFG 9000",
								"BFG 9000",
								"BFG 9000",
								" ",
								" ",
								
								" ",
								" ",
								" ",
								" "
						 };
						 
str TalentHelpCornerMessage[MAX_TALENTS] = {
	"Adds 7.5%\ndamage to\nBullet\nDamage",
	"Adds 7.5%\ndamage to\nShell\nDamage",
	"Adds 7.5%\ndamage to\nMelee\nDamage",
	"Adds 7.5%\ndamage to\nOccult\nDamage",
	"Adds 7.5%\ndamage to\nExplosive\nDamage",
	"Adds 7.5%\ndamage to\nEnergy\nDamage"
};

str TalentTypeNames[MAX_TALENTS] = {
	"bullet",
	"shell",
	"melee",
	"occult",
	"explosive",
	"energy"
};

// this is stupid but oh well
str TalentTypeNamesCapital[MAX_TALENTS] = {
	"Bullet",
	"Shell",
	"Melee",
	"Occult",
	"Explosive",
	"Energy"
};

int ResearchEntryNumbers[MAX_RESEARCHES] = {
	4301,
	4300,
	3531,
	6914,
	
	2302,
	2303,
	2304,
	
	2411,
	2412,
	
	2440,
	
	611,
	640,
	783,
	831,
	895,
	899,
	909,
	
	7982,
	7991,
	7995,
	8010,
	8277,
	8216,
	8433,
	8566,
	
	5779,
	9999,
	7744,
	3616
};

int ResearchCosts[MAX_RESEARCHES] = {
	60,
	80,
	55,
	105,
	
	40,
	45,
	45,
	
	55,
	55,
	
	75,
	
	40,
	40,
	45,
	45,
	45,
	45,
	55,
	
	40,
	45,
	45,
	50,
	20,
	50,
	60,
	
	105,
	140,
	85,
	75
};

str ResearchDescription[MAX_RESEARCHES] = {
	"By using parts from fallen\nenemies, we can manufacture\narmors of varying properties.",
	"With this breakthrough techno-\nlogy, we can start distributing\nstate of the art armors to the\nmarines, blocking 100% of the\ndamage.",
	"Instead of wasting medikits, by\nusing this new technology we\ncan allow marines to store the\nmedikits picked up permanently.\n\cgMedic\c- perk increases the cap by\n15% each.",
	"Unlocking the occult secrets of\ndemonic energy, we can allow\nmarines to use ancient trophies\nthey come across. Allows use of\naccessories.",

	"Our scientists managed to create\na highly ballistic shell that can\nscatter around and pierce tar-\ngets, \cfignoring shields\c-.",
	"We can now utilize the same bul-\nlets used by magnum handguns\non shotguns. Magnum shells\npenetrate any target.",
	"When you need some extra zap\nto go with your shell burst, we\ncan use these now. They const-\nantly lock enemies in their pain\nstate and \cfignore shields\c-.",
	
	"For when normal grenades are\ninsufficient, try a Heavy Explo-\nsive one. Unlocks HE Grenades.",
	"Sometimes it is not raw power\nyou need, but some sustained\ndamage. Unlocks Sonic Grenades.",
	
	"New generation backpacks are\nsuper lightweight, marines can\ncarry these to double the capa-\ncity of their special ammo types.",
	
	"Investigating the corpses of the\nvarious demons killed helped us\nunlock the secrets of their\noccult powers, allowing use of\noccult melee weaponry. Unlocks\nExcalibat and Necromancer's\nScythe.",
	"Some can say pistols are useless\nbut we beg to differ. Some\npistols can be quite potent.\nUnlocks Scatter Pistol.",
	"Through scientific research we\ncame up with stronger tiers of\nslot 3 weaponry. Unlocks Silver\nGun and Slayer.",
	"Ever wanted to use more danger-\nous machineguns? Now you can!\nUnlocks Minigun and Ebony Can-\nnon.",
	"Our scientists never cease to a-\nmaze us! We have new toys to\nblow things up with! Unlocks Ro-\ntary GL and Heavy Missile\nLauncher.",
	"Destorying things has never been\nthis fun! Demons sure know how\nto kill things... Unlocks Nailgun\nand Basilisk.",
	"If you think your BFG6000 is un-\nderwhelming, try these! Unlocks\nBFG32768, Devastator and\nDestruction Generator.",
	
	"Some of the zombies were using\nquite improved versions of your\nweaponry. Now we can utilize\nthe same for your slot 2\nweapons. Unlocks Assault Rifle.",
	"Through various investments we\ncan now utilize better shotgun\nmechanics. Unlocks Deadlock.",
	"Our scientists were obsessed\nwith creating energy in fixed\nbursts and now they can! Unlocks\nPlasma Cannon.",
	"Finally an answer to the un-\ndead menace, this silver bullet\nshooting machine gun will make\nquick work of undeads and magi-\ncal creatures alike! Unlocks\nTemplar MG.",
	"Using energies of demons we can\nnow create meteors at will and\nso can you! Unlocks Meteor\nLauncher.",
	"It always occured to us, why\ndon't we have a Grenade Launcher\nwhen we have a Rocket Launcher?\nYeah, now we have both.",
	"Burning enemies to crisps is\nnever boring! Unlocks Flame\nThrower.",
	"We have miniguns, laser cannons\nand other various toys but not\nan Ion Cannon... Now we do!",
	
	"With this groundbreaking rese-\narch, we can now utilize powers\nof the demons to empower our-\nselves! Unlocks certain abilities.",
	"Powerful demons can teach us\na lot of things. Now we can uti-\nlize their immense power for even\nbetter weapons! Unlocks\nslot 8 weapons.",
	"Nano-technology is finally here!\nUnlocks certain abilities.",
	"Artifacts have always been an\nelusive aspect. However with de-\nmon technology we can harness\nmore! Unlocks certain\nartifacts."
	
};

enum {
	POPUP_NONE,
	POPUP_NOFUNDS,
	POPUP_CANTBUY,
	POPUP_ALREADYOWN,
	POPUP_DONTOWN,
	POPUP_NEEDRESEARCH,
	POPUP_NOBUDGET,
	POPUP_NEEDDISCOVER,
	POPUP_ALREADYRESEARCHED
};

#define MAX_POPUPS POPUP_ALREADYRESEARCHED + 1
str PopupText[MAX_POPUPS] = {
	"",
	"Insufficient funds.",
	"You can't buy this item.",
	"You already own this\nitem!",
	"You don't own this item.",
	"You need to research\nthis item!",
	"Insufficient budget!",
	"You need to discover\nthis research!",
	"You already did this\nresearch!"
};