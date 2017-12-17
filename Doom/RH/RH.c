#library "hudlib"
#include "zcommon.acs"

#include "RH.h"
#include "acshudlib.acs"

Script 500 ENTER {
	StartTime[PlayerNumber()] = Timer();
	Thing_ChangeTID(0, PTID_BEGIN + PlayerNumber());
	CleanPlayerFX(PTID_BEGIN + PlayerNumber());
	SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
	Delay(1);
	CheckTeamBalance();
	Delay(34);
	SetInventory("UltimateCharge", 0);
}

Script 501 DEATH {
	CleanPlayerFX(ActivatorTID());
	Thing_ChangeTID(PTID_BEGIN + PlayerNumber(), 0);
	SetActivatorToTarget(0);
	int targtid = ActivatorTID();
	GiveActorInventory(targtid, "UltimateCharge", ULTCHARGE_KILL);
	CleanPlayerMenu(PlayerNumber());
}

Script 502 RESPAWN {
	Thing_ChangeTID(0, PTID_BEGIN + PlayerNumber());
	CleanPlayerFX(PTID_BEGIN + PlayerNumber());
	if(!StartTime[PlayerNumber()])
		StartTime[PlayerNumber()] =  Timer();
}

Script 503 (int pnum) DISCONNECT {
	CleanPlayerFX(PTID_BEGIN + pnum);
	SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
	CleanPlayerMenu(pnum);
	ClassMenuOpened[pnum + PTID_BEGIN] = 0;
	StartTime[pnum] = 0;
	// if game is not during countdown, enforce this
	if(GetGameModeState() == GAMESTATE_COUNTDOWN)
		CheckTeamBalance();
	else {
		// while not countdown, wait
		while(GetGameModeState() != GAMESTATE_COUNTDOWN)
			Delay(35);
		// game play ended, countdown time, check team situation
		CheckTeamBalance();
	}
}

// Energy Script + Armor Check
Script 504 (void) {
	int flip = 0;
	while(IsAlive()) {
		int dtime = ENERGY_RECHARGE_TIME;
		if(!CheckInventory("Rampaging") && !CheckInventory("NoEnergyCharge")) {
			GiveInventory("Energy", 5);
			int ctype = GetClass(ActivatorTID());
			if(CheckInventory("ColossusPower3"))
				GiveInventory("Energy", COLOSSUS_PASSIVE_ENERGY);
		}
		dtime += flip;
		flip = !flip;
		for(int i = 0; i < dtime; ++i) {
			if(CheckInventory("Armor"))
				GiveInventory("HasArmor", 1);
			else
				TakeInventory("HasArmor", 1);
			Delay(1);
		}
	}
}

// Ultimate not available
Script 505 (int mode) CLIENTSIDE {
	if(ConsolePlayerNumber() != PlayerNumber()) Terminate;
	if(mode) {
		TakeInventory("UltimateReady", 1);
	}
	else {
		SetFont("BIGFONT");
		HudMessage(s:"Ultimate Not Ready!"; HUDMSG_PLAIN, ULTMSG_NOTREADY_ID, CR_LIGHTBLUE, 0.5, 0.1, 1.5);
	}
}

// Ultimates Script
Script 506 (void) {
	Delay(35);
	int delaybase = Clamp_Between(Get_Ultimate_Delay(), ULTCHARGE_MIN_DELAY, ULTCHARGE_DELAY * 35);
	while(GetActorProperty(0, APROP_HEALTH) > 0) {
		Delay(delaybase);
		// don't give charges during colossus ultimate
		if(!CheckInventory("Rampaging"))
			GiveInventory("UltimateCharge", 1);
	}
}

// Draw the ultimate and status text also updates player aspect ratio
Script 507 ENTER CLIENTSIDE {
	if(ConsolePlayerNumber() != PlayerNumber()) Terminate;
	CleanClientsideStuff(PlayerNumber());
	ACS_ExecuteAlways(702, 0);
	while(isAlive()) {
		int cx1 = 600.0, cy1 = 20.0, cx2 = 522.1, cy2 = 453.0;
		// update player aspect ratio here
		paspect = GetAspectRatio();
		if(paspect == ASPECT_5_4) {
			cy1 -= 16.0;
			cy2 += 16.0;
		}
		else if(paspect == ASPECT_16_9) {
			cx1 += 106.0;
			cx2 += 106.0;
		}
		else if(paspect == ASPECT_16_10) {
			cx1 += 64.0;
			cx2 += 64.0;
		}
		SetFont("OBJFONT");
		SetHudSize(640, 480, 0);
		HudMessage(s:"STATUS"; HUDMSG_PLAIN, STATUS_HUD_ID, -1, cx1, cy1, 0);
		SetFont("MSGBOX");
		HudMessage(s:"A"; HUDMSG_PLAIN, COOLDOWN_BOX_ID, CR_WHITE, cx2, cy2, 0);
		// refresh every second for possible aspect ratio change
		Delay(35);
	}
}

Script 508 (int cointype, int givenum) {
	if(!CheckInventory("UltimatePainCooldown")) {
		for(int i = 0; i < givenum; ++i)
			if(!cointype)
				GiveInventory("HumanCoinSpawner", 1);
			else
				GiveInventory("GolgothanCoinSpawner", 1);
		GiveInventory("UltimatePainCooldown", 1);
	}
}

Script 509 ENTER NET CLIENTSIDE {
	if(ConsolePlayerNumber() != PlayerNumber()) Terminate;
	ACS_ExecuteAlways(708, 0);
}

Script 510 (int pnum) DISCONNECT CLIENTSIDE {
	CleanClientsideStuff(pnum);
	ClearClassMenu();
}

Script 511 RESPAWN CLIENTSIDE {
	CleanClientsideStuff(PlayerNumber());
}

// Warlock mana regen
Script 512 (void) {
	while(IsAlive()) {
		GiveInventory("WarlockMana", Clamp_Between(5 + CheckInventory("WarlockSouls"), 5, WARLOCK_MANAREGEN_MAX));
		Delay(24);
	}
}

Script 513 (void) {
	while(isAlive()) {
		int percent = GetHealthPercent(ActivatorTID(), GetClass(ActivatorTID()));
		// would do strparam if there were many...
		if(percent <= 25 && !CheckInventory("ColossusPower3")) {
			GiveInventory("ColossusPower3", 1);
			ActivatorSound("Colossus/Mad", 127);
			GiveInventory("ColossusMadParticles", 1);
		}
		else if(percent <= 50 && !CheckInventory("ColossusPower2")) {
			GiveInventory("ColossusPower2", 1);
			ActivatorSound("Colossus/Mad", 127);
			GiveInventory("ColossusMadParticles", 1);
		}
		else if(percent <= 75 && !CheckInventory("ColossusPower1")) {
			GiveInventory("ColossusPower1", 1);
			ActivatorSound("Colossus/Mad", 127);
			GiveInventory("ColossusMadParticles", 1);
		}
		Delay(10);
	}
}

// special debuff giver
Script 597 (int id, int amount) {
	SetActivator(0, AAPTR_TARGET);
	GiveInventory(SpecialDebuffs[id], amount);
}

// Randomly spawn crusader heal fx when hes ulted
Script 598 (void) CLIENTSIDE {
	while(isAlive() && CheckInventory("ConsecrationRegenPower")) {
		GiveInventory("ConsecrationAuraSpawner", 1);
		Delay(5);
	}
}

Script 599 (void) CLIENTSIDE {
	int tid = ActivatorTID() + FXTIDList[RHFX_AZAGOTHLIFEMARKER];
	Spawn("AzagothLifeMarker", GetActorX(0), GetActorY(0), GetActorZ(0), tid);
	while(IsAlive() && (CheckInventory("AzagothDrain") || CheckInventory("AzagothDrainWeak"))) {
		SetActorPosition(tid, GetActorX(0), GetActorY(0), GetActorZ(0) + 64.0, 0);
		Delay(1);
	}
	Thing_Remove(tid);
}

