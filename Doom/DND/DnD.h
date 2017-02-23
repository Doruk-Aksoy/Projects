#define MAXUPG 14
#define MAXTEMPWEPS 10
#define MAXBACKPACK 55 // To reach 600 shells
#define UNUSEDWEPS 5
#define TEMPBEGIN (MAXWEPS - MAXTEMPWEPS) - UNUSEDWEPS
#define PERK_GAIN_RATE 5

#define ASPECT_4_3 (4.0 / 3)
#define ASPECT_5_4 1.25
#define ASPECT_16_9 (16.0 / 9)
#define ASPECT_16_10 1.6

#define BASEPISTCLIP 12
#define BASEMGCLIP 50
#define BASEHMGCLIP 60

#define SHELLMAX 600
#define EXPSHELLMAX 480
#define CLIPMAX 2400
#define EBONYMAX 720
#define EBONYXMAX 360
#define ROCKETMAX 600
#define GRENADEMAX 600
#define HMISMAX 480
#define CELLMAX 3600
#define NAILMAX 1200
#define BASILISKMAX 3000
#define GAUSSMAX 900

// dash script defs, by KeksDose
#define SD_TIMEFRAME		7					// Tics during which you must double press
#define SD_DASHDELAY		27			// Tics before being able to dash again
#define SD_DASHSPEED		9.0	   		// Dash speed whilst in the air
#define SD_DASHJUMP			4.0	   	    // Adds a little z-velocity while in the air
#define SD_DASHSTRONG		20.0			// And dash speed whilst grounded
#define SD_SOUNDVOLUME		1.0	    // How loud the dash sound is played

#define CHANCE_HEART 10

#define UPGRADETEXTID 6999
#define SURVIVEICO 7000
#define SURVIVETOPTEXTID 7001
#define SURVIVETEXTID 7002
#define SURVIVEID 7003

#define VORTEXTIDSTART 10000
#define P_TEMPTID 200
#define RAILINITTID 2000
#define RAILTIDADD 500
#define SPECIAL_FX_TID 32768

#define REFLECTFXTID 9000

#define EXP_SCALE_MAX 10
#define CREDIT_SCALE_MAX 10

#define INTERVENTION_DURATION TICRATE * 8

#define DND_BUDGET_BASE 5
#define DND_BACKPACK_RATIO 5
#define DND_MAX_SHARE 4
#define DND_MUNITION_GAIN 10
#define DND_SPREE_AMOUNT 4 * TICRATE // 4 * 35
#define DND_SPREE_PER 10
#define DND_SPREE_TRIGGER DND_SPREE_PER - 1 // -1 because current monster killed doesn't count
#define DND_SPREE_BASE 4 // 1 / 4
#define DND_SPECIALAMMO_TEXTID 6001
#define DND_SPREE_BLOODID 6000
#define DND_SPREE_TEXT1ID 5999
#define DND_SPREE_TEXT2ID 5998

#define DND_CYBERNETICARMOR_AMOUNT 200
#define DND_RAVAGERARMOR_AMOUNT 150

#define DND_HEALTHEXPSCALE 5
#define DND_HEALTHCREDITSCALE 15
#define DND_HEALTHCREDITUPSCALE 2

#define AGAMOTTO_MOVE_WINDOW 1 << 16

#define TEMP_TID 999999

// RPG ELEMENTS END

global int 0: MedkitAmount[];
global int 2: ShieldAmount[];
global int 3: MapChanged;

int screenres1, screenres2;
int setplayer = 0;
// see if map changed or not

enum {
	AMMO_CLIP,
	AMMO_SHELL,
	AMMO_ROCKET,
	AMMO_CELL,
	AMMO_GRENADE,
	AMMO_HMISSILE,
	AMMO_NAIL,
	AMMO_EXSHELL,
	AMMO_SOUL,
	AMMO_EBONY1,
	AMMO_EBONY2,
	AMMO_LAVA,
	AMMO_GAUSS,
	AMMO_SLAYER,
	AMMO_PCANNON,
	AMMO_ION,
	AMMO_FUEL,
	AMMO_METEOR,
    AMMO_LIGHTNING
};

#define MAXAMMOTYPES AMMO_LIGHTNING + 1

str AmmoTypes[MAXAMMOTYPES] = { "Clip",    "Shell",    "RocketAmmo", "Cell",    "Grenades",   "MISAmmo", "Nail",    "ExplodingShell",    "Souls",   "EbonyAmmo", "EbonyAmmoX", "BasiliskAmmo", "GaussRound", "SlayerAmmo", "PCanAmmo", "IonAmmo", "Fuel", "MeteorAmmo", "LightningCell" };
str AmmoMaxes[MAXAMMOTYPES] = { "ClipMax", "ShellMax", "RocketMax",  "CellMax", "GrenadeMax", "MISMax",  "NailMax", "ExplodingShellMax", "SoulMax", "EbonyMax",  "EbonyXMax", "BasiliskMax", "GaussMax", "SlayerMax", "PCanAmmoMax", "IonAmmoMax", "FuelMax", "MeteorMax", "LightningCellMax"  };

int InitialCapacity[MAXAMMOTYPES] = { 
	200, 
	50, 
	50, 
	300, 
	50, 
	80, 
	175, 
	40, 
	75, 
	60, 
	30, 
	250, 
	75, 
	40,
	35,
	180,
	250,
	40,
    375
};

int CapacityPerBackPack[MAXAMMOTYPES] = {  
	40,  
	10,  
	10,  
	60,  
	10,  
	16,  
	35,  
	8, 
	0, 
	12, 
	6, 
	50, 
	15, 
	8,
	7,
	36,
	50,
	8,
    75
};

