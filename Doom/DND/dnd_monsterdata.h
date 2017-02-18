enum {
	// Classics
	MONSTER_ZOMBIEMAN,
	MONSTER_SHOTGUNNER,
	MONSTER_CHAINGUNNER,
	MONSTER_DEMON,
	MONSTER_SPECTRE,
	MONSTER_IMP,
	MONSTER_CACODEMON,
	MONSTER_PAINELEMENTAL,
	MONSTER_LOSTSOUL,
	MONSTER_REVENANT,
	MONSTER_HELLKNIGHT,
	MONSTER_BARON,
	MONSTER_FATSO,
	MONSTER_VILE,
	MONSTER_SPIDER,
	MONSTER_MASTERMIND,
	MONSTER_CYBERDEMON,
	MONSTER_NAZI,
	
	// DnD Exclusives
	
	// Zombieman
	MONSTER_ZOMBIEMANGRAY,
	MONSTER_ZOMBIERANGER,
	MONSTER_ZOMBIESMG,
	MONSTER_ZOMBIERAPID,
	MONSTER_ZOMBIEMARINE,
	MONSTER_ZOMBIELOS,
	MONSTER_ZOMBIEPISTOL,
	MONSTER_ZOMBIEQUAKE1,
	MONSTER_ZOMBIEHUNTER,
	MONSTER_ZOMBIEPROPHET,
	
	// Shotgunner
	MONSTER_SSGLOS,
	MONSTER_ZSPECSG,
	MONSTER_SGLOS,
	MONSTER_SAWEDOFF1,
	MONSTER_SAWEDOFF2,
	MONSTER_ROGUE,
	MONSTER_ZOMBIEQUAKE2,
	MONSTER_ZOMBIESSG,
	
	// Chaingunner
	MONSTER_ZOMBIEQUAKE3,
	MONSTER_ZOMBIEMG,
	MONSTER_INITIATE,
	MONSTER_DOUBLEGUNNER,
	MONSTER_CGMAJOR,
	MONSTER_MRROBOT,
	MONSTER_ZSEC,
	MONSTER_ZSPECMG,
	
	// Demon
	MONSTER_BLOODDEMON,
	MONSTER_BLOODFIEND,
	MONSTER_CYBERFIEND,
	MONSTER_FLAMEDEMON,
	MONSTER_STONEIMP,
	MONSTER_SCAVENGER,
	MONSTER_SOULEATER,
	MONSTER_NHUMCIGN,
	MONSTER_STONEDEMON,
	MONSTER_BRUTY,
	MONSTER_HOUND,
	
	// Spectre
	MONSTER_LURKER,
	MONSTER_GRAVEDIGGER,
	MONSTER_DEVOURER,
	MONSTER_NIGHTMAREDEMON,
	
	// Imp
	MONSTER_DARKIMP1,
	MONSTER_VOIDDARKIMP,
	MONSTER_NETHERDARKIMP,
	MONSTER_DARKIMP2,
	MONSTER_IMPABOM,
	MONSTER_STIMP,
	MONSTER_VOIDIMP,
	MONSTER_SOULHARVESTER,
	MONSTER_PYROIMP,
	MONSTER_DEVIL,
	MONSTER_VULGAR,
	MONSTER_UNDEADMAGE,
	MONSTER_SHADOW,
	MONSTER_ROACH,
	
	// Lost Soul
	MONSTER_BABYCACO,
	MONSTER_ETHEREALSOUL,
	MONSTER_FLESHSPAWN,
	MONSTER_GUARDIANCUBE,
	MONSTER_FORGOTTENONE,
	MONSTER_HADESSPHERE,
	MONSTER_WATCHER,
	
	// Cacodemon
	MONSTER_WEAKENER,
	MONSTER_SHADOWPRIEST,
	MONSTER_GRELL,
	MONSTER_DEATHWHISPERER,
	MONSTER_CACOLICH,
	MONSTER_INFERNO,
	MONSTER_GUARDIAN,
	MONSTER_ENHANCEDCACO,
	MONSTER_EARTHLICH,
	
	// Pain Elemental
	MONSTER_BLOODLICH,
	MONSTER_HADESELEMENTAL,
	MONSTER_HELLARBITER,
	MONSTER_DEFILER,
	MONSTER_TORTUREDSOUL,
	MONSTER_SHADOWDISCIPLE,
	MONSTER_SENTINEL,
	MONSTER_WRAITH,
	
	// Revenant
	MONSTER_INCARNATE,
	MONSTER_BEAMREVENANT,
	MONSTER_AXEKNIGHT,
	MONSTER_WIDOWMAKER,
	MONSTER_YETI,
	MONSTER_SLUDGEGIANT,
	MONSTER_CADAVER,
	MONSTER_DARKSERVANT,
	MONSTER_CRAWLER,
	
	// Hell Knight
	MONSTER_SATYR,
	MONSTER_HELLWARRIOR,
	MONSTER_HELLSFURY,
	MONSTER_BLACKKNIGHT,
	MONSTER_ARCHON,
	MONSTER_WARLORD,
	MONSTER_SKULLWIZARD,
	MONSTER_CYBORGWARRIOR,
	MONSTER_SHADOWBEAST,
	MONSTER_CHAOSSERPENT,

	// Baron
	MONSTER_LAVADEMON,
	MONSTER_LORDOFHERESY,
	MONSTER_BORMERETH,
	MONSTER_BARBATOS,
	MONSTER_BLOODSEEKER,
	MONSTER_SHADOWWIZARD,
	MONSTER_KJAROCH,
	MONSTER_CYBRUISER,
	MONSTER_BRUISERDEMON,
	MONSTER_MAGMASERPENT,
	
	// Fatso
	MONSTER_CORPULENT,
	MONSTER_DAEDABUS,
	MONSTER_PALADIN,
	MONSTER_GAMON,
	MONSTER_MEPHISTO,
	MONSTER_MAFIBUS,
	MONSTER_ICEFATSO,
	MONSTER_ABOMINATION,
	
	// Arachnotron
	MONSTER_FUSIONSPIDER,
	MONSTER_RAILARACHNOTRON,
	MONSTER_HELLFORGESPIDER,
	MONSTER_VORE,
	MONSTER_BABYDEMOLISHER,
	MONSTER_CHAINGUNGENERAL,
	MONSTER_CHAINGUNCOMMANDO,
	
	// ArchVile
	MONSTER_DIABLOIST,
	MONSTER_UNDEADPRIEST,
	MONSTER_DEATHVILE,
	MONSTER_HIEROPHANT,
	MONSTER_GURU,
	MONSTER_DEATHKNIGHT,
	MONSTER_HORSHACKER,
	MONSTER_DARKZEALOT,
	
	// Spider Mastermind
	MONSTER_DEMOLISHER,
	MONSTER_ARACHNOPHYTE,
	MONSTER_PSIONICQUEEN,
	MONSTER_ANGELOFDEATH,
	MONSTER_GOLDLICH,
	MONSTER_IRONLICH,
	MONSTER_SPIDEROVERLORD,
	
	// Cyberdemon
	MONSTER_CARDINAL,
	MONSTER_TERMINATOR,
	MONSTER_THAMUZ,
	MONSTER_AZAZEL,
	MONSTER_HELLSMITH,
	MONSTER_THANATOS,
	MONSTER_AVATAR
};