// Shield Script
Script 600 (void) {
	int i, check = 0;
	Spawn("CrusaderShield", GetActorX(0), GetActorY(0), GetActorZ(0) + 48.0, ActivatorTID() + FXTIDList[RHFX_CRUSADERSHIELD1]);
	Spawn("CrusaderShield", GetActorX(0), GetActorY(0), GetActorZ(0) + 48.0, ActivatorTID() + FXTIDList[RHFX_CRUSADERSHIELD2]);
	Spawn("CrusaderShield", GetActorX(0), GetActorY(0), GetActorZ(0) + 48.0, ActivatorTID() + FXTIDList[RHFX_CRUSADERSHIELD3]);
	for(i = 0; i < CRUSADER_SHIELD_TIME; i++) {
		SetActorPosition(ActivatorTID() + FXTIDList[RHFX_CRUSADERSHIELD1], GetActorX(0)  + 48 * cos(GetActorAngle(0)), GetActorY(0) + 48 * sin(GetActorAngle(0)), GetActorZ(0) + 8.0, 0);
		SetActorPosition(ActivatorTID() + FXTIDList[RHFX_CRUSADERSHIELD2], GetActorX(0)  + 40 * cos(GetActorAngle(0) + 0.25), GetActorY(0) + 40 * sin(GetActorAngle(0) + 0.25), GetActorZ(0) + 8.0, 0);
		SetActorPosition(ActivatorTID() + FXTIDList[RHFX_CRUSADERSHIELD3], GetActorX(0)  + 40 * cos(GetActorAngle(0) - 0.25), GetActorY(0) + 40 * sin(GetActorAngle(0) - 0.25), GetActorZ(0) + 8.0, 0);
		Delay(1);
		if(GetActorProperty(0, APROP_HEALTH) <= 0) {
			check = 1;
			break;
		}
	}
	CleanPlayerFX(ActivatorTID());
	if(!check) {
		int hp = GetActorProperty(0, APROP_HEALTH);
		int missing = (200 - hp) / 2;
		if(missing && hp < CRUSADER_HEAL_CAP) {
			if(hp + missing > CRUSADER_HEAL_CAP)
				GiveInventory("Stimpack", CRUSADER_HEAL_CAP - hp);
			else
				GiveInventory("Stimpack", missing);
			GiveInventory("HealFXSpawner", 1);
		}
	}
}

// Consecration Activation Script
Script 601 (void) {
	int thisactor = ActivatorTID(), counter = 0, curtid;
	// first give the initial damage/slow/haste
	for(int i = 0; i < MAXPLAYERS; i++) {
		curtid = PTID_BEGIN + i;
		if(fdistance(ActivatorTID(), curtid) <= CONSECRATION_DIST) {
			if(CheckActorInventory(curtid, "GoodTeam"))
				GiveActorInventory(curtid, "ConsecrationHaste", 1);
			else if(CheckActorInventory(curtid, "EvilTeam")) {
				// kjaroch debuff immunity
				if(!CheckActorInventory(curtid, "KjarochNetherForm")) {
					GiveActorInventory(curtid, "ConsecrationSlow", 1);
					GiveActorInventory(curtid, "ConsecrationDamageFX", 1);
					Thing_Damage2(curtid, GetPercent(MAXHPValues[GetClass(curtid)], CONSECRATION_PERCENT), MOD_EXIT);
				}
			}
			GiveActorInventory(curtid, "ConsecrationHealFX2", 1);
		}
	}
	// now constant area heal
	while(isAlive() && CheckInventory("ConsecrationRegenPower")) {
		for(int i = 0; i < MAXPLAYERS; i++) {
			curtid = PTID_BEGIN + i;
				if(curtid != thisactor && CheckActorInventory(curtid, "GoodTeam") && fdistance(ActivatorTID(), curtid) <= CONSECRATION_DIST)
					GiveActorInventory(curtid, "ConsecrationRegen", 1);
		}
		GiveInventory("ConsecrationRegen", 1);
		Delay(18);
		GiveInventory("ConsecrationRegen", 1);
		Delay(17);
	}
}

// Consecration Regen Script
Script 602 (void) {
	int hp = GetActorProperty(0, APROP_HEALTH), thisactor = ActivatorTID();
	if(IsAlive() && hp < MAXHPValues[GetClass(thisactor)]) {
		fadeto(160, 255, 160, 0.1, 0.5);
		Delay(5);
		fadeto(160, 255, 160, 0.0, 0.5);
		LocalAmbientSound("Crusader/SHeal2", 127);
		GiveInventory("ConsecrationHealFX", 1);
		hp = Clamp_Between(hp + CONSECRATION_REGEN, 1, MAXHPValues[GetClass(thisactor)]);
		SetActorProperty(0, APROP_HEALTH, hp);
	}
}

// Azagoth Lightning Script
Script 603 (void) {
	int time = AZAGOTH_CONE_TIME >> 1;
	for(int i = 0; i < time && IsAlive(); ++i) {
		GiveInventory("AzagothLightningShooter", 1);
		Delay(2);
	}
}

Script 604 (void) {
	int time = 0, pnum = PlayerNumber(), owner = ActivatorTID(), newtid, k, pang = GetActorAngle(0), counter = 0;
	for(k = 0; k < AZAGOTH_WHIP_COUNT; ++k) {
		newtid = (pnum + 1) * FXTIDList[RHFX_AZAGOTHWHIP] + k;
		Spawn("AzagothWhiplash", GetActorX(0), GetActorY(0), GetActorZ(0) + 32.0, newtid, 0);
		SetActivator(newtid);
		SetPointer(AAPTR_TARGET, owner);
		SetActivator(owner);
	}
	while(IsAlive() && time < AZAGOTH_WHIP_TIME << 1) {
		for(k = 0; k < AZAGOTH_WHIP_COUNT; ++k) {
			newtid = (pnum + 1) * FXTIDList[RHFX_AZAGOTHWHIP] + k;
			SetActorPosition(newtid, GetActorX(0) + (1 + k) * 16 * cos(pang + counter), GetActorY(0) +  (1 + k) * 16 * sin(pang + counter), GetActorZ(0) + 36.0 - (1 + k) * 16 * sin(GetActorPitch(0)) - 12 * sin((k * counter ) >> 1), 0);
		}
		Delay(1);
		counter = (counter % 1.0) + 1092; // 6 degrees
		if(!(time % 25))
			ActivatorSound("Azagoth/LashLoop", 127);
		++time;
	}
	for(k = 0; k < AZAGOTH_WHIP_COUNT; ++k) {
		newtid = (pnum + 1) * FXTIDList[RHFX_AZAGOTHWHIP] + k;
		Thing_Remove(newtid);
	}
}

// Azagoth Kill Heal
Script 605 (void) {
	int hp = GetActorProperty(0, APROP_HEALTH);
	SetActorProperty(0, APROP_HEALTH, hp + GetPercent(MaxHPValues[GetClass(ActivatorTID())] - hp, AZAGOTH_HEALPERCENT));
}

