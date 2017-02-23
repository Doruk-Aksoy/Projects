#library "DND"
#include "zcommon.acs"

#include "DnD_Common.h"
#include "DnD_Defs.h"
#include "DnD_MonsterData.h"
#include "DnD.h"

Script 700 ENTER CLIENTSIDE {
	int hp, hpcomp, armor, armcomp;
	str ammo, ammoalt;
	while(1) {
		if(GetCVar("dnd_killspree"))
			GiveInventory("KillSpreeOn", 1);
		hpcomp = 100 + GetHealthCap();
		hp = GetActorProperty(0, APROP_HEALTH);
		if(hp > hpcomp) {
			SetInventory("HPOverAmount", hp - hpcomp);
			GiveInventory("HPOver100", 1);
			TakeInventory("HPNormal", 1);
			TakeInventory("HPBelow50", 1);
			TakeInventory("HPBelow25", 1);
		}
		else if(hp > (hpcomp >> 1) - 1) {
			SetInventory("HPOverAmount", 0);
			TakeInventory("HPOver100", 1);
			GiveInventory("HPNormal", 1);
			TakeInventory("HPBelow50", 1);
			TakeInventory("HPBelow25", 1);
		}
		else if(hp > (hpcomp >> 2) - 1) {
			SetInventory("HPOverAmount", 0);
			TakeInventory("HPOver100", 1);
			TakeInventory("HPNormal", 1);
			GiveInventory("HPBelow50", 1);
			TakeInventory("HPBelow25", 1);
		}
		else {
			SetInventory("HPOverAmount", 0);
			TakeInventory("HPOver100", 1);
			TakeInventory("HPNormal", 1);
			TakeInventory("HPBelow50", 1);
			GiveInventory("HPBelow25", 1);
		}
		
		armor = CheckInventory("Armor");
		if(armor > 100) {
			SetInventory("ARMOverAmount", armor - armcomp);
			GiveInventory("ARMOver100", 1);
			TakeInventory("ARMNormal", 1);
			TakeInventory("ARMBelow50", 1);
			TakeInventory("ARMBelow25", 1);
		}
		else if(armor > 49) {
			SetInventory("ARMOverAmount", 0);
			TakeInventory("ARMOver100", 1);
			GiveInventory("ARMNormal", 1);
			TakeInventory("ARMBelow50", 1);
			TakeInventory("ARMBelow25", 1);
		}
		else if(armor > 24) {
			SetInventory("ARMOverAmount", 0);
			TakeInventory("ARMOver100", 1);
			TakeInventory("ARMNormal", 1);
			GiveInventory("ARMBelow50", 1);
			TakeInventory("ARMBelow25", 1);
		}
		else {
			SetInventory("ARMOverAmount", 0);
			TakeInventory("ARMOver100", 1);
			TakeInventory("ARMNormal", 1);
			TakeInventory("ARMBelow50", 1);
			GiveInventory("ARMBelow25", 1);
		}
			
		if(((Timer() * 98) / (100 * TICRATE)) < GetLevelInfo(LEVELINFO_PAR_TIME))
			GiveInventory("H_UnderPar", 1);
		else
			TakeInventory("H_UnderPar", 1);

		if(GetLevelInfo(LEVELINFO_KILLED_MONSTERS) == GetLevelInfo(LEVELINFO_TOTAL_MONSTERS))
			GiveInventory("H_KillsAchieved", 1);
		else
			TakeInventory("H_KillsAchieved", 1);

		if(GetLevelInfo(LEVELINFO_FOUND_ITEMS) == GetLevelInfo(LEVELINFO_TOTAL_ITEMS))
			GiveInventory("H_ItemsAchieved", 1);
		else
			TakeInventory("H_ItemsAchieved", 1);

		if(GetLevelInfo(LEVELINFO_FOUND_SECRETS) == GetLevelInfo(LEVELINFO_TOTAL_SECRETS))
			GiveInventory("H_SecretsAchieved", 1);
		else
			TakeInventory("H_SecretsAchieved", 1);
			
		if(GetCVar("sv_infiniteammo"))
            GiveInventory("H_InfiniteAmmo", 1);
        else
            TakeInventory("H_InfiniteAmmo", 1);
		
		ammo = GetWeaponAmmoType(GetCurrentWeaponID(), 0);
		if(StrCmp(" ", ammo)) { // if uses ammo
			int acomp = GetAmmoCapacity(ammo);
			int curammo = CheckInventory(ammo);
			if(curammo > acomp / 2) {
				GiveInventory("H_PrimaryGreen", 1);
				TakeInventory("H_PrimaryYellow", 1);
				TakeInventory("H_PrimaryRed", 1);
			}
			else if(curammo > acomp / 4) {
				TakeInventory("H_PrimaryGreen", 1);
				GiveInventory("H_PrimaryYellow", 1);
				TakeInventory("H_PrimaryRed", 1);	
			}
			else {
				TakeInventory("H_PrimaryGreen", 1);
				TakeInventory("H_PrimaryYellow", 1);
				GiveInventory("H_PrimaryRed", 1);		
			}
		}
		
		ammoalt = GetWeaponAmmoType(GetCurrentWeaponID(), 1);
		if(StrCmp(" ", ammoalt) && StrCmp(ammoalt, ammo)) { // if uses altammo and is not same as normal ammo
			int acomp = GetAmmoCapacity(ammoalt);
			int curammo = CheckInventory(ammoalt);
			if(curammo > acomp / 2) {
				GiveInventory("H_SecondaryGreen", 1);
				TakeInventory("H_SecondaryYellow", 1);
				TakeInventory("H_SecondaryRed", 1);
			}
			else if(curammo > acomp / 4) {
				TakeInventory("H_SecondaryGreen", 1);
				GiveInventory("H_SecondaryYellow", 1);
				TakeInventory("H_SecondaryRed", 1);	
			}
			else {
				TakeInventory("H_SecondaryGreen", 1);
				TakeInventory("H_SecondaryYellow", 1);
				GiveInventory("H_SecondaryRed", 1);		
			}
		}
		Delay(1);
	}
}

Script 701 OPEN CLIENTSIDE {
	while(1) {
		if(GameType() != GAME_SINGLE_PLAYER) {
			if(!GetCVar("compat_clientssendfullbuttoninfo"))
				Log(s:"\cgWARNING:\c- Please activate '\cdcompat_clientssendfullbuttoninfo\c-' in order to use the menu properly.");
			if(GetCVar("sv_weapondrop"))
				Log(s:"\cgWARNING:\c- Please deactivate '\cdsv_weapondrop\c-'. It breaks mod rules!");
		}
		Delay(35);
	}
}

Script 702 OPEN {
	CalculateMapDifficulty();
	while(1) {
		if(GetCVar("dnd_hardcore"))
			HardcoreSet = CheckHardcoreSettings();
		Delay(30);
	}
}

// Basically shut the menu down
Script 703 DEATH {
	SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
	TakeInventory("P_Frozen", 1);
	StatListOpened[ActivatorTID()] = 0;
	SetInventory("ShowingMenu", 0);
	SetInventory("MenuOption", 5);
	SetInventory("MenuPosX", 0);
	SetInventory("MadeChoice", 0);
	SetInventory("DnD_PopupId", 0);
	TakeInventory("DnD_ShowPopup", 1);
	TakeInventory("DnD_ShowSellPopup", 1);
	TakeInventory("DnD_SellConfirm", 1);
	//SetInventory("MenuPosY", 5);
	ACS_ExecuteAlways(906, 0, 0);
}

// Health Kits Script (Used by Portable Medikits as well, ported here)
Script 818 (int amt, int isspecial) {
	int hp = GetActorProperty(0, APROP_HEALTH);
	int stat = GetHealthCap();
	int bonus = PERK_MEDICBONUS * CheckInventory("Perk_Medic");
	int toGive;
	if(isspecial == 3) {
	    GiveInventory("HealthBonusX", 100 + stat - hp);
	    Terminate;
	}
	else if(isspecial == 2) // ubersphere
	    toGive = 300 + stat - hp;
	else if(isspecial == 1) // SoulSphere / Megasphere
	    // max for pickup + stat - current hp
	    toGive = 200 + stat - hp;
	else // for anything else (stims, medkits etc)
	    toGive = 100 + stat - hp;
	
	if(toGive > amt + bonus)
		toGive = amt + bonus;
	
	if(CheckResearchStatus(RES_MEDKITSTORE) == RES_DONE && !isspecial) {
		if(hp < 100 + stat) // if my current hp is less than max
			GiveInventory("HealthBonusX", toGive);
        if(toGive < amt + bonus)
            GiveInventory("StoredMedkit", amt + bonus - Clamp_Between(toGive, 0, amt + bonus));
	}
	else
		GiveInventory("HealthBonusX", toGive);
}

Script 819 (int pnum, int type) {
	int res = 0;
    int research_cond = CheckResearchStatus(RES_MEDKITSTORE) == RES_DONE && CheckInventory("StoredMedkit") < GetAmmoCapacity("StoredMedkit");
	if(type == 2) // portable medikit
        res = GetActorProperty(0, APROP_HEALTH) < 100 + GetHealthCap() && CheckInventory("StoredMedkit");
    else
    if(type == 1) // the artifact kit
		res = GetActorProperty(0, APROP_HEALTH) < 100 + GetHealthCap();
	else // normal health pickup
		res = (GetActorProperty(0, APROP_HEALTH) < 100 + GetHealthCap() || research_cond) && GetPlayerNumber() == pnum;
	SetResultValue(res);
}
// Health kits end here

Script 825 ENTER {
    while(PlayerInGame(PlayerNumber())) {
        // additional hack for the slayer weapon's dynamic alt fire
        if(CheckWeapon("Slayer") && GetPlayerInput(-1, INPUT_BUTTONS) & BT_ALTATTACK)
            GiveInventory("SlayerBack", 1);
        SetInventory("MedkitItem", CheckInventory("StoredMedKit"));
        SetInventory("DnD_PrevHealth", GetActorProperty(0, APROP_HEALTH));
        TakeInventory("FadeIntensity", 1);
        Delay(const:1);
    }
}