#define MONSTER_COUNT MONSTER_AVATAR + 50 // possible compatibility for other wads' monsters

function int IsBoss(int monsterid) {
	if(monsterid == MONSTER_CYBERDEMON || monsterid == MONSTER_MASTERMIND || monsterid >= MONSTER_DEMOLISHER)
		return 1;
	return 0;
}

#define MAX_MONSTER_TRAITS 21
#define MONSTER_TRAITID 1103
#define MONSTER_BARID MONSTER_TRAITID + MAX_MONSTER_TRAITS + 1
// up to 1102 is occupied by barfillid, 1102 included
#define MONSTER_BARFILLID 1001
#define MONSTER_TEXTID 1000
#define MONSTER_NAMEID 999

str MonsterTraits[MAX_MONSTER_TRAITS] = {
	"Explosive Resist",
	"High Explosive Resist",
	"Explosive Immune",
	"Physical Resist",
	"Ghost",
	"Hardened Skin",	// ripper immune
	"Reflective",
	"Summon Minion",
	"Can Curse",		// monsters with curses
	"Can Heal",		// monsters with healing
	"Can Block",		// shielded monster
	"Can Split",
	"Can Raise",
	"Can Teleport",
	"Resurrect Fallen",	// arch vile
	"Mobility",	// dashes, fast speed etc
	"Homing",
	"Poisonous",
	"Death Surprise",	// monsters with dangerous deaths
	"Rage", // monsters that get angry after a certain condition
	"Pierces Armor" // monsters that ignore player armor
};