// Azagoth/Bane/Reaper Move/Ignite/Bleed Checker
Script 606 (int mode) {
	int count = 0, flip = 0;
	if(!mode) {
		while(count < AZAGOTH_MOVE_TIME << 1) {
			for(int i = 0; i < MAXPLAYERS; ++i) {
				int velx = GetActorVelX(i + PTID_BEGIN);
				int vely = GetActorVelY(i + PTID_BEGIN);
				if(CheckActorInventory(i + PTID_BEGIN, "AzagothMove") &&
				   (velx <= -AZAGOTH_MOVE_WINDOW || 
				   velx >= AZAGOTH_MOVE_WINDOW || 
				   vely <= -AZAGOTH_MOVE_WINDOW || 
				   vely >= AZAGOTH_MOVE_WINDOW)
				  ) 
				{
					if(GetClass(i + PTID_BEGIN) == C_CRUSADER)
						Thing_Damage2(i + PTID_BEGIN, (AZAGOTH_MOVE_DAMAGE & 1) + AZAGOTH_MOVE_DAMAGE >> 1, "AzagothMoveDamage");
					else
						Thing_Damage2(i + PTID_BEGIN, AZAGOTH_MOVE_DAMAGE, "AzagothMoveDamage");
				}
			}
			Delay(17);
			++count;
		}
	}
	else if(mode == 1) {
		while(1) {
			count = 0;
			for(int i = 0; i < MAXPLAYERS; ++i) {
				if(CheckActorInventory(i + PTID_BEGIN, "BaneIgniteDebuff")) {
					if(GetClass(i + PTID_BEGIN) == C_CRUSADER)
						Thing_Damage2(i + PTID_BEGIN, BANE_IGNITE_DAMAGE >> 1, "BaneIgnite");
					else
						Thing_Damage2(i + PTID_BEGIN, BANE_IGNITE_DAMAGE, "BaneIgnite");
					GiveActorInventory(i + PTID_BEGIN, "IgniteFXSpawner", 1);
					++count;
				}
			}
			if(!count)
				break;
			if(!flip)
				Delay(2);
			flip = !flip;
			Delay(11);
		}
		TakeInventory("BaneIgniteChecking", 1);
	}
	else {
		while(1) {
			count = 0;
			for(int i = 0; i < MAXPLAYERS; ++i) {
				if(CheckActorInventory(i + PTID_BEGIN, "ReaperBleed")) {
					int hp = GetActorProperty(i + PTID_BEGIN, APROP_HEALTH);
					hp = GetPercent(MAXHPValues[GetClass(i + PTID_BEGIN)] - hp, REAPER_BLEED_PERCENT);
					Thing_Damage2(i + PTID_BEGIN, (REAPER_BLEED_DAMAGE + hp) >> 2, "RazorBleed");
					if(GetClass(i + PTID_BEGIN) == C_COLOSSUS)
						GiveActorInventory(i + PTID_BEGIN, "ColossusBloodFXSpawner", 1);
					else
						GiveActorInventory(i + PTID_BEGIN, "BloodFXSpawner", 1);
					++count;
				}
			}
			if(!count)
				break;
			Delay(17);
		}
		TakeInventory("ReaperChecking", 1);
	}
}

// By IjonTichy, modified by Ivan
Script 607 (int mode) {
	int newtid = PlayerNumber() + AZAGOTH_FURNACETID;
	if(!mode) {
		Delay(1);
		Thing_ChangeTID(AZAGOTH_FURNACETID_INIT, newtid);
	}
	else {
		int thisactor = ActivatorTID();
		SetActivatorToTarget(0);
		int owner = ActivatorTID();
		int myx, myy, myz;
		int vx, vy, vz, magnitude, nx, ny, nz, victim, count, cond = 1;
		
		while(cond) {
			myx = GetActorX(thisactor);
			myy = GetActorY(thisactor);
			myz = GetActorZ(thisactor);
			if(mode == 1)
				cond = count < AZAGOTH_FURNACE_DURATION;
			else
				cond = !CheckActorInventory(owner, "AzagothBallHit");
			for(int i = 0; i < MAXPLAYERS; ++i) {
				if(CheckActorInventory(i + PTID_BEGIN, "AzagothFurnaceVictim")) {
					victim = i + PTID_BEGIN;
					vx = myx - GetActorX(victim);
					vy = myy - GetActorY(victim);
					vz = myz - GetActorZ(victim);

					magnitude = magnitudeThree(vx >> 16, vy >> 16, vz >> 16);

					if (magnitude) {
						nx = vx / magnitude; 
						ny = vy / magnitude; 
						nz = vz / magnitude;
					}
					else {
						nx = 0; 
						ny = 0; 
						nz = 0;
					}
					
					SetActorVelocity(victim, nx << 3, ny << 3, nz << 3, true, true);
				}
			}
			Delay(1);
			++count;
		}
	}
}

// Leash slowdown script
Script 608 (void) {
	int victim = CheckInventory("LeashVictimTID"), banetid = ActivatorTID(), count = 0, tics = 1;
	SetInventory("LeashVictimTID", 0);
	GiveInventory("BaneLeashLoopPlayer", 1);
	while(fdistance(victim, banetid) < BANE_LEASH_DISTANCE && count < BANE_LEASH_DURATION) {
		if(!(count % 17)) {
			SetActorProperty(victim, APROP_SPEED, GetActorProperty(0, APROP_SPEED) - 0.175 * tics);
			++tics;
		}
		Delay(1);
		++count;
	}
	GiveInventory("BaneLeashLoopStopper", 1);
	TakeActorInventory(victim, "BaneLeashDebuff", 1);
	SetActorProperty(victim, APROP_SPEED, 1.0);
	if(GetClass(victim) == C_CRUSADER) {
		if(count == BANE_LEASH_DURATION >> 1) {
			GiveActorInventory(victim, "BaneLeashSnarePlayer", 1);
			GiveActorInventory(victim, "BaneSnareWeak", 1);
			GiveActorInventory(victim, "BaneSnareFXSpawner", 1);
		}
	}
	else {
		if(count == BANE_LEASH_DURATION) {
			GiveActorInventory(victim, "BaneLeashSnarePlayer", 1);
			GiveActorInventory(victim, "BaneSnare", 1);
			GiveActorInventory(victim, "BaneSnareFXSpawner", 1);
		}
	}
}

// Leash Trail Form Script
Script 609 (void) CLIENTSIDE {
	int banetid = ActivatorTID(), victim = CheckInventory("LeashVictimTID"), count = 0;
	while(fdistance(victim, banetid) < BANE_LEASH_DISTANCE && count < BANE_LEASH_DURATION) {
		ACS_ExecuteAlways(610, 0, victim, banetid, 16);
		Delay(1);
		++count;
	}
}

// By IjonTichy, modified by Ivan
Script 610 (int victimTid, int playerTid, int density) CLIENTSIDE {
    int plX; int plY;  int plZ;
    int grX; int grY;  int grZ;
    int vX;  int vY;   int vZ;
    int nX;  int nY;   int nZ;
    int bX;  int bY;   int bZ;
    int magnitude;
    int pointCount;
    int pointOffset;

    plX = GetActorX(playerTid); grX = GetActorX(victimTid);
    plY = GetActorY(playerTid); grY  = GetActorY(victimTid);
    plZ = GetActorZ(playerTid); grZ  = GetActorZ(victimTid);
    vX   = grX - plX;       vY   = grY - plY;       vZ   = grZ - plZ;

    magnitude = magnitudeThree(vX >> 16, vY >> 16, vZ >> 16);

    pointCount  = magnitude / density;
    pointOffset = magnitude - (pointCount * density);

    if (magnitude != 0)
    {
        nX = vX / magnitude; nY = vY / magnitude; nZ = vZ / magnitude;

        int i; int j;
        for (i = 0; i < pointCount; i++)
        {
            j = (i * density) + pointOffset;

            bX = (nX * j) + plX;
            bY = (nY * j) + plY;
            bZ = (nZ * j) + plZ;

            Spawn("BaneLeashTrail", bX, bY, bZ + 32.0);
        }
    }
}

Script 611 (void) {
	SetResultValue(ActivatorTID());
}

