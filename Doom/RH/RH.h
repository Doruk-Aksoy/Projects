#define MAXCLASSES 8
#define MAXCOOLDOWNS 5
#define MAXBUFFTYPES 27
#define MAXPLAYERS 64
#define PTID_BEGIN 1000
#define FIRST_GOLGOTHAN_ID 4
#define CLASS_CORPSE_TID 16384
#define EYECANDY_TID 131072

enum { C_CRUSADER, C_PROPHET, C_HUNTER, C_WARLOCK, C_AZAGOTH, C_BANE, C_COLOSSUS, C_KJAROCH };


#define MENU_MAXPOS (MAXCLASSES >> 1) - 1
#define WEAPON_TIP_ID 98
#define ULTMSG_NOTREADY_ID 100
#define ULTMSG_HUD_ID 101
#define PROPHET_HUD_ID 102
#define COOLDOWN_HUD_ID 200
#define STATUS_HUD_ID 300
#define BUFF_HUD_ID 301
#define COOLDOWN_BOX_ID 499
#define PROPHET_HUD_ID_BEG 500
#define SWITCH_HUD_ID 2150

enum {
	RH_CLASSTEXT_ID = 40,
	RH_FRAME_ID = RH_CLASSTEXT_ID + MAXCLASSES,
	RH_SELECT_ID,
	RH_CURSOR_ID,
	RH_CLASSTOP_ID,
	RH_CLASSBOX_ID,
	RH_BUTTON_ID,
	RH_CLASSMENU_ID = RH_BUTTON_ID + 3, // option text count = 3
};

#define MIN_PITCH_ANGLE 1.0

#define TICRATE 35
#define MAX_TEAM_STAY_TIME 2 // 2 minutes
#define MINUTETICS 35 * 60
int StartTime[MAXPLAYERS] = { 0 };

#define ENERGY_RECHARGE_TIME 17
#define ULTCHARGE_KILL 25
#define ULTCHARGE_DELAY 5
#define ULTCHARGE_MIN_DELAY TICRATE

#define CRUSADER_HEAL_CAP 85
#define CRUSADER_SHIELD_TIME 8 * TICRATE
#define CONSECRATION_REGEN 10
#define CONSECRATION_DIST 384 << 16
#define CONSECRATION_PERCENT 10

#define PROPHET_RESIST_TIME 4
#define PROPHET_DAMAGE_TIME 4
#define PROPHET_HEAL 5
#define PROPHET_DAMAGE_PERCENT 10
#define PROPHET_DAMAGE_PERCENT2 20
#define PROPHET_IMPACT_RANGE 160 << 16
#define PROPHET_SIGHT_RANGE 8192 << 16
#define PROPHET_FACE_COUNT 7

#define REAPER_BLEED_DAMAGE 8
#define REAPER_BLEED_PERCENT 12
#define REAPER_GUN_TID 500

#define DH_DASH_ENERGY 	25
#define SD_DASHSPEED			9.0	   	// Dash speed whilst in the air
#define SD_DASHJUMP			7.0	   	// Adds a little z-velocity while in the air
#define SD_DASHSTRONG		13.0		// And dash speed whilst grounded
#define SD_SOUNDVOLUME		1.0	    // How loud the dash sound is played

int settings[4][2] = {
									{ BT_FORWARD,						0.00 	},
									{ BT_MOVELEFT | BT_LEFT,		0.25	},
									{ BT_BACK,								0.50	},
									{ BT_MOVERIGHT | BT_RIGHT,	0.75	}
							 };

#define WARLOCK_MANAREGEN_MAX 10
#define WARLOCK_LINK_SOULDROP TICRATE
#define WARLOCK_LINK_COOLDOWN 12 * TICRATE
#define WARLOCK_DSTAFF_GAIN 5
#define WARLOCK_DSTAFF_MAXGAIN 3
#define WARLOCK_DSTAFF_MANA 25
#define WARLOCK_DSTAFF_CHARGE_MANA 25
#define WARLOCK_BLADE_GAIN 1
#define WARLOCK_BOOM_GAIN 8
#define WARLOCK_SHIELD_TIME TICRATE * 4 + (TICRATE / 2)
#define WARLOCK_SHIELD_BASE 100
#define WARLOCK_SHIELD_GAIN 25
#define WARLOCK_RAY_RANGE 160
#define WARLOCK_RAY_RANGEGAIN 32
#define WARLOCK_RAY_DENSITY 16
#define WARLOCK_RAY_TIME TICRATE * 5
#define WARLOCK_RAY_TIMEGAIN TICRATE >> 1
							 