// from woc
Script 826 (int opt) {
    int intensity, maxhp = GetHealthMax();
    int diff = FixedDiv((100 * (CheckInventory("DnD_PrevHealth") - GetActorProperty(0, APROP_Health)) << 16), maxhp << 16);
    if(CheckInventory("FadeIntensity"))
        intensity = (CheckInventory("FadeIntensity") << 16) + diff;
    else
        intensity = diff;
    intensity >>= 16;
    if(!opt) {
        if(intensity > 75)
            SetInventory("FadeIntensity", 75);
        else
            SetInventory("FadeIntensity", intensity);
    }
    SetInventory("DnD_PrevHealth", GetActorProperty(0, APROP_Health));
    SetResultValue(CheckInventory("FadeIntensity"));
}

Script 827 (int spree, int mult, int reward) CLIENTSIDE {
	LocalAmbientsound("KillStreak/Show", 127);
	SetHudSize(480, 360, 0);
	str temp = "KILLST";
	for(int i = 0; i < 4; ++i) {
		SetFont(StrParam(s:temp, d:i + 1));
		HudMessage(s:"A"; HUDMSG_FADEOUT, DND_SPREE_BLOODID, CR_WHITE, 220.4, 324.0, 3.0, 1.0);		
		Delay(3);
	}
	SetFont("MONFONT");
	HudMessage(s:"\ci", s:SpreeText[Clamp_Between(mult - 1, 0, MAX_SPREE_TEXT)], s:"!\c- \cix", f:mult * 0.25, s:"\c- bonus!"; HUDMSG_FADEINOUT, DND_SPREE_TEXT1ID, CR_WHITE, 240.4, 320.0, 2.0, 1.0, 1.0);
	HudMessage(s:"Gained extra \cf", d:reward, s: "\c- exp!"; HUDMSG_FADEINOUT, DND_SPREE_TEXT2ID, CR_WHITE, 240.4, 328.0, 2.0, 1.0, 1.0);
}

Script 828 (void) {
	while(CheckInventory("DnD_SpreeTimer")) {
		TakeInventory("DnD_SpreeTimer", 1);
		Delay(1);
	}
	// countdown over, reset spree xp
	TakeInventory("DnD_SpreeCountdownRunning", 1);
}

Script 829 (int mode) {
	if(mode) { // kill streaks
		// if a kill streak wasn't running, run it now
		if(!CheckInventory("DnD_SpreeCountdownRunning")) {
			GiveInventory("DnD_SpreeCountdownRunning", 1);
			ACS_ExecuteAlways(828, 0);
		}
		// spree count was given, so a possible spree may be in reach
		if(CheckInventory("DnD_SpreeTimer")) {
			GiveInventory("DnD_MultikillCounter", 1);
			if(GetArmorType("RavagerArmor", PlayerNumber()))
				GiveInventory("RavagerPower", 1);
		}
		// give spree counter
		GiveInventory("DnD_SpreeTimer", DND_SPREE_AMOUNT);
		
		if(CheckInventory("DnD_MultikillCounter")) {
			while(CheckInventory("DnD_SpreeTimer"))
				Delay(1);
			if(CheckInventory("DnD_MultikillCounter") >= DND_SPREE_TRIGGER && isAlive()) {
				int spree = CheckInventory("DnD_MultiKillCounter") + 1, mult, reward, temp;
				SetInventory("DnD_MultiKillCounter", 0);
				// shows kill spree result on hud
				// for every 10 enemy killed in spree, add a 0.25 multiplier
				// base multiplication factor is 0.25
				mult = spree / DND_SPREE_PER; // how many .25 to add
				temp = CheckInventory("SpreeXP") / DND_SPREE_BASE;
				while(mult) {
					reward += temp;
					--mult;
				}
				ACS_ExecuteAlways(827, 0, spree, spree / DND_SPREE_PER, reward);
				GiveInventory("Exp", reward);
				GiveInventory("ExpVisual", reward);
				GiveInventory("LevelExp", reward);
				SetInventory("SpreeXP", 0);
				
				// ravager armor add
				int armor = GetArmorType("RavagerArmor", PlayerNumber());
				if(armor) {
					if(armor < DND_RAVAGERARMOR_AMOUNT) {
						GiveInventory("NewArmorBonus", DND_RAVAGERARMOR_AMOUNT - armor);
						GiveInventory("RavagerEffect", 1);
						LocalAmbientSound("items/armorbonus", 127);
					}
				}
			}
			else {
				SetInventory("DnD_MultikillCounter", 0);
				SetInventory("SpreeXP", 0);
			}
		}
	}
	else // to force a grin on custom weapon pickups
		SetMugshotState("Grin");
}

// Spawn the exp gain on monster
Script 830 (int exp, int credit) {
	if(CheckInventory("Mo_Revived")) // don't continue if monster is a revived one
		Terminate;
	int target = GetActorProperty(0, APROP_TARGETTID);
	if(target < P_TIDSTART || target > P_TIDSTART + MAXPLAYERS - 1) // only work if you can determine target as a player
		Terminate;
	int expshare = GetCVar("dnd_sharexp");
	int creditshare = GetCVar("dnd_sharecredit");
	int haswisdom = IsAccessoryEquipped(target, ACC_WISDOM);
	int hasgreed = IsAccessoryEquipped(target, ACC_GREED);
    
    // decide how exp/credit base is calculated
	int exptemp;
	int credtemp;
    if(GetCVar("dnd_healthbasedexp"))
        exptemp = CheckInventory("MonsterMaxHealth") / DND_HEALTHEXPSCALE;
    else
        exptemp = exp;
    if(GetCVar("dnd_healthbasedcredit"))
        credtemp = (DND_HEALTHCREDITUPSCALE * CheckInventory("MonsterMaxHealth")) / DND_HEALTHCREDITSCALE;
    else
        credtemp = credit;
    
	int pnum = 0;
	int pcount = Clamp_Between(PlayerCount(), 1, DND_MAX_SHARE);
	int expscale = Clamp_Between(GetCVar("dnd_exp_scale"), 1, EXP_SCALE_MAX);
	int creditscale = Clamp_Between(GetCVar("dnd_credit_scale"), 1, CREDIT_SCALE_MAX);
	int addone = 0;
	if(pcount > 4)
		pcount = 4;
		
	// add monster scale stuff
	if(CheckInventory("MonsterLevel") > 1) {
		exptemp += exptemp * CheckInventory("MonsterLevel") * Clamp_Between(GetCVar("dnd_monster_rewardscalepercent"), 1, 25) / 100;
		credtemp += credtemp * CheckInventory("MonsterLevel") * Clamp_Between(GetCVar("dnd_monster_rewardscalepercent"), 1, 25) / 100;
	}
	
	ACS_ExecuteAlways(831, 0, exptemp * expscale, credtemp * creditscale, haswisdom + 10 * hasgreed); // show the numbers
	
	if(haswisdom) { // wisdom
		exptemp *= 3;
		if(exptemp % 2)
			addone = 1;
		exptemp >>= 1;
		exptemp += addone;
	}
	addone = 0;
	if(hasgreed) { // greed
		credtemp *= 3;
		if(credtemp % 2)
			addone = 1;
		credtemp >>= 1;
		credtemp += addone;
	}
	
	addone = GetCVar("dnd_gainonlyinrange");
	
	// if full share is on we won't divide by player count, but if it isn't we will
	if(!GetCVar("dnd_fullshare")) {
		exptemp = (exptemp * expscale)  / pcount;
		if(exptemp < MIN_EXP_GAIN)
			exptemp = min(exp, MIN_EXP_GAIN);
		credtemp = (credtemp * creditscale) / pcount;
		if(credtemp < MIN_CREDIT_GAIN)
			credtemp = min(credit, MIN_CREDIT_GAIN);
	}
	
	if(expshare || creditshare) {
		int expprev, credprev;
		for(int i = 0; i < MAXPLAYERS; i++) {
			expprev = exptemp;
			credprev = credtemp;
			pnum = P_TIDSTART + i;
			if(IsActorAlive(pnum) && pnum != target) { // dont give twice
				// check if range flag is on, if it is check the range
				if(!addone || (addone && AproxDistance(GetActorX(target) - GetActorX(pnum), GetActorY(target) - GetActorY(pnum)) >> 16 <= GetCVar("dnd_gainrange"))) {
					if(expshare) {
						expprev += expprev * BASE_WISDOM_GAIN * CheckActorInventory(P_TIDSTART + i, "Perk_Wisdom") / 100;
						GiveActorExp(pnum, expprev * expscale);
					}
					
					if(creditshare) {
						credprev += credprev * BASE_GREED_GAIN * CheckActorInventory(P_TIDSTART + i, "Perk_Greed") / 100;
						GiveActorCredit(pnum, credprev * creditscale);
					}
				}
			}
		}
		// now give target his stuff (if expshare or creditshare, one of them was not on the target would not receive it in the loop)
		exptemp += exptemp * BASE_WISDOM_GAIN * CheckActorInventory(target, "Perk_Wisdom") / 100;
		credtemp += credtemp * BASE_GREED_GAIN * CheckActorInventory(target, "Perk_Greed") / 100;
		GiveActorExp(target, exptemp * expscale);
		GiveActorCredit(target, credtemp * creditscale);
	}
	else {
		// just give target his stuff
		exptemp += exptemp * BASE_WISDOM_GAIN * CheckActorInventory(target, "Perk_Wisdom") / 100;
		credtemp += credtemp * BASE_GREED_GAIN * CheckActorInventory(target, "Perk_Greed") / 100;
		GiveActorExp(target, exptemp * expscale);
		GiveActorCredit(target, credtemp * creditscale);
	}

	// drop coins if there should be
	if(GetCVar("dnd_credit_drops")) {
		int chance = random(1, 100);
		for(int i = 0; i < MAXCREDITDROPS; ++i)
			if(CheckInventory("MonsterBaseHealth") < CreditDropThresholds[i]) {
				if(chance > CreditDropChances[i] + Clamp_Between(GetCVar("dnd_credit_droprateadd"), 0, 100))
					break;
				GiveInventory(CreditDroppers[i], 1);
				break;
			}
	}
    
    if(!GetCVar("dnd_allresearchesfound")) {
        int chance = random(1, 100);
        if(Clamp_Between(GetCVar("dnd_researchdroprate"), 0, 100) >= chance)
            GiveInventory("ResearchDropItem", 1);
    }
	
	SetActivator(target);
	// Kill spree
	if(GetCVar("dnd_killspree"))
		ACS_ExecuteAlways(829, 0, 1);
}