Script 612 (void) NET {
	if(GetClass(ActivatorTID()) != C_HUNTER)
		Terminate;
	int input;
	int angle;
	int velX;
	int velY;
	int velZ;
	int dashed = 0;
	
	if(CanMove() && !CheckInventory("DashCooldown") && (CheckInventory("Energy") >= DH_DASH_ENERGY || CheckInventory("FinalHourSpeed"))) {
		input = GetPlayerInput(-1, INPUT_BUTTONS);
		
		for(int i = 0; i < 4; ++i) {
			if(input & settings[i][0]) {
				angle = GetActorAngle(0) + settings[i][1];
				
				if(GetActorZ(0) - GetActorFloorZ(0) > 0) {
					velX = FixedMul(cos(angle), SD_DASHSPEED);
					velY = FixedMul(sin(angle), SD_DASHSPEED);
					velZ = -GetActorVelZ(0) + SD_DASHJUMP;
				}
				
				else {
					velX = FixedMul(cos(angle), SD_DASHSTRONG);
					velY = FixedMul(sin(angle), SD_DASHSTRONG);
					velZ = 1.5;
				}
				
				SetActorVelocity(0, velX, velY, velZ, true, false);
				dashed = 1;
			}
		}
		if(dashed) {
			ActivatorSound("Reaper/Dash", SD_SOUNDVOLUME);
			GiveInventory("DashEffect", 1);
			GiveInventory("DashCooldown", 1);
			if(!CheckInventory("FinalHourSpeed"))
				TakeInventory("Energy", DH_DASH_ENERGY);
		}
	}
}

Script 613 (void) {
	int prev = GetActorProperty(0, APROP_JUMPZ);
	SetActorProperty(0, APROP_JUMPZ, 0);
	while(CheckInventory("ReaperSnare")) {
		Delay(1);
	}
	SetActorProperty(0, APROP_JUMPZ, prev);
}

Script 614 (int mode) {
	int owner = GetActorProperty(0, APROP_MASTERTID);
	if(!mode) {
		GiveActorInventory(owner, "GunTrapCount", 1);
		SetPointer(AAPTR_MASTER, owner);
		Thing_ChangeTID(0, owner + REAPER_GUN_TID);
	}
	else
		TakeActorInventory(owner, "GunTrapCount", 1);
}

// Randomly spawn souls around Demon Hunter when Final Hour is on
Script 615 (void) CLIENTSIDE {
	while(CheckInventory("FinalHourSpeed")) {
		GiveInventory("FinalHourBuffFXSpawner", 1);
		Delay(5);
	}
}

// Prophet Damage script
Script 616 (void) {
	str dmglvl;
	int hp;
	// use strparam to generate current bonus, remove any previous
	while(isAlive()) {
		hp = GetMissingHealthPercent(ActivatorTID(), C_PROPHET);
		// hp is now the percent of life missing
		if(hp) {
			dmglvl = StrParam(s:"Prophet_Damage", d:hp);
			if(!CheckInventory(dmglvl)) {
				for(int i = 1; i < 100; ++i)
					TakeInventory(StrParam(s:"Prophet_Damage", d:i), 1);
				Clamp_Between(hp, 1, 100);
				GiveInventory(dmglvl, 1);
			}
		}
		Delay(10);
	}
}

// Clientside Prophet dmg buff
Script 617 (void) CLIENTSIDE {
	if(ConsolePlayerNumber() != PlayerNumber()) Terminate;
	int hp;
	str textcolor;
	// use strparam to generate current bonus, remove any previous
	while(isAlive()) {
		int cx = 506.1, cy = 390.0;
		if(paspect == ASPECT_5_4) {
			cy += 16.0;
		}
		else if(paspect == ASPECT_16_9) {
			cx += 106.0;
		}
		else if(paspect == ASPECT_16_10) {
			cx += 64.0;
		}
		hp = MAXHPValues[C_PROPHET] - GetActorProperty(0, APROP_HEALTH);
		hp *= 100;
		hp /= MAXHPValues[C_PROPHET];
		// hp is now the percent of life missing
		if(hp) {
			SetFont("OBJFONT");
			SetHudSize(640, 480, 0);
			if(hp < 25)
				textcolor = "\cd";
			else if(hp < 50)
				textcolor = "\ck";
			else if(hp < 75)
				textcolor = "\ci";
			else
				textcolor = "\cg";
			HudMessage(s:"Damage Bonus: ", s:textcolor, d:hp, s:"%\c-"; HUDMSG_PLAIN, PROPHET_HUD_ID, CR_WHITE, cx, cy, 0);
		}
		Delay(10);
	}
	HudMessage(s:""; HUDMSG_PLAIN, PROPHET_HUD_ID, -1, 0.0, 0.0, 1);
}

// Prophet holy missile
Script 618 (int buffed) {
	int tid, mx = GetActorX(0), my = GetActorY(0), mz = GetActorZ(0);
	SetActivatorToTarget(0);
	for(int i = 0; i < MAXPLAYERS; ++i) {
		tid = i + PTID_BEGIN;
		if(!CheckActorInventory(tid, "ProphetResist") &&
		   !CheckActorInventory(tid, "ProphetDamage") &&
		   fdistancexyz(mx, my, mz, tid) <= PROPHET_IMPACT_RANGE
		  ) 
		  {
			  if(CheckActorInventory(tid, "GoodTeam")) {
				  GiveActorInventory(tid, "ProphetPowerGiver", 1);
				  if(buffed)
					  GiveActorInventory(tid, "Stimpack", PROPHET_HEAL * 10);
			  }
			  else {
				  if(buffed)
					  Thing_Damage2(tid, GetPercent(MAXHPValues[GetClass(tid)], PROPHET_DAMAGE_PERCENT2), "ProphetHoly");
				  else
					  Thing_Damage2(tid, GetPercent(MAXHPValues[GetClass(tid)], PROPHET_DAMAGE_PERCENT), "ProphetHoly");
				  GiveActorInventory(tid, "ProphetHolyFXSpawner", 1);
			  }
		  }
	}
}

// Prophet Buff rotation
Script 619 (void) {
	GiveInventory("ProphetResist", 1);
	GiveInventory("ProphetResistFXSpawner", 1);
	Delay(35 * PROPHET_RESIST_TIME);
	GiveInventory("ProphetDamage", 1);
	GiveInventory("ProphetDamageFXSpawner", 1);
}

// Holysight Reveal script
Script 620 (void) CLIENTSIDE {
	if(ConsolePlayerNumber() != PlayerNumber()) Terminate;
	while(isAlive() && CheckInventory("HolySightBuff")) {
		for(int i = 0; i < MAXPLAYERS; ++i) {
			if(CheckActorInventory(i + PTID_BEGIN, "EvilTeam") && IsAliveTID(i + PTID_BEGIN))
				HudMessageOnActor(i + PTID_BEGIN, PROPHET_SIGHT_RANGE, "HOLYMARK", 0, 1024, 768, PROPHET_HUD_ID_BEG + i);
			else
				HudMessage(s:" "; HUDMSG_PLAIN, PROPHET_HUD_ID_BEG + i, -1, 0, 0, 0);
		}
		Delay(1);
	}
	for(int i = 0; i < MAXPLAYERS; ++i)
		HudMessage(s:" "; HUDMSG_PLAIN, PROPHET_HUD_ID_BEG + i, -1, 0, 0, 0);
}

Script 621 (void) CLIENTSIDE {
	int tid = ActivatorTID() + FXTIDListClientside[RHCFX_HOLYSIGHTICON];
	do {
		delay(1);
   } until (Spawn("HolySightFX", GetActorX(0), GetActorY(0), GetActorZ(0), tid));
	while(isAlive() && CheckInventory("HolySightBuff")) {
		SetActorPosition(tid, GetActorX(0), GetActorY(0), GetActorZ(0) + 56.0, 0);
		Delay(1);
	}
	SetActorState(tid, "Fade");
}

