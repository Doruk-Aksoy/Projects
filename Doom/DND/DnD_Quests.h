#ifndef DND_QUESTS_IN
#define DND_QUESTS_IN

#include "DnD_Common.h"
#include "DnD_MonsterData.h"

enum {
	QUEST_HPOVER50,
	QUEST_ONLYONEWEAPON,
	QUEST_NODYING,
	QUEST_10SPREES,
	QUEST_HEALFOR500,
	QUEST_KILL10BOSSES,
	QUEST_KILL20ELITES,
	QUEST_USENOARTIFACT,
	QUEST_ONLYENERGY,
	QUEST_NOHEALINGPICKUP,
	QUEST_ONLYPISTOLWEAPONS,
	QUEST_NOSHOTGUNS,
	QUEST_NOARMORS,
	QUEST_SPAREZOMBIES,
	QUEST_NOSUPERWEAPONS,
	QUEST_ONLYNOTALENTWEAPONS,
	QUEST_ONLYSPECIALAMMO,
	QUEST_SPEND25K,
	QUEST_KILLDREAMINGGOD,
	QUEST_KILLTORRASQUE,
	QUEST_KILLMORDECQAI,
	QUEST_KILLGODSLAYER
};

typedef struct quest {
	int qflag;
	str qreward;
} quest_T;

enum {
	QTYPE_INDIVIDUAL = 1, // individual satisfaction of requirements, rewarded to those who accomplish first (only 1)
	QTYPE_EVERYONE = 2, // everyone must satisfy requirements, rewarded to all (everyone or no one)
	QTYPE_ATLEASTONE = 4, // at least one person must satisfy requirement, rewarded to all those who accomplish
	QTYPE_TRACKABLE = 8, // progress tracking
	QTYPE_IMMEDIATE = 16, // if conditions are met, doesn't wait till map ends to give
	QTYPE_NOSAVE = 32 // for some reason this quests reward should not be saved
};

#define MAX_QUESTS QUEST_KILLGODSLAYER + 1
quest_T Quest_List[MAX_QUESTS] = {
		{ QTYPE_ATLEASTONE, 											"DnD_QuestReward_RegenCap" 				},
		{ QTYPE_ATLEASTONE, 											"DnD_QuestReward_15PercentDamage"		},
		{ QTYPE_EVERYONE, 												"DnD_QuestReward_100BonusCap"			},
		{ QTYPE_INDIVIDUAL | QTYPE_TRACKABLE | QTYPE_IMMEDIATE,			"DnD_QuestReward_KillingSpree15"		},
		{ QTYPE_INDIVIDUAL | QTYPE_TRACKABLE | QTYPE_IMMEDIATE,			"DnD_QuestReward_HealingIncrease25"		},
		{ QTYPE_INDIVIDUAL | QTYPE_TRACKABLE | QTYPE_IMMEDIATE,			"DnD_QuestReward_ReducedBossDmg"		},
		{ QTYPE_INDIVIDUAL | QTYPE_TRACKABLE | QTYPE_IMMEDIATE,			"DnD_QuestReward_EliteDropBonus"		},
		{ QTYPE_ATLEASTONE, 											"DnD_QuestReward_ExtraArtiDmg"			},
		{ QTYPE_ATLEASTONE,												"DnD_QuestReward_EnergyDamage"			},
		{ QTYPE_EVERYONE,												"DnD_QuestReward_HealingAndCapIncrease" },
		{ QTYPE_ATLEASTONE,												"DnD_QuestReward_Slot2DmgIncrease"		},
		{ QTYPE_ATLEASTONE,												"DnD_QuestReward_ShotgunDmgIncrease"	},
		{ QTYPE_ATLEASTONE,												"DnD_QuestReward_ArmorCapIncrease"		},
		{ QTYPE_EVERYONE,												"DnD_QuestReward_UndeadDamageIncrease"  },
		{ QTYPE_ATLEASTONE,												"DnD_QuestReward_SuperWeaponDamage"		},
		{ QTYPE_ATLEASTONE,												"DnD_QuestReward_TalentIncrease"		},
		{ QTYPE_ATLEASTONE,												"DnD_QuestReward_SpecialAmmoDamage"		},
		{ QTYPE_INDIVIDUAL | QTYPE_TRACKABLE | QTYPE_IMMEDIATE,			"DnD_QuestReward_MoreCredit"			},
		{ QTYPE_ATLEASTONE | QTYPE_IMMEDIATE,							"DnD_QuestReward_DreamingGodBonus"		},
		{ QTYPE_ATLEASTONE | QTYPE_IMMEDIATE,							"DnD_QuestReward_TorrasqueBonus"		},
		{ QTYPE_ATLEASTONE | QTYPE_IMMEDIATE,							"DnD_QuestReward_MordecqaiBonus"		},
		{ QTYPE_ATLEASTONE | QTYPE_IMMEDIATE,							"DnD_QuestReward_GodSlayerBonus"		}
};