Script 831 (int exp, int credit, int hasstuff) CLIENTSIDE {
	int tid = ConsolePlayerNumber() + P_TIDSTART;
	int exptemp = exp;
	int credtemp = credit;
	int haswisdom = hasstuff % 10;
	int hasgreed = hasstuff / 10;
	int NumberID = Random(EXP_NUMBER_TID, EXP_NUMBER_TID_END);
	int edigit, cdigit, digitlen = 1, bonus;
	
	int mx = GetActorX(0) + Random(-10.0, 10.0);
	int my = GetActorY(0) + Random(-10.0, 10.0);
	int mz = GetActorZ(0) + (Random(46, 68) << 16) + GetActorProperty(0, APROP_HEIGHT) / 2;

	int SelectedColor = Random(0, 7);
	int TranslationNumber = Random(6000, 6499);
	CreateTranslation (TranslationNumber, 160 : 160 = Exp_ColorSet[SelectedColor] : Exp_ColorSet[SelectedColor]);
	CreateTranslation (TranslationNumber + 1, 160 : 160 = 216 : 216);
	
	// has support for as many digits, currently 5
	while(exp) {
		edigit = exp % 10;
		Spawn(StrParam(s:"Digit", d:digitlen, s:"Num", d:edigit), mx, my, mz, NumberID, 0);
		++digitlen;
		exp /= 10;
	}
	digitlen = 1;
	while(credit) {
		cdigit = credit % 10;
		Spawn(StrParam(s:"Digit", d:digitlen, s:"Num", d:cdigit), mx, my, mz - 18.0, NumberID + 1, 0);
		++digitlen;
		credit /= 10;
	}
	
	if(CheckActorInventory(tid, "Perk_Wisdom") || haswisdom) {
		digitlen = 1;
		exp = exptemp * BASE_WISDOM_GAIN * CheckActorInventory(tid, "Perk_Wisdom") / 100;
		
		if(haswisdom) {
			bonus = exptemp;
			if(bonus % 2)
				++bonus;
			bonus >>= 1;
		}
		exp += bonus;
		exptemp = exp;
		while(exp) {
			edigit = exp % 10;
			Spawn(StrParam(s:"Digit", d:digitlen, s:"Num", d:edigit), mx, my, mz - 9.0, NumberID, 0);
			++digitlen;
			exp /= 10;
		}
		if(exptemp)
			Spawn(StrParam(s:"Digit", d:digitlen, s:"Plus"), mx, my, mz - 9.0, NumberID, 0);
	}
	
	if(CheckActorInventory(tid, "Perk_Greed") || hasgreed) {
		digitlen = 1;
		credit = credtemp * BASE_GREED_GAIN * CheckActorInventory(tid, "Perk_Greed") / 100;
		
		if(hasgreed) {
			bonus = credtemp;
			if(bonus % 2)
				++bonus;
			bonus >>= 1;
		}
		credit += bonus;
		
		credtemp = credit;
		while(credit) {
			cdigit = credit % 10;
			Spawn(StrParam(s:"Digit", d:digitlen, s:"Num", d:cdigit), mx, my, mz - 27.0, NumberID + 1, 0);
			++digitlen;
			credit /= 10;
		}
		if(credtemp)
			Spawn(StrParam(s:"Digit", d:digitlen, s:"Plus"), mx, my, mz - 27.0, NumberID + 1, 0);
	}

	Thing_SetTranslation(NumberID, TranslationNumber);
	Thing_SetTranslation(NumberID + 1, TranslationNumber + 1);
	SetActorVelocity(NumberID, 0, 0, 0.25, 0, 0);
	SetActorVelocity(NumberID + 1, 0, 0, 0.25, 0, 0);
	Thing_ChangeTID(NumberID, 0);
	Thing_ChangeTID(NumberID + 1, 0);
}

// Stat Reset
Script 832 (void) {
	int statpts = Calculate_Stats();
	int perkpts = Calculate_Perks();
	Reset_RPGInfo(RESET_STATS | RESET_PERKS);
	StatListOpened[PlayerNumber() + P_TIDSTART] = 0;
	SetInventory("AttributePoint", statpts);
	SetInventory("PerkPoint", perkpts);
}

// Weapon pickup checks, bulkiness armor check and agamotto check
Script 891 ENTER {
	int i;
	while(1) {
		i = 0;
		while(i < MAXWEPS) {
			if(CheckInventory(Weapons[i][WEAPON_NAME]) && !CheckInventory(Weapons[i][WEAPON_GOT])) {
				Delay(5);
				GiveInventory(Weapons[i][WEAPON_GOT], 1);
			}
			++i;
		}
		
		// Bulkiness
		if(CheckInventory("Armor")) {
			if(CheckInventory("PSTAT_Bulkiness"))
				SetActorProperty(0, APROP_DAMAGEFACTOR, 1.0 - DND_BULKINESS_GAIN * CheckInventory("PSTAT_Bulkiness"));
		}
		else
			SetActorProperty(0, APROP_DAMAGEFACTOR, 1.0);
		
		if(isAlive()) {
			// Agamotto check
			if(CheckInventory("AgamottoCheck")) {
				int velx = GetActorVelX(0), vely = GetActorVelY(0), velz = GetActorVelZ(0);
				if(velx <= AGAMOTTO_MOVE_WINDOW && velx >= -AGAMOTTO_MOVE_WINDOW &&
					vely <= AGAMOTTO_MOVE_WINDOW && vely >= -AGAMOTTO_MOVE_WINDOW &&
					velz <= AGAMOTTO_MOVE_WINDOW && velz >= -AGAMOTTO_MOVE_WINDOW
				  ) 
				  {
						if(!CheckInventory("AgamottoOffense")) {
							TakeInventory("AgamottoDefense", 1);
							GiveInventory("AgamottoOffense", 1);
						}
				  }
				  else if(!CheckInventory("AgamottoDefense")) {
						GiveInventory("AgamottoDefense", 1);
						TakeInventory("AgamottoOffense", 1);
				  }
			}
			
			if(GetArmorType("KnightArmor", PlayerNumber()) && IsUsingMeleeWeapon())
				GiveInventory("KnightProtection", 1);
			else
				TakeInventory("KnightProtection", 1);
		}
		
		Delay(10);
	}
}

Script 893 (int mode, int index, int val) {
    str uvar = Data_Variables[index];
    int res = 0;
    if(!mode)
        SetInventory(uvar, val);
    else
        res = CheckInventory(uvar);
    SetResultValue(res);
}

// 894 is for database save

Script 895 ENTER CLIENTSIDE {
	int i;
	while(1) {
		i = 0;
		if(CheckInventory("LeveledUp")) {
			Log(s:"\ccAnnouncement  : \c-", n:0, s:" \c[Y5]has leveled up to\c- \cv", d:CheckInventory("Level"), s:"\c-\c[Y5]!");
			if(CheckInventory("PerkedUp"))
				Log(s:"\ccAnnouncement  : \c-", n:0, s:" \c[Y5]has gained a\c- \cjperk point\c-!");
			TakeInventory("LeveledUp", 1);
		}
		while(i < MAXWEPS) {
			str check = Weapons[i][WEAPON_NAME];
			if(StrLen(check) && CheckInventory(check) && !CheckInventory(Weapons[i][WEAPON_GOT])) {
				if(GetCVar("dnd_weapontips")) {
					ACS_ExecuteAlways(977, 0, 0, i);
					GiveInventory(Weapons[i][WEAPON_GOT], 1);
					GiveInventory("TipBoxOpen", 1);
					Delay(5);
				}
			}
			++i;
		}
		Delay(5);
	}
}

Script 896 (void)
{
	int check = 0;
	for(int i = 0; i < MAXTEMPWEPS; i++)
	  if(CheckInventory(TemporaryWeapons[i]))
	  {
		  check = 1;
	      SetResultValue(0);
	  }
	if(!check)
	  SetResultValue(1);
}

Script 897 (void)
{
	int i = random(0, MAXTEMPWEPS-1);
	GiveInventory(TemporaryWeapons[i], 1);
	// Soul Render exception
	if(i != 1)
	  GiveInventory(TemporaryAmmos[i], 999);
	SetWeapon(TemporaryWeapons[i]);
	LocalAmbientSound("weapons/pickup", 127);
}

Script 898 (int msg) CLIENTSIDE {
	if(PlayerNumber() != ConsolePlayerNumber()) Terminate;
	if(msg)
		Log(s:"Weapon tip boxes on");
	else
		Log(s:"Weapon tip boxes off");
}

Script 899 (int tips) NET CLIENTSIDE
{
	if(GetCVar("dnd_weapontips")) {
		SetCVar("dnd_weapontips", 0);
		ACS_ExecuteAlways(898, 0, 0);
	}
	else {
		SetCVar("dnd_weapontips", 1);
		ACS_ExecuteAlways(898, 0, 1);
	}
}

// 900 is in the menu.c

Script 902 (int forceset, int id) CLIENTSIDE {
	if(ConsolePlayerNumber() != PlayerNumber())
		Terminate;
	int i = CheckInventory("AmmoChangeMessage");
	if(forceset)
		i = id;
	if(!CheckInventory("NoAmmoMessage")) {
		SetFont("BIGFONT");
		HudMessage(s:"Now using ", s:SpecialAmmoNames[i][SPECIALAMMO_TAG], s:"!"; HUDMSG_PLAIN | HUDMSG_LOG, DND_SPECIALAMMO_TEXTID, CR_WHITE, 0.5, 0.1, 2.0);
		// hack: update ammo table to trick hud
		int pos = GetCurrentWeaponID();
		Weapons[pos][WEPINFO_AMMO1] = SpecialAmmoNames[i][SPECIALAMMO_NAME];
	}
}

