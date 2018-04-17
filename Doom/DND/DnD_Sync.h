#ifndef DND_SYNC_IN
#define DND_SYNC_IN

enum {
	DND_SYNC_WEAPONENHANCE,
	
	DND_SYNC_SPEED,
	
	DND_SYNC_DROPCHANCE,
	
	DND_SYNC_PROSPERITY_BONUS,
	DND_SYNC_FORTITUDE_BONUS,
	DND_SYNC_HPFLAT_BONUS,
	DND_SYNC_ARMORFLAT_BONUS,
	DND_SYNC_HPPERCENT_BONUS,
	DND_SYNC_ARMORPERCENT_BONUS,
	
	DND_SYNC_GREEDPERCENT_BONUS,
	DND_SYNC_WISDOMPERCENT_BONUS,
	
	DND_SYNC_HOLDING,
	
	DND_SYNC_DAMAGEBULLET,
	DND_SYNC_DAMAGEMELEE,
	DND_SYNC_DAMAGEOCCULT,
	DND_SYNC_DAMAGEEXPLOSIVE,
	DND_SYNC_DAMAGEENERGY,
	DND_SYNC_DAMAGEELEMENTAL,
	
	DND_SYNC_WEPBONUS_CRIT,
	DND_SYNC_WEPBONUS_CRITDMG,
	DND_SYNC_WEPBONUS_CRITPERCENT,
	DND_SYNC_WEPBONUS_DMG
};
#define MAX_SYNC_VARS DND_SYNC_WEPBONUS_DMG + 1

int GetPlayerSyncValue(int pos, int extra) {
	int pnum = PlayerNumber();
	switch(pos) {
		case DND_SYNC_WEAPONENHANCE:
		return Player_Weapon_Infos[pnum][extra].enchants;
		case DND_SYNC_SPEED:
		return Player_Bonuses[pnum].speed_bonus;
		case DND_SYNC_DROPCHANCE:
		return Player_Bonuses[pnum].drop_chance;
		case DND_SYNC_PROSPERITY_BONUS:
		return Player_Bonuses[pnum].prosperity_orb_bonus;
		case DND_SYNC_FORTITUDE_BONUS:
		return Player_Bonuses[pnum].fortitude_orb_bonus;
		case DND_SYNC_HPFLAT_BONUS:
		return Player_Bonuses[pnum].hp_flat_bonus;
		case DND_SYNC_ARMORFLAT_BONUS:
		return Player_Bonuses[pnum].armor_flat_bonus;
		case DND_SYNC_HPPERCENT_BONUS:
		return Player_Bonuses[pnum].hp_percent_bonus;
		case DND_SYNC_ARMORPERCENT_BONUS:
		return Player_Bonuses[pnum].armor_percent_bonus;
		case DND_SYNC_GREEDPERCENT_BONUS:
		return Player_Bonuses[pnum].greed_percent_bonus;
		case DND_SYNC_WISDOMPERCENT_BONUS:
		return Player_Bonuses[pnum].wisdom_percent_bonus;
		case DND_SYNC_HOLDING:
		return Player_Bonuses[pnum].holding;
		case DND_SYNC_DAMAGEBULLET:
		return Player_Bonuses[pnum].damage_type_bonus[TALENT_BULLET];
		case DND_SYNC_DAMAGEENERGY:
		return Player_Bonuses[pnum].damage_type_bonus[TALENT_ENERGY];
		case DND_SYNC_DAMAGEEXPLOSIVE:
		return Player_Bonuses[pnum].damage_type_bonus[TALENT_EXPLOSIVE];
		case DND_SYNC_DAMAGEMELEE:
		return Player_Bonuses[pnum].damage_type_bonus[TALENT_MELEE];
		case DND_SYNC_DAMAGEELEMENTAL:
		return Player_Bonuses[pnum].damage_type_bonus[TALENT_ELEMENTAL];
		case DND_SYNC_DAMAGEOCCULT:
		return Player_Bonuses[pnum].damage_type_bonus[TALENT_OCCULT];
		case DND_SYNC_WEPBONUS_CRIT:
		return Player_Weapon_Infos[pnum][extra].wep_bonuses[WEP_BONUS_CRIT].amt;
		case DND_SYNC_WEPBONUS_CRITDMG:
		return Player_Weapon_Infos[pnum][extra].wep_bonuses[WEP_BONUS_CRITDMG].amt;
		case DND_SYNC_WEPBONUS_CRITPERCENT:
		return Player_Weapon_Infos[pnum][extra].wep_bonuses[WEP_BONUS_CRITPERCENT].amt;
		case DND_SYNC_WEPBONUS_DMG:
		return Player_Weapon_Infos[pnum][extra].wep_bonuses[WEP_BONUS_DMG].amt;
	}
	return 0;
}

