#ifndef DND_ORBS_IN
#define DND_ORBS_IN

#include "DnD_Common.h"
#include "DnD_Stat.h"
#include "DnD_Ammo.h"
#include "DnD_TempWeps.h"
#include "DnD_Weapons.h"
#include "DnD_OrbsDef.h"
#include "DnD_Sync.h"

#define MAX_ITER 200

#define ENHANCEORB_MAX 25 // 25% bonus
#define PROSPERITY_MAX 500 // 500 max
#define FORTITUDE_MAX 200 // 200% max
#define WISDOMORB_MAX 250
#define GREEDORB_MAX 250
#define VIOLENCEORB_MAX 300 // 300% for each category
#define SINORB_MAX_TAKE 8
#define AFFLUENCE_MAX 4 // x16
#define AFFLUENCE_MULT 2

// this is server side only, clients aren't even aware of the values here so we can put as many stuff as needed...
// because zan doesn't sync variables to clients unless told to do (sdee dnd_sync.h for it)
typedef struct {
	int orb_type;
	int val1, val2, val3, val4, val5;
	// corrupt orb ammo save
	int p_ammos[MAXWEPS];
	int p_tempammo;
	int p_tempwep;
	bool sins_cant_repent;
} orb_info_T;

// holds most recently used orb values
global orb_info_T 3: Player_MostRecent_Orb[MAXPLAYERS];

#define MAX_ORBS_BITS getpow2(MAX_ORBS)
#define MAX_ORBS_BITONES (1 << (MAX_ORBS_BITS)) - 1

#define ORB_NAME 0
#define ORB_TAG 1
str OrbList[MAX_ORBS][2] = {
	{ "OrbOfEnhancement", "Orb of Enhancement" },
	{ "OrbOfCorruption", "Orb of Corruption" },
	{ "OrbOfSpirit", "Orb of Spirit" },
	{ "OrbofRepentance", "Orb of Repentance" },
	{ "OrbofAffluence", "Orb of Affluence" },
	{ "OrbofCalamity", "Orb of Calamity" },
	{ "OrbofProsperity", "Orb of Prosperity" },
	{ "OrbofWisdom", "Orb of Wisdom" },
	{ "OrbofGreed", "Orb of Greed" },
	{ "OrbofViolence", "Orb of Violence" },
	{ "OrbofFortitude", "Orb of Fortitude" },
	{ "OrbofSin", "Orb of Sin" },
	{ "OrbofRiches", "Orb of Riches" },
	{ "OrbofHolding", "Orb of Holding" }
};

// percentages
/*
17.5
5
10
2.5
1.5
8
18
10
10
5
5
2.5
2.5
2.5
*/

int OrbDropWeights[MAX_ORBS] = {
	175,
	225,
	325,
	350,
	365,
	445,
	625,
	725,
	825,
	875,
	925,
	950,
	975,
	1000
};

#define ENHANCEORB_BONUS 0.01
#define ENHANCEORB_BONUS_INT 1

#define ORB_MAXWEIGHT 1000

#define STATORB_MAXWEIGHT 40
#define STATORB_MAXSTATS 6
int SpiritOrb_StatDropWeights[STATORB_MAXSTATS] = { 10, 20, 24, 25, 31, 40 };

enum {
	CORRUPTORB_NOTHING,
	
	CORRUPTORB_TAKEHP,
	CORRUPTORB_TAKEDMG,
	CORRUPTORB_TAKESPEED,
	CORRUPTORB_TAKEAMMO,
	CORRUPTORB_TAKEBACKPACK,
	CORRUPTORB_REDUCEDMGMAP,
	
	CORRUPTORB_ADDDMG,
	CORRUPTORB_ADDCRIT,
	CORRUPTORB_ADDCRITDMG,
	CORRUPTORB_ADDSPEED,
	CORRUPTORB_DROPCHANCE,
	CORRUPTORB_GIVESTAT
};

#define CORRUPTORB_MAXEFFECTS CORRUPTORB_GIVESTAT + 1
#define CORRUPTORB_MAXWEIGHT 300
int CorruptOrb_Weights[CORRUPTORB_MAXEFFECTS] = {
	150,
	
	165,
	180,
	195,
	210,
	225,
	240,
	
	250,
	260,
	270,
	280,
	290,
	300
};

#define CORRUPTORB_MINDMG -2.0
#define CORRUPTORB_MINSPEED -0.5
#define CORRUPTORB_MAXCRITPERCENT 1.0
#define CORRUPTORB_MAXDMG 4.0
#define CORRUPTORB_MAXCRITDMG 2.0
#define CORRUPTORB_MAXSPEED 0.5
#define CORRUPTORB_MAXDROPCHANCE 0.5
#define CORRUPTORB_MINHEALTH 100

#define CORRUPTORB_DMGTAKE 0.1
#define CORRUPTORB_HPTAKE 10
#define CORRUPTORB_SPEEDTAKE 0.025
#define CORRUPTORB_DMGGIVE 0.2
#define CORRUPTORB_CRITGIVE 0.05
#define CORRUPTORB_CRITDMGGIVE 0.25
#define CORRUPTORB_SPEEDGIVE 0.05
#define CORRUPTORB_DROPCHANCEGIVE 0.025
#define CORRUPTORB_STATGIVE 5

// sin orb stuff
enum {
	SINORB_STAT,
	SINORB_CRIT,
	SINORB_CRITDMG,
	SINORB_PERK
};
#define SINORB_OPT_BEGIN SINORB_STAT
#define SINORB_OPT_END SINORB_PERK
#define SINORB_CRITMAX 0.2
#define SINORB_CRITDMGMAX 1.0
#define SINORB_CRED_MIN 50
#define SINORB_CRED_MAX 500
#define SINORB_CRITGIVE 0.01
#define SINORB_CRITDMGGIVE 0.05
#define SINORB_STATSAVEBITS 8
#define SINORB_STATSAVEMASK 0xFF

#define SINORB_MAXRUNS 12

#define SINORB_STATGIVE 4
#define SINORB_PERKGIVE 1

#define HOLDING_MAX 1.0
#define HOLDINGORB_BONUS 0.01

enum {
	RICHES_EXP,
	RICHES_CREDIT,
	RICHES_BUDGET
};
#define MAX_RICHES RICHES_BUDGET + 1

int RichesAmount[MAX_RICHES] = {
	5,
	2000,
	5
};

#define MAX_RICHES_WEIGHT 10
int RichesWeights[MAX_RICHES] = {
	2,
	9,
	10
};