#define AZAGOTH_CONE_TIME 52 // 35 + 17 (1.5 seconds)
#define AZAGOTH_WHIP_TIME 35
#define AZAGOTH_WHIP_COUNT 18
#define AZAGOTH_HP_GAIN 40
#define AZAGOTH_MOVE_TIME 4
#define AZAGOTH_MOVE_DAMAGE 3
#define AZAGOTH_MOVE_WINDOW 1 << 16
#define AZAGOTH_HEALPERCENT 35
#define AZAGOTH_FURNACETID_INIT 32768
#define AZAGOTH_FURNACETID 8000
#define AZAGOTH_FURNACE_DURATION 84

#define BANE_LEASH_DISTANCE 420 << 16
#define BANE_LEASH_DURATION 2 * TICRATE
#define BANE_IGNITE_DAMAGE 1

#define COLOSSUS_PASSIVE_ENERGY 5
#define COLOSSUS_MELEE_TRIES 3
#define COLOSSUS_MELEE_ANGLE 6400
#define COLOSSUS_MELEE_DIST 136 << 16
#define COLOSSUS_MELEE_DMG 75
#define COLOSSUS_RAMPAGE_TIME TICRATE * 10
#define COLOSSUS_MAX_GAIN_TIME TICRATE * 4

#define KJAROCH_PASSIVE_LIMIT 50
#define KJAROCH_PASSIVE_GAIN 0.01
#define KJAROCH_WARP_RANDMAX 160
#define KJAROCH_WARP_VELZMAX 12.0
#define KJAROCH_ULT_DISTANCE 128 << 16
#define KJAROCH_SERVANTMULT MAXPLAYERS
#define KJAROCH_MIN_HEAL 50
#define KJAROCH_MAX_HEAL 250
#define KJAROCH_HEAL_PERCENT 50
#define KJAROCH_SERVANT_CHECKTIME 5
#define KJAROCH_SERVANT_LASTTIME 15 * TICRATE / KJAROCH_SERVANT_CHECKTIME

#define ASPECT_4_3 (4.0 / 3)
#define ASPECT_5_4 1.25
#define ASPECT_16_9 (16.0 / 9)
#define ASPECT_16_10 1.6

#include "RH_Msg.h"

// holds client aspect ratio
int paspect = 0;

// fx that are manipulated non-clientside
enum {
	RHFX_CRUSADERSHIELD1,
	RHFX_CRUSADERSHIELD2,
	RHFX_CRUSADERSHIELD3,
	RHFX_AZAGOTHLIFEMARKER,
	RHFX_WARLOCKSHIELD,
	RHFX_WARLOCKDEATHRAY,
	RHFX_AZAGOTHWHIP
};

// clientside manipulated fx
enum {
	RHCFX_HOLYSIGHTICON
};

// Special FX TID begin markers
#define MAXFX 7
int FXTIDList[MAXFX] = { 1000, 1150, 1300, 1450, 2000, 2150, 6000 };

#define MAXCLIENTSIDEFX 1
int FXTIDListClientside[MAXCLIENTSIDEFX] = { 1550 };
// MAX HP values of all classes
int MAXHPValues[MAXCLASSES] = { 200, 125, 100, 100, 650, 550, 875, 600 };

int HUDMSGActorCounts[MAXPLAYERS];

str ClassNames[MAXCLASSES] = {
	"Crusader",
	"Prophet",
	"DemonHunter",
	"Warlock",
	"Azagoth",
	"Bane",
	"Colossus",
	"Kjaroch"
};

