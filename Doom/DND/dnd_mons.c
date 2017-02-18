#library "DND"
#include "zcommon.acs"
#include "DnD_Common.h"
#include "DnD_Monsters.h"

// Monster stuff

// Monster Healer
Script 958 (int amount) {
	int hp = GetActorProperty(0, APROP_HEALTH);
	amount = Clamp_Between(amount, 0, CheckInventory("MonsterMaxHealth") - hp);
	SetActorProperty(0, APROP_HEALTH, hp + amount);
}

Script 959 (int type) CLIENTSIDE {
	if(!type) {
		int count = 0, tid = ActivatorTID();
		int newtid = tid + ZEALOT_SHIELD_TIDADD;
		Spawn("ZealotShield", GetActorX(tid), GetActorY(tid), GetActorZ(tid) + 32.0, newtid);
		while (count < ZEALOT_SHIELD_TIME) {
			SetActorPosition(newtid, GetActorX(tid), GetActorY(tid), GetActorZ(tid) + 32.0, 0);
			Delay(1);
			++count;
		}
		SetActorState(newtid, "Death");
	}
	else if(type == 1)
		GiveInventory("ArbiterFade", 1);
	else if(type == 2)
		GiveInventory("ArbiterDead", 1);
	else if(type == 3)
		TakeInventory("ArbiterFade", 1);
	else if(type == 4)
		TakeInventory("ArbiterFade", 1);
	else if(type == 5) {
		SetActivatorToTarget(0);
		SetResultValue(CheckInventory("ArbiterFade"));
	}
	else if(type == 6) {
		SetActivatorToTarget(0);
		SetResultValue(CheckInventory("ArbiterDead"));
	}
}

Script 960 (int type) {
	if(!type) {
		int count = 0;
		while(count < ZEALOT_SHIELD_TIME) {
			Delay(1);
			++count;
		}
		GiveInventory("ZealotUnsetReflection", 1);
	}
}

Script 961 (int type, int amt, int item) {
	if(!type) {
		SetActivator(0, AAPTR_TARGET);
		int targtid = ActivatorTID();
		SetActivator(0);
		SetResultValue(GetActorProperty(targtid, APROP_HEALTH) <= 50 + CheckInventory("MaxHealthBonusCounter") / 2 && CheckSight(targtid, 0, CSF_NOBLOCKALL));
	}
	else if(type == 1) {
		while(!CheckInventory("GamonShift") && isAlive())
			Delay(5);
		SetActorProperty(0, APROP_ALPHA, 0.5);
		ActivatorSound("Veste/Cast", 127.0);
		SpawnForced("SalvationEffectSpawner", GetActorX(0), GetActorY(0), GetActorZ(0));
	}
	else if(type == 2)
		SetActorProperty(0, APROP_ALPHA, 0.5);
	else if(type == 3)
		SetActorProperty(0, APROP_ALPHA, 1.0);
	else if(type == 4) {
		str itemname;
		switch(item) {
			case 0:
				itemname = "MonsterTraits";
			break;
			default:
				itemname = "";
			break;
		}
		SetInventory(itemname, amt);
	}
	else if(type == 5) {
		SetResultValue(GetActorProperty(0, APROP_HEALTH) < CheckInventory("MonsterMaxHealth") >> 1);
	}
	else if(type == 6) {
		// don't judge me, this shit just doesn't work in decorate of zan 3.0...
		Spawn("DarkHealEffectSpawner", GetActorX(0), GetActorY(0), GetActorZ(0));
	}
	else if(type == 7)
		SetResultValue(CheckInventory("MonsterMaxHealth"));
}

Script 963 (int type) {
	int vit, thisactor;
	if(!type) {
		vit = CheckInventory("PSTAT_Vitality");
		thisactor = ActivatorTID();
		SetActivator(0, AAPTR_TARGET);
		Thing_Damage2(thisactor, vit / 2, "VileGhostDrain");
		HealThing(vit / 2);
		Spawn("RegenEffectSpawner", GetActorX(0), GetActorY(0), GetActorZ(0), 0);
	}
}

// general TID assigner
Script 964 (int which) {
	switch (which) {
		case 0:
			Thing_ChangeTID(0, AVATAR_BASE_TID + (AvatarTID++));
		break;
		case 1:
			Thing_ChangeTID(0, PURP_DEM_TID + (PurpDemTID++));
		break;
		case 2:
			Thing_ChangeTID(0, ZEALOT_BASE_TID + (ZealotTID++));
		break;
	}
}

Script 965 (void) {
	int montid = ActivatorTID();
	int monang = GetActorAngle(0);
	SetActivatorToTarget(montid);
	int targtid = ActivatorTID();
	SetActivator(montid);
	
	int x = (GetActorX(montid) - GetActorX(targtid)) >> 16;
	int y = (GetActorY(montid) - GetActorY(targtid)) >> 16;
	int distance = sqrt((x*x) + (y*y));
	
	ThrustThingZ(montid, (distance >> 6) + 24, 0, 1);
	Delay(3);
	ThrustThing(monang >> 8, (distance >> 5) + 15, 1, montid);
}

Script 966 () {
	int t = 0;
	while(t < WAIT_MAX) {
		if(GetActorZ(0) - GetActorFloorZ(0) < 4.0) {
			GiveInventory("Landed", 1);
			break;
		}
		GiveInventory("DemonFlightDamager", 1);
		Delay(3);
		GiveInventory("DemonFlightDamager", 1);
		Delay(2);
		++t;
	}
	TakeInventory("DemonGoJump", 1);
	if(t == WAIT_MAX - 1) { // waited full duration, high chance it was stuck, get it unstuck
		ThrustThing((GetActorAngle(0) >> 8), 24, 0, 0);
		Delay(4);
		ThrustThing((GetActorAngle(0) >> 8) + 64, 24, 0, 0);
		Delay(4);
		ThrustThing((GetActorAngle(0) >> 8) + 128, 24, 0, 0);
		Delay(4);
		ThrustThing((GetActorAngle(0) >> 8) + 192, 24, 0, 0);
	}
}