// Current weapon tip

Script 903 (void) NET CLIENTSIDE {
	if(!CheckInventory("TipBoxOpen")) {
		int curweap = GetCurrentWeaponID();
		ACS_ExecuteAlways(977, 0, 0, curweap);
		GiveInventory("TipBoxOpen", 1);
	}
}

// 904 is used by the menu

// 0 drops 1 reloads
Script 905 (int mode) NET {
	if(!mode) {
		int curweap = GetCurrentWeaponID() - TEMPBEGIN; // to put it in range of the temporary weapons 0 - 7
		int amt;
		// valid range, no drop spam and not able to while firing and has ammo to spare
		if(curweap >= 0 && curweap < MAXTEMPWEPS && !CheckInventory("DropItemCooldown") && CheckInventory("TempWeaponReady") && (amt = CheckInventory(TemporaryAmmos[curweap]))) {
			int temptid = ActivatorTID() + P_TEMPTID;
			GiveInventory("DropItemCooldown", 1);
			SpawnForced(TemporaryWeaponDrops[curweap], GetActorX(0) + cos(GetActorAngle(0)), GetActorY(0) + sin(GetActorAngle(0)), GetActorZ(0) + 32, temptid);
			SetActorProperty(temptid, APROP_MASS, amt);
			ThrustThing(GetActorAngle(0) >> 8, 16, 0, temptid);
			ThrustThingZ(temptid, 8, 0, 0);
			Thing_ChangeTID(temptid, 0); // clear tid to prevent stupid shit
			GiveInventory("ForceWeaponRemove", 1);
		}
	}
}

// 906 to 914 reserved

script 915 enter CLIENTSIDE {
	if (GetAspectRatio() == ASPECT_5_4) { screenres1 = 0.0; screenres2 =0.0; }
	if (GetAspectRatio() == ASPECT_4_3) { screenres1 = 0.0; screenres2 =0.0; }
	if (GetAspectRatio() == ASPECT_16_9) { screenres1 = 108.0; screenres2 = 110.0; }
	if (GetAspectRatio() == ASPECT_16_10) { screenres1 = 64.0; screenres2 = 76.0; }
	delay(35);
	restart;
}

script 916 RESPAWN CLIENTSIDE {
	if (GetAspectRatio() == ASPECT_5_4) { screenres1 = 0.0; screenres2 =0.0; }
	if (GetAspectRatio() == ASPECT_4_3) { screenres1 = 0.0; screenres2 =0.0; }
	if (GetAspectRatio() == ASPECT_16_9) { screenres1 = 108.0; screenres2 = 110.0; }
	if (GetAspectRatio() == ASPECT_16_10) { screenres1 = 64.0; screenres2 = 76.0; }
	delay(35);
	restart;
}

// For each ammo category, use a multiple of 10 to store values
Script 917 (int ammo_category, int weptype) {
    // if a change did occur
	if(HasSpecialAmmoForWeapon(ammo_category) != SpecialAmmoBase[ammo_category]) {
		SetSpecialAmmoMode(ammo_category, weptype);
		int pos = GetCurrentWeaponID();
		if(ammo_category == AMMO_TYPE_SHELL)
			SetInventory(Weapons[pos][WEPINFO_AMMO2], 0);
		ActivatorSound("AmmoType/Switch", 127);
		Delay(4);
	}
	else
		GiveInventory("NoAmmoMessage", 1);
	SetInventory("AmmoChangeMessage", 0);
}

// type = 0, check stat, type = 1, check accessory
Script 918 (int type, int acc, int notarget) {
	int res = 0;
	
	if(!type) { 
		if(!acc) // get strength
			res = CheckInventory("PSTAT_Strength");
		else {
			if(CheckInventory("Perk_Munitionist")) {
				res = (CheckInventory("Perk_Munitionist") * notarget * DND_MUNITION_GAIN) / 100;
				if(!res)
					res = 1;
			}
			else
				res = 0;
		}
	}
	else if(type == 1) { // check for accessory
		int tid = ActivatorTID();
		if(!notarget)
			tid = GetActorProperty(0, APROP_TARGETTID);
		
		if(IsAccessoryEquipped(tid, acc))
			res = 1;
	}
	else if(type == 2) { // check for abilities
		switch(acc) {
			case 0:
				if(CheckInventory("Ability_Reloader"))
					res = 1;
			break;
			case 1:
				if(CheckInventory("Ability_Arcanery"))
					res = 1;
			break;
		}
	}
	else if(type == 3) { // talents
		if(notarget)
			SetActivator(0, AAPTR_TARGET);
		res = CheckInventory(TalentNames[acc]);
	}
	else if(type == 4) { // dexterity
		if(notarget)
			SetActivator(0, AAPTR_TARGET);
		res = CheckInventory("PSTAT_Dexterity");
	}
	else if(type == 5) { // bulkiness
		if(notarget)
			SetActivator(0, AAPTR_TARGET);
		res = CheckInventory("PSTAT_Bulkiness");
	}
	SetResultValue(res);
}

Script 919 (void) NET CLIENTSIDE {
	if(!GetCVar("dnd_nofx")) {
		SetFont("SMALLFONT");
		HudMessage(s:"Special Effects Off"; HUDMSG_FADEINOUT | HUDMSG_LOG, 1, CR_WHITE, 0.5, 0.24, 1.2, 0.5, 0.35);
		SetCVar("dnd_nofx", 1);
	}
	else {
		SetFont("SMALLFONT");
		HudMessage(s:"Special Effects On"; HUDMSG_FADEINOUT | HUDMSG_LOG, 1, CR_GOLD, 0.5, 0.24, 1.2, 0.5, 0.35);
		SetCVar("dnd_nofx", 0);
	}
	Delay(5);
}

Script 920 (int mode) {
	if(!mode) {
		SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
		SetActorProperty(0, APROP_SPEED, 0.0);
		GiveInventory("P_Frozen", 1);
	}
	else if(mode == 1) {
		if(!CheckInventory("ShowingMenu")) // don't break menu functionality
			SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
		SetActorProperty(0, APROP_SPEED, 1.0);
		TakeInventory("P_Frozen", 1);
	}
	else if(mode == 2) {
		if(!CheckInventory("MinigunFiring"))
			SetActorProperty(0, APROP_SPEED, 0.25);
	}
}

Script 921 (int type, int duration) {
	Delay(duration);
	switch(type) {
		case 0:
			GiveInventory("ChangeReflect", 1);
			TakeInventory("P_Invulnerable", 1);
		break;
		case 1:
			SetPlayerProperty(0, 0, PROP_BUDDHA);
			TakeInventory("P_Invulnerable", 1);
		break;
	}
}

script 922 (int actor_num, int radius, int totalactors) {
     int angle = GetUserVariable(0, "user_angle") * 360; 
     Thing_ChangeTID(0, REFLECTFXTID);
	 SetActivatorToTarget(0);
	 int owner = ActivatorTID();
	 // the below arrangement ensures each and every fireball gets a unique TID relative to the owner's tid
	 int newtid =  REFLECTFXTID + ((owner % 100) + 1) * totalactors + actor_num;
	 Thing_ChangeTID(REFLECTFXTID, newtid);
	 
	 int cx = radius * cos(angle) + GetActorX(owner);
	 int cy = radius * sin(angle) + GetActorY(owner);
	 int cz = GetActorZ(owner) + 32.125;
	 
	 SetActorPosition(newtid, cx, cy, cz, 0);
}

// Till 922 are reserved for mons.c

// Monster scaler -- add scaling stuff here
Script 962 (int monsterid, int traits) {
	if(!CheckInventory("DontRun")) {
		if(GetCVar("dnd_monsterscale")) {
			GiveInventory("DontRun", 1);
			// scaling code -- delay is because monsters are initialized before enter scripts are executed
			while(setplayer < PlayerCount())
				Delay(3);
			int base = GetActorProperty(0, APROP_HEALTH);
			int add = 0, level = 1, rnd, pcount;
			pcount = PlayerCount();
			if(!pcount)
				pcount = 1;
			level = total_level / pcount;
			if(GetCVar("dnd_randomize_levels")) {
				int low = Clamp_Between(GetCVar("dnd_monsterlevel_low"), 0, 50);
				int high = Clamp_Between(GetCVar("dnd_monsterlevel_high"), 1, 50);
				// give some sort of variety in the levels
				rnd = (max_level - min_level) >> 1;
				if(rnd <= 0)
					rnd = random(low, high);
				level += random(-rnd, rnd);
			}
			if(GetCVar("dnd_monsterlevel_behind"))
				level = Clamp_Between(level, 1, total_level / pcount);
			else
				level = Clamp_Between(level, 1, MAXLEVELS);
			if(level > 1) {
				add = base * Clamp_Between(GetCVar("dnd_monster_hpscalepercent"), 1, 100);
				add *= level - 1;
				// percentage
				add /= 100;
				if(GetCVar("dnd_playercount_scales_monsters"))
					add *= pcount;
			}
			SetActorProperty(0, APROP_HEALTH, base + add);
			SetInventory("MonsterID", monsterid);
			SetInventory("MonsterTraits", traits);
			SetInventory("MonsterBaseHealth", base);
			SetInventory("MonsterMaxHealth", base + add);
			SetInventory("MonsterLevel", level);
		}
		else {
			GiveInventory("DontRun", 1);
			SetInventory("MonsterID", monsterid);
			SetInventory("MonsterTraits", traits);
			SetInventory("MonsterBaseHealth", GetActorProperty(0, APROP_HEALTH));
			SetInventory("MonsterMaxHealth", GetActorProperty(0, APROP_HEALTH));
			SetInventory("MonsterLevel", 1);
		}
	}
}