#define MAXFRAMES 4
#define FRAMETICS 8
str ClassFrames[MAXCLASSES][MAXFRAMES] = {
	{ "CRMDA2", "CRMDB2", "CRMDC2", "CRMDD2" },
	{ "PRPHA2A8", "PRPHB2B8", "PRPHC2C8", "PRPHD2D8" },
	{ "UNDPA2A8", "UNDPB2B8", "UNDPC2C8", "UNDPD2D8" },
	{ "CMYSA2", "CMYSB2", "CMYSC2", "CMYSD2" },
	
	{ "AVATA2C8", "AVATB2D8", "AZAMOV1", "AZAMOV2" },
	{ "HIERA2C8", "HIERB2D8", "HIERMOV1", "HIERMOV2" },
	{ "GOL3A2A8", "GOL3B2B8", "GOL3C2C8", "GOL3D2D8" },
	{ "BOS3A2A8", "BOS3B2B8", "BOS3C2C8", "BOS3D2D8" }
};

str CorpseNames[MAXCLASSES] = {
										"CrusaderCorpse",
										"ProphetCorpse",
										"ReaperCorpse",
										"WarlockCorpse",
										"AzagothCorpse",
										"BaneCorpse",
										"ColossusCorpse",
										"KjarochCorpse"
};
									
int ClassCooldownsMaxCount[MAXCLASSES] = { 2, 2, 4, 2, 3, 3, 2, 2 };
									
str ClassCooldowns[MAXCLASSES][MAXCOOLDOWNS] = 
	{
		{ "CrusaderShieldCooldown", "CrusaderJetCooldown", "", "", "" },
		{ "ProphetHolyCooldown", "ProphetDarkCooldown" },
		{ "DashCooldown", "RazorCooldown", "ReaperSnareTrapCooldown", "ReaperGunTrapCooldown" },
		{ "WarlockLinkCooldown", "WarlockShieldCooldown" },
		{ "AzagothLashCooldown", "AzagothLifeCurseCooldown", "AzagothMovementCurseCooldown", "", "" },
		{ "BaneVolcanoCooldown", "BaneAblazeCooldown", "BaneLeashCooldown", "", "" },
		{ "ColossusStunCooldown", "ColossusGazeCooldown" },
		{ "KjarochWarpCooldown", "KjarochOrbCooldown" }
	};
									
str ClassCooldownText[MAXCLASSES][MAXCOOLDOWNS] = 
	{
		{ "Blessed Shield", "Purge", "", "", "" },
		{ "Inspire", "Death Seeker", "", "", "" },
		{ "Dash", "Razor Blades", "Bear trap", "Gun trap", "" },
		{ "Dark Link", "Spirit Shield" },
		{ "Lash", "Drain Curse", "Golgotha's Gift", "", "" },
		{ "Volcano", "Incinerate", "Fire Leash", "", "" },
		{ "Ground Slam", "Gaze", "", "", "" },
		{ "Nether Warp", "Nether Orb" }
	};
				
int ClassCooldownValues[MAXCLASSES][MAXCOOLDOWNS] =
	{
		{ 16, 8, 0, 0, 0 },
		{ 9, 7, 0, 0, 0 },
		{ 2, 3, 6, 18, 0 },
		{ 12, 10, 0, 0, 0 },
		{ 7, 5, 5, 0, 0 },
		{ 6, 2, 6, 0, 0 },
		{ 6, 5, 0, 0, 0 },
		{ 8, 12, 0, 0, 0 }
	};
	
#define DEBUFF_BEGIN 8
str BuffTypes[MAXBUFFTYPES] = 
	{
		"ConsecrationHaste", 
		"ConsecrationRegenPower", 
		"CrusaderShieldProtection", 
		"FinalHourSpeed",
		"ProphetResist",
		"ProphetDamage",
		"WarlockBoneShieldBuff",
		"HolySightBuff",
		"ConsecrationSlow", 
		"AzagothDrain", 
		"AzagothDrainWeak",
		"ColossusReduction", 
		"AzagothFurnaceVictim", 
		"BaneSnare", 
		"BaneSnareWeak",
		"BaneIgniteDebuff", 
		"AzagothMove",
		"ColossusStun",
		"BaneLeashDebuff",
		"ReaperBleed",
		"ReaperSnare",
		"ColossusReductionWeak", 
		"ColossusStunWeak",
		"ColossusSlow",
		"ColossusSlowWeak",
		"KjarochWeaken",
		"KjarochWeakenWeak"
	};
				