bool CanUseOrb(int orbtype) {
	bool res = 0;
	int temp = -1, i;
	SetInventory("OrbUseType", orbtype + 1);
	switch(orbtype) {
		case DND_ORB_ENHANCE:
			if(Player_Weapon_Infos[PlayerNumber()][GetWeaponPosFromTable()].enchants != ENHANCEORB_MAX)
				res = 1;
		break;
		case DND_ORB_CORRUPT:
			res = 1; // can always use this, the orb will find a way to fuck you up in some way
		break;
		case DND_ORB_SPIRIT:
			for(i = 0; i <= DND_ATTRIB_END && temp == -1; ++i)
				if(GetStat(i) != DND_STAT_FULLMAX)
					temp = i;
			res = temp != -1;
		break;
		case DND_ORB_REPENT:
			res = Player_MostRecent_Orb[PlayerNumber()].orb_type && Player_MostRecent_Orb[PlayerNumber()].orb_type - 1 != DND_ORB_REPENT && Player_MostRecent_Orb[PlayerNumber()].orb_type - 1 != DND_ORB_RICHES;
		break;
		case DND_ORB_AFFLUENCE:
			res = CheckInventory("AffluenceCounter") < AFFLUENCE_MAX;
		break;
		case DND_ORB_CALAMITY:
			res = HasOrbsBesidesCalamity();
		break;
		case DND_ORB_PROSPERITY:
			res = Player_Bonuses[PlayerNumber()].prosperity_orb_bonus != PROSPERITY_MAX;
		break;
		case DND_ORB_FORTITUDE:
			res = Player_Bonuses[PlayerNumber()].fortitude_orb_bonus != FORTITUDE_MAX;
		break;
		case DND_ORB_WISDOM:
			res = Player_Bonuses[PlayerNumber()].wisdom_percent_bonus != GREEDORB_MAX;
		break;
		case DND_ORB_GREED:
			res = Player_Bonuses[PlayerNumber()].greed_percent_bonus != GREEDORB_MAX;
		break;
		case DND_ORB_VIOLENCE:
			for(i = TALENT_BULLET; i < MAX_TALENTS && !res; ++i)
				if(Player_Bonuses[PlayerNumber()].damage_type_bonus[i] != VIOLENCEORB_MAX)
					res = 1;
		break;
		case DND_ORB_SIN:
			res = Calculate_Stats() >= SINORB_MAX_TAKE * GetAffluenceBonus();
		break;
		case DND_ORB_RICHES:
			res = 1; // always give resource
		break;
		case DND_ORB_HOLDING:
			res = Player_Bonuses[PlayerNumber()].holding != HOLDING_MAX;
		break;
	}
	if(!res)
		SetInventory("OrbResult", 0x7FFFFFFF);
	return res;
}

void HandleOrbUse (int orbtype) {
	int res = -1;
	int pnum = PlayerNumber();
	int temp;
	int i;
	SetInventory("OrbUseType", orbtype + 1);
	// for any other orb, reset most recently used orb
	if(orbtype != DND_ORB_REPENT)
		ResetMostRecentOrb(pnum);
	switch(orbtype) {
		case DND_ORB_ENHANCE:
			res = GetWeaponPosFromTable();
			Player_Weapon_Infos[pnum][res].enchants = Clamp_Between(Player_Weapon_Infos[pnum][res].enchants + GetAffluenceBonus() * ENHANCEORB_BONUS_INT, 0, ENHANCEORB_MAX);
			SetInventory("OrbResult", res);
			Player_MostRecent_Orb[pnum].val1 = res;
			Player_MostRecent_Orb[pnum].val2 = GetAffluenceBonus() * ENHANCEORB_BONUS_INT;
			SyncClientsideVariable(DND_SYNC_WEAPONENHANCE, res);
		break;
		case DND_ORB_CORRUPT:
			// roll what to do
			do {
				temp = random(0, CORRUPTORB_MAXWEIGHT);
				for(i = 0; i < CORRUPTORB_MAXEFFECTS && temp > CorruptOrb_Weights[i]; ++i);
			} while(!CorruptionMaxChecks(i) && res++ < MAX_ITER);
			// i has the effect to do now
			SetInventory("OrbResult", i);
			Player_MostRecent_Orb[pnum].val1 = i;
			Player_MostRecent_Orb[pnum].val1 |= GetAffluenceBonus() << 8;
			HandleCorruptOrbUse(i);
		break;
		case DND_ORB_SPIRIT:
			// find a random stat to give points to, checking they aren't max already
			do {
				temp = random(0, STATORB_MAXWEIGHT);
				for(i = 0; i < STATORB_MAXSTATS; ++i)
					if(temp <= SpiritOrb_StatDropWeights[i])
						break;
			} while(GetStat(i) == DND_STAT_FULLMAX);
			GiveStat(i, GetAffluenceBonus());
			res = i;
			SetInventory("OrbResult", res);
			Player_MostRecent_Orb[pnum].val1 = res;
			Player_MostRecent_Orb[pnum].val2 = GetAffluenceBonus();
		break;
		case DND_ORB_REPENT:
			RevertLastOrbEffect();
		break;
		case DND_ORB_AFFLUENCE:
			GiveInventory("AffluenceCounter", 1);
			res = CheckInventory("AffluenceCounter");
			SetInventory("OrbResult", res);
			Player_MostRecent_Orb[pnum].val1 = res;
		break;
		case DND_ORB_CALAMITY:
			do {
				temp = PickRandomOrb();
			} while(temp == DND_ORB_CALAMITY || !CheckInventory(OrbList[temp][ORB_NAME]));
			// take the orb, then roll another new orb
			TakeInventory(OrbList[temp][ORB_NAME], GetAffluenceBonus());
			res = temp;
			do {
				temp = PickRandomOrb();
			} while(temp == DND_ORB_CALAMITY);
			GiveInventory(OrbList[temp][ORB_NAME], GetAffluenceBonus());
			res += temp * 100;
			SetInventory("OrbResult", res);
			Player_MostRecent_Orb[pnum].val1 = res;
			Player_MostRecent_Orb[pnum].val2 = GetAffluenceBonus();
		break;
		case DND_ORB_PROSPERITY:
			res = Player_Bonuses[pnum].prosperity_orb_bonus;
			Player_Bonuses[pnum].prosperity_orb_bonus = Clamp_Between(Player_Bonuses[pnum].prosperity_orb_bonus + GetAffluenceBonus(), 0, PROSPERITY_MAX);
			SetInventory("OrbResult", res);
			Player_MostRecent_Orb[pnum].val1 = res;
			SyncClientsideVariable(DND_SYNC_PROSPERITY_BONUS, 0);
		break;
		case DND_ORB_FORTITUDE:
			res = Player_Bonuses[pnum].fortitude_orb_bonus;
			Player_Bonuses[pnum].fortitude_orb_bonus = Clamp_Between(Player_Bonuses[pnum].fortitude_orb_bonus + GetAffluenceBonus(), 0, FORTITUDE_MAX);
			SetInventory("OrbResult", res);
			Player_MostRecent_Orb[pnum].val1 = res;
			SyncClientsideVariable(DND_SYNC_FORTITUDE_BONUS, 0);
		break;
		case DND_ORB_WISDOM:
			res = Player_Bonuses[pnum].wisdom_percent_bonus;
			Player_Bonuses[pnum].wisdom_percent_bonus = Clamp_Between(Player_Bonuses[pnum].wisdom_percent_bonus + GetAffluenceBonus(), 0, WISDOMORB_MAX);
			SetInventory("OrbResult", res);
			Player_MostRecent_Orb[pnum].val1 = res;
			SyncClientsideVariable(DND_SYNC_WISDOMPERCENT_BONUS, 0);
		break;
		case DND_ORB_GREED:
			res = Player_Bonuses[pnum].greed_percent_bonus; // hold prev
			Player_Bonuses[pnum].greed_percent_bonus = Clamp_Between(Player_Bonuses[pnum].greed_percent_bonus + GetAffluenceBonus(), 0, GREEDORB_MAX);
			SetInventory("OrbResult", res);
			Player_MostRecent_Orb[pnum].val1 = res;
			SyncClientsideVariable(DND_SYNC_GREEDPERCENT_BONUS, 0);
		break;
		case DND_ORB_VIOLENCE:
			do {
				temp = PickRandomTalent();
			} while(Player_Bonuses[pnum].damage_type_bonus[temp] == VIOLENCEORB_MAX);
			Player_MostRecent_Orb[pnum].val1 = temp;
			Player_MostRecent_Orb[pnum].val1 += 100 * Player_Bonuses[pnum].damage_type_bonus[temp];
			Player_Bonuses[pnum].damage_type_bonus[temp] = Clamp_Between(Player_Bonuses[pnum].damage_type_bonus[temp] + GetAffluenceBonus(), 0, VIOLENCEORB_MAX);
			SetInventory("OrbResult", temp);
			// start from ballistic talent end with occult
			SyncClientsideVariable(DND_SYNC_DAMAGEBULLET + temp, 0);
		break;
		case DND_ORB_SIN:
			// take away random stats
			int s = GetAffluenceBonus();
			temp = random(1, SINORB_MAX_TAKE);
			res = 0;
			// save each stat's previous values in 7 bits (it can take max 64), 6 stats = 42 bits needed => 2 ints. 3rd int can hold type of sin orb effect + affluence count
			RecentOrb_SaveOldStats(pnum);
			for(i = 0; i < temp; ++i)
				TakeStat(GetRandomSinStat(), s);
			RecentOrb_FindDifference(pnum);
			// use inv style encoding for which states are gone
			//res |= s;
			// got from 0 to 5 in res
			res |= temp;
			//do {
				temp = random(SINORB_OPT_BEGIN, SINORB_OPT_END);
			//} while(temp == SINORB_RES && !HasIncompleteResearches()); // repeat if we got research and we have all researches done
			Player_MostRecent_Orb[pnum].val3 = s;
			Player_MostRecent_Orb[pnum].val3 |= temp << 5;
			res |= temp << 8;
			res |= HandleSinOrbBonus(temp) << 11;
			// save the bonus type
			SetInventory("OrbResult", res);
		break;
		case DND_ORB_RICHES:
			temp = random(1, MAX_RICHES_WEIGHT);
			for(i = 0; i < MAX_RICHES && temp > RichesWeights[i]; ++i);
			res = GetAffluenceBonus() * RichesAmount[i];
			Player_MostRecent_Orb[pnum].val1 = i;
			Player_MostRecent_Orb[pnum].val2 = res;
			if(!i)
				GiveExp((LevelCurve[CheckInventory("Level") - 1] / 100) * res); // don't want overflows! -- technically it still can, but hopefully wont
			else if(i == 1)
				GiveCredit(res);
			else if(i == 2)
				GiveBudget(res);
			res |= i << 16;
			SetInventory("OrbResult", res);
		break;
		case DND_ORB_HOLDING:
			res = GetAffluenceBonus() * HOLDINGORB_BONUS;
			temp = Player_Bonuses[pnum].holding;
			Player_Bonuses[pnum].holding = Clamp_Between(Player_Bonuses[pnum].holding + res, 0, HOLDING_MAX);
			Player_MostRecent_Orb[pnum].val1 = Player_Bonuses[pnum].holding - temp;
			SetAllAmmoCapacities();
			SetInventory("OrbResult", res);
			SyncClientsideVariable(DND_SYNC_HOLDING, 0);
		break;
	}
	Player_MostRecent_Orb[pnum].orb_type = orbtype + 1; // +1 because 0 is used as no orb
}