// This is here because for some reason, in dnd_mons.c the variable values are not changed while here, they are
// Decide monster to spawn on a certain monster category given weight list
Script 957 (int category) {
    // if not hardcore use normal spawner
    if(!GetCVar("dnd_hardcore") && !GetCVar("dnd_usesmartmonsterspawner")) {
        SetActorState(0, "Soft", true);
        Terminate;
    }
    // count
    if(!Monster_VariationCounts[category]) {
        int i = 0;
        // add up total count and weight sum of category
        for(; i < MAX_MONSTER_VARIATIONS && Monster_Weights[category][i] != -1; Monster_CategoryWeightSum[category] += Monster_Weights[category][i++]);
        Monster_VariationCounts[category] = i + 1;
    }
    
    int sum = Monster_CategoryWeightSum[category];
    int picked = 0;
    // for each bin, do condition check, see if roll fits in a range
    // wait for the player to enter
    while(max_level <= 0)
        Delay(5);
    while(!picked) {
        int roll = random(0, sum);
        int bin = 0;
        for(int j = Monster_Weights[category][0]; j <= sum && bin < Monster_VariationCounts[category] && j <= roll; j += Monster_Weights[category][bin + 1], ++bin);
        // go to vanilla if bin is 0
        if(!bin) {
            SetActorState(0, "Vanilla", true);
            picked = 1;
        }
        else {
            int m_level = Monster_Weights[category][bin] << 16;
            int ratio = FixedDiv(Monster_Weights[category][0] << 16, m_level);
            int bias = random(0, 1.5);
            if(ratio <= bias + FixedDiv(GetGameLevelInfo(LEVEL_MAX) << 16, m_level)) {
                SetActorState(0, StrParam(s:"Var", d:bin), true);
                picked = 1;
            }
        }
    }
}

// 969 - 961 are in mons.c

script 970 (int type, int actor_num, int radius) CLIENTSIDE {
	if(!type) {
		int this = ActivatorTID();
		int angle = (GetUserVariable(this, "user_angle") * 360) % 1.0;
		int owner = GetActorProperty(this, APROP_HEALTH);
		int cx = radius * cos(angle) + GetActorX(owner);
		int cy = radius * sin(angle) + GetActorY(owner);
		int cz = GetActorZ(owner) + 108.0;

		SetActorPosition(this, cx, cy, cz, 0);
	}
	else {
		int angle = (GetUserVariable(0, "user_angle") * 360) % 1.0;
		int this = ActivatorTID();
		int owner = GetActorProperty(this, APROP_HEALTH);
		
		if(CheckInventory("AvatarOnAttack")) {
			angle = (60 * (actor_num - 1)) * 360;
			SetUserVariable(this, "user_angle", 60 * (actor_num - 1));
		}
		
		int cx = radius * cos(angle) + GetActorX(owner);
		int cy = radius * sin(angle) + GetActorY(owner);
		int cz = GetActorZ(owner) + 108.0;
		SetActorPosition(this, cx, cy, cz, 0);
	}
}

// 971 - 973 are in mons.c

// Form the blade vortex
Script 974 (int radius) {
	int tid = ActivatorTID(); // Owner TID
	int newtid = tid + VORTEXTIDSTART + 16 * ((tid + 1) % 100);
	
	for(int m = 0; m < 16; m++)
		Thing_Remove(newtid + m);
	
	int cx, cy, cz;
	cz = GetActorZ(tid) + 26.125;
	int pang = GetActorAngle(tid) >> 8;
	
	// i goes to 16, pang += 16 to complete 256, 360 degrees of doom.
	for(int i = 0; i < 16; ++i) {
		// initial radius is 1/32th of the intended to make all of the blades spawn properly
		cx = GetActorX(tid) + radius*cos(pang<<8)/32;
		cy = GetActorY(tid) + radius*sin(pang<<8)/32;
		pang += 16;
		Spawn("VortexBlade", cx, cy, cz, newtid + i, 0); // Basically, first 1032 are for playernum 0, then a 32 is added and it becomes 1064 etc... Max Value is 3144. (For 64th player)
		SetActivator(newtid + i);
		SetPointer(AAPTR_TARGET, tid);
		SetActivator(tid);
	}
	ACS_executeAlways(975, 0, tid, pang, radius); // Align coords
}

// Constantly rotate the ring
Script 975 (int tid, int pang, int radius) {
	// Create the phase
	int angadd = 0;
	int bladetid = tid + VORTEXTIDSTART + 16 * ((tid + 1) % 100);
	str tocheck = "VortexTimer";
	if(CheckInventory("Ability_Arcanery"))
		tocheck = "VortexTimer2";
	while(1) {
		if(!CheckActorInventory(tid, tocheck) || GetActorProperty(tid, APROP_HEALTH) <= 0) {
			for(int m = 0; m < 16; ++m)
				Thing_Remove(bladetid + m);
			angadd = 0;
			break;
		}
		
		int cx, cy;
		int cz = GetActorZ(tid) + 26.125;
		
		for(int i = 0; i < 16; ++i) {
			pang += 16;
			cx = GetActorX(tid) + radius*cos((pang+angadd)<<8);
			cy = GetActorY(tid) + radius*sin((pang+angadd)<<8);
			SetActorPosition(bladetid + i, cx, cy, cz, 0);
		}
		angadd += 2;
		Delay(1);
	}
}

// Level up / Bonus detecting
Script 976 ENTER {
	while(1) {
		if(PlayerInGame(PlayerNumber())) {
			if(CheckLevelUp()) {
				LocalAmbientSound("RPG/LevelUp", 127);
				GiveInventory("LevelUpEffectSpawner", 1);
				GiveInventory("LeveledUp", 1);
				++total_level;
				if(GetStat(STAT_LVL) - 1 == max_level)
					max_level = GetStat(STAT_LVL);
				// heal on level up flag is on
				if(GetCVar("dnd_healonlevelup"))
					ACS_ExecuteAlways(818, 0, 100, 0);
			}
			
			// ankh check
			if(!CheckInventory("P_Invulnerable") && GetActorProperty(0, APROP_HEALTH) == 1 && !CheckInventory("Intervened") && CheckInventory("InterventionSelected") && CheckInventory("CanIntervene")) {
				GiveInventory("Intervention", 1);
				GiveInventory("Intervened", 1);
				TakeInventory("CanIntervene", 1);
				GiveInventory("InterventionFXSpawner", 1);
				GiveInventory("P_Invulnerable", 1);
				ACS_ExecuteAlways(921, 0, 1, INTERVENTION_DURATION);
			}
		}
		Delay(5);
	}
}

// Weapon tip display
Script 977 (int type, int itemnum) CLIENTSIDE {
	if(ConsolePlayerNumber() != PlayerNumber())
	    Terminate;
	if(!type && !CheckInventory("ParsingData")) { // weapon tip
		LocalAmbientSound("Weapon/Popup", 127);
		SetHudSize(640, 480, 1);
		SetFont("MSGBOX2");
		HudMessage(s:"A"; HUDMSG_FADEINOUT, SURVIVEID, CR_UNTRANSLATED, 515.0 + screenres2, 70.0, 4.0, 1.0, 1.0);
		SetFont(Weapons[itemnum][WEAPON_ICON]);
		HudMessage(s:"A"; HUDMSG_FADEINOUT, SURVIVEICO, CR_UNTRANSLATED, 537.1 + screenres2, 30.0, 4.0, 1.0, 1.0);
		SetFont("OBJFONT");
		HudMessage(s:Weapons[itemnum][WEAPON_SLOT]; HUDMSG_FADEINOUT, SURVIVETOPTEXTID, CR_GOLD, 416.0 + screenres2, 18.0, 4.0, 1.0, 1.0);

		SetHudSize(960, 600, 1);
		HudMessage(s:WeaponPickupText[itemnum]; HUDMSG_FADEINOUT, SURVIVETEXTID, CR_WHITE, 632.1 + 3 * screenres2 / 2, 44.1, 4.0, 1.0, 1.0);
	}
}

// Checking for Bonuses
Script 978 ENTER {
	int KillBonus, ItemBonus, SecretBonus, BonusBonus;
	int curkills, curitems, cursecrets;
	Delay(35);
	while(1) {
		if(!GetCVar("dnd_disablelevelbonus") && PlayerInGame(PlayerNumber())) {
			curkills = GetLevelInfo(LEVELINFO_KILLED_MONSTERS);
			curitems = GetLevelInfo(LEVELINFO_FOUND_ITEMS);
			cursecrets = GetLevelInfo(LEVELINFO_FOUND_SECRETS);
			int pnum = GetPlayerNumber();
			
			if(GetLevelInfo(LEVELINFO_TOTAL_MONSTERS)) {
				if(!KillBonus && curkills && curkills >= GetLevelInfo(LEVELINFO_TOTAL_MONSTERS)) {
					int bonusval = CalculateBonus(BONUS_KILL);
					SetHudSize(800, 600, 1);
					SetFont("BIGFONT");
					HudMessageBold(s:"All monsters have been killed! ", d:bonusval, s:"% Exp bonus!"; HUDMSG_FADEINOUT, KILLBONUSID, CR_RED, 400.4, DnD_MessageY(), 4.0, 1.0, 1.0);
					LocalAmbientSound("RPG/KillBonus", 127);
					GiveInventory("DnD_ShowKillBonus", 1);
					
					int expbonus = GetStat(STAT_LVLEXP) * bonusval / 100;
					GiveInventory("Exp", expbonus);
					GiveInventory("ExpVisual", expbonus);
					
					KillBonus = 1;
				}
			}
			else
				KillBonus = 2; // means there were no monsters at all

			if(GetLevelInfo(LEVELINFO_TOTAL_ITEMS)) {
				if(!ItemBonus && curitems >= GetLevelInfo(LEVELINFO_TOTAL_ITEMS)) {
					int bonusval = CalculateBonus(BONUS_ITEM);
					SetHudSize(800, 600, 1);
					SetFont("BIGFONT");
					HudMessageBold(s:"All items have been taken! ", d:bonusval, s:" Credit!"; HUDMSG_FADEINOUT, ITEMBONUSID, CR_GOLD, 400.4, DnD_MessageY(), 4.0, 1.0, 1.0);
					LocalAmbientSound("RPG/ItemBonus", 127);
					GiveInventory("DnD_ShowItemBonus", 1);
					GiveInventory("Credit", bonusval);
					ItemBonus = 1;
				}
			}
			else
				ItemBonus = 2; // means there were no items at all
			
			if(GetLevelInfo(LEVELINFO_TOTAL_SECRETS)) { // if there are some secrets
				if(!SecretBonus && cursecrets >= GetLevelInfo(LEVELINFO_TOTAL_SECRETS)) {
					int bonusval = CalculateBonus(BONUS_SECRET);
					SetHudSize(800, 600, 1);
					SetFont("BIGFONT");
					if(bonusval > 1)
						HudMessageBold(s:"All secrets have been found! ", d:bonusval, s:" Stat Points!"; HUDMSG_FADEINOUT, SECRETBONUSID, CR_GOLD, 400.4, DnD_MessageY(), 4.0, 1.0, 1.0);
					else
						HudMessageBold(s:"All secrets have been found! 1 Stat Point!"; HUDMSG_FADEINOUT, SECRETBONUSID, CR_GOLD, 400.4, DnD_MessageY(), 4.0, 1.0, 1.0);
					GiveInventory("DnD_ShowSecretBonus", 1);
					LocalAmbientSound("RPG/SecretBonus", 127);
					GiveInventory("AttributePoint", bonusval);
					SecretBonus = 1;	
				}
			}
			else
				SecretBonus = 2;
			
			// if there was at least some bonus involved!
			if(KillBonus && ItemBonus && SecretBonus && !BonusBonus && (KillBonus + ItemBonus + SecretBonus != 6)) {
				// if difficulty was hard or above, give 1 perk point
				// else give 2 stat points per difficulty level
				int bonusval = CalculateBonus(BONUS_BONUS);
				SetHudSize(800, 600, 1);
				SetFont("BIGFONT");
				if(MapDifficulty >= DND_HARD) {
					HudMessageBold(s:"The entire map is toast! ", d:bonusval, s:" Stat Points and 1 Perk Point!"; HUDMSG_FADEINOUT, BONUSBONUSID, CR_GOLD, 400.4, DnD_MessageY(), 4.0, 1.0, 1.0);
					GiveInventory("PerkPoint", 1);
				}
				else {
					HudMessageBold(s:"The entire map is toast! ", d:bonusval, s: " Stat Points!"; HUDMSG_FADEINOUT, BONUSBONUSID, CR_GOLD, 400.4, DnD_MessageY(), 4.0, 1.0, 1.0);
				}
				GiveInventory("DnD_ShowBonusBonus", 1);
				LocalAmbientSound("RPG/BonusBonus", 127);
				GiveInventory("AttributePoint", bonusval);
				BonusBonus = 1;
			}
		}
		Delay(15);
	}
}