// I HAVE NO IDEA WHY BUT IT WORKS BETTER THIS WAY IN CLIENTSIDE
Script 622 (void) CLIENTSIDE {
	int owner = ActivatorTID(), tid, wep = 0;
	// take away weapons
	if(CheckWeapon("Farseer_Dark"))
		wep = 1;
	GiveInventory("Farseer_Holy_Auto", 1);
	GiveInventory("Farseer_Dark_Auto", 1);
	TakeInventory("Farseer_Holy", 1);
	TakeInventory("Farseer_Dark", 1);
	if(wep)
		SetWeapon("Farseer_Dark_Auto");
	while(isAlive() && CheckInventory("HolySightBuff")) {
		// find enemy closest to us
		if(GetPlayerInput(-1, INPUT_BUTTONS) & BT_ATTACK) {
			int candidate = 0, cand_dist = 0x7FFFFFFF;
			for(int i = 0; i < MAXPLAYERS; ++i) {
				tid = i + PTID_BEGIN;
				if(owner != tid && CheckActorInventory(tid, "EvilTeam") && CheckSight(owner, tid, CSF_NOBLOCKALL)) {
					int dist = fdistance(owner, tid);
					if(cand_dist > dist) {
						candidate = tid;
						cand_dist = dist;
					}
				}
			}
			if(candidate) {
				// face this guy now
				for(int i = 0; i < PROPHET_FACE_COUNT; ++i) {
					FaceActor(owner, candidate);
					Delay(1);
				}
			}
		}
		Delay(1);
	}
	// give back
	if(CheckWeapon("Farseer_Dark_Auto"))
		wep = 1;
	GiveInventory("Farseer_Holy", 1);
	GiveInventory("Farseer_Dark", 1);
	TakeInventory("Farseer_Holy_Auto", 1);
	TakeInventory("Farseer_Dark_Auto", 1);
	if(wep)
		SetWeapon("Farseer_Dark");
}

// Colossus Melee Script
Script 623 (void) {
	int owner = ActivatorTID(), tid, stop = 0, tries = 0;
	while(isAlive() && !stop && tries < COLOSSUS_MELEE_TRIES) {
		// find enemy closest to us
		int candidate = 0, cand_dist = COLOSSUS_MELEE_DIST;
		for(int i = 0; i < MAXPLAYERS; ++i) {
			tid = i + PTID_BEGIN;
			if(owner != tid && CheckActorInventory(tid, "GoodTeam") && MaxAngleDiff(owner, tid, COLOSSUS_MELEE_ANGLE) && CheckSight(owner, tid, CSF_NOBLOCKALL)) {
				int dist = fdistance(owner, tid);
				if(cand_dist > dist) {
					candidate = tid;
					cand_dist = dist;
				}
			}
		}
		
		// look for possible targets besides players now (GunTrap of Reaper for example)
		if(!candidate) {
			cand_dist = COLOSSUS_MELEE_DIST;
			for(int i = 0; i < MAXPLAYERS; ++i) {
				tid = i + PTID_BEGIN + REAPER_GUN_TID;
				if(MaxAngleDiff(owner, tid, COLOSSUS_MELEE_ANGLE) && CheckSight(owner, tid, CSF_NOBLOCKALL)) {
					int dist = fdistance(owner, tid);
					if(cand_dist > dist) {
						candidate = tid;
						cand_dist = dist;
					}
				}
			}
		}
		
		if(candidate) {
			// damage this guy
			// FaceActor(owner, candidate);
			GiveActorInventory(candidate, "ColossusHitFX", 1);
			Thing_Damage2(candidate, COLOSSUS_MELEE_DMG, "ColossusMelee");
			stop = 1;
		}
		Delay(1);
		++tries;
	}
}

Script 624 (void) {
	SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
	while(isAlive() && (CheckInventory("ColossusStun") || CheckInventory("ColossusStunWeak")))
		Delay(1);
	SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
}

Script 625 (void) {
	SetResultValue(CheckInventory("Landed"));
}

Script 626 (void) {
	while(isAlive()) {
		GiveInventory("ColossusLandChecker", 1);
		Delay(4);
	}
}

Script 627 (void) {
	int count = 0, angle, jumpz = GetActorProperty(0, APROP_JUMPZ), rate;
	SetActorProperty(0, APROP_JUMPZ, 0);
	SetPlayerProperty(0, 1, PROP_FROZEN);
	GiveInventory("Rampaging", 1);
	TakeInventory("Colossus Fist", 1);
	TakeInventory("Ranged Attacks", 1);
	GiveInventory("Colossus Running", 1);
	while(isAlive() && !CheckInventory("StopRampage") && count < COLOSSUS_RAMPAGE_TIME) {
		angle = GetActorAngle(0);
		int velx = cos(angle) << 4;
		int vely = sin(angle) << 4;
		rate = FixedDiv((100.0 + 0.5714 * Clamp_Between(count, 0, COLOSSUS_MAX_GAIN_TIME)), 100.0); // 20% / 35 = 0.5714
		velx = FixedMul(velx, rate);
		vely = FixedMul(vely, rate);
		SetActorVelocity(0, velx, vely, GetActorVelZ(0), 0, 0);
		GiveInventory("RampageStopChecker", 1);
		if(count >= 70)
			GiveInventory("RampageDamagerKiller", 1);
		else
			GiveInventory("RampageDamager", 1);
		Delay(1);
		++count;
		if(!(count % 35))
			GiveInventory("RampageLevel", 1);
	}
	SetActorProperty(0, APROP_JUMPZ, jumpz);
	GiveInventory("TurnPainOn", 1);
	GiveInventory("Colossus Fist", 1);
	GiveInventory("Ranged Attacks", 1);
	TakeInventory("Colossus Running", 1);
	GiveInventory("ColossusStopped", 1);
	TakeInventory("Rampaging", 1);
	TakeInventory("StopRampage", 1);
	TakeInventory("RampageSpeed", 1);
	SetInventory("RampageLevel", 0);
	SetPlayerProperty(0, 0, PROP_FROZEN);
}

// Warlock value returns + key press
Script 628 (int type) {
	if(!type)
		SetResultValue(GetPlayerInput(-1, INPUT_BUTTONS) & BT_ATTACK);
	else if(type == 1)
		SetResultValue(WARLOCK_DSTAFF_MANA - WARLOCK_DSTAFF_GAIN * Clamp_Between(CheckInventory("WarlockSouls"), 0, WARLOCK_DSTAFF_MAXGAIN));
	else if(type == 2)
		SetResultValue(WARLOCK_DSTAFF_MANA + WARLOCK_DSTAFF_CHARGE_MANA - WARLOCK_DSTAFF_GAIN * Clamp_Between(CheckInventory("WarlockSouls"), 0, 2 * WARLOCK_DSTAFF_MAXGAIN));
	else if(type == 3) {
		SetActivatorToTarget(0);
		SetResultValue(WARLOCK_BLADE_GAIN * CheckInventory("WarlockSouls"));
	}
	else if(type == 4) {
		SetResultValue(WARLOCK_BOOM_GAIN * CheckInventory("WarlockSouls"));
	}
}

Script 629 (void) {
	Delay(WARLOCK_LINK_COOLDOWN - CheckInventory("WarlockSouls") * WARLOCK_LINK_SOULDROP - 1);
	TakeInventory("WarlockLinkCooldown", 1);
}

// Warlock shield things
Script 630 (void) {
	// Give his armor
	GiveInventory("WarlockShieldBonus", WARLOCK_SHIELD_BASE + WARLOCK_SHIELD_GAIN * CheckInventory("WarlockSouls"));
	for(int i = 0; i < WARLOCK_SHIELD_TIME && CheckInventory("Armor"); ++i)
		Delay(1);
	if(!CheckInventory("Armor"))
		GiveInventory("WarlockRepel", 1);
	TakeInventory("Armor", 0x7FFF);
}

// Summon warlock shield
Script 631 (int mode) CLIENTSIDE {
	int tid = ActivatorTID();
	if(!mode) {
		do {
			delay(1);
		} until(Spawn("WarlockShieldFX", GetActorX(0), GetActorY(0), GetActorZ(0) + 32.0, tid + FXTIDList[RHFX_WARLOCKSHIELD]));
		for(int i = 0; i < WARLOCK_SHIELD_TIME && CheckInventory("Armor"); ++i ) {
			SetActorPosition(tid + FXTIDList[RHFX_WARLOCKSHIELD], GetActorX(0), GetActorY(0), GetActorZ(0) + 32.0, 0);
			Delay(1);
		}
		Thing_Remove(tid + FXTIDList[RHFX_WARLOCKSHIELD]);
	}
	else {
		// warlock passive souls
	}
}