// check if player has any orbs besides calamity
bool HasOrbsBesidesCalamity() {
	for(int i = DND_ORB_ENHANCE; i < MAX_ORBS; ++i) {
		if(i == DND_ORB_CALAMITY)
			continue;
		if(CheckInventory(OrbList[i][ORB_NAME]))
			return true;
	}
	return false;
}

int HandleSinOrbBonus(int type) {
	int temp, loop = 0, i;
	int pnum = PlayerNumber();
	switch(type) {
		case SINORB_STAT:
			// give random stat points
			for(i = 0; i < GetAffluenceBonus() * SINORB_STATGIVE; ++i) {
				do {
					temp = random(STAT_STR, STAT_INT);
				} while(GetStat(i) == DND_STAT_FULLMAX && loop++ != MAX_ITER);
				Player_MostRecent_Orb[pnum].sins_cant_repent = GetStat(i) == DND_STAT_FULLMAX;
				GiveStat(temp, 1);
				// 6 stats, can give max of 64 on 1 stat. 8 x 6 = 48 bits needed. 2 ints
				if(temp < 4)
					Player_MostRecent_Orb[pnum].val4 += 1 << (SINORB_STATSAVEBITS * temp);
				else
					Player_MostRecent_Orb[pnum].val5 += 1 << (SINORB_STATSAVEBITS * (temp - 4));
			}
		return SINORB_STATGIVE;
		case SINORB_PERK:
			// give a random perk
			for(i = 0; i < GetAffluenceBonus() * SINORB_PERKGIVE; ++i) {
				do {
					temp = random(STAT_SHRP, STAT_SAV);
				} while(GetStat(i + DND_PERK_BEGIN) == DND_PERK_MAX && loop++ != MAX_ITER);
				Player_MostRecent_Orb[pnum].sins_cant_repent = GetStat(i + DND_PERK_BEGIN) == DND_PERK_MAX;
				GiveStat(temp, 1);
				// int_max is 10 digits, max give is 16
				if((Player_MostRecent_Orb[pnum].val4 / (pow(10, temp - STAT_SHRP))) % 10 != 9)
					Player_MostRecent_Orb[pnum].val4 += pow(10, temp - STAT_SHRP);
				else
					Player_MostRecent_Orb[pnum].val5 += pow(10, temp - STAT_SHRP);
			}
		return SINORB_PERKGIVE;
		/*case SINORB_RES:
			int s = 0;
			temp =  GetAffluenceBonus();
			for(i = 0; i < temp;) {
				s = random(0, MAX_RESEARCHES - 1);
				if(CheckResearchStatus(s) == RES_NA) {
					GiveResearch(s);
					++i;
				}
				else if(CheckResearchStatus(s) == RES_KNOWN) {
					CompleteResearch(s);
					++i;
				}
			}
		return s;*/
		case SINORB_CRIT:
			do {
				temp = PickRandomOwnedWeapon();
			} while(Player_Weapon_Infos[pnum][temp].wep_bonuses[WEP_BONUS_CRIT].amt >= SINORB_CRITMAX && loop++ != MAX_ITER);
			Player_MostRecent_Orb[pnum].val5 = temp;
			Player_MostRecent_Orb[pnum].val4 = Player_Weapon_Infos[pnum][temp].wep_bonuses[WEP_BONUS_CRIT].amt;
			Player_Weapon_Infos[pnum][temp].wep_bonuses[WEP_BONUS_CRIT].amt = Clamp_Between(Player_Weapon_Infos[pnum][temp].wep_bonuses[WEP_BONUS_CRIT].amt + SINORB_CRITGIVE * pow(2, CheckInventory("AffluenceCounter")), 0, SINORB_CRITMAX);
			// get the difference, should be negative
			Player_MostRecent_Orb[pnum].val4 -= Player_Weapon_Infos[pnum][temp].wep_bonuses[WEP_BONUS_CRIT].amt;
			SyncClientsideVariable(DND_SYNC_WEPBONUS_CRIT, temp);
		return temp;
		case SINORB_CRITDMG:
			do {
				temp = PickRandomOwnedWeapon();
			} while(Player_Weapon_Infos[pnum][temp].wep_bonuses[WEP_BONUS_CRITDMG].amt >= SINORB_CRITDMGMAX && loop++ != MAX_ITER);
			Player_MostRecent_Orb[pnum].val5 = temp;
			Player_MostRecent_Orb[pnum].val4 = Player_Weapon_Infos[pnum][temp].wep_bonuses[WEP_BONUS_CRITDMG].amt;
			Player_Weapon_Infos[pnum][temp].wep_bonuses[WEP_BONUS_CRITDMG].amt = Clamp_Between(Player_Weapon_Infos[pnum][temp].wep_bonuses[WEP_BONUS_CRITDMG].amt + SINORB_CRITDMGGIVE * pow(2, CheckInventory("AffluenceCounter")), 0, SINORB_CRITDMGMAX);
			Player_MostRecent_Orb[pnum].val4 -= Player_Weapon_Infos[pnum][temp].wep_bonuses[WEP_BONUS_CRITDMG].amt;
			SyncClientsideVariable(DND_SYNC_WEPBONUS_CRITDMG, temp);
		return temp;
		/*case SINORB_CREDIT:
			temp = 10 * random(SINORB_CRED_MIN, SINORB_CRED_MAX) * GetAffluenceBonus();
			GiveCredit(temp);
		return temp;*/
	}
	return -1;
}