Script 980 ENTER {
	int thisactor = ActivatorTID();
	int monhp, monlvl, monsterid, mmaxhp, healthbarcolor, traits, nameskip;
	while(1) {
		SetActivatorToTarget(thisactor);
		if(!CheckInventory("EnemyInDisguise") && CheckActorProperty(0, APROP_Friendly, 0) || CheckInventory("FriendlyInDisguise"))
			healthbarcolor = 1;
		else if(CheckActorProperty(0, APROP_Friendly, 1) || CheckInventory("EnemyInDisguise"))
			healthbarcolor = 0;
		if(ActivatorTID() == thisactor || CheckInventory("EnemyInDisguise")) {
			// player has no targets
			SetActivator(thisactor);
			SetInventory("TargetMaximumHealth", 0);
			SetInventory("TargetCurrentHealth", 0);
			SetInventory("TargetLevel", 0);
			SetInventory("TargetTraits", 0);
			SetInventory("TargetIsWhat", 0);
		}
		else {
			mmaxhp = CheckInventory("MonsterMaxHealth");
			monhp = GetActorProperty (0, APROP_Health);
			monlvl = CheckInventory("MonsterLevel");
			monsterid = CheckInventory("MonsterID");
			traits = CheckInventory("MonsterTraits");
			nameskip = CheckInventory("MonsterNameSkip");
			SetActivator(thisactor);
			SetInventory("TargetMaximumHealth", mmaxhp);
			SetInventory("TargetCurrentHealth", monhp);
			SetInventory("TargetHealthBarColor", healthbarcolor);
			SetInventory("TargetLevel", monlvl);
			SetInventory("TargetTraits", traits);
			SetInventory("TargetIsWhat", monsterid);
		}
		Delay (1);
	}
}

Script 981 ENTER CLIENTSIDE {
	int mmaxhp, hdisp, monhp, monlevel, monid, traits;
	while(1) {
		if(GetCVar("dnd_nofx") && ConsolePlayerNumber() == PlayerNumber())
			Thing_Remove(SPECIAL_FX_TID);
			
		if(CheckInventory("Ability_MonsterInfo")) {
			mmaxhp = CheckInventory("TargetMaximumHealth");
			hdisp;
			if(mmaxhp && GetCVar("dnd_monsterbars")) {
				monhp = CheckInventory("TargetCurrentHealth");
				monlevel = CheckInventory("TargetLevel");
				monid = CheckInventory("TargetIsWhat");
				traits = CheckInventory("TargetTraits");
				hdisp = (monhp * 100 / mmaxhp);
				int i, j;
				if(CheckInventory("TargetHealthBarColor")) {
					SetFont ("MNRHPBAR");
				}
				else
					SetFont ("MNGHPBAR");
				
				SetHudSize (800, 600, 0);
				HudMessage(s:"a"; 1, MONSTER_BARID, CR_UNTRANSLATED, 400.0, 27.0, 1);
				// inner text
				SetFont ("MONFONT");
				HudMessage(s:"Lvl: ", i:monlevel, s:"  ", i:monhp, s:"/", i:mmaxhp; 1, MONSTER_TEXTID, CR_WHITE, 400.0, 27.0, 1);
				if(isBoss(monid))
					HudMessage(s:MonsterInfo[monid]; 1, MONSTER_NAMEID, CR_ORANGE, 404.4, 10.0, 1);
				else
					HudMessage(s:MonsterInfo[monid]; 1, MONSTER_NAMEID, CR_WHITE, 404.4, 10.0, 1);
					
				for (i = 0; i <= hdisp && i <= 100; ++i) {
					j = j + 2.0;
					if(CheckInventory("TargetHealthBarColor"))
						SetFont ("FILLCRIT");
					else
						SetFont ("FILLNORM");
					if(monhp)
						HudMessage(s:"a"; 1, MONSTER_BARFILLID + i, CR_GREEN, 303.0 + j, 27.0, 1);
				}
				i = j = 0;
				// show monster traits
				if(traits) {
					SetFont ("MONFONT");
					for(i = 0; i < MAX_MONSTER_TRAITS; ++i) {
						if(CheckBit(traits, i)) {
							HudMessage(s:MonsterTraits[i]; 1, MONSTER_TRAITID + j, CR_WHITE, 404.4, 44.0 + 8.0 * j, 1);
							++j;
						}
					}
				}
			}
		}
		Delay (1);
	}
}

// Script for Monsters
Script 982 (int type) {
	if(type == 2) { // drop heart
		if(CheckActorInventory(GetActorProperty(0, APROP_TARGETTID), "Ability_HeartSeeker") && !random(0, CHANCE_HEART - 1)) {
			SpawnForced("DemonHeartPickup", GetActorX(0), GetActorY(0), GetActorZ(0) + 24.0, 65536);
			ThrustThingZ(65536, 16, 0, 0);
		}
	}
}

// Calculate chance of item drop, drop if needed (out of 100)
Script 983 (int basechance) {
	SetActivatorToTarget(0);
	int dropchance = random(1, 100);
	if(basechance >= dropchance)
	  SetResultValue(1);
	else
	  SetResultValue(0);
}

// Railgun trails
Script 984 (int actortype, int density) {
	Thing_ChangeTID(0, RAILINITTID);
	SetactivatorToTarget(RAILINITTID);
	int ptid = ActivatorTID();
	int newtid = ActivatorTID() + RAILTIDADD;
	Thing_ChangeTID(RAILINITTID, newtid);
	
    int plX; int plY;  int plZ;
    int grX; int grY;  int grZ;
    int vX;  int vY;   int vZ;
    int nX;  int nY;   int nZ;
    int bX;  int bY;   int bZ;
    int magnitude;
    int pointCount;
    int pointOffset;
    plX = GetActorX(ptid); grX = GetActorX(newtid);
    plY = GetActorY(ptid); grY  = GetActorY(newtid);
    plZ = GetActorZ(ptid)+32.0; grZ  = GetActorZ(newtid);
    vX   = grX - plX;       vY   = grY - plY;       vZ   = grZ - plZ;

    magnitude = magnitudeThree(vX >> 16, vY >> 16, vZ >> 16);

    pointCount  = magnitude / density;
    pointOffset = magnitude - (pointCount * density);

    if (magnitude != 0) {
        nX = vX / magnitude; nY = vY / magnitude; nZ = vZ / magnitude;

        int i; int j;
        for (i = 1; i < pointCount; i++) {
            j = (i * density) + pointOffset;

            bX = (nX * j) + plX;
            bY = (nY * j) + plY;
            bZ = (nZ * j) + plZ;

            Spawn(RailGunTrails[actortype], bX, bY, bZ);
			Spawn(RailGunDamagers[actortype], bX, bY, bZ, newtid + RAILTIDADD);
			SetActivator(newtid + RAILTIDADD); // fixes ownership problems
			SetPointer(AAPTR_TARGET, ptid);			
        }
    }
}

// Some Generic Chat Log Script
Script 985 (int type, int id) CLIENTSIDE {
	if(PlayerNumber() != ConsolePlayerNumber()) Terminate;
	if(!type)
		Log(s:TemporaryWeaponMsg[id]);
	else if(type == 1)
		Log(s:WeaponMsg[id]);
    else
        Log(s:ResearchPrefix, s:Research_Label[id], s:"!");
}