str BuffIcons[MAXBUFFTYPES] =
	{
		"BF_HASTE", 
		"BF_REGEN", 
		"BF_RESIS", 
		"BF_RAGE",
		"BF_RESI2",
		"BF_DMG",
		"BF_BONSH",
		"BF_SIGHT",
		"DF_SLOW", 
		"DF_DRAIN", 
		"DF_DRAIN",
		"DF_AMP", 
		"DF_LASH", 
		"DF_SNARE", 
		"DF_SNARE",
		"DF_BURN", 
		"DF_AMOV",
		"DF_STUN",
		"DF_LASH",
		"DF_BLED",
		"DF_SNARE",
		"DF_AMP",
		"DF_STUN",
		"DF_SLOW2",
		"DF_SLOW2",
		"DF_KJAR",
		"DF_KJAR"
	};

// This is needed because decorate doesn't always access the right actor through target
enum {
	RHSD_AZAGOTHMOVE,
	RHSD_AZAGOTHDRAIN,
	RHSD_BANEBURN,
	RHSD_BANELEASH1,
	RHSD_BANELEASH2,
	RHSD_REAPERBLEED
};
	
#define MAXSPECIALDEBUFFS RHSD_REAPERBLEED + 1
str SpecialDebuffs[MAXSPECIALDEBUFFS] = {
		"AzagothMoveBegin",
		"AzagothHealFXSpawnItem",
		"BaneIgniteBegin",
		"LeashVictimTID",
		"BaneLeashInitiate",
		"ReaperBleedBegin"
};
				
function int abs(int x) {
	if(x < 0)
		return -x;
	return x;
}

function int min(int x, int y) {
	if(x < y)
		return x;
	return y;
}

function int max(int x, int y) {
	if(x > y)
		return x;
	return y;
}
											
function int CheckBit(int x, int b) {
	return x & (1 << b);
}

function int SetInventory (str item, int count) {
	int n = count - CheckInventory (item);
	if (n > 0)
		GiveInventory (item, n);
	else if (n < 0)
		TakeInventory (item, -n);
	return n;
}

// Clean clientside stuff here
function void CleanClientsideStuff(int pnum) {
	for(int i = 0; i < MAXCOOLDOWNS; ++i)
		HudMessage(s:" "; HUDMSG_PLAIN, COOLDOWN_HUD_ID + i, CR_WHITE, 520.0, 440.0, 1);
	for(int i = 0; i < MAXBUFFTYPES; ++i)
		HudMessage(s:" "; HUDMSG_PLAIN, BUFF_HUD_ID + i, -1, 600.0, 32.0, 1);
	for(int i = 0; i < MAXPLAYERS; ++i)
		HudMessage(s:" "; HUDMSG_PLAIN, PROPHET_HUD_ID_BEG + i, -1, 0, 0, 1);
	// prophet icon
	SetActorState(FXTIDListClientside[RHCFX_HOLYSIGHTICON] + PTID_BEGIN + pnum, "Fade");
	HudMessage(s:" "; HUDMSG_PLAIN, PROPHET_HUD_ID, -1, 0.0, 0.0, 1);
	CleanMenu();
}
		
function void CleanPlayerFX (int tid) {
	int i;
	for(i = 0; i < MAXFX - 1; i++)
		Thing_Remove(tid + FXTIDList[i]);
	for(i = 0; i < 64; ++i)
		Thing_Remove(i * FXTIDList[MAXFX - 1]);
}

function void CleanClientsideFX (int tid) {
	
}

function int IsAlive(void) {
	return GetActorProperty(0, APROP_HEALTH) > 0;
}

function int IsAliveTID(int tid) {
	return GetActorProperty(tid, APROP_HEALTH) > 0;
}

function int GetPlayerTeam (int p) {
	return GetPlayerInfo (p, PLAYERINFO_TEAM);
}

function int CanMove(void) {
	return !CheckInventory("ColossusStun") && !CheckInventory("BaneSnare") && !CheckInventory("ReaperSnare");
}

function int IsButtonPressed (int input, int oldInput, int mask) {
	return (input & ~oldInput) & mask;
}

function int fdistancexyz(int mx, int my, int mz, int tid) {
	int len;
	int x = mx - getactorx(tid);
	int y = my - getactory(tid);
	int z = mz - getactorz(tid);

	int ang = vectorangle(x, y);
	if(((ang+0.125)%0.5) > 0.25) len = fixeddiv(y, sin(ang));
	else len = fixeddiv(x, cos(ang));

	ang = vectorangle(len, z);
	if(((ang+0.125)%0.5) > 0.25) len = fixeddiv(z, sin(ang));
	else len = fixeddiv(len, cos(ang));

	return len;
}