Script 632 (int mode) {
	if(!mode) {
		if(!StrICmp("Death Staff", GetWeapon()))
			SetPlayerProperty(0, 1, PROP_INSTANTWEAPONSWITCH);
		TakeInventory("WarlockSpells", 1);
		TakeInventory("Death Staff", 1);
		GiveInventory("DeathRay", 1);
	}
	else {
		for(int i = 0; isAlive() && i < WARLOCK_RAY_TIME + WARLOCK_RAY_TIMEGAIN * CheckInventory("WarlockSouls"); ++i) {
			ACS_ExecuteAlways(633, 0, ActivatorTID(), 8);
			GiveInventory("WarlockPusher", 1);
			Delay(1);
		}
		TakeInventory("DeathRayOn", 1);
		SetPlayerProperty(0, 1, PROP_INSTANTWEAPONSWITCH);
		GiveInventory("DeathRayStopper", 1);
		GiveInventory("Death Staff", 1);
		GiveInventory("WarlockSpells", 1);
		TakeInventory("DeathRay", 1);
		SetPlayerProperty(0, 0, PROP_INSTANTWEAPONSWITCH);
	}
}

// By IjonTichy, modified by Ivan
Script 633 (int playerTid, int density) {
	int ang = GetActorAngle(playerTid);
	int souls = CheckInventory("WarlockSouls");
    int vX;  int vY;   int vZ;
    int nX;  int nY;   int nZ;
    int bX;  int bY;   int bZ;
    int magnitude;
    int pointCount;
    int pointOffset;
	
    vX   = (WARLOCK_RAY_RANGE + WARLOCK_RAY_RANGEGAIN * souls) * cos(ang);
	vY   = (WARLOCK_RAY_RANGE + WARLOCK_RAY_RANGEGAIN * souls) * sin(ang);
	vZ   = 0;

    magnitude = magnitudeThree(vX >> 16, vY >> 16, vZ >> 16);

    pointCount  = magnitude / density;
    pointOffset = magnitude - (pointCount * density);

    if (magnitude != 0)
    {
        nX = vX / magnitude; nY = vY / magnitude; nZ = vZ / magnitude;

        int i; int j;
        for (i = 2; i < pointCount + 2; i++)
        {
            j = (i * density) + pointOffset;

            bX = (nX * j) + GetActorX(playerTid);
            bY = (nY * j) + GetActorY(playerTid);
            bZ = (nZ * j) + GetActorZ(playerTid) - j * sin(GetActorPitch(playerTid));

            Spawn("DeathRayDamager", bX, bY, bZ + 36.0, playerTid + FXTIDList[RHFX_WARLOCKDEATHRAY]);
			SetActivator(playerTid + FXTIDList[RHFX_WARLOCKDEATHRAY]);
			SetPointer(AAPTR_TARGET, playerTid);
        }
    }
}

Script 634 (void) {
	// Weapon frame delay
	Delay(8);
	int jz = GetActorProperty(0, APROP_JUMPZ);
	SetActorProperty(0, APROP_JUMPZ, 0);
	while(isAlive() && CheckInventory("KjarochStand") && !(GetPlayerInput(-1, INPUT_BUTTONS) & BT_ALTATTACK))
		Delay(2);
	GiveInventory("KjarochCancel", 1);
	while(CheckInventory("KjarochFinished"))
		Delay(1);
	SetActorProperty(0, APROP_JUMPZ, jz);
	TakeInventory("KjarochCancel", 1);
}

Script 635 (void) {
	if(isAlive()) {
		int owner = ActivatorTID(), target, servid, powercount = 0;
		for(int i = 0; i < MAXPLAYERS; ++i) {
			target = i + PTID_BEGIN;
			if(owner != target && CheckActorInventory(target, "GoodTeam")) {
				int success = 0, servid = KJAROCH_SERVANTMULT * owner + i;
				if(CheckSight(owner, target, CSF_NOBLOCKALL)) {
					// if sight, spawn near kjaroch
					success = SpawnAreaTID(owner, KJAROCH_ULT_DISTANCE, 4.0, "KjarochServant", servid, 180.0, 0);
				}
				else {
					// if no sight, spawn near target
					success = SpawnAreaTID(target, KJAROCH_ULT_DISTANCE, 4.0, "KjarochServant", servid, 180.0, 0);
				}
				// if success hate the corresponding target player
				if(success) {
					++powercount;
					Thing_Hate(servid, target, 6);
					GiveActorInventory(servid, "HateTID", target);
					SetActivator(servid);
					SetActorProperty(0, APROP_MASTERTID, owner);
					// 3.0 has these :)
					SetPointer(AAPTR_MASTER, owner);
					SetPointer(AAPTR_TARGET, target);
					SetActivator(owner);
				}
			}
		}
		if(powercount > 5)
			powercount = 5;
		GiveInventory(StrParam(s:"KjarochHauntResist_", d:powercount), 1);
	}
}

Script 636 (void) {
	int target = CheckInventory("HateTID"), count = 0, owner = GetActorProperty(0, APROP_MASTERTID);
	while(isAliveTID(target) && count < KJAROCH_SERVANT_LASTTIME) {
		Delay(KJAROCH_SERVANT_CHECKTIME);
		++count;
		if(!isAliveTID(owner)) {
			DamageThing(9999, MOD_EXIT);
			break;
		}
		if(!isAlive())
			Terminate;
	}
	if(count >= KJAROCH_SERVANT_LASTTIME) {
		DamageThing(9999, MOD_EXIT);
		Terminate;
	}
	int hp = Clamp_Between(GetPercent(GetActorProperty(0, APROP_HEALTH), KJAROCH_HEAL_PERCENT), KJAROCH_MIN_HEAL, KJAROCH_MAX_HEAL);
	DamageThing(9999, MOD_EXIT);
	SetActivator(owner);
	ActivatorSound("Kjaroch/HauntHeal", 127);
	GiveInventory("KjarochHealFXSpawner", 1);
	HealThing(hp);
}

Script 637 (void) {
	int thisactor = ActivatorTID();
	while(isAlive()) {
		int hp = Clamp_Between(GetMissingHealthPercent(thisactor, C_KJAROCH), 0, KJAROCH_PASSIVE_LIMIT);
		SetActorProperty(0, APROP_SPEED, 1.0 + KJAROCH_PASSIVE_GAIN * hp);
		if(hp == KJAROCH_PASSIVE_LIMIT) {
			GiveInventory("KjarochNetherForm", 1);
			SetActorProperty(0, APROP_ALPHA, 0.5);
			GiveInventory("KjarochAntiSeek", 1);
			// kjaroch can heal himself through ult
//			break;
		}
		else if(CheckInventory("KjarochNetherForm")) {
			TakeInventory("KjarochNet", 1);
			SetActorProperty(0, APROP_ALPHA, 1.0);
			GiveInventory("KjarochSeekBack", 1);
		}
		Delay(5);
	}
}

// Warp damage disorientation
Script 638 (void) {
	if(!CheckInventory("KjarochWarpDamageCooldown")) {
		GiveInventory("KjarochWarpDamageCooldown", 1);
		int randVal = Clamp_Between(random(0, 0x7FFFFFFF) & 255, 0, KJAROCH_WARP_RANDMAX);
		int velx = GetActorVelX(0) + (random(0, 255) << 10);
		int vely = GetActorVelY(0) + (random(0, 255) << 10);
		int velz = Clamp_Between(GetActorVelZ(0) + (randVal << 11), 0, KJAROCH_WARP_VELZMAX);
		SetActorAngle(0, GetActorAngle(0) + random(0, 255) << 20);
		SetActorVelocity(0, velx, vely, velz, 0, 0);
	}
}

// returns a velocity in Z dimension to rise/lower to the target
Script 639 (int mode) {
	int this_z = GetActorZ(0);
	SetActivatorToTarget(0);
	int targ_z = GetActorZ(0);
	if(!mode)
		SetResultValue(targ_z - this_z < 0);
	else
		SetResultValue(abs(targ_z - this_z) >> 16 >= 16);
}

