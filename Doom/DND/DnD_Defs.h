#ifndef DND_DEFS_IN
#define DND_DEFS_IN

#include "DnD_Research.h"
#include "DnD_SpecialAmmo.h"
#include "DnD_Quests.h"
#include "DnD_Weapons.h"
#include "DnD_Stat.h"

#define MAXWEPSLOTS 9

#define MGNUMID 709
#define BONUSBONUSID 708
#define SECRETBONUSID 707
#define ITEMBONUSID 706
#define KILLBONUSID 705
#define PERKID 704
#define CASHSPLITID 703
#define MENUUSEID 702

#define MIN_CREDIT_GAIN 7
#define MIN_EXP_GAIN 10
#define STAT_BASE 0
#define STAT_MAX 100 // for menu only, in game stats can go up to 200
#define PERK_MAX 10
#define BASE_WISDOM_GAIN 10
#define BASE_GREED_GAIN 10
#define ATTRIB_PER_LEVEL 3
#define NANOCAP 350

#define DND_MONSTERHP_PLAYERSCALE 25
#define DND_MAX_PLAYERHPSCALE 16

#define DND_HARDCORE_LOADTIME 10 // timer for hardcore load
#define DND_HARDCORE_SCREENID 6

global int 1: StatListOpened[];

#define MAX_MAP_DIFFICULTIES 5
global int 4: MapDifficulty;
str MapDifficultyLabel[MAX_MAP_DIFFICULTIES] = { 
	"\cdVery Easy\c-", 
	"\cqEasy\c-", 
	"\cfMedium\c-", 
	"\ckHard\c-", 
	"\cgVery Hard\c-" 
};

int settings[4][2] = {
	{ BT_FORWARD,					0.00 	},
	{ BT_MOVELEFT | BT_LEFT,		0.25	},
	{ BT_BACK,						0.50	},
	{ BT_MOVERIGHT | BT_RIGHT,	    0.75	}
};
	 
enum {
	RESET_LEVEL = 1,
	RESET_CREDIT = 2,
	RESET_STATS = 4,
	RESET_PERKS = 8
};
											
int IsButtonPressed (int input, int oldInput, int mask) {
	return (input & ~oldInput) & mask;
}

int IsButtonHeld (int input, int mask) {
	return input & mask;
}

int IsHardcore() {
	return HardcoreSet;
}

#endif