// returns fixed distance
function int AproxDistance (int dx, int dy) {
	dx = abs(dx);
	dy = abs(dy);

	if (dx < dy)
		return dx + dy - (dx >> 1);

	return dx + dy - (dy >> 1);
}

function int fdistance (int tid1, int tid2)
{
	int len;
	int x = getactorx(tid1) - getactorx(tid2);
	int y = getactory(tid1) - getactory(tid2);
	int z = getactorz(tid1) - getactorz(tid2);

	int ang = vectorangle(x,y);
	if(((ang+0.125)%0.5) > 0.25) len = fixeddiv(y, sin(ang));
	else len = fixeddiv(x, cos(ang));

	ang = vectorangle(len, z);
	if(((ang+0.125)%0.5) > 0.25) len = fixeddiv(z, sin(ang));
	else len = fixeddiv(len, cos(ang));

	return len;
}

// Square root function
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

function int magnitudeThree(int x, int y, int z) {
    return sqrt_z(x*x + y*y + z*z);
}

// Returns the ClassType as an integer
function int GetClass (int tid) {
	return CheckActorInventory(tid, "ClassType") - 1;
}

// Only valid where k * p >= 100 for integers
function int GetPercent(int k, int p) {
	return (k * p) / 100;
}

function int GetHealthPercent(int tid, int ctype) {
	return (100 * GetActorProperty(0, APROP_HEALTH)) / MAXHPValues[ctype];
}

function int GetMissingHealthPercent(int tid, int ctype) {
	return (100 * (MAXHPValues[ctype] - GetActorProperty(0, APROP_HEALTH))) / MAXHPValues[ctype];
}

function int Clamp_Between(int x, int low, int high) {
	int res = x;
	if(res < low)
		res = low;
	else if(res > high)
		res = high;
	return res;
}

function void hudmessageonactor(int tid, int range, str sprite, str text, int hx, int hy, int hudid) {
	if(GetCVar("vid_renderer")) {
		HudSetShowToEveryone(false);
        HudSetCameraActor(PTID_BEGIN + ConsolePlayerNumber());
        HudSetPoint3D(GetActorX(tid), GetActorY(tid), GetActorZ(tid));
		HudSetScale(2.0);
		if(range) {
			if(AproxDistance(GetActorX(0) - GetActorX(tid), GetActorY(0) - GetActorY(tid)) <= range) {
				if(sprite != -1)
					HudDrawImage(hudid, sprite);
				else
					HudDrawText(hudid, text);
			}
		}
	}
	else {
		// software uses old method
		int dist, ang, vang, pitch, x, y, ratio;
		int HUDX = hx;
		int HUDY = hy;
		int offset = 0;

		if(sprite != -1) {
			setfont(sprite);
			text = "A";
			offset = 0.1;
		}

		x = getactorx(tid) - getactorx(0);
		y = getactory(tid) - getactory(0); 

		vang = vectorangle(x,y);
		ang = (vang - GetActorAngle(0) + 1.0) % 1.0;

		if(((vang+0.125)%0.5) > 0.25) dist = fixeddiv(y, sin(vang));
		else dist = fixeddiv(x, cos(vang));
		
		if ((ang < 0.2 || ang > 0.8) && dist < range) {
			ratio = Clamp_Between(FixedDiv(range, dist), 0.05, 1.0);
			HUDX *= ratio;
			HUDY *= ratio;
			HUDX >>= 16;
			HUDY >>= 16;
			sethudsize(HUDX, HUDY, 1);
		
			pitch = vectorangle(dist, getactorz(tid) - (getactorz(0) + 41.0));
			pitch = (pitch + GetActorPitch(0) + 1.0) % 1.0;

			x = HUDX/2 - ((HUDX/2) * sin(ang) / cos(ang));
			y = HUDY/2 - ((HUDX/2) * sin(pitch) / cos(pitch));

			hudmessage(s:text; HUDMSG_PLAIN, hudid, CR_UNTRANSLATED, (x<<16)+offset, (y<<16)+offset, 0);
		}
		else
			hudmessage(s:" "; HUDMSG_PLAIN, hudid, CR_UNTRANSLATED, 0, 0, 0);
	}
}