void SetSyncValue(int pos, int val, int extra) {
	int pnum = PlayerNumber();
	switch(pos) {
		case DND_SYNC_WEAPONENHANCE:
			Player_Weapon_Infos[pnum][extra].enchants = val;
		break;
		case DND_SYNC_SPEED:
			Player_Bonuses[pnum].speed_bonus = val;
		break;
		case DND_SYNC_DROPCHANCE:
			Player_Bonuses[pnum].drop_chance = val;
		break;
		case DND_SYNC_PROSPERITY_BONUS:
			Player_Bonuses[pnum].prosperity_orb_bonus = val;
		break;
		case DND_SYNC_FORTITUDE_BONUS:
			Player_Bonuses[pnum].fortitude_orb_bonus = val;
		break;
		case DND_SYNC_HPFLAT_BONUS:
			Player_Bonuses[pnum].hp_flat_bonus = val;
		break;
		case DND_SYNC_ARMORFLAT_BONUS:
			Player_Bonuses[pnum].armor_flat_bonus = val;
		break;
		case DND_SYNC_HPPERCENT_BONUS:
			Player_Bonuses[pnum].hp_percent_bonus = val;
		break;
		case DND_SYNC_ARMORPERCENT_BONUS:
			Player_Bonuses[pnum].armor_percent_bonus = val;
		break;
		case DND_SYNC_GREEDPERCENT_BONUS:
			Player_Bonuses[pnum].greed_percent_bonus = val;
		break;
		case DND_SYNC_WISDOMPERCENT_BONUS:
			Player_Bonuses[pnum].wisdom_percent_bonus = val;
		break;
		case DND_SYNC_HOLDING:
			Player_Bonuses[pnum].holding = val;
		break;
		case DND_SYNC_DAMAGEBULLET:
			Player_Bonuses[pnum].damage_type_bonus[TALENT_BULLET] = val;
		break;
		case DND_SYNC_DAMAGEENERGY:
			Player_Bonuses[pnum].damage_type_bonus[TALENT_ENERGY] = val;
		break;
		case DND_SYNC_DAMAGEEXPLOSIVE:
			Player_Bonuses[pnum].damage_type_bonus[TALENT_EXPLOSIVE] = val;
		break;
		case DND_SYNC_DAMAGEMELEE:
			Player_Bonuses[pnum].damage_type_bonus[TALENT_MELEE] = val;
		break;
		case DND_SYNC_DAMAGEELEMENTAL:
			Player_Bonuses[pnum].damage_type_bonus[TALENT_ELEMENTAL] = val;
		break;
		case DND_SYNC_DAMAGEOCCULT:
			Player_Bonuses[pnum].damage_type_bonus[TALENT_OCCULT] = val;
		break;
		case DND_SYNC_WEPBONUS_CRIT:
			Player_Weapon_Infos[pnum][extra].wep_bonuses[WEP_BONUS_CRIT].amt = val;
		break;
		case DND_SYNC_WEPBONUS_CRITDMG:
			Player_Weapon_Infos[pnum][extra].wep_bonuses[WEP_BONUS_CRITDMG].amt = val;
		break;
		case DND_SYNC_WEPBONUS_CRITPERCENT:
			Player_Weapon_Infos[pnum][extra].wep_bonuses[WEP_BONUS_CRITPERCENT].amt = val;
		break;
		case DND_SYNC_WEPBONUS_DMG:
			Player_Weapon_Infos[pnum][extra].wep_bonuses[WEP_BONUS_DMG].amt = val;
		break;
	}
}

void SyncClientsideVariable(int var, int extra) {
	if(var == DND_SYNC_WEAPONENHANCE || var >= DND_SYNC_WEPBONUS_CRIT)
		ACS_NamedExecuteAlways("DND Clientside Syncer", 0, var, GetPlayerSyncValue(var, extra), extra);
	else
		ACS_NamedExecuteAlways("DND Clientside Syncer", 0, var, GetPlayerSyncValue(var, 0), 0);
}

void SyncAllClientsideVariables() {
	for(int i = 0; i < MAX_SYNC_VARS; ++i) {
		if(i == DND_SYNC_WEAPONENHANCE || i >= DND_SYNC_WEPBONUS_CRIT) {
			for(int j = 0; j < MAXWEPS; ++j)
				ACS_NamedExecuteAlways("DND Clientside Syncer", 0, i, GetPlayerSyncValue(i, j), j);
		}
		else
			ACS_NamedExecuteAlways("DND Clientside Syncer", 0, i, GetPlayerSyncValue(i, 0), 0);
	}
}

#endif