#define DND_QUEST_CAUTIOUS_REGENBONUS 100
#define DND_QUEST_PRECIOUSLIFE_BONUS 100
#define DND_QUEST_BERSERK_SPREEREQ 10
#define DND_QUEST_BERSERK_SPREEBONUS 15
#define DND_QUEST_MASTERHEALER_INCREASE 25
#define DND_QUEST_MASTERHEALER_REQ 500
#define DND_QUEST_BOSSKILLER_REQ 20
#define DND_QUEST_ELITEKILLER_REQ 50
#define DND_QUEST_SKINOTEETH_BONUS 100
#define DND_QUEST_SKINOTEETH_INCREASE 25
#define DND_QUEST_TALENTBONUS 25
#define DND_QUEST_MONEYMAKERREQ 25000
#define DND_QUEST_CREDITBONUS 15
#define DND_QUEST_ARMORBONUS 150

#define DND_LEGQUEST_START QUEST_KILLDREAMINGGOD
#define DND_TORRASQUE_BOOST 15

#define DND_GUNSLINGER_GAIN 0.5
#define DND_BOOMSTICK_GAIN 0.5
#define DND_SUPERWEAPON_GAIN 0.25
#define DND_ELITEDROP_GAIN 0.05

#define QUEST_NAME 0
#define QUEST_REQ 1
#define QUEST_REW 2
str Quest_Description[MAX_QUESTS][3] = {
		{ 
			"Cautious",
			"Keep health over 50% at all times.",			
			"Regeneration life cap increases to one half your cap."
		},
		{ 
			"Simple Minded",
			"Only use (fire) one weapon for the entirety of the map.",
			"15% extra damage on all weapons."
		},
		{ 
			"Precious Life",
			"End a map with nobody dying even once.",
			"+100 health capacity."
		},
		{ 
			"Berserker",
			"Get 10 killing sprees in a map.",
			"All killing sprees grant additional 15% more experience."
		},
		{
			"Master Healer",
			"Heal for at least 500 health.",
			"Healing received increases by 25%."
		},
		{
			"Demon Bane",
			"Kill 20 boss level monsters.",
			"Bosses deal 15% less damage."
		},
		{
			"Elite Slayer",
			"Kill 50 elite monsters.",
			"Elites have 5% more chance of rare drops."
		},
		{
			"Power Overwhelming",
			"Use no artifacts.",
			"When using artifacts, gain extra 25% damage for 15 seconds."
		},
		{
			"Overdrive",
			"Use only energy weapons.",
			"Energy weapon damage increases by 30%."
		},
		{
			"Skin O' My Teeth",
			"Use/Pick no healing items.",
			"Health capacity increases by +100, healing received increases by 25%."
		},
		{
			"Gunslinger",
			"Use only Slot 2 weapons.",
			"Slot 2 weapon damage increases by 50%."
		},
		{
			"No Boomstick",
			"Use no shotgun weapons.",
			"Shotgun damage increases by 50%."
		},
		{
			"Thick Skin",
			"Pick or buy no armors.",
			"Armor capacity increases by 150."
		},
		{
			"Let them Rot",
			"Spare all zombies.",
			"Weapons effective against undead and magical monsters do 30% more damage."
		},
		{
			"Casual Weaponry",
			"Use no super weapons. (Slot 7 and 8)",
			"Super Weapons do 25% more damage."
		},
		{
			"Natural Talent",
			"Only use weapon types that have no talents applied.",
			"Talents get 25% dexterity bonus applied."
		},
		{
			"Specialist",
			"Use only special ammo types.",
			"Special ammo damage increases by 50%."
		},
		{
			"Money Maker",
			"Spend 25k credits.",
			"Credit amount from monsters increase by 15%."
		},
		{
			"The Dreaming God",
			"Find and kill the Dreaming God.",
			"Seal of the Dreaming God."
		},
		{
			"Torrasque",
			"Find and kill Torrasque.",
			"Seal of Torrasque."
		},
		{
			"Mordecqai",
			"Find and kill Mordecqai.",
			"Seal of Mordecqai."
		},
		{
			"GodSlayer",
			"Find and kill GodSlayer.",
			"Seal of GodSlayer."
		}
};