function void FaceActor(int m1, int m2) {
	int xdiff = GetActorX(m2) - GetActorX(m1);
	int ydiff = GetActorY(m2) - GetActorY(m1);
	int zdiff = (GetActorZ(m2) + GetActorProperty(m2, APROP_HEIGHT)) - (GetActorZ(m1) + GetActorProperty(m1, APROP_HEIGHT));
	int dist = AproxDistance(xdiff, ydiff);
	SetActorAngle(m1, VectorAngle(xdiff, ydiff));
	dist = FixedDiv(dist, 256.0);
	zdiff = FixedDiv(zdiff, 256.0);
	int tpitch = -VectorAngle(dist, zdiff);
//	printbold(d:dist, s: " ", f:tpitch);
	SetActorPitch(m1, tpitch);
}

// compare angle diff for m1 looking at m2, see if its less than maxdiff
function int MaxAngleDiff (int m1, int m2, int maxdiff) {
	int x = GetActorX(m2) - GetActorX(m1);
	int y = GetActorY(m2) - GetActorY(m1);
	int pang = GetActorAngle(m1);
	int angdiff = VectorAngle(x, y);
	if(angdiff <= pang + maxdiff && angdiff >= pang - maxdiff)
		return 1;
	return 0;
}

function int Get_Ultimate_Delay(void) {
	// every player adds a ~0.26 delay, minimum of 1 second
	return TICRATE * (PlayerCount() / 8);
}

// Return 1 if zealots have too many, 2 if golgothans are too many, 0 if it's ok
function int accepted_ratio(int golcount, int zealcount) {
	if(golcount + zealcount < 2)
		return 0;
	// there are golgothans but no zealots
	if(golcount && !zealcount)
		return 2;
	// there are zealots
	if(zealcount) {
		// if there are no golgothans that's a problem
		if(!golcount && zealcount > 1)
			return 1;
		// zealots are favored while balancing
		if(zealcount < golcount)
			return 2;
		int check = (zealcount >> 1) + (zealcount & 1);
		// now there are both on the field, force a ratio
		if(golcount < check - 1)
			return 1;
		if(golcount > check + 1)
			return 2;
	}
	return 0;
}

// Team Balance script from AoW -- Script by Dusk, modified by Ivan
function void CheckTeamBalance (void) {
	int PlayerStayTics = MAX_TEAM_STAY_TIME * MINUTETICS;
	int do_restart, again = 0, do_again = 0;
	do {
		do_restart = false;
		again = do_again;
		// golgotha is red, zealots are blue (red is 1, blue is 0)
		int check = accepted_ratio(RedCount(), BlueCount()), lesserteam;
		if (!check)
			break;
		else if(check == 2)
			lesserteam = TEAM_BLUE;
		else
			lesserteam = TEAM_RED;
		
		// Find someone to switch
		int switchee = -1;
		int switcheetime = 0;
		for (int i = 0; i < MAXPLAYERS; i++) {
			if (!PlayerInGame(i) || GetPlayerTeam (i) == lesserteam)
				continue;
			// find player who has recently joined
			// if we have to iterate through players again, this time the time constraint can be lifted
			if (StartTime[i] > switcheetime && (again || (Timer() - StartTime[i] < PlayerStayTics))) {
				switchee = i;
				switcheetime = StartTime[i];
			}
		}
		
		// Found someone, switch him.
		if (switchee != -1) {
			SetActivator (PTID_BEGIN + switchee);
				SetFont ("BIGFONT");
				HudMessage (s:"You have been switched to even out teams.\n        Use class menu to change class!";
				HUDMSG_FadeOut, SWITCH_HUD_ID, CR_WHITE, 0.5, 0.4, 3.0, 1.0);
			Player_SetTeam (lesserteam);
			SetActivator (-1);
			do_restart = true;
		}
		else if(!do_again)
			do_again = 1;
	} while (do_restart || !again);
}