// Pickup check for the temporary weapons
Script 986 (int wepnum, int type)
{
	int who = ActivatorTID();
	if(type) {
		SetActivatorToTarget(0);
		who = ActivatorTID();
	}
	
	int t = 0;
	int res = 0;
	for(int i = 0; i < MAXTEMPWEPS; ++i)
	{
		if(i == wepnum)
		{   // do we have max ammo on this weapon
			if(CheckActorInventory(who, TemporaryAmmos[i]) == GetAmmoCapacity(TemporaryAmmos[i]))
			  ++t;
		}
		else if(CheckActorInventory(who, TemporaryWeapons[i])) { // do I have any temp weapon
			if(!CheckActorInventory(who, TemporaryAmmos[i])) // hack to prevent a desync problem
				TakeActorInventory(who, TemporaryWeapons[i], 1);
			else
				++t;
		}
	}
	if(!t)
	    res = 1;
	SetResultValue(res);
}

Script 987 RESPAWN {
	Thing_ChangeTID(0, P_TIDSTART + PlayerNumber());
	SetInventory("PNum", PlayerNumber());
	
	int hp = GetActorProperty(0, APROP_HEALTH);
	// So the player respawns with his actual new max hp
	GiveInventory("HealthBonusX", 100 + GetHealthCap() - hp);
	TakeInventory("PowerReflection", 1);
	RestoreRPGStat(RES_PERK_SHARP | RES_PERK_ENDURANCE);
	
	// if game mode is coop, we don't want any sort of reset on death here! make sure it's not coop
	if(GetCVar("Survival")) {
		if(CheckInventory("CurrentLives"))
			TakeInventory("CurrentLives", 1);
		else {
			// After tests, it enters this block when you die and respawn after losing all lives ie. round restarted. Safer than Death script.
			MedkitAmount[ActivatorTID()] = 0;
			ShieldAmount[ActivatorTID()] = 0;
			for(int j = 0; j < MAXAMMOTYPES; j++)
				SetInventory(AmmoMaxes[j], InitialCapacity[j]);
			  
			Reset_RPGInfo(RESET_LEVEL | RESET_CREDIT | RESET_STATS | RESET_PERKS);
			StatListOpened[PlayerNumber() + P_TIDSTART] = 0;
		}
	}
	
	// for properly setting up taltos translucency when spawn protection is on
	while(GetActorProperty(0, APROP_INVULNERABLE) && !CheckInventory("P_Invulnerable"))
		Delay(5);
	if(CheckInventory("TaltosUp"))
		GiveInventory("TaltosEffect", 1);
}

Script 988 (int wepslot, int type) {
	int res = 0;
	if(!type) {
		if(CheckSlotWeapon(wepslot))
			res = 1;
	}
	else if(type == 1) {
		if(GetCVar("sv_weaponstay"))
			res = 1;
	}
	SetResultValue(res);
}

// Clear upon leaving
Script 989 (int pnum) DISCONNECT {
	MedkitAmount[pnum] = 0;
	ShieldAmount[ActivatorTID()] = 0;
	StatListOpened[pnum] = 0;
}

// End of level checks
Script 990 UNLOADING {
	MapChanged = 1;
	for(int i = 0; i < MAXPLAYERS; ++i) {
	    if(GetActorProperty(P_TIDSTART + i, APROP_HEALTH) > 0) {
		    GiveActorInventory(P_TIDSTART + i, "LevelToken", 1);
		    MedkitAmount[P_TIDSTART + i] = CheckActorInventory(P_TIDSTART + i, "FieldKit");
		    ShieldAmount[P_TIDSTART + i] = CheckActorInventory(P_TIDSTART + i, "PortableShield");
			StatListOpened[P_TIDSTART + i] = 0;
            GiveActorInventory(P_TIDSTART + i, "Budget", (MapDifficulty + 1) + DND_BUDGET_BASE);
		}
	}
}

// Enter level checks
Script 991 ENTER {
	Thing_ChangeTID(0, P_TIDSTART + PlayerNumber());
	SetInventory("PNum", PlayerNumber());
	SetInventory("SphereMade", 0);
	// reset anything related to kill sprees on entering a new map
	SetInventory("SpreeXP", 0);
	SetInventory("DnD_SpreeTimer", 0);
	SetInventory("DnD_SpreeCountdownRunning", 0);
	SetInventory("DnD_MultikillCounter", 0);
	SetInventory("LevelExp", 0);
	SetInventory("LevelCredit", 0);
	setInventory("AllMapOnlyOnce", 0);
	SetInventory("MapDifficultyClientside", MapDifficulty);
	int pnum = PlayerNumber(), curlvl;
	if(MedkitAmount[P_TIDSTART + pnum] > 1)
		GiveInventory("FieldKit", MedkitAmount[P_TIDSTART + pnum] - 1);
	if(ShieldAmount[P_TIDSTART + pnum] > 1)
		GiveInventory("PortableShield", ShieldAmount[P_TIDSTART + pnum] - 1);
	SetPlayerProperty(0, 0, PROP_TOTALLYFROZEN);
	TakeInventory("P_Frozen", 1);

	// Checks if we should set the lives to the inventory or not (also includes one time execute things)
	// when player joins for the first time
	if(CheckInventory("SetMyLives")) {
		// can only reflect once per map
		SetInventory("ReflectCount", 0);
		SetInventory("Intervened", 0);
		SetInventory("CanIntervene", 1);
		TakeInventory("SetMyLives", 1);
		Reset_RPGInfo(RESET_LEVEL | RESET_CREDIT | RESET_STATS | RESET_PERKS);
		StatListOpened[PlayerNumber() + P_TIDSTART] = 0;
		GiveInventory(" Fists ", 1);
		GiveInventory(" Pistol ", 1);
		if(GetCVar("dnd_allresearchesfound"))
			GiveAndDoAllResearch();
		ACS_ExecuteAlways(906, 0, 0);
	}
	
	// if map changed, reset accessory stuff
	if(MapChanged) {
		SetInventory("ReflectCount", 0);
		SetInventory("Intervened", 0);
		SetInventory("P_Invulnerable", 0);
	}
	TakeInventory("PowerReflection", 1);
	// order of the above reset is important
	if(!GetCVar("sv_maxlives"))
		SetInventory("CurrentLives", 0);
	else
		SetInventory("CurrentLives", GetCvar("sv_maxlives") - 1);
	RestoreRPGStat(RES_PERK_SHARP | RES_PERK_ENDURANCE);
	
	// a little hack to prevent ankh going off when finishing maps with 1 hp
	if(GetActorProperty(0, APROP_HEALTH) == 1 && CheckInventory("CanIntervene"))
		HealThing(1);
	
	// Give Temporal Sphere
	if(CheckInventory("Ability_Temporal") && !CheckInventory("TemporalSphere"))
        GiveInventory("TemporalSphere", 1);
	
	// Set the ammo capacity
	for(int j = 0; j < MAXAMMOTYPES; ++j) {
		// If not set to a value before, set it to initial
		if(!CheckInventory(AmmoMaxes[j]))
			SetInventory(AmmoMaxes[j], InitialCapacity[j]);
		else
			SetAmmoCapacity(AmmoTypes[j], CheckInventory(AmmoMaxes[j]));
	}
	setplayer++;
	if(setplayer == PlayerCount())
		MapChanged = 0;
	curlvl = GetStat(STAT_LVL);
	total_level += curlvl;
	if(max_level < curlvl)
		max_level = curlvl;
	if(min_level > curlvl)
		min_level = curlvl;
	// for properly setting up taltos translucency when spawn protection is on
	while(GetActorProperty(0, APROP_INVULNERABLE) && !CheckInventory("P_Invulnerable"))
		Delay(5);
	if(CheckInventory("TaltosUp"))
		GiveInventory("TaltosEffect", 1);
}

// Control for ammo capacity
Script 992 (int t, int simple) {
	int res = 0;
	if(!t) {
		res = CheckInventory("Shell") == GetAmmoCapacity("Shell");
		if(!simple)
			  res &= CheckInventory("ExplodingShell") == GetAmmoCapacity("ExplodingShell") && CheckInventory("SlayerAmmo") == GetAmmoCapacity("SlayerAmmo");
	}
	else
	if(t == 1) {
		res = CheckInventory("Clip") == GetAmmoCapacity("Clip");
		if(!simple) 
			  res &= CheckInventory("EbonyAmmo") == GetAmmoCapacity("EbonyAmmo") && CheckInventory("EbonyAmmoX") == GetAmmoCapacity("EbonyAmmoX");
	}
	else
	if(t == 2) {
		res = CheckInventory("RocketAmmo") == GetAmmoCapacity("RocketAmmo");
		if(!simple)
			  res &= CheckInventory("Grenades") == GetAmmoCapacity("Grenades") && CheckInventory("MISAmmo") == GetAmmoCapacity("MISAmmo") && CheckInventory("MeteorAmmo") == GetAmmoCapacity("MeteorAmmo");
	}
	else
	if(t == 3) {
		res = CheckInventory("Cell") == GetAmmoCapacity("Cell");
		if(!simple)
			  res &= CheckInventory("Nail") == GetAmmoCapacity("Nail") && CheckInventory("BasiliskAmmo") == GetAmmoCapacity("BasiliskAmmo") && CheckInventory("GaussRound") == GetAmmoCapacity("GaussRound") && CheckInventory("Fuel") == GetAmmoCapacity("Fuel");
	}
	SetResultValue(res);
}

Script 993 ENTER CLIENTSIDE {
	if(ConsolePlayerNumber() != PlayerNumber()) Terminate;
	if(GetCVar("dnd_showmapinfo"))
		SetInventory("ShowMapInfo", 1);
	// Set the ammo capacity
	SetAmmoCapacity("ExpVisual", LevelCurve[CheckInventory("Level") - 1]);
	for(int j = 0; j < MAXAMMOTYPES; ++j) {
		// If not set to a value before, set it to initial
		if(!CheckInventory(AmmoMaxes[j]))
			SetInventory(AmmoMaxes[j], InitialCapacity[j]);
		else
			SetAmmoCapacity(AmmoTypes[j], CheckInventory(AmmoMaxes[j]));
	}
}