void RevertLastOrbEffect() {
	int pnum = PlayerNumber();
	switch(Player_MostRecent_Orb[pnum].orb_type - 1) {
		case DND_ORB_ENHANCE:
			// val 1 is wepid, val2 is overall gain
			Player_Weapon_Infos[pnum][Player_MostRecent_Orb[pnum].val1].enchants -= Player_MostRecent_Orb[pnum].val2;
			SyncClientsideVariable(DND_SYNC_WEAPONENHANCE, Player_MostRecent_Orb[pnum].val1);
		break;
		case DND_ORB_SPIRIT:
			TakeStat(Player_MostRecent_Orb[pnum].val1, Player_MostRecent_Orb[pnum].val2);
		break;
		case DND_ORB_AFFLUENCE:
			TakeInventory("AffluenceCounter", 1);
		break;
		case DND_ORB_CORRUPT:
			UndoCorruptOrbEffect();
		break;
		case DND_ORB_CALAMITY:
			GiveInventory(OrbList[Player_MostRecent_Orb[pnum].val1 % 100][ORB_NAME], Player_MostRecent_Orb[pnum].val2);
			TakeInventory(OrbList[Player_MostRecent_Orb[pnum].val1 / 100][ORB_NAME], Player_MostRecent_Orb[pnum].val2);
		break;
		case DND_ORB_PROSPERITY:
			Player_Bonuses[pnum].prosperity_orb_bonus = Player_MostRecent_Orb[pnum].val1;
			SyncClientsideVariable(DND_SYNC_PROSPERITY_BONUS, 0);
		break;
		case DND_ORB_FORTITUDE:
			Player_Bonuses[pnum].fortitude_orb_bonus = Player_MostRecent_Orb[pnum].val1;
			SyncClientsideVariable(DND_SYNC_FORTITUDE_BONUS, 0);
		break;
		case DND_ORB_WISDOM:
			Player_Bonuses[pnum].wisdom_percent_bonus = Player_MostRecent_Orb[pnum].val1;
			SyncClientsideVariable(DND_SYNC_WISDOMPERCENT_BONUS, 0);
		break;
		case DND_ORB_GREED:
			Player_Bonuses[pnum].greed_percent_bonus = Player_MostRecent_Orb[pnum].val1;
			SyncClientsideVariable(DND_SYNC_GREEDPERCENT_BONUS, 0);
		break;
		case DND_ORB_VIOLENCE:
			Player_Bonuses[pnum].damage_type_bonus[Player_MostRecent_Orb[pnum].val1 % 100] = Player_MostRecent_Orb[pnum].val1 / 100;
			SyncClientsideVariable(DND_SYNC_DAMAGEBULLET + (Player_MostRecent_Orb[pnum].val1 % 100), 0);
		break;
		case DND_ORB_SIN:
			// give back stats
			for(int i = STAT_STR; i <= STAT_INT; ++i) {
				if(i < 4) {
					GiveStat(i, Player_MostRecent_Orb[pnum].val1 & SINORB_STATSAVEMASK);
					Player_MostRecent_Orb[pnum].val1 >>= SINORB_STATSAVEBITS;
				}
				else {
					GiveStat(i, Player_MostRecent_Orb[pnum].val2 & SINORB_STATSAVEMASK);
					Player_MostRecent_Orb[pnum].val2 >>= SINORB_STATSAVEBITS;
				}
			}
			// take away the property given by sin orb
			UndoSinOrbEffect();
		break;
		case DND_ORB_HOLDING:
			Player_Bonuses[pnum].holding -= Player_MostRecent_Orb[pnum].val1;
			SetAllAmmoCapacities();
			SyncClientsideVariable(DND_SYNC_HOLDING, 0);
		break;
	}
	SetInventory("OrbResult", Player_MostRecent_Orb[pnum].orb_type - 1);
}

void UndoSinOrbEffect() {
	// val3 holds affluence on first 5 bits
	int pnum = PlayerNumber(), i;
	switch ((Player_MostRecent_Orb[pnum].val3 & 0b111100000) >> 5) {
		case SINORB_STAT:
			if(!Player_MostRecent_Orb[pnum].sins_cant_repent) {
				// val4 and val5 hold stat values that we currently have gained, so we take them away
				for(i = STAT_STR; i <= STAT_INT; ++i) {
					if(i < 4) {
						TakeStat(i, Player_MostRecent_Orb[pnum].val4 & SINORB_STATSAVEMASK);
						Player_MostRecent_Orb[pnum].val4 >>= SINORB_STATSAVEBITS;
					}
					else {
						TakeStat(i, Player_MostRecent_Orb[pnum].val5 & SINORB_STATSAVEMASK);
						Player_MostRecent_Orb[pnum].val5 >>= SINORB_STATSAVEBITS;
					}
				}
			}
		break;
		case SINORB_PERK:
			if(!Player_MostRecent_Orb[pnum].sins_cant_repent) {
				for(i = DND_PERK_BEGIN; i <= DND_PERK_END; ++i) {
					TakeStat(i, Player_MostRecent_Orb[pnum].val4 % 10);
					TakeStat(i, Player_MostRecent_Orb[pnum].val5 % 10);
					Player_MostRecent_Orb[pnum].val4 /= 10;
					Player_MostRecent_Orb[pnum].val5 /= 10;
				}
				// after operation perk checks
				UpdatePerkStuff();
			}
		break;
		case SINORB_CRIT:
			//printbold(d: Player_MostRecent_Orb[pnum].val5, s: " ", f:Player_Weapon_Infos[pnum][Player_MostRecent_Orb[pnum].val5].wep_bonuses[WEP_BONUS_CRIT].amt, s: " ", f:Player_MostRecent_Orb[pnum].val4);
			Player_Weapon_Infos[pnum][Player_MostRecent_Orb[pnum].val5].wep_bonuses[WEP_BONUS_CRIT].amt += Player_MostRecent_Orb[pnum].val4;
			SyncClientsideVariable(DND_SYNC_WEPBONUS_CRIT, Player_MostRecent_Orb[pnum].val5);
		break;
		case SINORB_CRITDMG:
			Player_Weapon_Infos[pnum][Player_MostRecent_Orb[pnum].val5].wep_bonuses[WEP_BONUS_CRITDMG].amt += Player_MostRecent_Orb[pnum].val4;
			SyncClientsideVariable(DND_SYNC_WEPBONUS_CRITDMG, Player_MostRecent_Orb[pnum].val5);
		break;
	}
}