Script 640 (int type) CLIENTSIDE {
	if(!type)
		SetResultValue(GetPlayerInput(-1, INPUT_BUTTONS) & BT_ATTACK);
}

// Generic Cooldown Checker Script
Script 700 (void) CLIENTSIDE {
	if(ConsolePlayerNumber() != PlayerNumber()) Terminate;
	int ctype = GetClass(ActivatorTID());
	while(IsAlive()) {
		int bits = CheckInventory("CooldownBits");
		for(int i = 0; i < ClassCooldownsMaxCount[ctype]; ++i) {
			if(!CheckBit(bits, i) && CheckInventory(ClassCooldowns[ctype][i])) {
				bits |= 1 << i;
				SetInventory("CooldownBits", bits);
				ACS_ExecuteAlways(701, 0, ctype, i, CheckInventory("WarlockSouls"));
			}
		}
		Delay(1);
	}
	CleanClientsideStuff(PlayerNumber());
}

// Actual countdown display
Script 701 (int ctype, int bit, int wsouls) CLIENTSIDE {
	if(ConsolePlayerNumber() != PlayerNumber()) Terminate;
	SetHudSize(640, 480, 0);
	SetFont("OBJFONT");
	int limit = ClassCooldownValues[ctype][bit];
	if(ctype == C_WARLOCK && !bit) // first cooldown of warlock can be reduced by souls
		limit -= WARLOCK_LINK_SOULDROP * wsouls / TICRATE;
	for(int i = 0; i < limit; ++i) {
		int cx = 528.1, cy = 464.0;
		if(paspect == ASPECT_5_4) {
			cy	+= 16.0;
		}
		else if(paspect == ASPECT_16_9) {
			cx += 106.0;
		}
		else if(paspect == ASPECT_16_10) {
			cx += 64.0;
		}
		HudMessage(s:ClassCooldownText[ctype][bit], s:": ", d:limit - i; HUDMSG_PLAIN, COOLDOWN_HUD_ID + bit, CR_WHITE, cx, cy - 16.0 * bit, 0);
		Delay(TICRATE);
	}
	HudMessage(s:" "; HUDMSG_PLAIN, COOLDOWN_HUD_ID + bit, CR_WHITE, 520.0, 440.0, 1);
	SetInventory("CooldownBits", CheckInventory("CooldownBits") ^ (1 << bit));
}

// Buff giving script + other things
Script 702 (int buffnum) CLIENTSIDE {
	if(ConsolePlayerNumber() != PlayerNumber()) Terminate;
	while(isAlive()) {
		int bcount = 0, dcount = 0;
		SetHudSize(1024, 768, 0);
		for(int i = 0; i < MAXBUFFTYPES; ++i) {
			int cxl = 992.0, cy = 70.0, cxr = 944.0;
			if(paspect == ASPECT_5_4) {
				cy -= 24.0;
			}
			if(CheckInventory(BuffTypes[i])) {
				SetFont(BuffIcons[i]);
				if(i >= DEBUFF_BEGIN) {
					HudMessage(s:"A"; HUDMSG_PLAIN, BUFF_HUD_ID + i, -1, cxl, cy + 48.0 * dcount, 0);
					++dcount;
				}
				else {
					HudMessage(s:"A"; HUDMSG_PLAIN, BUFF_HUD_ID + i, -1, cxr, cy + 48.0 * bcount, 0);
					++bcount;
				}
			}
			else
				HudMessage(s:""; HUDMSG_PLAIN, BUFF_HUD_ID + i, -1, 600.0, 32.0, 0);
		}
		// check ultimate
		if(CheckInventory("UltimateCharge") == 100 && !CheckInventory("UltimateReady")) {
			GiveInventory("UltimateReady", 1);
			LocalAmbientSound("Ultimate/Ready", 127);
			SetFont("BIGFONT");
			SetHudSize(640, 480, 0);
			HudMessage(s:"Ultimate Ready!"; HUDMSG_PLAIN, ULTMSG_NOTREADY_ID, CR_ORANGE, 240.1, 440.0, 1.5);
		}
		Delay(1);
	}
}

Script 703 (void) NET {
	int pclass = GetClass(ActivatorTID()), state = 0;
	if(!CheckInventory("Reloading")) {
		if(pclass == C_HUNTER) {
			if(CheckInventory("ReaperShell") < 8)
				state = 1;
		}
		else if(pclass == C_PROPHET) {
			if(CheckInventory("ProphetClip") < 6)
				state = 1;
		}
		if(state)
			GiveInventory("ReloadToken", 1);
	}
}

// Transfer tid's velocity to current actor
Script 704 (int classtype) {
	int tid = CLASS_CORPSE_TID + ActivatorTID();
	str corpsename = CorpseNames[classtype];
	Spawn(corpsename, GetActorX(0), GetActorY(0), GetActorZ(0), tid);
	SetActorVelocity(tid, GetActorVelX(0), GetActorVelY(0), GetActorVelZ(0), 0, 0);
	Thing_SetTranslation(tid, -1);
}

// Display Weapon tip
Script 705 (int id) CLIENTSIDE {
	if (GetCVAR("rh_notips"))
		Terminate;
    SetHudSize(640, 480, true);
    SetFont("SMALLFONT");
    HudMessage(s: Weapon_Messages[id]; HUDMSG_FADEOUT, WEAPON_TIP_ID, CR_WHITE, 32.1, 8.1, 5.0, 0.5);
	HudMessage(s: Weapon_Messages[id + 1]; HUDMSG_FADEOUT, WEAPON_TIP_ID + 1, CR_WHITE, 32.1, 32.1, 5.0, 0.5);
}


// Class tip
Script 706 (void) NET CLIENTSIDE {
	int ctype = GetClass(ActivatorTID()) << 1;
    SetHudSize(640, 480, true);
    SetFont("SMALLFONT");
    HudMessage(s: Class_Tip[ctype]; HUDMSG_FADEOUT, WEAPON_TIP_ID, CR_WHITE, 32.1, 8.1, 5.0, 0.5);
	HudMessage(s: Class_Tip[ctype + 1]; HUDMSG_FADEOUT, WEAPON_TIP_ID + 1, CR_WHITE, 32.1, 24.1, 5.0, 0.5);
}

// Toggle special FX
Script 707 (void) NET CLIENTSIDE {
	if(!GetCVar("rh_nofx")) {
		SetFont("SMALLFONT");
		HudMessage(s:"Special Effects Off"; HUDMSG_FADEINOUT | HUDMSG_LOG, 1, CR_WHITE, 0.5, 0.24, 1.2, 0.5, 0.35);
		SetCVar("rh_nofx", 1);
	}
	else {
		SetFont("SMALLFONT");
		HudMessage(s:"Special Effects On"; HUDMSG_FADEINOUT | HUDMSG_LOG, 1, CR_GOLD, 0.5, 0.24, 1.2, 0.5, 0.35);
		SetCVar("rh_nofx", 0);
	}
	Delay(5);
}

Script 708 (void) NET CLIENTSIDE {
	while(1) {
		if(ConsolePlayerNumber() != PlayerNumber()) Terminate;
		if(GetCVar("rh_nofx"))
			Thing_Remove(EYECANDY_TID);
		Delay(1);
	}
}

/////////////////
// MENU
////////////////