str MonsterInfo[MONSTER_COUNT] = {
	// Classics
	"Zombieman",
	"Shotgunner",
	"Chaingunner",
	"Demon",
	"Spectre",
	"Imp",
	"Cacodemon",
	"Pain Elemental",
	"Lost Soul",
	"Revenant",
	"Hell Knight",
	"Baron of Hell",
	"Mancubus",
	"Arch Vile",
	"Arachnotron",
	"Spider Mastermind",
	"Cyberdemon",
	"SS Nazi",
	
	// DnD Exclusive
	
	// Zombieman
	"Zombieman",
	"Zombie Ranger",
	"SMG Zombie",
	"Rapid Fire Zombie",
	"Zombie Marine",
	"Armored Zombie",
	"Pistol Zombie",
	"Enforcer",
	"Undead Hunter",
	"Prophet",
	
	// Shotgunner
	"Armored SSG Zombie",
	"ZSpec Shotgunner",
	"Armored Shotgunner",
	"Sawedoff Zombie",
	"Sawedoff Zombie",
	"Undead Rogue",
	"Enforcer Captain",
	"SSG Zombie",
	
	// Chaingunner
	"Enforcer Elite",
	"MG Zombie",
	"Undead Initiate",
	"Double Chaingunner",
	"Chaingun Major",
	"Robot Guard",
	"ZSec",
	"ZSpec MG",
	
	// Demon
	"Blood Demon",
	"Blood Fiend",
	"Cyber Fiend",
	"Gray Demon",
	"Stone Imp",
	"Scavenger",
	"Soul Eater",
	"Nhumcign",
	"Stone Demon",
	"Big Bruty",
	"Demon Hound",
	
	// Spectre
	"Lurker",
	"Gravedigger",
	"Devourer",
	"Nightmare Demon",
	
	// Imp
	"Dark Imp",
	"Void Dark Imp",
	"Nether Dark Imp",
	"Dark Imp",
	"Imp Abomination",
	"Imp",
	"Void Imp",
	"Soul Harvester",
	"Pyro Imp",
	"Devil",
	"Vulgar",
	"Undead Mage",
	"Shadow",
	"Roach",
	
	// Lost Soul
	"Baby Cacodemon",
	"Ethereal Soul",
	"Fleash Spawn",
	"Guardian Cube",
	"Forgotten One",
	"Hades Sphere",
	"Watcher",
	
	// Cacodemon
	"Weakener",
	"Shadow Priest",
	"Grell",
	"Death Whisperer",
	"Cacolich",
	"Inferno",
	"Guardian",
	"Enhanced Cacodemon",
	"Earth Lich",
	
	// Pain Elemental
	"Blood Lich",
	"Hades Elemental",
	"Hell Arbiter",
	"Defiler",
	"Tortured Soul",
	"Shadow Disciple",
	"Sentinel",
	"Wraith",
	
	// Revenant
	"Incarnate",
	"Beam Revenant",
	"Undead Knight",
	"Widowmaker",
	"Yeti",
	"Sludge Giant",
	"Cadaver",
	"Dark Servant",
	"Crawler",
	
	// Hell Knight
	
	"Satyr",
	"Hell Warrior",
	"Hell's Fury",
	"Black Knight",
	"Archon of Hell",
	"Warlord of Hell",
	"Skull Wizard",
	"Cyborg Warrior",
	"Shadow Beast",
	"Chaos Serpent",

	// Baron
	"Lava Giant",
	"Lord of Heresy",
	"Bormereth",
	"Barbatos",
	"Bloodseeker",
	"Shadow Wizard",
	"Kjaroch",
	"Cybruiser",
	"Bruiser Demon",
	"Magma Serpent",
	
	// Fatso
	"Corpulent",
	"Daedabus",
	"Paladin",
	"Gamon",
	"Mephisto",
	"Mafibus",
	"Ice Mancubus",
	"Abomination",
	
	// Arachnotron
	"Fusion Spider",
	"Rail Arachnotron",
	"Hellforge Spider",
	"Vore",
	"Baby Demolisher",
	"Chaingun General",
	"Chaingun Commando",
	
	// ArchVile
	"Diabloist",
	"Undead Priest",
	"Death Vile",
	"Hierophant",
	"Guru",
	"Death Knight",
	"Horshacker",
	"Dark Zealot",
	
	// Spider Mastermind
	"Spider Demolisher",
	"Arachnophyte",
	"Pisonic Queen",
	"Angel of Death",
	"Gold Lich",
	"Iron Lich",
	"Spider Overlord",
	
	// Cyberdemon
	"Dark Cardinal",
	"Terminator",
	"Thamuz",
	"Azazel",
	"Hell Smith",
	"Thanatos",
	"Avatar of Chaos"
};