// picks a random orb
int PickRandomOrb() {
	return random(DND_ORB_ENHANCE, MAX_ORBS - 1);
}

int PickRandomTalent() {
	return random(TALENT_BULLET, MAX_TALENTS - 1);
}

int PickRandomStat() {
	return random(STAT_STR, STAT_INT);
}

int GetAffluenceBonus() {
	return 1 << CheckInventory("AffluenceCounter");
}

int GetRandomSinStat() {
	int s = STAT_STR;
	int runs = 0;
	do {
		s = PickRandomStat();
		// unlucky rng counter measures
		if(++runs > SINORB_MAXRUNS) {
			for(runs = STAT_STR; runs <= STAT_INT; ++runs) {
				if(GetStat(runs))
					return runs;
			}
			break;
		}
	} while(!GetStat(s));
	return s;
}

// pick a random weapon that the player currently owns
int PickRandomOwnedWeapon() {
	int res = 0;
	do {
		res = random(0, MAXWEPS - 1);
	} while(!CheckInventory(Weapons[res][WEAPON_NAME]));
	return res;
}

void RecentOrb_SaveOldStats(int pnum) {
	// 0 to 5, need 8 bits
	for(int i = STAT_STR; i <= STAT_INT; ++i) {
		if(i < 4)
			Player_MostRecent_Orb[pnum].val1 |= GetStat(i) << (i * SINORB_STATSAVEBITS);
		else
			Player_MostRecent_Orb[pnum].val2 |= GetStat(i) << ((i - 4) * SINORB_STATSAVEBITS);
	}
}

void RecentOrb_FindDifference(int pnum) {
	// 0 to 5
	int tmp1 = Player_MostRecent_Orb[pnum].val1, tmp2 = Player_MostRecent_Orb[pnum].val2;
	Player_MostRecent_Orb[pnum].val1 = Player_MostRecent_Orb[pnum].val2 = 0;
	for(int i = STAT_STR; i <= STAT_INT; ++i) {
		if(i < 4) {
			Player_MostRecent_Orb[pnum].val1 |= ((tmp1 & SINORB_STATSAVEMASK) - GetStat(i)) << (i * SINORB_STATSAVEBITS);
			tmp1 >>= SINORB_STATSAVEBITS;
		}
		else {
			Player_MostRecent_Orb[pnum].val2 |= ((tmp2 & SINORB_STATSAVEMASK) - GetStat(i)) << ((i - 4) * SINORB_STATSAVEBITS);
			tmp2 >>= SINORB_STATSAVEBITS;
		}
	}
}

void DoSinOrbMessage(int val) {
	int pts = (val & 0x7F) * pow(2, CheckInventory("AffluenceCounter"));
	str temp = "";
	if(pts > 1)
		temp = StrParam(s:"\cjOrb of Sin takes \cg", d:pts, s:"\cj random stat points ");
	else
		temp = StrParam(s:"\cjOrb of Sin takes \cg", d:pts, s:"\cj random stat point ");
	//Log(s:"type ", d: (val >> 8) & 0x7);
	switch((val >> 8) & 0x7) {
		case SINORB_STAT:
			Log(s:temp, s:"and grants \cd", d:(val >> 11) * GetAffluenceBonus(), s:" stat points!");
		break;
		case SINORB_PERK:
			pts = (val >> 11) * pow(2, CheckInventory("AffluenceCounter"));
			if(pts > 1)
				Log(s:temp, s:"and grants \cd", d:pts, s:" random perks!");
			else
				Log(s:temp, s:"and grants \cd", d:pts, s:" random perk!");
		break;
		case SINORB_CRIT:
			Log(s:temp, s:"and grants \cd", f:ftrunc(SINORB_CRITGIVE * GetAffluenceBonus() * 100), s:"% crit chance to \cd", s:Weapons[val >> 11][WEAPON_TAG], s:"\c-!");
		break;
		case SINORB_CRITDMG:
			Log(s:temp, s:"and grants \cd", f:ftrunc(SINORB_CRITDMGGIVE * GetAffluenceBonus() * 100), s:"% crit damage to \cd", s:Weapons[val >> 11][WEAPON_TAG], s:"\c-!");
		break;
		/*case SINORB_RES:
			pts = pow(2, CheckInventory("AffluenceCounter"));
			if(pts > 1)
				Log(s:temp, s:"and shows \cd", d:pts, s:"\c- researches!");
			else
				Log(s:temp, s:"and shows \cd", d:pts, s:"\c- research!");
		break;*/
		/*case SINORB_CREDIT:
			Log(s:temp, s: "and gives \cd", d:(val >> 11) * GetAffluenceBonus(), s: "\c- credits!");
		break;*/
	}
}

bool HasWeaponWithoutCritDmgMax() {
	int pnum = PlayerNumber();
	for(int i = 0; i < MAXWEPS; ++i) {
		if(Player_Weapon_Infos[PlayerNumber()][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_CRITDMG].amt < CORRUPTORB_MAXCRITDMG)
			return 1;
	}
	return 0;
}

bool HasUnmaxedStats() {
	for(int i = STAT_STR; i <= STAT_INT; ++i) {
		if(GetStat(i) < DND_STAT_FULLMAX)
			return 1;
	}
	return 0;
}

// do bad stuff as much as you can (except map duration dmg reduction, do it only once in the map)
bool CorruptionMaxChecks(int effect) {
	switch(effect) {
		case CORRUPTORB_NOTHING:
		case CORRUPTORB_TAKEAMMO:
		return 1; 
		
		case CORRUPTORB_TAKEBACKPACK:
		return CheckInventory("BackpackCounter"); // take only if we have at least 1
		
		case CORRUPTORB_TAKEDMG:
		return Player_Weapon_Infos[PlayerNumber()][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_DMG].amt > CORRUPTORB_MINDMG;
		
		case CORRUPTORB_TAKEHP:
		return GetSpawnHealth() > CORRUPTORB_MINHEALTH;
		
		case CORRUPTORB_TAKESPEED:
		return Player_Bonuses[PlayerNumber()].speed_bonus > CORRUPTORB_MINSPEED;
		
		case CORRUPTORB_REDUCEDMGMAP:
		return !CheckInventory("CorruptOrb_DamageReduction");
		
		// good ones
		
		case CORRUPTORB_ADDCRIT:
		return Player_Weapon_Infos[PlayerNumber()][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_CRITPERCENT].amt < CORRUPTORB_MAXCRITPERCENT;
	
		case CORRUPTORB_ADDDMG:
		return Player_Weapon_Infos[PlayerNumber()][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_DMG].amt < CORRUPTORB_MAXDMG;
	
		case CORRUPTORB_ADDCRITDMG:
		return HasWeaponWithoutCritDmgMax();
		
		case CORRUPTORB_ADDSPEED:
		return Player_Bonuses[PlayerNumber()].speed_bonus < CORRUPTORB_MAXSPEED;
		
		case CORRUPTORB_DROPCHANCE:
		return Player_Bonuses[PlayerNumber()].drop_chance < CORRUPTORB_MAXDROPCHANCE;
		
		case CORRUPTORB_GIVESTAT:
		return HasUnmaxedStats();
	}
	return 1;
}