int BackpackAmounts[MAXAMMOTYPES] =     {  10,  4,  1,  20,  1,  2,   2,  2, 0, 4, 2, 15, 5, 2, 3, 9, 15, 2, 18 };
str PickupText[2] = { "\cgPicked up a stimpack", "\cgPicked up a medikit." };

str RailGunTrails[3] = { "RedRayTrail", "YellowRayTrail", "BlueRayTrail" };
str RailGunDamagers[3] = { "RailDamager_Red", "RailDamager_Yellow", "RailDamager_Blue" };

str TemporaryWeapons[MAXTEMPWEPS] = { "Sawedoff", "Soul Render", "SMG", "Hellforge Cannon", "Bloodfiend Spine", "Enforcer Rifle", "Venom", "Demon Heart", "DarkServantGloves", "Nailgun2" };
str TemporaryWeaponDrops[MAXTEMPWEPS] = { "SawedoffPickup_D", "SoulRenderPickup_D", "SMGPickup_D", "HellforgePickup_D", "SpinePickup_D", "LaserPickup_D", "VenomPickup_D", "DemonHeartPickup_D", "DarkServantGlovesPickup_D", "Nailgun2Pickup_D" };
str TemporaryAmmos[MAXTEMPWEPS] = { "SawedoffShell", "BladeHits", "SMGAmmo", "IronBalls", "BloodAmmo", "LaserAmmo", "VenomAmmo", "HeartAmmo", "DarkServantEnergy", "BigNail" };
str TemporaryWeaponMsg[MAXTEMPWEPS] = { 
        "\ccWeapon Pickup : \c[Y5]Sawedoff - 9\c-",
        "\ccWeapon Pickup : \c[Y5]Soul Render - 9\c-",
        "\ccWeapon Pickup : \c[Y5]Submachine Gun - 9\c-",
        "\ccWeapon Pickup : \c[Y5]Hellforge Cannon - 9\c-",
        "\ccWeapon Pickup : \c[Y5]Bloodfiend Spine - 9\c-",
        "\ccWeapon Pickup : \c[Y5]Enforcer Laser Rifle - 9\c-",
        "\ccWeapon Pickup : \c[Y5]Venom - 9\c-",
        "\ccWeapon Pickup : \c[Y5]Demon Heart - 9\c-",
        "\ccWeapon Pickup : \c[Y5]Dark Servant Gloves - 9\c-",
        "\ccWeapon Pickup : \c[Y5]Heavy Nailgun - 9\c-"
};
									  
str WeaponMsg[7] = 	{  
						"\ccWeapon Pickup : \c[Y5]Chainsaw - 1\c-",
						"\ccWeapon Pickup : \c[Y5]Shotgun - 3\c-",
						"\ccWeapon Pickup : \c[Y5]Super Shotgun - 3\c-",
						"\ccWeapon Pickup : \c[Y5]Machine Gun - 4\c-",
						"\ccWeapon Pickup : \c[Y5]Rocket Launcher - 5\c-",
						"\ccWeapon Pickup : \c[Y5]Plasma Rifle - 6\c-",
						"\ccWeapon Pickup : \c[Y5]BFG 9000 - 7\c-"
					};
							