Script 994 (void) {
	while(isAlive() && CheckInventory ("ShowingMenu")) {
		int bpress = GetPlayerInput(-1, INPUT_BUTTONS);
		int obpress = GetPlayerInput(-1, INPUT_OLDBUTTONS);
		int curposy = CheckInventory("MenuPosY");
		if(IsButtonPressed(bpress, obpress, BT_BACK)) {
			if(curposy == MENU_MAXPOS)
				SetInventory("MenuPosY", 0);
			else
				GiveInventory("MenuPosY", 1);
			LocalAmbientSound("HelpMenu/Page", 127);
		}
		else if(IsButtonPressed(bpress, obpress, BT_FORWARD)) {
			if(!curposy)
				SetInventory("MenuPosY", MENU_MAXPOS);
			else
				TakeInventory("MenuPosY", 1);
			LocalAmbientSound("HelpMenu/Page", 127);
		}
		else if(IsButtonPressed(bpress, obpress, BT_USE) || IsButtonPressed(bpress, obpress, BT_ATTACK)) {
			GiveInventory("Clicked", 1);
			while(CheckInventory("Clicked"))
				Delay(1);
			SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
			ClassMenuOpened[ActivatorTID()] = 0;
			SetInventory("ShowingMenu", 0);
			SetInventory("MenuPosY", 0);
			ACS_ExecuteAlways(995, 0, 0);
			LocalAmbientSound("HelpMenu/Close", 127);
			Terminate;
		}
		else if(IsButtonPressed(bpress, obpress, BT_ALTATTACK)) {
			SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
			ClassMenuOpened[ActivatorTID()] = 0;
			SetInventory("ShowingMenu", 0);
			SetInventory("MenuPosY", 0);
			ACS_ExecuteAlways(995, 0, 0);
			LocalAmbientSound("HelpMenu/Close", 127);
			Terminate;
		}
		Delay(1);
	}
}

Script 995 (int mode) CLIENTSIDE {
	if(ConsolePlayerNumber() != PlayerNumber()) Terminate;
	if(!mode) {
		ClearClassMenu();
	}
	else {
		int curposy, framecounter = 0, frameindex = 0;
		clearhudmessage(RH_SELECT_ID);
		while(CheckInventory("ShowingMenu") && isAlive()) {
			curposy = CheckInventory("MenuPosY");
			SetHudSize(800, 600, 0);
			str curpic = "ZEALMENU", text = "ZEALOT CLASS MENU";
			int add = 0;
			if(PlayerTeam()) {
				curpic = "GOLGMENU";
				text = "GOLGOTHAN CLASS MENU";
				add = MENU_MAXPOS + 1;
			}
			SetFont(curpic);
			HudMessage(s:"A"; HUDMSG_PLAIN, RH_CLASSMENU_ID, CR_UNTRANSLATED, 400.0, 300.0, 0);
			curpic = "CLASSBOX";
			SetFont(curpic);
			HudMessage(s:"A"; HUDMSG_PLAIN, RH_CLASSBOX_ID, CR_UNTRANSLATED, 640.0, 300.0, 0, 0);
			SetFont("CLASSFONT");
			SetHudSize(640, 480, 0);
			curpic = "ZEALOT CLASS MENU";
			HudMessage(s:text; HUDMSG_PLAIN, RH_CLASSTOP_ID, CR_ORANGE, 320.4, 96.0, 0, 0);
			SetHudSize(800, 600, 0);
			HudMessage(s:"* Use \cvforward/backward\c- keys to move"; HUDMSG_PLAIN, RH_BUTTON_ID, CR_YELLOW, 40.1, 552.0, 0);
			HudMessage(s:"* Use \cvuse/fire\c- keys to select"; HUDMSG_PLAIN, RH_BUTTON_ID + 1, CR_YELLOW, 40.1, 568.0, 0);
			HudMessage(s:"* Use \cvmenu key/alt fire\c- to exit"; HUDMSG_PLAIN, RH_BUTTON_ID + 2, CR_YELLOW, 40.1, 584.0, 0);
			for(int i = 0; i <= MENU_MAXPOS; ++i) {
				text = ClassNames[i + add];
				if(i == curposy)
					HudMessage(s:"\cf>>> \c- ", s:text; HUDMSG_PLAIN, RH_CLASSTEXT_ID + i, CR_GREEN, 300.1, 240.0 + 24.0 * i, 0, 0);
				else
					HudMessage(s:text; HUDMSG_PLAIN, RH_CLASSTEXT_ID + i, CR_UNTRANSLATED, 300.1, 240.0 + 24.0 * i, 0, 0);
			}
			if(CheckInventory("Clicked")) {
				HudMessage(s:"Selected class: \cg", s:ClassNames[curposy + add]; HUDMSG_PLAIN, RH_SELECT_ID, CR_YELLOW, 240.1, 300.0, 2.0);
				ConsoleCommand(StrParam(s:"playerclass \"", s:ClassNames[curposy + add], s:"\""));
				Terminate;
			}
			SetFont(ClassFrames[curposy + add][frameindex]);
			if(curposy + add == C_COLOSSUS) {
				SetHudSize(480, 320, 0);
				HudMessage(s:"A"; HUDMSG_PLAIN, RH_FRAME_ID, CR_UNTRANSLATED, 385.1, 220.0, 0.0);
			}
			else {
				SetHudSize(640, 480, 0);
				HudMessage(s:"A"; HUDMSG_PLAIN, RH_FRAME_ID, CR_UNTRANSLATED, 510.1, 320.0, 0.0);
			}
			++framecounter;
			if(!(framecounter % FRAMETICS)) {
				frameindex = (frameindex + 1) % 4;
				framecounter = 0;
			}
			Delay(1);
		}
	}
}

// Class select menu
Script 996 (void) NET {
	if(ClassMenuOpened[ActivatorTID()]) {
		SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
		ClassMenuOpened[ActivatorTID()] = 0;
		SetInventory("ShowingMenu", 0);
		SetInventory("MenuPosY", 0);
		ACS_ExecuteAlways(995, 0, 0);
		LocalAmbientSound("HelpMenu/Close", 127);
	}
	else {
		if(!PlayerIsSpectator(PlayerNumber())) {
			SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
			ClassMenuOpened[ActivatorTID()] = 1;
			SetInventory("ShowingMenu", 1);
			SetInventory("MenuMainPosY", 0);
			LocalAmbientSound("HelpMenu/Open", 127);
			ACS_ExecuteAlways(995, 0, 1);
			ACS_ExecuteAlways(994, 0);
		}
		else {
			SetHudSize(800, 600, 1);
			HudMessage(s: "You have to be in the game to use the menu"; HUDMSG_FADEINOUT, RH_CLASSMENU_ID, CR_GOLD, 400.4, 2.1, 4.0, 1.0, 1.0);
		}
	}
}

Script 997 (int helpmode) NET {
	if(PlayerOnMenu()) {
		SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
		LocalAmbientSound("HelpMenu/Close", 127);
		SetPlayerMenuMode(HELPMENU_OFF);
	}
	else {
		SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
		LocalAmbientSound("HelpMenu/Open", 127);
		// if 0, it will be on, if 1 it will be class mode
		SetPlayerMenuMode(helpmode + 1);
	}
	ACS_ExecuteAlways(998, 0, GetPlayerMenuMode(), GetPlayerPages());
}

Script 998 (int drawmode, int page) CLIENTSIDE {
	if(ConsolePlayerNumber() != PlayerNumber()) Terminate;
	if(drawmode == HELPMENU_ON)
		DrawMenu(drawmode, page);
	else if(drawmode == HELPMENU_OFF)
		CleanMenu();
}

// helpmode = 0 if just generic help, 1 otherwise
Script 999 (int dir) NET {
	int cur;
	if(PlayerOnMenu()) {
		if(!dir) {
			// currently not much use but allows support for multi page clas helps
			if(!PlayerOnClass()) { // on helpmode
				cur = GetPlayerPages();
				// change index here for page counts of sections
				cur = Clamp_Between(cur - 1, 0, HELPMENU_MAXPAGES - 1);
				SetPlayerPages(cur);
				LocalAmbientSound("HelpMenu/Page", 127);
			}
		}
		else {
			if(!PlayerOnClass()) { // on helpmode
				cur = cur = GetPlayerPages();
				// change index here for page counts of sections
				cur = Clamp_Between(cur + 1, 0, HELPMENU_MAXPAGES - 1);
				SetPlayerPages(cur);
				LocalAmbientSound("HelpMenu/Page", 127);
			}
		}
		ACS_ExecuteAlways(998, 0, GetPlayerMenuMode(), GetPlayerPages());
	}
}

/////////////////
// MENU END
////////////////