void HandleCorruptOrbUse(int type) {
	int i;
	int pnum = PlayerNumber(), temp = 0;
	switch(type) {
		case CORRUPTORB_TAKEAMMO:
			for(i = 0; i < MAXAMMOTYPES; ++i) {
				Player_MostRecent_Orb[pnum].p_ammos[i] = CheckInventory(AmmoTypes[i]);
				SetInventory(AmmoTypes[i], 0);
			}
			for(i = 0; i < MAXTEMPWEPS; ++i) {
				if(CheckInventory(TemporaryAmmos[i])) {
					Player_MostRecent_Orb[pnum].p_tempammo = CheckInventory(TemporaryAmmos[i]);
					Player_MostRecent_Orb[pnum].p_tempwep = i;
					SetInventory(TemporaryAmmos[i], 0);
					break;
				}
			}
		break;
		case CORRUPTORB_TAKEBACKPACK:
			Player_MostRecent_Orb[pnum].val3 = CheckInventory("BackpackCounter");
			TakeInventory("BackpackCounter", GetAffluenceBonus());
			Player_MostRecent_Orb[pnum].val3 -= CheckInventory("BackpackCounter");
		break;
		case CORRUPTORB_TAKEDMG:
			// we hold the difference while we can
			temp = CORRUPTORB_DMGTAKE * GetAffluenceBonus();
			Player_MostRecent_Orb[pnum].val4 = CheckInventory("DnD_WeaponID");
			if(Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_DMG].amt - temp > CORRUPTORB_MINDMG) {
				Player_MostRecent_Orb[pnum].val3 = temp;
				Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_DMG].amt -= temp;
			}
			else {
				Player_MostRecent_Orb[pnum].val3 = Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_DMG].amt - CORRUPTORB_MINDMG;
				Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_DMG].amt = CORRUPTORB_MINDMG;
			}
			SyncClientsideVariable(DND_SYNC_WEPBONUS_DMG, Player_MostRecent_Orb[pnum].val4);
		break;
		case CORRUPTORB_TAKEHP:
			temp = CORRUPTORB_HPTAKE * GetAffluenceBonus();
			if(GetSpawnHealth() - temp > CORRUPTORB_MINHEALTH) {
				Player_MostRecent_Orb[pnum].val3 = temp;
				Player_Bonuses[pnum].hp_flat_bonus -= temp;
			}
			else {
				Player_MostRecent_Orb[pnum].val3 = GetSpawnHealth() - CORRUPTORB_MINHEALTH;
				Player_Bonuses[pnum].hp_flat_bonus = CORRUPTORB_MINHEALTH;
			}
			SyncClientsideVariable(DND_SYNC_HPFLAT_BONUS, 0);
		break;
		case CORRUPTORB_TAKESPEED:
			temp = CORRUPTORB_SPEEDTAKE * GetAffluenceBonus();
			if(Player_Bonuses[pnum].speed_bonus - temp > CORRUPTORB_MINSPEED) {
				Player_MostRecent_Orb[pnum].val3 = temp;
				Player_Bonuses[pnum].speed_bonus -= temp;
			}
			else {
				Player_MostRecent_Orb[pnum].val3 = Player_Bonuses[pnum].speed_bonus - CORRUPTORB_MINSPEED;
				Player_Bonuses[pnum].speed_bonus = CORRUPTORB_MINSPEED;
			}
			RestoreRPGStat(RES_PLAYERSPEED);
			SyncClientsideVariable(DND_SYNC_SPEED, 0);
		break;
		case CORRUPTORB_REDUCEDMGMAP:
			GiveInventory("CorruptOrb_DamageReduction", 1);
		break;
		
		case CORRUPTORB_ADDDMG:
			temp = CORRUPTORB_DMGGIVE * GetAffluenceBonus();
			Player_MostRecent_Orb[pnum].val4 = CheckInventory("DnD_WeaponID");
			Player_MostRecent_Orb[pnum].val3 = Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_DMG].amt;
			Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_DMG].amt = Clamp_Between(Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_DMG].amt + temp, 0, CORRUPTORB_MAXDMG);
			Player_MostRecent_Orb[pnum].val3 -= Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_DMG].amt;
			SyncClientsideVariable(DND_SYNC_WEPBONUS_DMG, Player_MostRecent_Orb[pnum].val4);
		break;
		case CORRUPTORB_ADDCRIT:
			temp = CORRUPTORB_DMGGIVE * GetAffluenceBonus();
			Player_MostRecent_Orb[pnum].val4 = CheckInventory("DnD_WeaponID");
			Player_MostRecent_Orb[pnum].val3 = Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_CRITPERCENT].amt;
			Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_CRITPERCENT].amt = Clamp_Between(Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_CRITPERCENT].amt + temp, 0, CORRUPTORB_MAXCRITPERCENT);
			Player_MostRecent_Orb[pnum].val3 -= Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_CRITPERCENT].amt;
			SyncClientsideVariable(DND_SYNC_WEPBONUS_CRITPERCENT, Player_MostRecent_Orb[pnum].val4);
		break;
		case CORRUPTORB_ADDCRITDMG:
			temp = CORRUPTORB_CRITDMGGIVE * GetAffluenceBonus();
			Player_MostRecent_Orb[pnum].val4 = CheckInventory("DnD_WeaponID");
			Player_MostRecent_Orb[pnum].val3 = Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_CRITDMG].amt;
			Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_CRITDMG].amt = Clamp_Between(Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_CRITDMG].amt + temp, 0, CORRUPTORB_MAXCRITDMG);
			Player_MostRecent_Orb[pnum].val3 -= Player_Weapon_Infos[pnum][CheckInventory("DnD_WeaponID")].wep_bonuses[WEP_BONUS_CRITDMG].amt;
			SyncClientsideVariable(DND_SYNC_WEPBONUS_CRITDMG, Player_MostRecent_Orb[pnum].val4);
		break;
		case CORRUPTORB_ADDSPEED:
			temp = CORRUPTORB_SPEEDGIVE * GetAffluenceBonus();
			Player_MostRecent_Orb[pnum].val3 = Player_Bonuses[pnum].speed_bonus;
			Player_Bonuses[pnum].speed_bonus = Clamp_Between(Player_Bonuses[pnum].speed_bonus + temp, 0, CORRUPTORB_MAXSPEED);
			Player_MostRecent_Orb[pnum].val3 -= Player_Bonuses[pnum].speed_bonus;
			RestoreRPGStat(RES_PLAYERSPEED);
			SyncClientsideVariable(DND_SYNC_SPEED, 0);
		break;
		case CORRUPTORB_DROPCHANCE:
			temp = CORRUPTORB_DROPCHANCEGIVE * GetAffluenceBonus();
			Player_MostRecent_Orb[pnum].val3 = Player_Bonuses[pnum].drop_chance;
			Player_Bonuses[pnum].drop_chance = Clamp_Between(Player_Bonuses[pnum].drop_chance + temp, 0, CORRUPTORB_MAXDROPCHANCE);
			Player_MostRecent_Orb[pnum].val3 -= Player_Bonuses[pnum].drop_chance;
			SyncClientsideVariable(DND_SYNC_DROPCHANCE, 0);
		break;
		case CORRUPTORB_GIVESTAT:
			do {
				temp = random(0, STATORB_MAXWEIGHT);
				for(i = 0; i < STATORB_MAXSTATS; ++i)
					if(temp <= SpiritOrb_StatDropWeights[i])
						break;
			} while(GetStat(i) == DND_STAT_FULLMAX);
			GiveStat(i, CORRUPTORB_STATGIVE * GetAffluenceBonus());
			Player_MostRecent_Orb[pnum].val3 = i;
			SetInventory("OrbResult", CheckInventory("OrbResult") | i << 8);
		break;
	}
}