str WeaponPickupText[MAXWEPS] = {  
									// |                                                                       | 81 characters
									 "Time to get your hands dirty. Does 10 - 30 damage\nnormally or 180 - 240 with berserk per hit.",
									 "Open invitiation to the slaughterhouse! Can be\n\cdreplaced.",
									 "Double the blade, double the fun! Twice as much\ndamage, same firing rate.",
									 "Sickle steals life from enemies on hit. Does\n35 - 50 damage 3 times. Alt fire swings for\nirreducable 60 - 80 damage 3 times. Altfire\nrequires Close Combat Mastery.",
									 "Does 100 - 150 damage per swing. Alt fire\ncharges and releases 17 baseballs each doing\n30 - 45 on impact and 64 damage in a 96\nunit radius. Alt fire requires Close Combat Mastery.\n\cfIgnores shields.\c- Can't hit \cughosts.",
									 "Your trustworthy Colt45, been with you since the\nstart. Does 15 damage in a 0.5 spread.\nCan be \cdreplaced.",
									 "Akimbo longslides. Does 35 damage per shot in a\n1.25 by 0.5 spread.",
									 "Magnum is a true classic, shooting bullets\neach doing 170 - 230 damage. Has a capacity of 6.\n50 damage from bullet rip through enemies.\nAlt fire reloads. \cfIgnores shields.",
									 "Laser Pistol is the fresh invention of UAC. Shoots\nlasers doing 15 - 30 damage in a 2.0 by 1.25 spread.\nsAlt fire charges to do up to a x5 damage rail.\nDoesn't use ammo. \cfIgnores shields.",
									 "Scatter Pistol shoots 3 pellets each doing\n8 - 16 damage. Pellets scatter to 5 tiny pel-\nlets doing 2- 8 damage. Alt fire shoots one\npellet. \cfIgnores shields.\c- Irreducable damage.",
									 "Assault Rifle does 18 damage per bullet in a 3.6 by\n2.4 spread. Magazine capacity of 31. Alt fire\nzooms, allowing more precise shots.",
									 "Typical boomstick, now spreads vertically too.\n9 pellets, each doing 5-10-15 damage.\nCan be \cdreplaced.",
									 "The purifier shotgun, spread's with 3.6 by 3.6.\n15 pellets, each doing 15 damage. Has a\nshell capacity of 8. Alt fire reloads.",
									 "Killstorm Auto Shotgun, drum fed with 10 shells,\ncan shoot 10 pellets each doing 15 damage in a\n7.2 by 5.2 spread. Alt fire reloads.",
									 "Deadlocks fires 16 pellets doing 15 damage in a 4.8\nby 3.6 spread. Has a shell capacity of 12. Can use\n\cialternate\c- ammo.",
									 "Same old buckshot we all love! Can be \cdreplaced.",
									 "Heavy Super Shotgun shoots 24 pellets doing 15\ndamage in a 9.6 by 5.8 spread. 8 of these rip\nthrough targets.",
									 "Erasus shotgun shoots highly ballistic shells\nwith 16 pellets each doing 15 damage. Has to\nreload after shooting twice. Alt fire shoots\nboth shells in the chamber, or reloads.",
									 "Fires 24 plasma balls in a circular fashion\neach doing 20 damage. Does irreducable\ndamage. Has a clip size of 5.",
									 "The explosive shotgun, the best there is. Fires\n9 pellets, each doing 15 on hit. Each pellet\ndoes 32-48 damage in a small area. Does self\ndamage. \cfIgnores shields.",
									 "Slayer creates 6 blades each doing 9 damage\nand rip through. Alt fire detonates blades at\nwill for 90 damage in a 96 unit radius, \cfignoring\n\cfshields\c-. Blades return to you after travelling a bit.\nCan't hit \cughosts.",
									 "An accurate and a very reliable weapon.\nEach bullet does 15 damage. Alt fire reloads.\nClip size is 50. Can be \cdreplaced.", 
									 "Finest machine guns UAC has to offer. Bullets\ndo 25 damage in a 1.6 by 0.8 spread.\nClip size is 60. Can zoom.",
									 "Lead Spitter is a super sonic bullet shooter\nshooting 2 bullets doing 18 damage in a\n6.4 by 4.8 spread. Clip size is 75.\n\cfIgnores shields.",
									 "Templar fires silver bullets doing 20 damage\nin a 4.4 by 2.8 spread. Bullets deal x3 damage\nto undead and magical enemies. Clip size of 40.\nCan use \cigrenades\c-.",
									 "Stronger, faster and better than ever! Poor\naccuracy, shoots tracers that do 16 - 28 damage\neach. Alt fire to spin. Can't hit \cughosts.",
									 "The ebony cannon shoots bouncing balls of death.\n16 - 40 damage with 48 explosion damage in 64\nunits. Alt fire shoots scatter bombs.\n\cfIgnores shields.",
									 "A true classic. Just don't blow yourself up.\nCan be \cdreplaced. Can't hit \cughosts.",
									 "The Torpedo Launcher shoots fast torpedos each\ndoing 180 - 220 damage on impact and 224\ndamage in a 128 unit radius. Can't hit \cughosts.",
									 "Mercury Launcher fires accelerating and heat\nseeking mercury missiles doing 256 - 320 damage on\nhit and 192 damage in a 160 unit radius over\n2 seconds. Can't hit \cughosts.",
									 "Fires a meteor doing 200 on impact and 192\nin a 192 unit radius. The meteor then splits into\nsmaller pieces, and those pieces as well. Main\nmeteor \cfignores shields\c-.",
									 "Useful for when you can't reach around corners.\nDoes 80 damage on impact and 128 damage in a\n144 unit radius. Can be \cdreplaced.\nCan't hit \cughosts",
									 "The UAC Rotary Grenade Launcher does 192\ndamage on impact and 192 damage on a 192 unit\nradius. Can't hit \cughosts",
									 "Top of the food chain for rockets. Shoots two\nhoming rockets each doing 160 damage both on\nimpact and explosion. Can't hit \cughosts.",
									 "Best friend of the trigger happy.\nCan be \cdreplaced.",
									 "Improved with a nuclear reactor, does 36 - 60 on\nhit and 10 - 30 explosion damage in a 48 unit\nradius. Can \cgoverheat\c-. Does self damage.",
									 "Turel Cannon fires highly ionized particles\ndoing 125 damage ripping through everything.\nContinuous fire is less accurate and does 80\ndamage. Has a range of 768 units. Altfire\nfires focused shots.",
									 "Flamethrower does what it says and throws\nflames doing 1 - 8 damage. When they hit, they\nleave a trail of flame doing 5 damage every 2 tics.\nFuel size of 75.",
									 "UAC offers this shockingly deadly weapon\nthat can shoot lightning doing 11-15 damage. Alt\nfire shoots forked lightning. Keep firing and da-\nmage increases by 4% per stack. Stacks additively.",
                                     "An interesting demonic artifact shooting nails.\nEach nail does 8 - 16 damage and rips through.\nAlt fire shoots explosive lava nails that\n\cfignores shields.\c- Can't hit \cughosts.",
									 "Basilisk is said to be the ancient weapon of\nhell's most elite warriors. If not loaded, shoots\nfire balls doing 5 - 40 damage. If loaded, shoots\nmeteors doing 60 - 120 on impact and 96 explosion\ndamage. \cf Ignores shields.",
									 "BFG 6000, an older model but still capable.\nCan be \cdreplaced.\cf Ignores shields.",
									 "The newest BFG model 32768, devastates\nwith 600 / 900 damage on impact and 384\ndamage in a 160 unit radius. Also shoots 64 tracers\ninstead of 40.",
									 "Devastator launches three mini rockets each\ndoing 32 to 80 with 32 radius damage in 72\nunits. Can't hit \cughosts. \c-\cfIgnores shields.",
									 "Fires a destructive orb doing 400 - 600 damage\non impact and 384 damage in a 768\nunit radius. Creates 6 smaller explosions doing\n250 damage on impact and 192 damage in a\n256 unit radius. \cfIgnores shields.",
									 "Fires ionized energy doing 100 impact and 96\narea damage in 160 unit radius. Can \cgoverheat\c-.\n\cfIngores shields\c-. Can't hit \cughosts\c-.",
									 "Gauss Rifle fires a magnetic pulse dealing 100\ndirect hit damage and 192 radius damage in a\n96 unit radius. Alt fire zooms and amplifies the\ndamage for each zoom. Can't hit \cughosts.\c-\n\cfIgnores shields.",
									 "This baby can rip through concrete with ease.\nEach shot does multiples of 92. Alt fire charges up\nthe next shot up to 2 times. \cfIgnores shields.",
									 "A magical staff, using demon souls as energy.\nFires meteors of magic, bursting on impact. Alt\nfire fires 3 columns of fire both on floor and\nceiling that travel and explode in flames.\n\cfIgnores shields.",
									 "This once was the ribcage of a powerful demon.\nFires magical bone shards that rip through.\nAlt fire switches the mode to shoot three\ndemon shredders that seek demons.",
									 "This holy relic was lost in ancient battles.\nFires sun beams to burn anything. Alt fire\nchannels the very essence of sun causing a\nmassive meltdown. \cfIgnores shields\c-.",
									 "Soul Reaver creates portals that lead to hungry\nghosts that devour their enemies. Hold to gain\na deflective shield. \cfIgnores shields.",
									 
                                     "The sawedoff is a western classic. Fires 16\npellets each doing 15 damage.\n\ceTemporary Weapon.",
									 "Soul Render is an unholy melee weapon.\nEach hit makes the weapon become less durable.\nAlt fire toggles life drain mode.\n\ceTemporary Weapon.",
									 "A standard UAC submachine gun. Each bullet\ndoes 15 damage.\n\ceTemporary Weapon.",
									 "The arm-cannon of a Corpulent. Shoots\nmetallic cannon balls that split on impact.\nAlt fire shoots tiny ripping cannon balls.\n\ceTemporary Weapon.",
									 "The spine of a Bloodfiend. Shoots tiny\nexplosive pukes. Alt fire changes it\nto a limited range hitscan.\n\ceTemporary Weapon.",
									 "The laser rifle shoots a laser or two, if using alt\nfire, each doing 20-45 damage. \cfIgnores\n\cfshields. \ceTemporary Weapon.",
									 "The torso of a Vulgar. Shoots acidic bones.\nAlt fire shoots bouncing acid bombs.\nCan't hit \cughosts\c-.\n\ceTemporary Weapon.",
									 "A demon heart. Squeeze to damage all enemies\n in an area.\cfIgnores shields.\n\ceTemporary Weapon.",
                                     "Gloves of a dark servant. Can shoot pain enforcing\nlightning bolts doing 60-90 damage. Alt fire shoots a\nhoming explosive lightning ball doing 120-180\ndamage on hit and 96 area damage over 9 tics.\n\ceTemporary Weapon.",
                                     "A nail-chaingun, quite useful for mass murder of\ndemons. Shoots nails ripping for 16-32 damage.\n\ceTemporary Weapon.",
                                };							
	