str Quest_Checkers[MAX_QUESTS] = {
	"DnD_HealthLess50",
	"DnD_WeaponFiredOther",
	"DnD_Boolean",
	"DnD_BerserkQuest_SpreeCounter",
	"DnD_MasterHealerQuest_HealAmount",
	"DnD_BossKillQuest_Counter",
	"DnD_EliteKillQuest_Counter",
	"DnD_UseNoArtifact",
	"DnD_UsingEnergy",
	"DnD_UseNoHealth",
	"DnD_UseOnlyPistol",
	"DnD_UseNoShotgun",
	"DnD_BoughtArmor",
	"DnD_ShotUndead",
	"DnD_UsedSuperWeapon",
	"DnD_UsedNonTalent",
	"DnD_UsedNonSpecial",
	"DnD_MoneySpentQuest",
	"DnD_Boolean",
	"DnD_Boolean"
};

void CompleteQuest(int tid, int qid) {
	str tocheck = "DnD_QuestState1";
	if(qid > 31)
		tocheck = "DnD_QuestState2";
	qid %= 32; // for 2nd part
	SetActorInventory(tid, tocheck, CheckActorInventory(tid, tocheck) | (1 << qid));
	GiveActorInventory(tid, Quest_List[qid].qreward, 1);
	SetActorInventory(tid, "QuestCompletionToken", active_quest_id + 1);
	FailQuest(qid);
}

bool IsQuestComplete(int tid, int qid) {
	str tocheck = "DnD_QuestState1";
	if(qid > 31)
		tocheck = "DnD_QuestState2";
	qid %= 32; // for 2nd part
	if(!tid)
		return IsSet(CheckInventory(tocheck), qid);
	return IsSet(CheckActorInventory(tid, tocheck), qid);
}

void FailQuest(int qid) {
	// individual quests are who gets it done first, so if someone gets it remove this quest
	if(Quest_List[qid].qflag != QTYPE_ATLEASTONE) {
		active_quest_id = -1;
		// clear from all players
		for(int i = 0; i < MAXPLAYERS; ++i)
			SetActorInventory(i + P_TIDSTART, "ActiveQuestID", 0);
	}
}

bool QuestExitCheckException(int qid) {
	return qid == QUEST_10SPREES || qid == QUEST_SPEND25K || qid == QUEST_KILL10BOSSES || qid == QUEST_KILL20ELITES;
}

int GetQuestProgressRequirement(int qid) {
	int res = 1;
	switch(qid) {
		case QUEST_10SPREES:
			res = DND_QUEST_BERSERK_SPREEREQ;
		break;
		case QUEST_KILL10BOSSES:
			res = DND_QUEST_BOSSKILLER_REQ;
		break;
		case QUEST_KILL20ELITES:
			res = DND_QUEST_ELITEKILLER_REQ;
		break;
		case QUEST_SPEND25K:
			res = DND_QUEST_MONEYMAKERREQ;
		break;
	}
	return res;
}

bool IsValidQuest(int qid) {
	bool res = 1;
	if(qid >= QUEST_KILLDREAMINGGOD)
		res = ThingCountName(LegendaryMonsters[qid - QUEST_KILLDREAMINGGOD], 0) == 1;
	return res;
}

#endif