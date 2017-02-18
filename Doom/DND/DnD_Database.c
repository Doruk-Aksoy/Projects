#library "DND_DB"
#include "zcommon.acs"

#include "DnD_Common.h"
#include "DnD_MenuTables.h"

/*
-- PLAYER STUFF SAVE --

1) Save weapons in two ints, use bits. There are enough weapons to fit in 64 bits.
2) Save artifacts and accessories the same way, each occupying an int. For artifacts having more than 1 carryable value, use 2-3 bits.
3) Save player stats like this => 7 bits from an int for each stat, 4 stats can fit in this way. 5th stat can occupy its own int.
4) Save backpack counts to the 5th stat's int, starting from bit 8. Max backpack count is < 64, so 6 bits is enough. After the 14th bit, store the active accessory data. So 15th bit to 32th. 13 accessories.
5) Save all perk counts into an int. Max perk count is 10, so 4 bits needed. 6 perks, so 24 bits is enough.
6) Save health, armor and armor type to one int. Max health limit around 400, fits 9 bits. Armor is also the same. 18 bits. Armor type can follow from there with 13 armor types. 31 bits.
7) For every weapon ammo, safest way to go is use an int for each type. Their limits are dynamic and annoying to use bits with.
8) For Talents, each talent can go up to 100. 7 bits per talent. Store 4 talent per int. We need 3 ints.
9) For exp, level and credit use one int each.
10) For abilities use one int, each ability occupies one bit.
12) For researches, things are a bit tricky. A research can be 0 (NA), 1 (KNOWN) or 2 (DONE). We need 2 bits to state the value of a research. We got 29 researches atm. 2 x 29 = 58 bits. Use two ints.
12) Finally for leftover stat and perk points, use one int. A player can have at most 1023 stats, so 10 bits. Assuming the same for perks, 10 more bits for that.

*/

function int SetBit(int x, int n) {
	return x | (1 << n);
}