#define MAX_SPREE_TEXT 16
str SpreeText[MAX_SPREE_TEXT] = {
	"Cruel",
	"Merciless",
	"Crushing",
	"Sadistic",
	"Vicious",
	"Terrifying",
	"Terrorizing",
	"Rampage",
	"Unstoppable",
	"Massacre",
	"Bloodthirsty",
	"Monstrous",
	"Genocide",
	"Holocaust",
	"Diabolical",
	"Legendary"
};

#define MAXWEPUPGRADES 5
#define MAXNORMALWEPSLOTS 8
str SlotWeapons[8][MAXWEPUPGRADES] = {
	{ " Chainsaw ", "Upgraded Chainsaw", "Sickle", "Excalibat", "" },
	{ "Magnum", " Akimbo Pistols ", "Laser Pistol", "ResPistol1", "" },
	{ " Shotgun ", "Upgraded Shotgun", "Upgraded Shotgun2", "ResShotgun1", "" },
	{ " Super Shotgun ", "Upgraded Super Shotgun", "Upgraded Super Shotgun2", "ResSSG1", "" },
	{ " Machine Gun ", "Upgraded Machine Gun", "Upgraded Machine Gun2", "ResMG1", "" },
	{ "Rocket Launcher", "Upgraded Rocket Launcher", "Upgraded Rocket Launcher2", "ResRL1", "" },
	{ "Plasma Rifle", "Upgraded Plasma Rifle", "Upgraded Plasma Rifle2", "ResPlasma1", "ResPlasma2" },
	{ "BFG 9000", "Upgraded BFG 9000", "Devastator", "MFG", "ResBFG1" },
};

enum {
	AMMO_BASICSHELL,
	AMMO_FLECHETTE,
	AMMO_PIERCING,
	AMMO_ELECTRIC,
	
	AMMO_BULLET,
	AMMO_BASICGRENADE,
	AMMO_40MMSONIC,
	AMMO_40MMHEGRENADE
};

enum {
	AMMO_TYPE_SHELL,
	AMMO_TYPE_MGGRENADE,
	AMMO_TYPE_GRENADE
};

#define SPECIALAMMO_TYPE_MAX AMMO_TYPE_GRENADE + 1
int SpecialAmmoBase[SPECIALAMMO_TYPE_MAX] = { AMMO_BASICSHELL, AMMO_BULLET, AMMO_BASICGRENADE };
int SpecialAmmoLimits[SPECIALAMMO_TYPE_MAX] = { AMMO_ELECTRIC, AMMO_40MMHEGRENADE, AMMO_40MMHEGRENADE };

#define AMMODISPLAY_ID 1000