// A generic checker function
Script 994 (int type, int extra)
{
	int res = 0;
	if(!type) {
		if(GetAmmoCapacity("Shell") != SHELLMAX)
		  res = 1;
	}
	if(type == 1) {
		if(!extra) { // attack check
			if(CheckInventory("FireLeft") && CheckInventory("AkimboClipLeft"))
				res = 2;
			if(!CheckInventory("FireLeft") && CheckInventory("AkimboClipRight"))
				res = 3;
			if(!res)
				res = 1;
		}
		else { // reload check
			if(CheckInventory("Clip")) {
				int cap = GetAmmoCapacity("AkimboClipLeft");
				res = CheckInventory("AkimboClipLeft") < cap || CheckInventory("AkimboClipRight") < cap;
			}
		}
	}
	else if(type == 2) { // accessory drop check
		res = random(1, 100) <= Clamp_Between(GetCVar("dnd_accessory_droprate"), 0, 100) && (total_level / PlayerCount()) >= Clamp_Between(GetCVar("dnd_accessorylevel"), 1, 100);
	}
	else if(type == 3)
		res = GetPlayerInput(-1, INPUT_BUTTONS) & BT_ALTATTACK;
	else if(type == 4)
		res = Clamp_Between(GetCVar("dnd_respawn_count"), 1, 0x7FFFFFFF);
	else if(type > 4 && type < 9) {
		if(GetCVar("dnd_monsterscale")) {
			if(type == 5)
				res = (Clamp_Between(CheckInventory("MonsterLevel"), 1, DND_MAX_MONSTERLVL) * Clamp_Between(GetCVar("dnd_monster_dmgscalepercent"), 0.01, 1.0)) >> 16;
			else if(type == 6) {
				SetActivatorToTarget(0);
				res = (Clamp_Between(CheckInventory("MonsterLevel"), 1, DND_MAX_MONSTERLVL) * Clamp_Between(GetCVar("dnd_monster_dmgscalepercent"), 0.01, 1.0)) >> 16;
			}
			else if(type == 7)
				res = (Clamp_Between(extra, 1, DND_MAX_MONSTERLVL) * Clamp_Between(GetCVar("dnd_monster_dmgscalepercent"), 0.01, 1.0)) >> 16;
			else if(type == 8)
				res = CheckInventory("MonsterLevel");
		}
	}
	else if(type == 9)
		res = GetPlayerInput(-1, INPUT_BUTTONS) & BT_RELOAD;
	else if(type == 10) { // checks shell clip size
		str tocheck = "ShellSize_8N";
		str ammotype = "Shell";
		str weptype = "SpecialAmmoMode_3";
		if(extra == 1)
			tocheck = "ShellSize_8";
		else if(extra == 2)
			tocheck = "ShellSize_10";
		else if(extra == 3)
			tocheck = "ShellSize_12";
		else if(extra == 4) {
			tocheck = "ShellSize_2";
				weptype = "SpecialAmmoMode_3X";
		}
		ammotype = SpecialAmmoNames[CheckInventory(weptype)][SPECIALAMMO_NAME];
		res = CheckInventory(ammotype) > CheckInventory(tocheck);
	}
    else if(type == 11) // has research?
        res = CheckResearchStatus(extra) == RES_NA;
    else if(type == 12)
        res = CheckInventory("LightningStacks");
	SetResultValue(res);
}

// Custom Powerup script
Script 995 (int power) {
	if(!power) {
		str togive = "FakeBloodPower";
		if(CheckInventory("Ability_Arcanery"))
			togive = "FakeBloodPowerBetter";
		ActivatorSound("items/bloodrun", 127);
		GiveInventory(togive, 1);
	}
	else if(power == 1) {
		if(CheckInventory("HateCheck")) {
			int this = ActivatorTID();
			SetActivator(0, AAPTR_TARGET);
			if(ActivatorTID() != this)
				GiveInventory("HateWeakness", 1);
		}
		// necro chance
		if(GetArmorType("NecroArmor", PlayerNumber()) && !random(0, 2))
			GiveInventory("NecroSpikeShooter", 1);
	}
}

// Backpack / Research script
Script 996 (int type, int id) {
    if(!type) {
        for(int j = 0; j < MAXAMMOTYPES; ++j) {
            if(GetCVar("dnd_firstbackpackold") && !CheckInventory("FirstBackpack"))
                GiveInventory(AmmoMaxes[j], CapacityPerBackpack[j] * DND_BACKPACK_RATIO);
            else
                GiveInventory(AmmoMaxes[j], CapacityPerBackpack[j]);
            SetAmmoCapacity(AmmoTypes[j], CheckInventory(AmmoMaxes[j]));
            GiveInventory(AmmoTypes[j], BackPackAmounts[j]);
        }
        GiveInventory("FirstBackpack", 1);
        GiveInventory("BackpackCounter", 1);
        // Reduce if over the limits
        if(GetAmmoCapacity("Shell") > SHELLMAX) {
            SetAmmoCapacity("Clip", CLIPMAX);
            SetAmmoCapacity("MISAmmo", HMISMAX);
            SetAmmoCapacity("Shell", SHELLMAX);
            SetAmmoCapacity("RocketAmmo", ROCKETMAX);
            SetAmmoCapacity("Cell", CELLMAX);
            SetAmmoCapacity("Grenades", GRENADEMAX);
            SetAmmoCapacity("Nail", NAILMAX);
            SetAmmoCapacity("ExplodingShell", EXPSHELLMAX);
            SetAmmoCapacity("EbonyAmmo", EBONYMAX);
            SetAmmoCapacity("EbonyAmmoX", EBONYXMAX);
            SetAmmoCapacity("BasiliskAmmo", BASILISKMAX);
            SetAmmoCapacity("GaussRound", GAUSSMAX);
            ACS_ExecuteAlways(993, 0, 1);
        } 
    }
    else if(type == 1) {
        // give research
        GiveResearch(id);
    }
    else {
        int num = random(0, MAX_RESEARCHES - 1);
        Spawn(StrParam(s:"ResearchModule_", s:Research_List[num]), GetActorX(0), GetActorY(0), GetActorZ(0), 0);
    }
}

// Dash Script
Script 997 ENTER {
	int input;
	int oldInput;
	int taps;
	int tics;
	int last;
	int angle;
	int velX;
	int velY;
	int velZ;
	while(1) {
        if(!CheckInventory("DashDisabled") && !CheckInventory("P_Frozen") && GetActorProperty(0, APROP_HEALTH) > 0) {
            if(CheckInventory("Ability_Dash")) {
                input = GetPlayerInput(-1, INPUT_BUTTONS);
                oldInput = GetPlayerInput(-1, INPUT_OLDBUTTONS);
                
                for(int i = 0; i < 4; ++i) {
                    if(IsButtonPressed(input, oldInput, settings[i][0])){
                        ++taps;
                        tics = SD_TIMEFRAME;
                        
                        if(taps == 2 && last == i) {
                            taps = 0;
                            angle = GetActorAngle(0) + settings[i][1];
                            
                            if(GetActorZ(0) - GetActorFloorZ(0) > 0) {
                                velX = FixedMul(cos(angle), SD_DASHSPEED);
                                velY = FixedMul(sin(angle), SD_DASHSPEED);
                                velZ = -GetActorVelZ(0) + SD_DASHJUMP;
                            }
                            
                            else {
                                velX = FixedMul(cos(angle), SD_DASHSTRONG);
                                velY = FixedMul(sin(angle), SD_DASHSTRONG);
                                velZ = 0.0;
                            }
                            
                            SetActorVelocity(0, velX, velY, velZ, true, false);
                            ActivatorSound("Player/Dash", SD_SOUNDVOLUME);
                            GiveInventory("DashEffect", 1);
                            Delay(const:SD_DASHDELAY);
                            
                            while(GetActorVelZ(0) < 0.0)
                                Delay(const:1);
                        }
                        
                        last = i;
                    }
                }
                
                if(tics) {
                    --tics;
                    
                    if(!tics)
                        taps = 0;
                }
            }
        }
        Delay(const:1);
    }
}

// reload script
Script 998 (int wepnum, int side) {
	int base, amt;
	str totake;
	if(!wepnum) {
		base = GetAmmoCapacity("MGClip");
		totake = "MGClip";
	}
	else if(wepnum == 1) {
		base = GetAmmoCapacity("AkimboClipLeft");
		if(!side)
			totake = "AkimboClipLeft";
		else
			totake = "AkimboClipRight";
	}
	else if(wepnum == 2) {
		base = GetAmmoCapacity("MGClip2");
		totake = "MGClip2";
	}
	else if(wepnum == 3) {
		base = GetAmmoCapacity("MGClip4");
		totake = "MGClip4";
	}
	else if(wepnum == 4) {
		base = GetAmmoCapacity("MGClip5");
		totake = "MGClip5";
	}
	
	amt = base - CheckInventory(totake);
	
	if(CheckInventory("Clip") < base) {
		GiveInventory(totake, CheckInventory("Clip"));
		TakeInventory("Clip", amt);
	}
	else {
		TakeInventory("Clip", amt);
		GiveInventory(totake, amt);
	}
}

// Regeneration
Script 999 ENTER {
	while(1) {
		if(GetActorProperty(0, APROP_HEALTH) > 0 && CheckInventory("Ability_Regeneration")) {
			int hp = GetActorProperty(0, APROP_HEALTH);
			if(!CheckInventory("RegenStopper") && hp < NANOCAP && hp < 30 + GetHealthCap()) {
				if(hp > 28 + GetHealthCap() || hp == NANOCAP - 1)
				  GiveInventory("HealthBonusX", 1);
				else
				  GiveInventory("HealthBonusX", 2);
				GiveInventory("RegenEffect", 1);
				LocalAmbientSound("ability/regen", 127);
			}
		}
		
		int armor = GetArmorType("CyberneticArmor", PlayerNumber());
		if(isAlive() && armor && armor < DND_CYBERNETICARMOR_AMOUNT && !CheckInventory("P_Damaged")) {
			if(armor < DND_CYBERNETICARMOR_AMOUNT - 5)
				GiveInventory("NewArmorBonus", 5);
			else
				GiveInventory("NewArmorBonus", DND_CYBERNETICARMOR_AMOUNT - armor);
			GiveInventory("CyberneticEffect", 1);
			LocalAmbientSound("items/armorbonus", 127);
		}
		Delay(35);
	}
}