Script 967 (int togive) CLIENTSIDE {
	if(!togive)
		GiveInventory("AvatarAttack", 1);
	else if(togive == 1)
		GiveInventory("AvatarOnAttack", 1);
	else if(togive == 2) {
		TakeInventory("AvatarAttack", 1);
		TakeInventory("AvatarOnAttack", 1);
	}
	else {
		TakeInventory("AvatarAttack", 1);
		TakeInventory("AvatarOnAttack", 1);
		GiveInventory("AvatarDead", 1);
	}
}

Script 968 (void) CLIENTSIDE {
    if(CheckInventory("AvatarBallSet"))
        Terminate;
    
    int x, y, z, newtid;
	int tid = 0;
    
    do {
        tid = ActivatorTID();
        Delay(1);
    } while(!tid);
    if(CheckInventory("AvatarBallSet"))
        Terminate;
    GiveInventory("AvatarBallSet", 1);
    
    x = GetActorX(0);
    y = GetActorY(0);
    z = GetActorZ(0) + 16.0;
    
    
	tid = ActivatorTID();
	newtid = AVATAR_CUBE_TID + (tid % 1000) * 3;
    while(!SpawnForced("SorcBall1New", x, y, z, newtid));
	while(!SpawnForced("SorcBall2New", x, y, z, newtid + 1));
	while(!SpawnForced("SorcBall3New", x, y, z, newtid + 2));
	SetActorProperty(newtid, APROP_HEALTH, tid);
	SetActorProperty(newtid + 1, APROP_HEALTH, tid);
	SetActorProperty(newtid + 2, APROP_HEALTH, tid);
}

Script 969 (void) CLIENTSIDE {
	int tid = GetActorProperty(0, APROP_HEALTH);
	int res = 1 + CheckActorInventory(tid, "AvatarAttack") - 2 * CheckActorInventory(tid, "AvatarOnAttack");
	if(CheckActorInventory(tid, "AvatarDead"))
		res = -2;
	SetResultValue(res);
}

Script 971 (void) {
	int velx = FixedMul(cos(GetActorAngle(0)), 14.0);
	int vely = FixedMul(sin(GetActorAngle(0)), 14.0);
	SetActorVelocity(0, velx, vely, 0, 0, 0);
}

Script 972 (int type) { // script for Lich Slow
	int i;
	if(!type) {
		for(i = 0; i < 5; i++) {
			SetActorProperty(0, APROP_SPEED, 1.0 - 0.22 * i);
			Delay(20);
		}
		Restore_PlayerSpeed();
	}
	else if(type == 1) {
		int temp = CheckInventory("ForcedMonsterLevel");
		SetInventory("ForcedMonsterLevel", 0);
		for(i = 0; !CheckInventory("CurseImmunity") && i < 5; i++) {
			Thing_Damage(0, 4 + 4 * ACS_ExecuteWithResult(994, 7, temp), MOD_POISON);
			Delay(17);
		}
	}
	else if(type == 2) {
		AmbientSound("Lich/VisionDim", 127);
		for(i = 0; i < MAXPLAYERS; i++) {
			if(GetActorProperty(P_TIDSTART + i, APROP_HEALTH) > 0)
				GiveActorInventory(P_TIDSTART + i, "LichVisionDim", 1);
		}
	}
}

Script 973 (int mode) { // Avatar tid / targeter
	if (mode == 1) {
		int owner = ActivatorTID(), curdist;
		int missiletid = ActivatorTID() + AVATAR_SOUL_TID;
		
		SetActivator(owner, AAPTR_TARGET);
		int target = ActivatorTID();
		SetActivator(owner);
		
		for(int i = 0; i < AVATAR_SOUL_COUNT; i++) {
			// choose closest target
			curdist = INT_MAX;
			for(int j = 0; j < MAXPLAYERS; j++) {
				int dist = fdistance(owner, P_TIDSTART + j);
				if(GetActorProperty(P_TIDSTART + j, APROP_HEALTH) > 0 && dist < curdist) {
					target = P_TIDSTART + j;
					curdist = dist;
				}
			}
			
			SetActorPosition(owner, GetActorX(owner), GetActorY(owner), GetActorZ(owner) + 56.0, 0);
			SpawnProjectile(owner, "HolyMissile2", GetActorAngle(owner), 128, 0, 0, missiletid + i);
			SetActorPosition(owner, GetActorX(owner), GetActorY(owner), GetActorZ(owner) - 56.0, 0);
			SetActorPosition(missiletid + i, GetActorX(missiletid + i), GetActorY(missiletid + i), GetActorZ(missiletid + i) + 54.0, 0);
			SetActivator(missiletid + i);
			SetPointer(AAPTR_TARGET, owner);
			SetPointer(AAPTR_TRACER, target);
			int dx = GetActorX(target) - GetActorX(missiletid + i);
			int dy = GetActorY(target) - GetActorY(missiletid + i);
			SetActorAngle(missiletid + i, VectorAngle(dx, dy));
			SetActivator(owner);
			Delay(12);
		}
	}
	else {
		if(GetActorProperty(0, APROP_HEALTH) < 2000)
			GiveInventory("AcolyteSummoner", 1);
	}
}