#define MAXSPECIALAMMOCATEGORY 2
#define MAXSPECIALAMMOTYPES AMMO_40MMHEGRENADE + 1
#define SPECIALAMMO_NAME 0
#define SPECIALAMMO_TAG 1
str SpecialAmmoNames[MAXSPECIALAMMOTYPES][2] = {
	{		"Shell",					"Normal Shells"						},
	{ 		"FlechetteShell",			"\cdFlechette Shells"				},
	{ 		"PiercingShell",			"\cfMagnum Shells"					},
	{		"ElectricShell",			"\cvElectric Shells"				},
	
	{		"Clip",						"Bullets"							},
	{		"Grenades",					"40mm Grenades"						},
	{		"A40mmSonicGrenade",		"\cu40mm Sonic Grenades"			},
	{		"A40mmHEGrenade",			"\cr40mm HEGrenades"				}
};

enum {
	SPWEP_SG,
	SPWEP_SSG,
	SPWEP_MG,
	SPWEP_GL
};

int CurrentLevelReward[MAXPLAYERS];
int CurrentStatReward[MAXPLAYERS];

#define MAXCREDITDROPS 3
int CreditDroppers[MAXCREDITDROPS] = { "SmallCreditDropper", "MediumCreditDropper", "LargeCreditDropper" };
int CreditDropThresholds[MAXCREDITDROPS] = { 500, 1500, 0x7FFFFFFF };
int CreditDropChances[MAXCREDITDROPS] = { 20, 25, 30 };

int SpecialFXRunning[MAXPLAYERS];

function int CheckBit(int x, int n) {
	return x & (1 << n);
}

function int ResetBits(int val, int begin, int end) {
	for(int i = begin; i < end + 1; ++i)
		val &= ~(1 << i);
	return val;
}

function int HasSpecialAmmoForWeapon(int ammo_category) {
	for(int i = SpecialAmmoBase[ammo_category] + 1; i <= SpecialAmmoLimits[ammo_category]; ++i)
		if(CheckInventory(SpecialAmmoNames[i][SPECIALAMMO_NAME]))
			return i;
	return SpecialAmmoBase[ammo_category];
}

function str GetSpecialAmmoSuffix(int weptype) {
	str suffix = "";
	if(weptype == SPWEP_SG)
		suffix = "_3";
	else if(weptype == SPWEP_SSG)
		suffix = "_3X";
	else if(weptype == SPWEP_MG)
		suffix = "_4";
	else if(weptype == SPWEP_GL)
		suffix = "_5X";
	return suffix;
}

function int GetSpecialAmmoMode(int ammo_category, int weptype) {
	str suffix = GetSpecialAmmoSuffix(weptype);
	return CheckInventory(StrParam(s:"SpecialAmmoMode", s:suffix));
}

function void SetSpecialAmmoMode(int ammo_category, int weptype) {
	int mode = GetSpecialAmmoMode(ammo_category, weptype);
	// while can cycle through on next, if no ammo keep searching and take mod
	do {
		mode = (mode + 1) % (SpecialAmmoLimits[ammo_category] + 1);
		if(!mode)
			mode = SpecialAmmoBase[ammo_category];
	} while(!CheckInventory(SpecialAmmoNames[mode][SPECIALAMMO_NAME]));
		
	str suffix = GetSpecialAmmoSuffix(weptype);
	SetInventory(StrParam(s:"SpecialAmmoMode", s:suffix), mode);
	SetInventory("AmmoChangeMessage", mode);
}

function int CheckSlotWeapon(int slot) {
	for(int i = 0; i < MAXWEPUPGRADES; ++i)
		if(StrLen(SlotWeapons[slot - 1][i]) && CheckInventory(SlotWeapons[slot - 1][i]))
			return 1;
	return 0;
}

function int GetWeaponPosFromTable(str wepname) {
	for(int i = 0; i < MAXWEPS; ++i)
		if(!StrCmp(wepname, Weapons[i][WEPINFO_NAME]))
			return i;
	return 0;
}

function int GetHealthCap(void) {
	return DEFENSE_BONUS * CheckInventory("PSTAT_Vitality");
}

function int GetHealthMax(void) {
    return 100 + GetHealthCap();
}

function int GetAspectRatio(void) {
	int width = getcvar("vid_defwidth");
	int height = getcvar("vid_defheight");
	int nowidescreen = getcvar("vid_nowidescreen");
	int tft = getcvar("vid_tft");
	int aspect = getcvar("vid_aspect");
	switch(aspect) {
		case 1:	return ASPECT_16_9;
		case 2:	return ASPECT_16_10;
		case 3:	return ASPECT_4_3;
		case 4:	return ASPECT_5_4;
	}
	if(nowidescreen) {
		if(!tft)
			return ASPECT_4_3;
		if(fixedmul(height<<16, fixeddiv(5.0, 4.0)) == width<<16)
			return ASPECT_5_4;
		else
			return ASPECT_4_3;
	}
	if(abs((abs(fixedmul(height<<16, fixeddiv(16.0, 9.0)))>>16) - width) < 10) {
		return ASPECT_16_9;
	}
	if(abs((abs(fixedmul(height<<16, fixeddiv(16.0, 10.0)))>>16) - width) < 60) {
		if((width == 320 && height == 200) || (width == 640 && height == 400))
			return ASPECT_4_3;
		return ASPECT_16_10;
	}
	if(fixedmul(height<<16, fixeddiv(5.0, 4.0))>>16 == width && tft) {
		return ASPECT_5_4;
	}
	return ASPECT_4_3;
}

function int Calculate_Stats() {
	return CheckInventory("PSTAT_Strength") + CheckInventory("PSTAT_Dexterity") + CheckInventory("PSTAT_Bulkiness") + CheckInventory("PSTAT_Vitality") + CheckInventory("PSTAT_Charisma");
}

function int Calculate_Perks() {
	return CheckInventory("Perk_Munitionist") + CheckInventory("Perk_Sharpshooting") + CheckInventory("Perk_Wisdom") + CheckInventory("Perk_Greed") + CheckInventory("Perk_Endurance") + CheckInventory("Perk_Medic");
}