function void SavePlayerData(int pnum) {
	int temp, tid = pnum + P_TIDSTART, i, bit;
	// save weapons
	for(i = SHOP_WEAPON_BEGIN; i < 32; ++i)
		if(CheckActorInventory(tid, ShopItemNames[i][SHOPNAME_ITEM]))
			temp = SetBit(temp, i);
	// send temp over
	
	temp = 0;
	for(i = SHOP_WEAPON_BEGIN + 32; i < SHOP_LASTWEP_INDEX; ++i)
		if(CheckActorInventory(tid, ShopItemNames[i][SHOPNAME_ITEM]))
			temp = SetBit(temp, i);
	// send temp over
	
	// save stats of player (can fit 4 stats in one int, using 7 bits)
	temp = CheckActorInventory(tid, "PSTAT_Strength");
	temp |= (0x7F & CheckActorInventory(tid, "PSTAT_Dexterity")) << 7;
	temp |= (0x7F & CheckActorInventory(tid, "PSTAT_Bulkiness")) << 14;
	temp |= (0x7F & CheckActorInventory(tid, "PSTAT_Charisma")) << 21;
	// send temp over
	
	// save vitality, backpack count and active accessory
	temp = CheckActorInventory(tid, "PSTAT_Vitality");
	// backpack covers 6 bits max (count = 55 < 63)
	temp |= CheckActorInventory(tid, "BackpackCounter") << 6; // for backpack
	// assuming that there will never be more than 32 accessories, 5 bits per accessory index is enough.
	temp |= CheckActorInventory(tid, "Accessory_Top_Index") << 5; // for accessory
	temp |= CheckActorInventory(tid, "Accessory_Bot_Index") << 5; // same
	// send temp over
	
	// save perks (use 4 bits per perk, max is 10 for a perk)
	temp = CheckActorInventory(tid, "Perk_Sharpshooting");
	temp |= (0xF & CheckActorInventory(tid, "Perk_Endurance")) << 4;
	temp |= (0xF & CheckActorInventory(tid, "Perk_Wisdom")) << 8;
	temp |= (0xF & CheckActorInventory(tid, "Perk_Greed")) << 12;
	temp |= (0xF & CheckActorInventory(tid, "Perk_Medic")) << 16;
	temp |= (0xF & CheckActorInventory(tid, "Perk_Munitionist")) << 20;
	// send temp over
	
	// save health, armor and armor type
	temp = GetActorProperty(tid, APROP_HEALTH);
	temp <<= 9;
	for(i = 0; i < MAXARMORS; ++i) {
		bit = GetArmorType(ShopItemNames[i + SHOP_FIRSTARMOR_INDEX][SHOPNAME_ITEM], pnum);
		if(bit) {
			temp |= bit;
			bit = i;
			break;
		}
	}
	temp <<= 9;
	temp = SetBit(temp, i);
	// send temp over
	
	// save ammo counts
	for(i = 0; i < MAXSHOPAMMOS; ++i) {
		temp = CheckActorInventory(tid, AmmoInfo[i][AMMO_NAME]);
		// send temp over
	}
	
	// save talents (7 bits per talent, can save 4 talents in one int)
	temp = 0;
	for(i = 0; i < 4; ++i) {
		temp |= (0x3F & CheckActorInventory(tid, ShopItemNames[i + SHOP_TALENT_BEGIN][SHOPNAME_ITEM])) << (7 * i);
	}
	// send temp over
	
	temp = 0;
	for(i = 4; i < 10; ++i) {
		temp |= (0x3F & CheckActorInventory(tid, ShopItemNames[i + SHOP_TALENT_BEGIN][SHOPNAME_ITEM])) << (7 * i);
	}
	
	// save exp, credit and level (when loading give expvisual, amt = exp % levelcurve[level])
	temp = CheckActorInventory(tid, "Exp");
	// send temp over
	
	temp = CheckActorInventory(tid, "Credit");
	//send temp over
	
	temp = CheckActorInventory(tid, "Level");
	// send temp over
	
	// save abilities
	temp = 0;
	for(i = 0; i < MAXABILITIES; ++i) {
		if(CheckActorInventory(tid, AbilityInfo[i]))
			temp = SetBit(temp, i);
	}
	// send temp over
	
	// save unspent attribute/perk points
	temp = CheckActorInventory(tid, "AttributePoint");
	temp |= (0x3FF & CheckActorInventory(tid, "PerkPoint")) << 10;
	// send temp over
	
	// save accessories and artifacts
	temp = 0;
	for(i = 0; i < MAX_ACCESSORY; ++i) {
		if(CheckActorInventory(tid, StrParam(s:"Accessory_", d:i + 1)))
			temp = SetBit(temp, i);
	}
	// send temp over
	
	temp = 0;
	// fieldkits can have 3, assume 3 bits. (Maybe in future) Portable Shields hold 3 as well. Rest are all 1. Do not save automap.
	// Take fieldkit and portable shields last
	// this guy breaks the loop sequence so take him first
	temp |= CheckActorInventory(tid, "SalvationSphere");
	for(i = 0; i < MAXARTIFACTS - 3; ++i) {
		if(CheckActorInventory(tid, ArtifactInfo[i + 3][ARTI_NAME]))
			temp = SetBit(temp, i + 1); // because 0th bit is for salvation sphere
	}
	// at this point MAXARTIFACTS - 3 bits are occupied
	temp |= CheckActorInventory(tid, "FieldKit") << (MAXARTIFACTS - 2);
	temp |= CheckActorInventory(tid, "PortableShield") << (MAXARTIFACTS - 1);
	// send temp over
	
	temp = 0;
	// save researches
	
	// send temp over
	
	// save leftover stat and perk points, tuck the budget in there as well
	
	// send temp over
}

// Loads from database and gives necessary items
function void LoadPlayerData(int pnum) {
	int tid = P_TIDSTART + pnum;
	// parse the encoded data
	GiveActorInventory(tid, "ParsingData", 1); // prevents weapon tips from going crazy
}

// Handle all database stuff now
Script 894 UNLOADING {
	for(int i = 0; i < MAXPLAYERS; ++i) {
		if(PlayerInGame(i))
			SavePlayerData(i);
	}
}