function int SpawnAreaTID(int stid, int maxdist, int degree_inc, str actortype, int newtid, int ang_begin, int forced) {
	// tries to spawn an object in a circle around stid
	// tries halving radius if a full circular attempt failed until radius becomes 1
	int r = maxdist, tries = 0, finish = 0, circle_comp = 360 / (degree_inc >> 16), test = 0;
	int sang = GetActorAngle(stid) + ang_begin;
	while(r != 1.0 && !finish) {
		// try to spawn at this one point
		int cx = GetActorX(stid) + FixedMul(r, cos(sang + tries * degree_inc));
		int cy = GetActorY(stid) + FixedMul(r, sin(sang + tries * degree_inc));
		int cz = GetActorZ(stid);
		if(forced)
			test = SpawnForced(actortype, cx, cy, cz, newtid);
		else
			test = Spawn(actortype, cx, cy, cz, newtid);
			
		if(test)
			finish = 1;
		else {
			++tries;
			if(tries == circle_comp) {
				tries = 0;
				r /= 2;
			}
		}
	}
	return finish;
}

/*
-----------------------
MENU DEFINITIONS
-----------------------
*/

#define HELPMENU_ID 1000
#define HELPMENU_MAXPAGES 5
#define HELPMENU_OFF 0
#define HELPMENU_ON 1
#define HELPMENU_CLASS 2
str HELPMENU_PICS[HELPMENU_MAXPAGES] = { "GENHELP1", "GENHELP2", "GENHELP3", "GENHELP4", "GENHELP5" };

int PlayerMenuModes[MAXPLAYERS] = { 0 };
int PlayerPages[MAXPLAYERS] = { 0 };

int PlayerOnMenu() {
	return PlayerMenuModes[PlayerNumber()] & (HELPMENU_ON | HELPMENU_CLASS);
}

int PlayerOnClass() {
	return PlayerMenuModes[PlayerNumber()] == HELPMENU_CLASS;
}

int GetPlayerMenuMode() {
	return PlayerMenuModes[PlayerNumber()];
}

int GetPlayerPages() {
	return PlayerPages[PlayerNumber()];
}

void SetPlayerPages(int pn) {
	PlayerPages[PlayerNumber()] = pn;
}

void SetPlayerMenuMode(int mode) {
	PlayerMenuModes[PlayerNumber()] = mode;
}

void CleanPlayerMenu(int pnum) {
	PlayerMenuModes[pnum] = 0;
	PlayerPages[pnum] = 0;
}

void CleanMenu() {
	HudMessage(s:" "; HUDMSG_PLAIN, HELPMENU_ID, -1, 0, 0, 1);
}

void ClearClassMenu() {
	// Closing Menu
	clearhudmessage(RH_CLASSMENU_ID);
	clearhudmessage(RH_CLASSBOX_ID);
	clearhudmessage(RH_CLASSTOP_ID);
	clearhudmessage(RH_FRAME_ID);
	clearhudmessage(RH_BUTTON_ID);
	clearhudmessage(RH_BUTTON_ID + 1);
	clearhudmessage(RH_BUTTON_ID + 2);
	for(int i = 0; i < MAXCLASSES; ++i)
		clearhudmessage(RH_CLASSTEXT_ID + i);
}

void DrawMenu(int mode, int page) {
	SetHudSize(1024, 768, 0);
	SetFont(HELPMENU_PICS[page]);
	HudMessage(s:"A"; HUDMSG_PLAIN, HELPMENU_ID, -1, 512.0, 384.0, 0);
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

// Class Select Menu
global int 0: ClassMenuOpened[];

str ClassMenuBackground[2] = { "ZEALMENU", "GOLGMENU" };

// Lib by Korshun, Monsterovich and DJ Skaarj
// One day, include the whole acsutil library and remove these :p
function void limiterror(str x) {}
function void programerror(Str x) {}
function int itrunc(int x) { return x>>16; }
function int screenwidth(void) { return GetCVar("vid_defwidth"); }
function int screenheight(void) { return GetCVar("vid_defheight"); }
function void clearhudmessage(int id) { HudMessage(s:""; 0, id, 0, 0, 0, 0); }
function bool statusbarshown(void) { return GetCVar("screenblocks") <= 10; }
function int tan(int x) { return FixedDiv(sin(x), cos(x)); }
function int trunc(int x) { return (x & 0xffff0000) + ((x < 0)<<16); }