function void Reset_RPGInfo (int resetflags) {
	if(resetflags & RESET_LEVEL) {
		SetInventory("Exp", 0);
		SetInventory("LevelExp", 0);
		SetInventory("Level", 1);
	}
	
	if(resetflags & RESET_CREDIT)
		SetInventory("Credit", 0);
		
	if(resetflags & RESET_STATS) {
		SetInventory("PSTAT_Strength", 0);
		SetInventory("PSTAT_Dexterity", 0);
		SetInventory("PSTAT_Vitality", 0);
		SetInventory("PSTAT_Charisma", 0);
		SetInventory("PSTAT_Bulkiness", 0);
	}
	
	if(resetflags & RESET_PERKS) {
		TakeInventory(StrParam(s:"Damage_Perk_", d:CheckInventory("Perk_Sharpshooting") * 5), 1);
		TakeInventory(StrParam(s:"Resist_Perk_", d:CheckInventory("Perk_Endurance") * 5), 1);
		SetInventory("Perk_Sharpshooting", 0);
		SetInventory("Perk_Endurance", 0);
		SetInventory("Perk_Wisdom", 0);
		SetInventory("Perk_Greed", 0);
		SetInventory("Perk_Medic", 0);
		SetInventory("Perk_Munitionist", 0);
	}
}

function int CheckLevelUp (void) {
	int curlevel = GetStat(STAT_LVL), exptemp;
	// -1 because initial level is 1
	while(curlevel < MAXLEVELS && GetStat(STAT_EXP) >= LevelCurve[GetStat(STAT_LVL) - 1]) {
		exptemp = GetStat(STAT_EXP) - LevelCurve[GetStat(STAT_LVL) - 1];
		if(!((GetStat(STAT_LVL) + 1) % 5)) { // multiples of 5 give perk
			GiveInventory("PerkPoint", 1);
			GiveInventory("PerkedUp", 1);
		}
		GiveInventory("Level", 1);
		SetAmmoCapacity("ExpVisual", LevelCurve[GetStat(STAT_LVL) - 1]);
		SetInventory("Exp", exptemp);
		SetInventory("ExpVisual", exptemp);
		GiveInventory("AttributePoint", ATTRIB_PER_LEVEL);
	}
	return GetStat(STAT_LVL) - curlevel;
}

function int DnD_MessageY() {
	int res = 34.1;
	if(CheckInventory("DnD_ShowKillBonus"))
		res += 16.0;
	if(CheckInventory("DnD_ShowItemBonus"))
		res += 16.0;
	if(CheckInventory("DnD_ShowSecretBonus"))
		res += 16.0;
	if(CheckInventory("DnD_ShowBonusBonus"))
		res += 16.0;
	return res;
}

// Map Evaluation

enum {
	// Monsters
	DND_ZOMBIE_CONTRIB = 3,
	DND_SHOTGUNNER_CONTRIB = 4,
	DND_CHAINGUNNER_CONTRIB = 5,
	DND_IMP_CONTRIB = 4,
	DND_DEMON_CONTRIB = 6,
	DND_HELLKNIGHT_CONTRIB = 10,
	DND_BARON_CONTRIB = 18,
	DND_CACO_CONTRIB = 8,
	DND_PAIN_CONTRIB = 12,
	DND_SOUL_CONTRIB = 4,
	DND_REVENANT_CONTRIB = 9,
	DND_ARACHNO_CONTRIB = 16,
	DND_VILE_CONTRIB = 20,
	DND_FATSO_CONTRIB = 16,
	DND_SPIDERMASTERMIND_CONTRIB = 45,
	DND_CYBERDEMON_CONTRIB = 50,
	DND_BOSSBRAIN_CONTRIB = 9000,
	
	// Items
	DND_HEALTHBONUS_CONTRIB = -1,
	DND_ARMORBONUS_CONTRIB = -1,
	DND_STIM_CONTRIB = -6,
	DND_MEDIKIT_CONTRIB = -12,
	DND_BERSERK_CONTRIB = -30,
	DND_INVUL_CONTRIB = -80,
	DND_SOULSPHERE_CONTRIB = -30,
	DND_MEGA_CONTRIB = -60,
	DND_EVIL_CONTRIB = -20,
	DND_GREENARMOR_CONTRIB = -12,
	DND_YELLOWARMOR_CONTRIB = -18,
	DND_BLUEARMOR_CONTRIB = -24,
	DND_REDARMOR_CONTRIB = -36
};

enum {
	DND_VERYEASY,
	DND_EASY,
	DND_MEDIUM,
	DND_HARD,
	DND_VERYHARD
};

enum {
	DND_VERYEASY_LIMIT = 300,
	DND_EASY_LIMIT = 500,
	DND_MEDIUM_LIMIT = 800,
	DND_HARD_LIMIT = 1250,
	DND_VERYHARD_LIMIT = 1800
};