void DoCorruptOrbMessage(int val) {
	// val just has the option, except for stat case which has which stat it is << 8
	int temp = GetAffluenceBonus();
	switch(val & 0xF) {
		case CORRUPTORB_NOTHING:
			Log(s:"\cjOrb of Corruption does \cgnothing!");
		break;
		case CORRUPTORB_TAKEAMMO:
			Log(s:"\cjOrb of Corruption \cgtakes away all your ammo!");
		break;
		case CORRUPTORB_TAKEBACKPACK:
			Log(s:"\cjOrb of Corruption \cgtakes away ", d:temp, s:" of your backpacks!");
		break;
		case CORRUPTORB_TAKEDMG:
			Log(s:"\cjOrb of Corruption takes \cg", f:ftrunc(CORRUPTORB_DMGTAKE * 100 * temp), s:"% damage\cj from \cv", s:Weapons[CheckInventory("DnD_WeaponID")][WEAPON_TAG], s:"\cj!");
		break;
		case CORRUPTORB_REDUCEDMGMAP:
			Log(s:"\cjOrb of Corruption \cgreduces your damage by 75%\cj for this map!");
		break;
		case CORRUPTORB_TAKEHP:
			Log(s:"\cjOrb of Corruption \cgreduces your life cap by ", d:CORRUPTORB_HPTAKE * temp, s:"\cj!");
		break;
		case CORRUPTORB_TAKESPEED:
			Log(s:"\cjOrb of Corruption \cgreduces your movement speed by ", f:ftrunc(CORRUPTORB_SPEEDTAKE * temp * 100), s:"%\cj!");
		break;
		
		case CORRUPTORB_ADDCRIT:
			Log(s:"\cjOrb of Corruption gives \cv", f:ftrunc(CORRUPTORB_CRITGIVE * temp * 100), s:"%\cj increased crit chance to \cv", s:Weapons[CheckInventory("DnD_WeaponID")][WEAPON_TAG], s:"\cj!");
		break;
		case CORRUPTORB_ADDCRITDMG:
			Log(s:"\cjOrb of Corruption gives \cv", f:ftrunc(CORRUPTORB_CRITDMGGIVE * temp * 100), s:"%\cj crit damage to ", s:Weapons[CheckInventory("DnD_WeaponID")][WEAPON_TAG], s:"\cj!");
		break;
		case CORRUPTORB_ADDDMG:
			Log(s:"\cjOrb of Corruption gives \cv", f:ftrunc(CORRUPTORB_DMGGIVE * temp * 100), s:"%\cj increased damage to ", s:Weapons[CheckInventory("DnD_WeaponID")][WEAPON_TAG], s:"\cj!");
		break;
		case CORRUPTORB_ADDSPEED:
			Log(s:"\cjOrb of Corruption gives \cv", f:ftrunc(CORRUPTORB_SPEEDGIVE * temp * 100), s:"%\cj increased movement speed!");
		break;
		case CORRUPTORB_DROPCHANCE:
			Log(s:"\cjOrb of Corruption increases your drop chance by \cv", f:ftrunc(CORRUPTORB_DROPCHANCEGIVE * temp * 100), s:"%\cj!");
		break;
		case CORRUPTORB_GIVESTAT:
			Log(s:"\cjOrb of Corruption grants you with \cv", d:CORRUPTORB_STATGIVE * temp, s:" ", s:StatLabels[val >> 8], s:"\cj points!");
		break;
	}
}

void UndoCorruptOrbEffect() {
	// if type is take, we give, if type is give, we take!
	int i;
	int pnum = PlayerNumber();
	switch(Player_MostRecent_Orb[pnum].val1 & 0xF) {
		case CORRUPTORB_TAKEAMMO:
			for(i = 0; i < MAXWEPS; ++i)
				GiveInventory(AmmoTypes[i], Player_MostRecent_Orb[pnum].p_ammos[i]);
			// try to give this temp weapon if only player doesn't have a temp wep
			if(HasNoTempWeapon()) {
				GiveInventory(TemporaryAmmos[Player_MostRecent_Orb[pnum].p_tempwep], Player_MostRecent_Orb[pnum].p_tempammo);
				GiveInventory(TemporaryWeapons[Player_MostRecent_Orb[pnum].p_tempwep], 1);
			}
		break;
		case CORRUPTORB_TAKEHP:
			Player_Bonuses[pnum].hp_flat_bonus += Player_MostRecent_Orb[pnum].val3;
			SyncClientsideVariable(DND_SYNC_HPFLAT_BONUS, 0);
		break;
		case CORRUPTORB_TAKEBACKPACK:
			GiveInventory("BackpackCounter", Player_MostRecent_Orb[pnum].val3);
		break;
		case CORRUPTORB_TAKEDMG:
			Player_Weapon_Infos[pnum][Player_MostRecent_Orb[pnum].val4].wep_bonuses[WEP_BONUS_DMG].amt += Player_MostRecent_Orb[pnum].val3;
			SyncClientsideVariable(DND_SYNC_WEPBONUS_DMG, Player_MostRecent_Orb[pnum].val4);
		break;
		case CORRUPTORB_TAKESPEED:
			Player_Bonuses[pnum].speed_bonus += Player_MostRecent_Orb[pnum].val3;
			RestoreRPGStat(RES_PLAYERSPEED);
			SyncClientsideVariable(DND_SYNC_SPEED, 0);
		break;
		case CORRUPTORB_REDUCEDMGMAP:
			TakeInventory("CorruptOrb_DamageReduction", 1);
		break;
		
		case CORRUPTORB_ADDCRIT:
			// since diff is meant to be negative, we now add it, not subtract it
			Player_Weapon_Infos[pnum][Player_MostRecent_Orb[pnum].val4].wep_bonuses[WEP_BONUS_CRITPERCENT].amt += Player_MostRecent_Orb[pnum].val3;
			SyncClientsideVariable(DND_SYNC_WEPBONUS_CRITPERCENT, Player_MostRecent_Orb[pnum].val4);
		break;
		case CORRUPTORB_ADDCRITDMG:
			Player_Weapon_Infos[pnum][Player_MostRecent_Orb[pnum].val4].wep_bonuses[WEP_BONUS_CRITDMG].amt += Player_MostRecent_Orb[pnum].val3;
			SyncClientsideVariable(DND_SYNC_WEPBONUS_CRITDMG, Player_MostRecent_Orb[pnum].val4);
		break;
		case CORRUPTORB_ADDDMG:
			Player_Weapon_Infos[pnum][Player_MostRecent_Orb[pnum].val4].wep_bonuses[WEP_BONUS_DMG].amt += Player_MostRecent_Orb[pnum].val3;
			SyncClientsideVariable(DND_SYNC_WEPBONUS_DMG, Player_MostRecent_Orb[pnum].val4);
		break;
		case CORRUPTORB_ADDSPEED:
			Player_Bonuses[pnum].speed_bonus += Player_MostRecent_Orb[pnum].val3;
			RestoreRPGStat(RES_PLAYERSPEED);
			SyncClientsideVariable(DND_SYNC_SPEED, 0);
		break;
		case CORRUPTORB_GIVESTAT:
			TakeStat(Player_MostRecent_Orb[pnum].val3, CORRUPTORB_STATGIVE * (Player_MostRecent_Orb[pnum].val1 >> 8));
		break;
		case CORRUPTORB_DROPCHANCE:
			Player_Bonuses[pnum].drop_chance += Player_MostRecent_Orb[pnum].val3;
			SyncClientsideVariable(DND_SYNC_DROPCHANCE, 0);
		break;
	}
}