// 5 Tiers: 0 -> Very Easy, 1 -> Easy, 2 -> Medium, 3 -> Hard and 4 -> Very Hard.
function void CalculateMapDifficulty() {
	int factor = 0;
	// yes this is ugly but it won't ever change, no new spawners will come etc so why not :)
	factor += ThingCountName("ZombiemanSpawner", 0) * DND_ZOMBIE_CONTRIB;
	factor += ThingCountName("ShotgunguySpawner", 0) * DND_SHOTGUNNER_CONTRIB;
	factor += ThingCountName("ChaingunguySpawner", 0) * DND_CHAINGUNNER_CONTRIB;
	factor += ThingCountName("DemonSpawner", 0) * DND_DEMON_CONTRIB;
	factor += ThingCountName("SpectreSpawner", 0) * DND_DEMON_CONTRIB;
	factor += ThingCountName("ImpSpawner", 0) * DND_IMP_CONTRIB;
	factor += ThingCountName("LostSoulSpawner", 0) * DND_SOUL_CONTRIB;
	factor += ThingCountName("CacodemonSpawner", 0) * DND_CACO_CONTRIB;
	factor += ThingCountName("PainElementalSpawner", 0) * DND_PAIN_CONTRIB;
	factor += ThingCountName("RevenantSpawner", 0) * DND_REVENANT_CONTRIB;
	factor += ThingCountName("HellKnightSpawner", 0) * DND_HELLKNIGHT_CONTRIB;
	factor += ThingCountName("BaronSpawner", 0) * DND_BARON_CONTRIB;
	factor += ThingCountName("FatsoSpawner", 0) * DND_FATSO_CONTRIB;
	factor += ThingCountName("SpiderSpawner", 0) * DND_ARACHNO_CONTRIB;
	factor += ThingCountName("ArchVileSpawner", 0) * DND_VILE_CONTRIB;
	factor += ThingCountName("MastermindSpawner", 0) * DND_SPIDERMASTERMIND_CONTRIB;
	factor += ThingCountName("CyberSpawner", 0) * DND_CYBERDEMON_CONTRIB;
	factor += ThingCountName("BossBrain", 0) * DND_BOSSBRAIN_CONTRIB;
	
	factor += ThingCountName("InvulnerabilitySphere2", 0) * DND_INVUL_CONTRIB;
	factor += ThingCountName("StimpackSpawner", 0) * DND_STIM_CONTRIB;
	factor += ThingCountName("MedikitSpawner", 0) * DND_MEDIKIT_CONTRIB;
	factor += ThingCountName("BonusReplacer", 0) * DND_HEALTHBONUS_CONTRIB;
	factor += ThingCountName("BonusReplacer2", 0) * DND_ARMORBONUS_CONTRIB;
	factor += ThingCountName("EvilSphere2", 0) * DND_EVIL_CONTRIB;
	factor += ThingCountName("UberSphere2", 0) * DND_MEGA_CONTRIB;
	factor += ThingCountName("SoulSphere3", 0) * DND_SOULSPHERE_CONTRIB;
	factor += ThingCountName("MegaSphere3", 0) * DND_MEGA_CONTRIB;
	factor += ThingCountName("Berserk2", 0) * DND_BERSERK_CONTRIB;
	factor += ThingCountName("NewGreenArmor2", 0) * DND_GREENARMOR_CONTRIB;
	factor += ThingCountName("YellowArmor2", 0) * DND_YELLOWARMOR_CONTRIB;
	factor += ThingCountName("NewBlueArmor2", 0) * DND_BLUEARMOR_CONTRIB;
	factor += ThingCountName("TheRedArmor2", 0) * DND_REDARMOR_CONTRIB;
	if(factor >= DND_VERYHARD_LIMIT)
		MapDifficulty = DND_VERYHARD;
	else if(factor >= DND_HARD_LIMIT)
		MapDifficulty = DND_HARD;
	else if(factor >= DND_MEDIUM_LIMIT)
		MapDifficulty = DND_MEDIUM;
	else if(factor >= DND_EASY_LIMIT)
		MapDifficulty = DND_EASY;
	else
		MapDifficulty = DND_VERYEASY;
}

enum {
	BONUS_KILL,
	BONUS_ITEM,
	BONUS_SECRET,
	BONUS_BONUS,
	BONUS_EXP_RATE = 5,
	BONUS_CREDIT_RATE = 250,
	BONUS_SECRET_RATE = 1,
};

function int CalculateBonus(int bonustype) {
	if(bonustype == BONUS_KILL) {
		// add 5% for each difficulty level
		return BONUS_EXP_RATE * (MapDifficulty + 1);
	}
	else if(bonustype == BONUS_ITEM) {
		// add 250 credit for each difficulty level
		return BONUS_CREDIT_RATE * (MapDifficulty + 1);
	}
	else if(bonustype == BONUS_SECRET) {
		// add 1 stat point for each difficulty level
		return BONUS_SECRET_RATE * (MapDifficulty + 1);
	}
	else if(bonustype == BONUS_BONUS) {
		return BONUS_SECRET_RATE * 2 * (MapDifficulty + 1);
	}
	return 1;
}

function int IsUsingMeleeWeapon() {
	return CheckWeapon(" Fists ") || CheckWeapon(" Chainsaw ") || CheckWeapon("Upgraded Chainsaw") || CheckWeapon("Sickle") || CheckWeapon("Excalibat") || CheckWeapon("Soul Render");
}

// Hardcore Info
#define DND_HARDCORE_INVALID 0
#define DND_HARDCORE_VALID 1
#define MAXFLAGS 26
str FlagCheckList[MAXFLAGS] = {
	"sv_maxlives",
	"sv_coop_damagefactor",
	"sv_cheats",
	"sv_fastweapons",
	"sv_nomapvote",
	"sv_nodrop",
	"sv_infiniteAmmo",
	"sv_NoMonsters",
	"SV_FastMonsters",
	"SV_RespawnSuper",
	"SV_NoWeaponSpawn",
	"SV_Coop_LoseInventory",
	"SV_Coop_LoseWeapons",
	"SV_Coop_LoseArmor",
	"SV_Coop_LosePowerups",
	"SV_Coop_LoseAmmo",
	"SV_Coop_HalveAmmo",
	"SV_WeaponDrop",
	"SV_DoubleAmmo",
	"SV_Degeneration",
	"SV_BFGFreeAim",
	"SV_ShotgunStart",
	"SV_InfiniteInventory",
	"SV_NoAutomap",
	"SV_NoAutomapAllies",
	"Compat_ClientsSendFullButtonInfo"
};