void HandleOrbUseMessage(int orbtype, int val) {
	if(ConsolePlayerNumber() != PlayerNumber()) 
		return;
	switch(orbtype) {
		case DND_ORB_ENHANCE:
			if(val != 0x7FFFFFFF)
				Log(s:"\cjOrb of Enhancement improves \cd", s:Weapons[val][WEAPON_TAG], s:"\cv damage by \cd", d:GetAffluenceBonus() * ENHANCEORB_BONUS_INT, s:"%\c-!");
			else
				Log(s:"\cgYou're maxed out on enhancements, Orb of Enhancement failed!");
		break;
		case DND_ORB_CORRUPT:
			DoCorruptOrbMessage(val);
		break;
		case DND_ORB_SPIRIT:
			if(val != 0x7FFFFFFF)
				Log(s:"\cjOrb of Spirit grants you with \cv", d:GetAffluenceBonus(), s:" \cd", s:StatLabels[val], s:"\cv!");
			else
				Log(s:"\cgYou're maxed out on stats, Orb of Spirit failed!");
		break;
		case DND_ORB_REPENT:
			if(val != 0x7FFFFFFF)
				Log(s:"\cjOrb of Repentance reverts the effects of \cv", s:OrbList[val][ORB_TAG], s:"\cj!");
			else
				Log(s:"\cgNo orb used or tried to revert effects of Orb of Repentance!");
		break;
		case DND_ORB_AFFLUENCE:
			if(val != 0x7FFFFFFF)
				Log(s:"\cjOrb of Affluence will improve the effect of the next orb used by \cd", d:GetAffluenceBonus(), s: "\c- times!");
			else
				Log(s:"\cgYou've reachde max stacks of Orb of Affluence. (\ck", d:1 << AFFLUENCE_MAX, s:"\cg)");
		break;
		case DND_ORB_CALAMITY:
			if(val != 0x7FFFFFFF)
				Log(s:"\cjOrb of Calamity turns your \ck", s:OrbList[val % 100][ORB_TAG], s:"\cv to an \cd", s:OrbList[val / 100][ORB_TAG], s:"\cv!");
			else
				Log(s:"\cgNo other orb found to convert!");
		break;
		case DND_ORB_PROSPERITY:
			if(val != 0x7FFFFFFF)
				Log(s:"\cjOrb of Prosperity grants \cd", d:GetAffluenceBonus(), s:" armor and health cap\cv increase!");
			else
				Log(s:"\cgMax prosperity bonus reached! (\ck+", d:PROSPERITY_MAX, s:"\c-)");
		break;
		case DND_ORB_FORTITUDE:
			if(val != 0x7FFFFFFF)
				Log(s:"\cjOrb of Fortitude grants \cd", d:GetAffluenceBonus(), s:"% armor and health cap\cv increase!");
			else
				Log(s:"\cgMax fortitude bonus reached! (\ck", d:FORTITUDE_MAX, s:"%\c-)");
		break;
		case DND_ORB_WISDOM:
			if(val != 0x7FFFFFFF)
				Log(s:"\cjOrb of Wisdom grants \cd", d:GetAffluenceBonus(), s:"% experience gain\cv increase!");
			else
				Log(s:"\cgMax wisdom bonus reached! (\ck", d:WISDOMORB_MAX, s:"%\c-)");
		break;
		case DND_ORB_GREED:
			if(val != 0x7FFFFFFF)
				Log(s:"\cjOrb of Greed grants \cd", d:GetAffluenceBonus(), s:"% credit gain\cv increase!");
			else
				Log(s:"\cgMax greed bonus reached! (\ck", d:GREEDORB_MAX, s:"%\c-)");
		break;
		case DND_ORB_VIOLENCE:
			if(val != 0x7FFFFFFF)
				Log(s:"\cjOrb of Violence grants \cd", d:GetAffluenceBonus(), s:"% ", s:TalentTypeNames[val], s:" Damage\cv increase!");
			else
				Log(s:"\cgMax violence bonus reached! (\ck", d:VIOLENCEORB_MAX, s:"%\c-)");
		break;
		case DND_ORB_SIN:
			if(val != 0x7FFFFFFF)
				DoSinOrbMessage(val);
			else
				Log(s:"\cgYou don't have enough allocated states! Need at least \ck", d:SINORB_MAX_TAKE * GetAffluenceBonus(), s:"\c-!");
		break;
		case DND_ORB_RICHES:
			if(!(val >> 16)) // exp
				Log(s:"\cjOrb of Riches gives you \cd", d:val & 0xFFFF, s:"\c- \ckexperience\c- points!");
			else if((val >> 16) == 1)
				Log(s:"\cjOrb of Riches gives you \cd", d:val & 0xFFFF, s:"\c- \cfcredits\c-!");
			else
				Log(s:"\cjOrb of Riches gives you \cd", d:val & 0xFFFF, s:"k\c- \cubudget\c-!");
		break;
		case DND_ORB_HOLDING:
			if(val != 0x7FFFFFFF)
				Log(s:"\cjOrb of Holding grants \cd", f:ftrunc(val * 100), s:"% increased ammo capacity!");
			else
				Log(s:"\cgYou're maxed out on holding bonuses! (\ck", f:ftrunc(HOLDING_MAX * 100), s:"\c-)!");
		break;
	}
}

void ResetMostRecentOrb(int pnum) {
	Player_MostRecent_Orb[pnum].orb_type = 0;
	Player_MostRecent_Orb[pnum].val1 = Player_MostRecent_Orb[pnum].val2 = Player_MostRecent_Orb[pnum].val3 = Player_MostRecent_Orb[pnum].val4 = Player_MostRecent_Orb[pnum].val5 = 0;
	for(int i = 0; i < MAXWEPS; ++i)
		Player_MostRecent_Orb[pnum].p_ammos[i] = 0;
	Player_MostRecent_Orb[pnum].p_tempammo = 0;
	Player_MostRecent_Orb[pnum].p_tempwep = 0;
}

void SpawnOrb() {
	int w = random(1, ORB_MAXWEIGHT), i = 0;
	for(; i < MAX_ORBS && OrbDropWeights[i] < w; ++i);
	SpawnDrop(OrbList[i][ORB_NAME], 24.0, 16, 0);
}

#endif