int FlagAcceptedValues[MAXFLAGS] = {
	2,
	1.0,
	0,
	0,
	1,
	1,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	1,
	0,
	0,
	0,
	0,
	1
};

#define MAXDNDFLAGS 39
str DNDFlagCheckList[MAXDNDFLAGS] = {
	"dnd_monsterbars",
	"dnd_monsterscale",
	"dnd_sharexp",
	"dnd_sharecredit",
	"dnd_healonlevelup",
	"dnd_bossfights",
	"dnd_killspree",
	"dnd_firstbackpackold",
	"dnd_playercount_scales_monsters",
	"dnd_fullshare",
	"dnd_monsterlevel_behind",
	"dnd_credit_drops",
	"dnd_gainonlyinrange",
	"dnd_allresearchesfound",
	"dnd_disablelevelbonus",
    "dnd_usesmartmonsterspawner",
    "dnd_healthbasedexp",
    "dnd_healthbasedcredit",
	
	"dnd_shop_scale",
	"dnd_shop_wep_scale",
	"dnd_shop_ammo_scale",
	"dnd_shop_artifact_scale",
	"dnd_shop_ability_scale",
	"dnd_shop_talent_scale",
	"dnd_shop_armor_scale",
	"dnd_monsterlevel_low",
	"dnd_monsterlevel_high",
	"dnd_respawn_count",
	"dnd_accessory_droprate",
	"dnd_credit_droprateadd",
	"dnd_gainrange",
	"dnd_exp_scale",
	"dnd_credit_scale",
	"dnd_accessorylevel",
	"dnd_accessorymonsterlevel",
	"dnd_monster_hpscalepercent",
	"dnd_monster_rewardscalepercent",
	"dnd_monster_dmgscalepercent",
    "dnd_researchdroprate"
};

int DNDFlagAcceptedValues[MAXDNDFLAGS] = {
	1,
	1,
	1,
	1,
	0,
	1,
	1,
	0,
	1,
	1,
	0,
	1,
	1,
	0,
	0,
    1,
    1,
    1,
	
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	2,
	3,
	3,
	0,
	768,
	1,
	1,
	20,
	24,
	4,
	5,
	0.04,
    1
};

// Checks pre-defined settings for hardcore mode that has character saving
// returns 1 if succeeded, 0 if failed
function int CheckHardcoreSettings() {
	// check all flags compare with default values
	int i;
	for(i = 0; i < MAXFLAGS; ++i) {
		if(GetCVar(FlagCheckList[i]) != FlagAcceptedValues[i]) {
			Log(s:"\"", s:FlagCheckList[i], s:"\" should be set to ", d:FlagAcceptedValues[i], s:" for \cghardcore\c- mode to work!");
			return DND_HARDCORE_INVALID;
		}
	}
	for(int i = 0; i < MAXDNDFLAGS; ++i) {
		if(GetCVar(DNDFlagCheckList[i]) != DNDFlagAcceptedValues[i]) {
			Log(s:"\"", s:DNDFlagCheckList[i], s:"\" should be set to ", d:DNDFlagAcceptedValues[i], s:" for \cghardcore\c- mode to work!");
			return DND_HARDCORE_INVALID;
		}
	}
	return DND_HARDCORE_VALID;
}

// These are only used when monster file is employed
// First element on each list is the "Vanilla" monster, rest follow from their variations with Var1 to VarX
#define MAX_MONSTER_CATEGORIES 17
#define MAX_MONSTER_VARIATIONS 15
int Monster_Weights[MAX_MONSTER_CATEGORIES][MAX_MONSTER_VARIATIONS] = {
    // Zombieman
    { 16, 16, 8, 12, 8, 8, 8, 8, 16, 12, 8, -1 },
    // Shotgunguy
    { 16, 4, 8, 6, 4, 4, 6, 6, 4, -1 },
    // Chaingunguy
    { 8, 8, 8, 6, 4, 4, 4, 3, 4, -1 },
    // Demon
    { 16, 16, 12, 8, 12, 16, 8, 10, 7, 8, 10, 10, -1 },
    // Spectre
    { 1, 1, 1, 1, 1, 1, 1, 1, -1 },
    // Imp
    { 16, 8, 8, 8, 8, 8, 16, 16, 16, 12, 12, 8, 8, 8, 10 },
    // Caco
    { 16, 16, 16, 12, 12, 10, 16, 16, 16, 12, -1 },
    // Pain Elemental
    { 16, 12, 10, 10, 16, 16, 12, 12, -1 },
    // Lost Soul
    { 8, 8, 6, 8, 8, 8, 6, -1 },
    // Revenant
    { 16, 16, 12, 12, 8, 9, 9, 8, 9, 10, -1 },
    // HellKnight
    { 16, 16, 14, 12, 10, 10, 10, 10, 8, 12, 12, -1 },
    // Baron
    { 16, 16, 16, 12, 12, 10, 10, 8, 8, 8, 10, -1 },
    // Fatso
    { 16, 12, 12, 10, 10, 8, 10, 12, 16, -1 },
    // ArchVile
    { 16, 8, 8, 12, 8, 8, 6, 6, 6, -1 },
    // Arachno
    { 16, 16, 16, 12, 10, 8, 10, 10, -1 },
    // Spider Mastermind
    { 16, 10, 10, 12, 8, 8, 8, 10, -1 },
    // Cyberdemon
    { 16, 12, 12, 12, 10, 10, 8, 8, -1 }
};

int Monster_VariationCounts[MAX_MONSTER_CATEGORIES] = { 0 };
int Monster_CategoryWeightSum[MAX_MONSTER_CATEGORIES] = { 0 };

function str GetIntermissionSong() {
    return StrParam(s:"INTER", d:random(1, 4));
}