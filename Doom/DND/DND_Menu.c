#library "DND_MENU"
#include "zcommon.acs"

#include "DnD_Common.h"
#include "DnD_MenuFuncs.h"

/*
- Main idea here is simple. There are two main scripts: One draws the menu CLIENTSIDE, the other receives button info and stuff from client and vital info from server.
- There are A TON of helper functions to formulate things. Getters are all over the place.
- Everything in the shop has an ID associated with it.
- Everything is flexible and can be customized very easily (!!!). The essential code for input listeners etc are provided, and can be changed at will depending on the menu pages to achieve
different behavior.

============= ADDING NEW WEAPONS TO SHOP =============

1) Add it to the DnD_Defs.h for the shop enum, weapon table, weapon desc and the shop names in here.
2) Add icon to the DrawHelpCornerImage
3) Add extra info to the weapon explanation
4) Add necessary cases to the clientside and serverside scripts under appropriate slot
*/

// Shows the menu
Script 900 (void) NET {
	if(StatListOpened[ActivatorTID()]) {
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
		DecideAccessories();
		//SetInventory("MenuPosY", 5);
		LocalAmbientSound("RPG/MenuClose", 127);
		ACS_ExecuteAlways(906, 0, 0);
	}
	else {
		if(!PlayerIsSpectator(PlayerNumber())) {
			SetPlayerProperty(0, 1, PROP_TOTALLYFROZEN);
			GiveInventory("P_Frozen", 1);
			StatListOpened[ActivatorTID()] = 1;
			SetInventory("ShowingMenu", 1);
			SetInventory("MenuOption", MENU_MAIN);
			SetInventory("MenuPosX", 0);
			SetInventory("MenuMainPosY", 0);
			LocalAmbientSound("RPG/MenuOpen", 127);
			ACS_ExecuteAlways(907, 0);
			ACS_ExecuteAlways(906, 0, 1);
		}
		else {
			SetHudSize(800, 600, 1);
			HudMessage(s: "You have to be in the game to use the menu"; HUDMSG_FADEINOUT, MENUUSEID, CR_GOLD, 400.4, 2.1, 4.0, 1.0, 1.0);
		}
	}
}

Script 904 (void) {
	while(CheckInventory("DnD_ShowPopup") || CheckInventory("DnD_ShowSellPopup"))
		Delay(1);
	TakeInventory("DnD_PopupHack", 1);
	TakeInventory("DnD_PopupError", 1);
	TakeInventory("DnD_PopupSell", 1);
}

Script 906 (int type) CLIENTSIDE {
	if(ConsolePlayerNumber() != PlayerNumber()) Terminate;
	if(!type) { // close the menu
		DeleteText(RPGMENUID);
		DeleteText(RPGMENUHELPID);
		DeleteText(RPGMENUNAMEID);
		DeleteText(RPGMENUHELPCORNERID);
		
		DeleteTextRange(RPGMENUINFOID, RPGMENULISTID);
		DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
	}
	else {
		int pnum = PlayerNumber();
		int animcounter = 0, framecounter = 0;
		int curposx, curposy, mainposy, curopt, curitem, price, color, popupid, drawlit;
		str toshow;
		while(CheckInventory("ShowingMenu") == 1) {
			curposx = CheckInventory("MenuPosX");
			curposy = CheckInventory("MenuPosY");
			mainposy = CheckInventory("MenuMainPosY");
			curopt = CheckInventory("MenuOption");
			popupid = CheckInventory("DnD_PopupId");
			drawlit = 0;
		
			SetHudSize(384, 200, 1);
			SetFont("DND_STAT");
			HudMessage(s:"A"; HUDMSG_PLAIN, RPGMENUID, -1, 192.0, 100.0, 0.0, 0.0);
			SetFont("SMALLFONT");
			SetHudSize(480, 320, 1);
			if(curopt == MENU_STAT1) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				
				HudMessage(s:"--- Player Stats ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0); 
			
				HudMessage(s:"\c[Y5]Level: \c-", d:CheckInventory("Level"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 192.1, 64.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Experience: \c-", d:CheckInventory("Exp"), s:" / ", d:LevelCurve[CheckInventory("Level") - 1]; HUDMSG_PLAIN, RPGMENUITEMID - 1, CR_WHITE, 192.1, 80.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID - 2, CR_WHITE, 192.1, 96.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Attribute Points: \c-", d:CheckInventory("AttributePoint"); HUDMSG_PLAIN, RPGMENUITEMID - 10, CR_WHITE, 192.1, 112.0, 0.0, 0.0);
								
				if(!curposx && !curposy)
					HudMessage(s:"\c[B1]Strength: \c-", d:STAT_BASE + CheckInventory("PSTAT_Strength"); HUDMSG_PLAIN, RPGMENUITEMID - 3, CR_WHITE, 192.1, 160.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Strength: \c-", d:STAT_BASE + CheckInventory("PSTAT_Strength"); HUDMSG_PLAIN, RPGMENUITEMID - 3, CR_WHITE, 192.1, 160.0, 0.0, 0.0);
				if(curposx == 1 && !curposy)
					HudMessage(s:"\c[B1]Dexterity: \c-", d:STAT_BASE + CheckInventory("PSTAT_Dexterity"); HUDMSG_PLAIN, RPGMENUITEMID - 4, CR_WHITE, 332.1, 160.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Dexterity: \c-", d:STAT_BASE + CheckInventory("PSTAT_Dexterity"); HUDMSG_PLAIN, RPGMENUITEMID - 4, CR_WHITE, 332.1, 160.0, 0.0, 0.0);
				if(!curposx && curposy == 1)
					HudMessage(s:"\c[B1]Bulkiness: \c-", d:STAT_BASE + CheckInventory("PSTAT_Bulkiness"); HUDMSG_PLAIN, RPGMENUITEMID - 5, CR_WHITE, 192.1, 176.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Bulkiness: \c-", d:STAT_BASE + CheckInventory("PSTAT_Bulkiness"); HUDMSG_PLAIN, RPGMENUITEMID - 5, CR_WHITE, 192.1, 176.0, 0.0, 0.0);
				if(curposx == 1 && curposy == 1)
					HudMessage(s:"\c[B1]Charisma: \c-", d:STAT_BASE + CheckInventory("PSTAT_Charisma"); HUDMSG_PLAIN, RPGMENUITEMID - 6, CR_WHITE, 332.1, 176.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Charisma: \c-", d:STAT_BASE + CheckInventory("PSTAT_Charisma"); HUDMSG_PLAIN, RPGMENUITEMID - 6, CR_WHITE, 332.1, 176.0, 0.0, 0.0);
				if(curposy == 2)
					HudMessage(s:"\c[B1]Vitality: \c-", d:STAT_BASE + CheckInventory("PSTAT_Vitality"); HUDMSG_PLAIN, RPGMENUITEMID - 7, CR_WHITE, 270.1, 192.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Vitality: \c-", d:STAT_BASE + CheckInventory("PSTAT_Vitality"); HUDMSG_PLAIN, RPGMENUITEMID - 7, CR_WHITE, 270.1, 192.0, 0.0, 0.0);
					
				if(curposy == MenuListenMax[MENU_STAT1].y) {
					if(!curposx) {
						HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 8, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 9, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
					}
					else {
						HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 8, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[B1]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 9, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
					}
				}
				else {
					HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 8, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 9, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
				}
				DrawHelpCornerMessage(MENU_STAT1, curposx, curposy);
			}
			else if(curopt == MENU_STAT2) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				
				HudMessage(s:"--- Current Gains ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"+ ", d:STR_GAIN * CheckInventory("PSTAT_Strength"), s:" melee damage"; HUDMSG_PLAIN, RPGMENUITEMID - 1, CR_WHITE, 208.1, 80.0, 0.0, 0.0);
				HudMessage(s:"+ ", d:2 * CheckInventory("PSTAT_Vitality"), s:" health capacity"; HUDMSG_PLAIN, RPGMENUITEMID - 2, CR_WHITE, 208.1, 96.0, 0.0, 0.0);
				HudMessage(s:"+ ", f:100 * DND_BULKINESS_GAIN * CheckInventory("PSTAT_Bulkiness"), s:"% armor efficiency"; HUDMSG_PLAIN, RPGMENUITEMID - 3, CR_WHITE, 208.1, 112.0, 0.0, 0.0);
				HudMessage(s:"+ ", f:DND_DEX_GAIN * CheckInventory("PSTAT_Dexterity"), s:"% talent bonus"; HUDMSG_PLAIN, RPGMENUITEMID - 4, CR_WHITE, 208.1, 128.0, 0.0, 0.0);
				HudMessage(s:"+ ", f:(0.5 * CheckInventory("PSTAT_Charisma")), s:"% discount"; HUDMSG_PLAIN, RPGMENUITEMID - 5, CR_WHITE, 208.1, 144.0, 0.0, 0.0);
				
				if(GetCVar("survival")) {
					HudMessage(s:"\c[Y5]Lives left: \c-", d:GetPlayerLivesLeft(PlayerNumber()); HUDMSG_PLAIN, RPGMENUITEMID - 6, CR_WHITE, 206.1, 208.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]Map Difficulty: \c-", s:MapDifficultyLabel[CheckInventory("MapDifficultyClientside")]; HUDMSG_PLAIN, RPGMENUITEMID - 7, CR_WHITE, 206.1, 224.0, 0.0, 0.0);
				}
				
				if(!curposx) {
					HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 8, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[B1]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 9, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
				}
				else {
					HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 8, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 9, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
				}
				
				DrawHelpCornerMessage(MENU_STAT2, curposx, curposy);
			}
			else if(curopt == MENU_PERK) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				
				HudMessage(s:"--- Player Perks ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0); 
				
				HudMessage(s:"\c[Y5]Perks Available: \c-", d:CheckInventory("PerkPoint"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 312.0, 64.0, 0.0, 0.0);
				
				if(!curposy)
					HudMessage(s:"\c[B1]Sharpshooting: \c-", d:CheckInventory("Perk_Sharpshooting"); HUDMSG_PLAIN, RPGMENUITEMID - 1, CR_WHITE, 184.1, 80.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Sharpshooting: \c-", d:CheckInventory("Perk_Sharpshooting"); HUDMSG_PLAIN, RPGMENUITEMID - 1, CR_WHITE, 184.1, 80.0, 0.0, 0.0);
				if(curposy == 1)
					HudMessage(s:"\c[B1]Endurance: \c-", d:CheckInventory("Perk_Endurance"); HUDMSG_PLAIN, RPGMENUITEMID - 2, CR_WHITE, 184.1, 96.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Endurance: \c-", d:CheckInventory("Perk_Endurance"); HUDMSG_PLAIN, RPGMENUITEMID - 2, CR_WHITE, 184.1, 96.0, 0.0, 0.0);
				if(curposy == 2)
					HudMessage(s:"\c[B1]Wisdom: \c-", d:CheckInventory("Perk_Wisdom"); HUDMSG_PLAIN, RPGMENUITEMID - 3, CR_WHITE, 184.1, 112.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Wisdom: \c-", d:CheckInventory("Perk_Wisdom"); HUDMSG_PLAIN, RPGMENUITEMID - 3, CR_WHITE, 184.1, 112.0, 0.0, 0.0);
				if(curposy == 3)
					HudMessage(s:"\c[B1]Greed: \c-", d:CheckInventory("Perk_Greed"); HUDMSG_PLAIN, RPGMENUITEMID - 4, CR_WHITE, 184.1, 128.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Greed: \c-", d:CheckInventory("Perk_Greed"); HUDMSG_PLAIN, RPGMENUITEMID - 4, CR_WHITE, 184.1, 128.0, 0.0, 0.0);
				if(curposy == 4)
					HudMessage(s:"\c[B1]Medic: \c-", d:CheckInventory("Perk_Medic"); HUDMSG_PLAIN, RPGMENUITEMID - 5, CR_WHITE, 184.1, 144.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Medic: \c-", d:CheckInventory("Perk_Medic"); HUDMSG_PLAIN, RPGMENUITEMID - 5, CR_WHITE, 184.1, 144.0, 0.0, 0.0);
				if(curposy == 5)
					HudMessage(s:"\c[B1]Munitionist: \c-", d:CheckInventory("Perk_Munitionist"); HUDMSG_PLAIN, RPGMENUITEMID - 6, CR_WHITE, 184.1, 160.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Munitionist: \c-", d:CheckInventory("Perk_Munitionist"); HUDMSG_PLAIN, RPGMENUITEMID - 6, CR_WHITE, 184.1, 160.0, 0.0, 0.0);
				
				if(curposy == MenuListenMax[MENU_PERK].y)
					HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 7, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 7, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					
					
				DrawHelpCornerMessage(MENU_PERK, 0, curposy);
			}
			else if(curopt == MENU_LOAD) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- Weapons Acquired ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0); 
				
				for(int i = 1; i < 9; ++i) {
					int shift = 0, overflow = 0;
					HudMessage(s:"\c[Y5]Slot ", d:i, s:":"; HUDMSG_PLAIN, RPGMENUITEMID - i + 1, CR_WHITE, 212.0, 44.0 + 26.0 * i, 0.0, 0.0);
					
					int prevstrlen = 0;
					for(int j = 0; j < MAXWEPS; ++j) {
						if(CheckInventory(Weapons[j][WEAPON_NAME]) && ParseInt(Weapons[j][WEAPON_SLOT]) == i) {
							str toshow = Weapons[j][WEAPON_TAG];
							HudMessage(s:toshow; HUDMSG_PLAIN, RPGMENUITEMID - MAXWEPS - j + 1, CR_WHITE, 244.1 + 8.0 * shift * prevstrlen - 56.0 * overflow, 44.0 + 26.0 * i + 13.0 * overflow, 0.0, 0.0); 
							++shift;
							prevstrlen = StrLen(toshow) + 1;
							if(shift > 1 && !overflow) {
								overflow = 1;
								prevstrlen = 0;
							}
						}
					}
					if(!curposx) {
						HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 1, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
					}
					else {
						HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 1, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[B1]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
					}
				}
				DrawHelpCornerMessage(MENU_LOAD, curposx, 0);
			}
			else if(curopt == MENU_LOAD2) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- Items Acquired ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0); 

				int yadd = 0;
				if(CheckInventory("FieldKit")) {
					HudMessage(s:"\c[Y5]Field Kits: \cj", d:CheckInventory("FieldKit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 184.1, 64.0, 0.0, 0.0);
					yadd += 16.0;
				}

				if(CheckInventory("Salvationsphere")) {
					HudMessage(s:"\c[Y5]Salvation Sphere: \cj", d:CheckInventory("Salvationsphere"); HUDMSG_PLAIN, RPGMENUITEMID - 1, CR_WHITE, 184.1, 64.0 + yadd, 0.0, 0.0);
					yadd += 16.0;
				}

				if(CheckInventory("PortableShield")) {
					HudMessage(s:"\c[Y5]Portable Shields: \cj", d:CheckInventory("PortableShield"); HUDMSG_PLAIN, RPGMENUITEMID - 2, CR_WHITE, 184.1, 64.0 + yadd, 0.0, 0.0);
					yadd += 16.0;
				}

				if(CheckInventory("BloodRune")) {
					HudMessage(s:"\c[Y5]Blood Rune: \cj", d:CheckInventory("BloodRune"); HUDMSG_PLAIN, RPGMENUITEMID - 3, CR_WHITE, 184.1, 64.0 + yadd, 0.0, 0.0);
					yadd += 16.0;
				}

				if(CheckInventory("TripleDamage")) {
					HudMessage(s:"\c[Y5]Triple Damage: \cj", d:CheckInventory("TripleDamage"); HUDMSG_PLAIN, RPGMENUITEMID - 4, CR_WHITE, 184.1, 64.0 + yadd, 0.0, 0.0);
					yadd += 16.0;
				}

				if(CheckInventory("BookofTheDead")) {
					HudMessage(s:"\c[Y5]Book of The Dead: \cj", d:CheckInventory("BookofTheDead"); HUDMSG_PLAIN, RPGMENUITEMID - 5, CR_WHITE, 184.1, 64.0 + yadd, 0.0, 0.0);
					yadd += 16.0;
				}
				
				if(CheckInventory("BladeVortex")) {
					HudMessage(s:"\c[Y5]Blade Vortex: \cj", d:CheckInventory("BladeVortex"); HUDMSG_PLAIN, RPGMENUITEMID - 6, CR_WHITE, 184.1, 64.0 + yadd, 0.0, 0.0);
//					yadd += 16;
				}

				if(!curposx) {
					HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 2, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[B1]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 1, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
				}
				else if(curposx == 1) {
					HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 2, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 1, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
				}
				else {
					HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 2, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 1, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[B1]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
				}
				
				DrawHelpCornerMessage(MENU_LOAD2, curposx, 0);
			}
			else if(curopt == MENU_LOAD3) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- Talents Acquired ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0); 
				
				for(int i = 0; i < MAX_TALENTS; ++i) {
					toshow = TalentTypeNamesCapital[i];
					HudMessage(s:"\c[Y5]", s:toshow, s:" Talent:"; HUDMSG_PLAIN, RPGMENUITEMID - i, CR_WHITE, 184.1, 64.0 + 16.0 * i, 0.0, 0.0);
					HudMessage(f:(DND_TALENT_INCREASE + DND_DEX_GAIN * CheckInventory("PSTAT_Dexterity")) * CheckInventory(TalentNames[i]), s:"%"; HUDMSG_PLAIN, RPGMENUITEMID - i - MAX_TALENTS, CR_WHITE, 448.2, 64.0 + 16.0 * i, 0.0, 0.0);
				}
				
				if(!curposx) {
					HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 2, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[B1]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 1, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
				}
				else if(curposx == 1) {
					HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 2, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 1, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
				}
				else {
					HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 2, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 1, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[B1]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
				}
				
				DrawHelpCornerMessage(MENU_LOAD3, curposx, 0);
			}
			else if(curopt == MENU_LOAD4) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- Current Accessories ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0); 
				
				toshow = CurrentAccessoryName(0, 1);
				if(!curposy) {
					HudMessage(s:"\c[B1]Slot One:\c- ", s:toshow; HUDMSG_PLAIN, RPGMENUITEMID - 2, CR_WHITE, 184.1, 96.0, 0.0, 0.0);
					curitem = CurrentAccessoryIndex(0);
					if(curitem)
						HudMessage(s:"* ", s:AccessoryExplanation[curitem]; HUDMSG_PLAIN, RPGMENUITEMID - 4, CR_WHITE, 184.1, 160.1, 0.0, 0.0);
					DrawHelpCornerImage(MENU_LOAD4, 0, 0);
				}
				else
					HudMessage(s:"\c[Y5]Slot One:\c- ", s:toshow; HUDMSG_PLAIN, RPGMENUITEMID - 2, CR_WHITE, 184.1, 96.0, 0.0, 0.0);

				toshow = CurrentAccessoryName(1, 1);
				if(curposy == 1) {
					HudMessage(s:"\c[B1]Slot Two:\c- ", s:toshow; HUDMSG_PLAIN, RPGMENUITEMID - 3, CR_WHITE, 184.1, 128.0, 0.0, 0.0);
					curitem = CurrentAccessoryIndex(1);
					if(curitem)
						HudMessage(s:"* ", s:AccessoryExplanation[curitem]; HUDMSG_PLAIN, RPGMENUITEMID - 4, CR_WHITE, 184.1, 160.1, 0.0, 0.0);
					DrawHelpCornerImage(MENU_LOAD4, 0, 1);
				}
				else
					HudMessage(s:"\c[Y5]Slot Two:\c- ", s:toshow; HUDMSG_PLAIN, RPGMENUITEMID - 3, CR_WHITE, 184.1, 128.0, 0.0, 0.0);
				
				if(curposy == MenuListenMax[MENU_LOAD4].y) {
					if(!curposx) {
						HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 1, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[B1]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
					}
					else {
						HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 1, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
					}
					DrawHelpCornerMessage(MENU_LOAD4, curposx, curposy);
				}
				else {
					HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 1, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
				}	
			}
			else if(curopt == MENU_SHOP) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				
				HudMessage(s:"--- DnD Shop ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID - 1, CR_WHITE, 264.1, 64.0, 0.0, 0.0);
				
				if(!curposy)
					HudMessage(s:"\c[B1]Weapons Menu"; HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 192.1, 96.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Weapons Menu"; HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 192.1, 96.0, 0.0, 0.0);

				if(curposy == 1)
					HudMessage(s:"\c[B1]Ammunition Menu"; HUDMSG_PLAIN, RPGMENUITEMID - 2, CR_WHITE, 192.1, 112.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Ammunition Menu"; HUDMSG_PLAIN, RPGMENUITEMID - 2, CR_WHITE, 192.1, 112.0, 0.0, 0.0);
				
				if(curposy == 2)
					HudMessage(s:"\c[B1]Abilities Menu"; HUDMSG_PLAIN, RPGMENUITEMID - 3, CR_WHITE, 192.1, 128.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Abilities Menu"; HUDMSG_PLAIN, RPGMENUITEMID - 3, CR_WHITE, 192.1, 128.0, 0.0, 0.0);
				
				if(curposy == 3)
					HudMessage(s:"\c[B1]Artifacts Menu"; HUDMSG_PLAIN, RPGMENUITEMID - 4, CR_WHITE, 192.1, 144.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Artifacts Menu"; HUDMSG_PLAIN, RPGMENUITEMID - 4, CR_WHITE, 192.1, 144.0, 0.0, 0.0);
				
				if(curposy == 4)
					HudMessage(s:"\c[B1]Talents Menu"; HUDMSG_PLAIN, RPGMENUITEMID - 5, CR_WHITE, 192.1, 160.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Talents Menu"; HUDMSG_PLAIN, RPGMENUITEMID - 5, CR_WHITE, 192.1, 160.0, 0.0, 0.0);

				if(curposy == 5)
					HudMessage(s:"\c[B1]Armors Menu"; HUDMSG_PLAIN, RPGMENUITEMID - 6, CR_WHITE, 192.1, 176.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Armors Menu"; HUDMSG_PLAIN, RPGMENUITEMID - 6, CR_WHITE, 192.1, 176.0, 0.0, 0.0);
					
				if(curposy == MenuListenMax[MENU_SHOP].y)
					HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 1, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMIDEND + 1, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				
				DrawHelpCornerMessage(MENU_SHOP, 0, curposy);
			}
			else if(curopt == MENU_SHOP_WEAPON) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- WEAPONS ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);
				
				for(int i = 0; i < 8; ++i) {
					if(curposy == i)
						HudMessage(s:"\c[B1]Slot ", d:i + 1, s:"\c- <--"; HUDMSG_PLAIN, RPGMENUITEMID - i - 1, CR_WHITE, 192.1, 96.0 + 16.0 * i, 0.0, 0.0);
					else
						HudMessage(s:"\c[Y5]Slot ", d:i + 1; HUDMSG_PLAIN, RPGMENUITEMID - i - 1, CR_WHITE, 192.1, 96.0 + 16.0 * i, 0.0, 0.0);
				}

				HudMessage(s:"\c[Y5]LEGEND\n* \c[J7][\c[S7]R\c[J7]] - Replaces slot weapon.\n* \c[J7][\c[E3]L\c[J7]] - Luxury weapon.\n\c[J7]        Can carry at most 1."; HUDMSG_PLAIN, RPGMENUITEMID - 17, CR_WHITE, 192.1, 240.0, 0.0, 0.0);

				if(curposy == MenuListenMax[MENU_SHOP_WEAPON].y)
					HudMessage(s:"\c[B1]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 16, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 16, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					
				DrawHelpCornerMessage(MENU_SHOP_WEAPON, 0, curposy);
			}
			else if(curopt == MENU_SHOP_WEAPON1) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- SLOT 1 ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);
			
				DrawToggledImage(SHOP_WEP_CSAW, 0, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot1Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_SICKLE, 1, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot1Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_EXCALIBAT, 2, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot1Replaced", 1, CR_RED);
				
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON1].y) {
					DrawHelpCornerMessage(MENU_SHOP_WEAPON1, 0, curposy);
					HudMessage(s:"\c[B1]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 16, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
				else {
					DrawHelpCornerImage(MENU_SHOP_WEAPON1, 0, curposy);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 16, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
			}
			else if(curopt == MENU_SHOP_WEAPON2) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- SLOT 2 ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);
				
				DrawToggledImage(SHOP_WEP_AKIMBOPISTOL, 0, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot2Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_MAGNUM, 1, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot2Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_LASERPISTOL, 2, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot2Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_SCATTERPISTOL, 3, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot2Luxury", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_RESPIS1, 4, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot2Replaced", 1, CR_RED);
			
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON2].y) {
					DrawHelpCornerMessage(MENU_SHOP_WEAPON2, 0, curposy);
					HudMessage(s:"\c[B1]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
				else {
					DrawHelpCornerImage(MENU_SHOP_WEAPON2, 0, curposy);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
			}
			else if(curopt == MENU_SHOP_WEAPON3) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- SLOT 3 ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);
				
				DrawToggledImage(SHOP_WEP_PURIFIER, 0, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot3Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_AUTOSG, 1, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot3Replaced", 1, CR_RED);	
				DrawToggledImage(SHOP_WEP_RESSG1, 2, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot3Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_HSSG, 3, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot3XReplaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_ERASUS, 4, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot3XReplaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_RESSSG1, 5, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot3XReplaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_SILVER, 6, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot3Luxury", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_SLAYER, 7, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot3Luxury", 1, CR_RED);
			
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON3].y) {
					DrawHelpCornerMessage(MENU_SHOP_WEAPON3, 0, curposy);
					HudMessage(s:"\c[B1]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
				else {
					DrawHelpCornerImage(MENU_SHOP_WEAPON3, 0, curposy);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
			}
			else if(curopt == MENU_SHOP_WEAPON4) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- SLOT 4 ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);
				
				DrawToggledImage(SHOP_WEP_HMG, 0, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot4Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_LEAD, 1, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot4Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_RESMG1, 2, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot4Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_MINIGUN, 3, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot4Luxury", 1, CR_RED);	
				DrawToggledImage(SHOP_WEP_EBONY, 4, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot4Luxury", 1, CR_RED);
			
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON4].y) {
					DrawHelpCornerMessage(MENU_SHOP_WEAPON4, 0, curposy);
					HudMessage(s:"\c[B1]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
				else {
					DrawHelpCornerImage(MENU_SHOP_WEAPON4, 0, curposy);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
			}
			else if(curopt == MENU_SHOP_WEAPON5) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- SLOT 5 ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);
				
				DrawToggledImage(SHOP_WEP_TORPEDO, 0, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot5Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_MERC, 1, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot5Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_RESRL1, 2, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot5Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_GRENADE, 3, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot5Luxury", 1, CR_RED);	
				DrawToggledImage(SHOP_WEP_ROTARYGL, 4, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot5Luxury", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_HEAVYML, 5, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot5Luxury", 1, CR_RED);
			
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON5].y) {
					DrawHelpCornerMessage(MENU_SHOP_WEAPON5, 0, curposy);
					HudMessage(s:"\c[B1]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
				else {
					DrawHelpCornerImage(MENU_SHOP_WEAPON5, 0, curposy);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
			}
			else if(curopt == MENU_SHOP_WEAPON6) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- SLOT 6 ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);
				
				DrawToggledImage(SHOP_WEP_NUCLEARPL, 0, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot6Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_TUREL, 1, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot6Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_RESPL1, 2, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot6Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_NAIL, 3, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot6Luxury", 1, CR_RED);	
				DrawToggledImage(SHOP_WEP_BASILISK, 4, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot6Luxury", 1, CR_RED);
			
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON6].y) {
					DrawHelpCornerMessage(MENU_SHOP_WEAPON6, 0, curposy);
					HudMessage(s:"\c[B1]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
				else {
					DrawHelpCornerImage(MENU_SHOP_WEAPON6, 0, curposy);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
			}
			else if(curopt == MENU_SHOP_WEAPON7) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- SLOT 7 ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);
				
				DrawToggledImage(SHOP_WEP_BFG, 0, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot7Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_DEVA, 1, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot7Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_MFG, 2, OBJ_WEP | OBJ_HASCHOICE, CR_WHITE, CR_GREEN, "P_Slot7Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_RESBFG1, 3, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot7Replaced", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_GAUSS, 4, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot7Luxury", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_RAIL, 5, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot7Luxury", 1, CR_RED);
			
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON7].y) {
					DrawHelpCornerMessage(MENU_SHOP_WEAPON7, 0, curposy);
					HudMessage(s:"\c[B1]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
				else {
					DrawHelpCornerImage(MENU_SHOP_WEAPON7, 0, curposy);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
			}
			else if(curopt == MENU_SHOP_WEAPON8) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- SLOT 8 ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);
				
				DrawToggledImage(SHOP_WEP_DEATHSTAFF, 0, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot8Luxury", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_RAZOR, 1, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot8Luxury", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_SUN, 2, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot8Luxury", 1, CR_RED);
				DrawToggledImage(SHOP_WEP_REAVER, 3, OBJ_WEP | OBJ_HASCHOICE | OBJ_RESEARCH, CR_WHITE, CR_GREEN, "P_Slot8Luxury", 1, CR_RED);
				
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON8].y) {
					DrawHelpCornerMessage(MENU_SHOP_WEAPON8, 0, curposy);
					HudMessage(s:"\c[B1]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
				else {
					DrawHelpCornerImage(MENU_SHOP_WEAPON8, 0, curposy);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
			}
			else if(curopt == MENU_SHOP_AMMO1) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- BASIC AMMUNITION ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);

				DrawToggledImage(SHOP_AMMO_CLIP, 0, OBJ_AMMO, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_SHELL, 1, OBJ_AMMO, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_ROCKET, 2, OBJ_AMMO, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_CELL, 3, OBJ_AMMO, CR_WHITE, CR_GREEN, 0, 0, 0);
				
				if(curposy == MenuListenMax[MENU_SHOP_AMMO1].y) {
					DrawHelpCornerMessage(MENU_SHOP_AMMO1, curposx, curposy);
					if(!curposx) {
						HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
					}
					else {
						HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[B1]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
					}
				}
				else {
					DrawHelpCornerImage(MENU_SHOP_AMMO1, 0, curposy);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
				}
			}
			else if(curopt == MENU_SHOP_AMMO2) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- RARE AMMUNITION (1) ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);

				DrawToggledImage(SHOP_AMMO_EXPSHELL, 0, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_EBONY, 1, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_EBONYX, 2, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_MIS, 3, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_GL, 4, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_NAIL, 5, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_BASILISK, 6, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_GAUSS, 7, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_SLAYER, 8, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				
				if(curposy == MenuListenMax[MENU_SHOP_AMMO2].y) {
					DrawHelpCornerMessage(MENU_SHOP_AMMO2, curposx, curposy);
					if(!curposx) {
						HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[B1]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 26, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
					}
					else if (curposx == 1) {
						HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 26, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
					}
					else {
						HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[B1]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 26, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
					}
				}
				else {
					DrawHelpCornerImage(MENU_SHOP_AMMO2, 0, curposy);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 26, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
				}
			}
            else if(curopt == MENU_SHOP_AMMO3) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- RARE AMMUNITION (2) ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);

				DrawToggledImage(SHOP_AMMO_PCAN, 0, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_METEOR, 1, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_FUEL, 2, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_ION, 3, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				
				if(curposy == MenuListenMax[MENU_SHOP_AMMO3].y) {
					DrawHelpCornerMessage(MENU_SHOP_AMMO3, curposx, curposy);
					if(!curposx) {
						HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[B1]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 26, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
					}
					else if (curposx == 1) {
						HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 26, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
					}
					else {
						HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[B1]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 26, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
					}
				}
				else {
					DrawHelpCornerImage(MENU_SHOP_AMMO3, 0, curposy);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 26, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
				}
            }
			else if(curopt == MENU_SHOP_AMMO_SPECIAL1) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- SPECIAL AMMUNITION ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);

				DrawToggledImage(SHOP_AMMO_FLECHETTE, 0, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_PIERCING, 1, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_ELECTRIC, 2, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_SONICGRENADE, 3, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_AMMO_HEGRENADE, 4, OBJ_AMMO | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				
				if(curposy == MenuListenMax[MENU_SHOP_AMMO_SPECIAL1].y) {
					DrawHelpCornerMessage(MENU_SHOP_AMMO_SPECIAL1, curposx, curposy);
					if(!curposx) {
						HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[B1]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
					}
					else {
						HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
					}
				}
				else {
					DrawHelpCornerImage(MENU_SHOP_AMMO_SPECIAL1, 0, curposy);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
				}
			}
			else if(curopt == MENU_SHOP_ABILITY) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				
				HudMessage(s:"--- ABILITIES ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);
				
				DrawToggledImage(SHOP_ABILITY_KICK, 0, OBJ_ABILITY, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_ABILITY_RELOAD, 1, OBJ_ABILITY, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_ABILITY_DASH, 2, OBJ_ABILITY, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_ABILITY_ARCANE, 3, OBJ_ABILITY | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_ABILITY_POISON, 4, OBJ_ABILITY | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_ABILITY_EXPLOSION, 5, OBJ_ABILITY | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_ABILITY_HEART, 6, OBJ_ABILITY | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_ABILITY_REGEN, 7, OBJ_ABILITY | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_ABILITY_TEMPORAL, 8, OBJ_ABILITY | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_ABILITY_SOUL, 9, OBJ_ABILITY | OBJ_RESEARCH, CR_WHITE, CR_GREEN, 0, 0, 0);
				DrawToggledImage(SHOP_ABILITY_MONSTERINFO, 10, OBJ_ABILITY, CR_WHITE, CR_GREEN, 0, 0, 0);

				if(curposy == MenuListenMax[MENU_SHOP_ABILITY].y)
					HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				
				DrawHelpCornerMessage(MENU_SHOP_ABILITY, 0, curposy);
			}
			else if(curopt == MENU_SHOP_ARTIFACT) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- ARTIFACTS ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);
				
				for(int i = 0; i < MAXARTIFACTS; ++i)
					DrawToggledImage(SHOP_FIRSTARTI_INDEX + i, i, ArtifactDrawInfo[i].flags, CR_WHITE, CR_GREEN, ArtifactInfo[i][ARTI_NAME], ShopInfo[SHOP_FIRSTARTI_INDEX + i][SHOPINFO_MAX], CR_RED);

				if(curposy == MenuListenMax[MENU_SHOP_ARTIFACT].y) {
					DrawHelpCornerMessage(MENU_SHOP_ARTIFACT, 0, curposy);
					HudMessage(s:"\c[B1]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
				else {
					DrawHelpCornerImage(MENU_SHOP_ARTIFACT, 0, curposy);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
			}
			else if(curopt == MENU_SHOP_TALENT) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- TALENTS ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);
				
				for(int i = 0; i < MAX_TALENTS; ++i)
					DrawToggledImage(SHOP_TALENT_BEGIN + i, i, OBJ_TALENT, CR_WHITE, CR_GREEN, TalentNames[i], TALENT_CAP, CR_RED);
			
				if(curposy == MenuListenMax[MENU_SHOP_TALENT].y)
					HudMessage(s:"\c[B1]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					
				DrawHelpCornerMessage(MENU_SHOP_TALENT, 0, curposy);
			}
			else if(curopt == MENU_SHOP_ARMOR1) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- COMMON ARMORS ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);
				
				for(int i  = 0; i < CLASSIC_ARMOR_COUNT; ++i)
					DrawToggledImage(SHOP_ARMOR_GREEN + i, i, ArmorDrawInfo[i].flags, CR_WHITE, CR_GREEN, "Armor", ArmorCapacities[i], CR_RED);
			
				if(curposy == MenuListenMax[MENU_SHOP_ARMOR1].y) {
					DrawHelpCornerMessage(MENU_SHOP_ARMOR1, curposx, curposy);
					if(!curposx) {
						HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
					}
					else {
						HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[B1]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
					}
				}
				else {
					DrawHelpCornerImage(MENU_SHOP_ARMOR1, 0, curposy);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]>>\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 356.0, 274.0, 0.0, 0.0);
				}
			}
			else if(curopt == MENU_SHOP_ARMOR2) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"--- RARE ARMORS ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				HudMessage(s:"\c[Y5]Credits: \c-$", d:CheckInventory("Credit"); HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 264.1, 64.0, 0.0, 0.0);
				
				for(int i  = 0; i < MAXARMORS - CLASSIC_ARMOR_COUNT; ++i)
					DrawToggledImage(SHOP_ARMOR_CYBERNETIC + i, i, ArmorDrawInfo[CLASSIC_ARMOR_COUNT + i].flags, CR_WHITE, CR_GREEN, "Armor", ArmorCapacities[i + CLASSIC_ARMOR_COUNT], CR_RED);
			
				if(curposy == MenuListenMax[MENU_SHOP_ARMOR2].y) {
					DrawHelpCornerMessage(MENU_SHOP_ARMOR2, curposx, curposy);
					if(!curposx) {
						HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[B1]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
					}
					else {
						HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
						HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
					}
				}
				else {
					DrawHelpCornerImage(MENU_SHOP_ARMOR2, 0, curposy);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]<<\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 25, CR_WHITE, 276.0, 274.0, 0.0, 0.0);
				}
			}
			else if(curopt == MENU_RESEARCH) {
				int budget = CheckInventory("Budget"), res_state = CheckResearchStatus(curposx);
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				
				HudMessage(s:"--- RESEARCH PANEL ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				if(budget)
					HudMessage(s:"\c[Y5]Budget: \c-", d:budget, s:"\cjK"; HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 280.1, 64.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Budget: \c-0"; HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 280.1, 64.0, 0.0, 0.0);
				
				HudMessage(s:"\c[Y5]Entry\c- #", d:ResearchEntryNumbers[curposx]; HUDMSG_PLAIN, RPGMENUITEMID - 11, CR_WHITE, 280.1, 80.0, 0.0, 0.0);
				if(res_state != RES_NA)
					HudMessage(s:"\c[Y5]Cost: \cj$\c-", d:ResearchCosts[curposx], s:"k"; HUDMSG_PLAIN, RPGMENUITEMID - 12, CR_WHITE, 280.1, 96.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Cost: ???\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 12, CR_WHITE, 280.1, 96.0, 0.0, 0.0);
				
				if(res_state < RES_DONE)
					SetFont("RESBLAK");
				else
					SetFont("RESDONE");
				HudMessage(s:"A"; HUDMSG_PLAIN, RPGMENUITEMID - 13, CR_WHITE, 192.1, 96.0, 0.0, 0.0);
				
				if(res_state == RES_NA)
					SetFont("RESNONE");
				else
					SetFont(StrParam(s:"RESBAK", d:curposx + 1));
				HudMessage(s:"A"; HUDMSG_PLAIN, RPGMENUITEMID - 14, CR_WHITE, 199.1, 96.0, 0.0, 0.0);
				
				SetFont("SMALLFONT");
				if(res_state != RES_NA)
					HudMessage(s:ResearchDescription[curposx]; HUDMSG_PLAIN, RPGMENUITEMID - 15, CR_WHITE, 192.1, 160.0, 0.0, 0.0);
				
				DrawHelpCornerMessage(MENU_RESEARCH, curposx, curposy);
				if(curposy == MenuListenMax[MENU_RESEARCH].y) {
					HudMessage(s:"\c[Y5]Research!"; HUDMSG_PLAIN, RPGMENUITEMID - 23, CR_WHITE, 316.0, 240.0, 0.0, 0.0);
					HudMessage(s:"\c[B1]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
				else {
					HudMessage(s:"\c[B1]Research!"; HUDMSG_PLAIN, RPGMENUITEMID - 23, CR_WHITE, 316.0, 240.0, 0.0, 0.0);
					HudMessage(s:"\c[Y5]RETURN"; HUDMSG_PLAIN, RPGMENUITEMID - 24, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				}
			}
			else if(curopt == MENU_ABILITY) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				
				HudMessage(s:"--- Abilities Learned ---"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0);
				
				for(int i = 0; i < MAXABILITIES; ++i) {
					toshow = "\c[G8]N/A";
					if(CheckInventory(ShopItemNames[SHOP_ABILITY_BEGIN + i][SHOPNAME_ITEM]))
						toshow = "\cdLearned\c-";
					if(curposy == i)
						HudMessage(s:"\c[B1]", s:ShopItemNames[SHOP_ABILITY_BEGIN + i][SHOPNAME_TAG], s:": \c-", s:toshow; HUDMSG_PLAIN, RPGMENUITEMID - i, CR_WHITE, 192.1, 80.0 + 16.0 * i, 0.0, 0.0);
					else
						HudMessage(s:"\c[Y5]", s:ShopItemNames[SHOP_ABILITY_BEGIN + i][SHOPNAME_TAG], s:": \c-", s:toshow; HUDMSG_PLAIN, RPGMENUITEMID - i, CR_WHITE, 192.1, 80.0 + 16.0 * i, 0.0, 0.0);
				}
					
				str dashstatus = "\cgDisabled";
				if(!CheckInventory("DashDisabled"))
					dashstatus = "\cdEnabled";
				if(curposy == MenuListenMax[MENU_ABILITY].y - 1) // always before return
					HudMessage(s:"\c[B1]Dash: ", s:dashstatus; HUDMSG_PLAIN, RPGMENUITEMID - 26, CR_WHITE, 192.1, 256.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Dash: ", s:dashstatus; HUDMSG_PLAIN, RPGMENUITEMID - 26, CR_WHITE, 192.1, 256.0, 0.0, 0.0);

				if(curposy == MenuListenMax[MENU_ABILITY].y)
					HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 27, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 27, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				
				DrawHelpCornerMessage(MENU_ABILITY, 0, curposy);
			}
			else if(curopt == MENU_MAIN) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);
				HudMessage(s:"Welcome to the DnD Menu!"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0); 
				
				HudMessage(s:"\cv*\c- Use \cd", 
						   k:"+forward", 
						   s:"\c-\n   and \cd", 
						   k:"+back", 
						   s:"\c-\n   keys to go up and down.\n\n\cv*\c- Use \cd", 
						   k:"+use", 
						   s:"\n\c-   or \cd",
						   k:"+attack",
						   s:"\c-\n   to select an option.\n\n\cv*\c- Use \cd",
						   k:"+moveleft",
						   s:"\c-\n   and \cd",
						   k:"+moveright",
						   s:"\c-\n   keys to go left and right.\n\n\cv*\c- Use \cd",
						   k:"+altattack",
						   s:"\c-\n   to sell weapons.\n\n\cv*\c- Use \cd",
						   k:"upgs",
						   s:"\c-\n   to leave.\n\n\cv*\c- You are frozen in place\n   during the menu. Do not die\n   while using it!"; 
				HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 304.0, 160.0, 0.0, 0.0);
				DrawHelpCornerMessage(MENU_MAIN, 0, mainposy);
			}
			else if(curopt == MENU_HELP) {
				DeleteTextRange(RPGMENUITEMIDEND, RPGMENUITEMID);

				HudMessage(s:"Additional Menu Help"; HUDMSG_PLAIN, RPGMENUHELPID, CR_CYAN, 316.4, 44.0, 0.0, 0.0); 
				
				HudMessage(s:"\cv*\c- Stat menu takes you to the\n   generic player stat screen.\n   You can also level your\n   stats there."; 
						   HUDMSG_PLAIN, RPGMENUITEMID, CR_WHITE, 184.1, 72.0, 0.0, 0.0);
				HudMessage(s:"\cv*\c- Perk menu takes you to the\n   perks screen. You can gain\n   your perks there."; 
						   HUDMSG_PLAIN, RPGMENUITEMID - 1, CR_WHITE, 184.1, 112.0, 0.0, 0.0);
				HudMessage(s:"\cv*\c- Loadout menu takes you to your\n   loaded equipments. See your \n   weapons, items and select\n   your accessories."; 
						   HUDMSG_PLAIN, RPGMENUITEMID - 2, CR_WHITE, 184.1, 152.0, 0.0, 0.0);
				HudMessage(s:"\cv*\c- Shop takes you to the equipment\n   shop. Buy items using your\n   earned credit."; 
						   HUDMSG_PLAIN, RPGMENUITEMID - 3, CR_WHITE, 184.1, 192.0, 0.0, 0.0);
				HudMessage(s:"\cv*\c- Abilities menu shows\n   the talents you've learned."; 
						   HUDMSG_PLAIN, RPGMENUITEMID - 4, CR_WHITE, 184.1, 224.0, 0.0, 0.0);
				
				str mapinfo = "\cgDisabled";
				if(CheckInventory("ShowMapInfo"))
					mapinfo = "\cdEnabled";
				if(!curposy)
					HudMessage(s:"\c[B1]Show Map Info: \c-", s:mapinfo; HUDMSG_PLAIN, RPGMENUITEMID - 5, CR_WHITE, 184.1, 244.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Show Map Info: \c-", s:mapinfo; HUDMSG_PLAIN, RPGMENUITEMID - 5, CR_WHITE, 184.1, 244.0, 0.0, 0.0);
					
				if(curposy == MenuListenMax[MENU_HELP].y)
					HudMessage(s:"\c[B1]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 6, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]RETURN\c-"; HUDMSG_PLAIN, RPGMENUITEMID - 6, CR_WHITE, 316.0, 274.0, 0.0, 0.0);
				
				DrawHelpCornerMessage(MENU_HELP, 0, curposy);
				
				if(CheckInventory("SetMapInfo")) {
					SetCVar("dnd_showmapinfo", !GetCVar("dnd_showmapinfo"));
					SetInventory("ShowMapInfo", !CheckInventory("ShowMapInfo"));
				}
			}
			
			// Main menu side bar
			
			// Side bar options with animations
			if(CheckInventory("AttributePoint") && !(framecounter % 2)) {
				if(!mainposy)
					drawlit = 1;
				HudMessage(s:"\c[B3]Stats\c-"; HUDMSG_PLAIN, RPGMENULISTID, -1, 96.0, 168.0, 0.0, 0.0);
			} 
			else {
				if(!mainposy)
					HudMessage(s:"\c[B1]Stats\c-"; HUDMSG_PLAIN, RPGMENULISTID, -1, 96.0, 168.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Stats\c-"; HUDMSG_PLAIN, RPGMENULISTID, -1, 96.0, 168.0, 0.0, 0.0);
			}
			
			if(CheckInventory("PerkPoint") && !(framecounter % 2)) {
				if(mainposy == 1)
					drawlit = 1;
				HudMessage(s:"\c[B3]Perks\c-"; HUDMSG_PLAIN, RPGMENULISTID - 1, -1, 96.0, 186.0, 0.0, 0.0);
			}
			else {
				if(mainposy == 1)
					HudMessage(s:"\c[B1]Perks\c-"; HUDMSG_PLAIN, RPGMENULISTID - 1, -1, 96.0, 186.0, 0.0, 0.0);
				else
					HudMessage(s:"\c[Y5]Perks\c-"; HUDMSG_PLAIN, RPGMENULISTID - 1, -1, 96.0, 186.0, 0.0, 0.0);
			}
			
			// Rest of the side bar options
			if(mainposy == 2)
				HudMessage(s:"\c[B1]Loadout\c-"; HUDMSG_PLAIN, RPGMENULISTID - 2, -1, 96.0, 204.0, 0.0, 0.0);
			else
				HudMessage(s:"\c[Y5]Loadout\c-"; HUDMSG_PLAIN, RPGMENULISTID - 2, -1, 96.0, 204.0, 0.0, 0.0);
			
			if(mainposy == 3)
				HudMessage(s:"\c[B1]Shop\c-"; HUDMSG_PLAIN, RPGMENULISTID - 3, -1, 96.0, 221.0, 0.0, 0.0);
			else
				HudMessage(s:"\c[Y5]Shop\c-"; HUDMSG_PLAIN, RPGMENULISTID - 3, -1, 96.0, 221.0, 0.0, 0.0);
			
			if(mainposy == 4)
				HudMessage(s:"\c[B1]Research\c-"; HUDMSG_PLAIN, RPGMENULISTID - 6, -1, 96.0, 251.0, 0.0, 0.0);
			else
				HudMessage(s:"\c[Y5]Research\c-"; HUDMSG_PLAIN, RPGMENULISTID - 6, -1, 96.0, 251.0, 0.0, 0.0);
			
			if(mainposy == 5)
				HudMessage(s:"\c[B1]Abilities\c-"; HUDMSG_PLAIN, RPGMENULISTID - 4, -1, 96.0, 269.0, 0.0, 0.0);
			else
				HudMessage(s:"\c[Y5]Abilities\c-"; HUDMSG_PLAIN, RPGMENULISTID - 4, -1, 96.0, 269.0, 0.0, 0.0);
			
			if(mainposy == 6)
				HudMessage(s:"\c[B1]Help\c-"; HUDMSG_PLAIN, RPGMENULISTID - 5, -1, 96.0, 287.0, 0.0, 0.0);
			else
				HudMessage(s:"\c[Y5]Help\c-"; HUDMSG_PLAIN, RPGMENULISTID - 5, -1, 96.0, 287.0, 0.0, 0.0);
			
			DrawHighLightBar(mainposy, drawlit);
			// Main Menu Side Bar Ends
			
			HudMessage(s:"\c[Y5]Survived: \cj", d:CheckInventory("RoundsSurvived"); HUDMSG_PLAIN, RPGMENUNAMEID, -1, 60.1, 140.0, 0.0, 0.0);
			
			// Handle all types of popups
			if(CheckInventory("DnD_ShowPopup") || CheckInventory("DnD_ShowSellPopup")) { // Handle error if we have to
				if(CheckInventory("DnD_PopupError"))
					HandlePopups(POPUP_ERROR, popupid);
				else if(CheckInventory("DnD_PopupSell"))
					HandlePopups(POPUP_SELL, popupid);
			}
			
			Delay(1);
			animcounter++;
			if(animcounter == 17) {
				animcounter = 0;
				framecounter = (++framecounter) % 3;
			}
		}
	}
}

Script 907 (void) {
	int curposx, curposy, mainposy, bpress, obpress, curopt, credit, price, itemid, buystatus = 0;
	int pnum = PlayerNumber();
	while(CheckInventory("ShowingMenu") == 1) { // first screen
		bpress = GetPlayerInput(-1, INPUT_BUTTONS);
		obpress = GetPlayerInput(-1, INPUT_OLDBUTTONS);
		curposx = CheckInventory("MenuPosX");
		curposy = CheckInventory("MenuPosY");
		mainposy = CheckInventory("MenuMainPosY");
		curopt = CheckInventory("MenuOption");
		credit = CheckInventory("Credit");
		
		// This handles the popup messages in the shop
		if(!CheckInventory("DnD_PopupHack") && CheckInventory("DnD_ShowPopup")) {
			GiveInventory("DnD_PopupHack", 1); // make this only execute one script
			ACS_ExecuteAlways(904, 0);
		}
		
		if(curopt == MENU_STAT1) { // stat screen
			ListenInput(LISTEN_UP | LISTEN_DOWN | LISTEN_LEFT | LISTEN_RIGHT, curposx, curposy, 0, MenuListenMax[MENU_STAT1].x, 0, MenuListenMax[MENU_STAT1].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(CheckInventory("AttributePoint")) { // tried to level stat, so you must have some attrib point
					if(!curposx && !curposy && CheckInventory("PSTAT_Strength") < STAT_MAX) { // str
						GiveInventory("PSTAT_Strength", 1);
						TakeInventory("AttributePoint", 1);
						LocalAmbientSound("RPG/MenuChoose", 127);
					}
					else if(curposx == 1 && !curposy && CheckInventory("PSTAT_Dexterity") < STAT_MAX) { // dex
						GiveInventory("PSTAT_Dexterity", 1);
						TakeInventory("AttributePoint", 1);
						LocalAmbientSound("RPG/MenuChoose", 127);
					}
					else if(!curposx && curposy == 1 && CheckInventory("PSTAT_Bulkiness") < STAT_MAX) { // bul
						GiveInventory("PSTAT_Bulkiness", 1);
//						GiveInventory("MaxArmorBonusNew", 2);
						TakeInventory("AttributePoint", 1);
						LocalAmbientSound("RPG/MenuChoose", 127);
					}
					else if(curposx == 1 && curposy == 1 && CheckInventory("PSTAT_Charisma") < STAT_MAX) { // chr
						GiveInventory("PSTAT_Charisma", 1);
						TakeInventory("AttributePoint", 1);
						LocalAmbientSound("RPG/MenuChoose", 127);
					}
					else if(curposy == 2 && CheckInventory("PSTAT_Vitality") < STAT_MAX) { // vit
						GiveInventory("PSTAT_Vitality", 1);
						GiveInventory("MaxHealthBonusNew", 2);
						TakeInventory("AttributePoint", 1);
						LocalAmbientSound("RPG/MenuChoose", 127);
					}
				}
				if(curposy == MenuListenMax[MENU_STAT1].y) {
					if(!curposx)
						ReturnToMain();
					else
						UpdateMenuPosition(0, 0, MENU_STAT2);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_STAT2) {
			ListenInput(LISTEN_LEFT | LISTEN_RIGHT, curposx, 0, 0, MenuListenMax[MENU_STAT2].x, 0, MenuListenMax[MENU_STAT2].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(!curposx) {
					SetInventory("MenuOption", MENU_STAT1);
					SetInventory("MenuPosX", 0);
					SetInventory("MenuPosY", 0);
				}
				else
					ReturnToMain();
				LocalAmbientSound("RPG/MenuChoose", 127);
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_PERK) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, MenuListenMax[MENU_PERK].x, 0, MenuListenMax[MENU_PERK].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(CheckInventory("PerkPoint")) { // tried to level perk, so you must have some perk point
					if(!curposy && CheckInventory("Perk_Sharpshooting") < PERK_MAX) { // sharp
						GiveInventory("Perk_Sharpshooting", 1);
						TakeInventory("PerkPoint", 1);
						if(CheckInventory("Perk_SharpShooting") > 1) // Take previous powerup so they don't stack
							TakeInventory(StrParam(s:"Damage_Perk_", d:(CheckInventory("Perk_Sharpshooting") - 1) * 5), 1);
						RestoreRPGStat(RES_PERK_SHARP);
						LocalAmbientSound("RPG/MenuChoose", 127);
					}
					else if(curposy == 1 && CheckInventory("Perk_Endurance") < PERK_MAX) { // end
						GiveInventory("Perk_Endurance", 1);
						TakeInventory("PerkPoint", 1);
						if(CheckInventory("Perk_Endurance") > 1) // Take previous powerup so they don't stack
							TakeInventory(StrParam(s:"Resist_Perk_", d:(CheckInventory("Perk_Endurance") - 1) * 5), 1);
						RestoreRPGStat(RES_PERK_ENDURANCE);
						LocalAmbientSound("RPG/MenuChoose", 127);
					}
					else if(curposy == 2 && CheckInventory("Perk_Wisdom") < PERK_MAX) { // wisdom
						GiveInventory("Perk_Wisdom", 1);
						TakeInventory("PerkPoint", 1);
						LocalAmbientSound("RPG/MenuChoose", 127);
					}
					else if(curposy == 3 && CheckInventory("Perk_Greed") < PERK_MAX) { // greed
						GiveInventory("Perk_Greed", 1);
						TakeInventory("PerkPoint", 1);
						LocalAmbientSound("RPG/MenuChoose", 127);
					}
					else if(curposy == 4 && CheckInventory("Perk_Medic") < PERK_MAX) { // medic
						GiveInventory("Perk_Medic", 1);
						SetAmmoCapacity("StoredMedkit", GetAmmoCapacity("StoredMedkit") + 15 * CheckInventory("Perk_Medic"));
						TakeInventory("PerkPoint", 1);
						LocalAmbientSound("RPG/MenuChoose", 127);
					}
					else if(curposy == 5 && CheckInventory("Perk_Munitionist") < PERK_MAX) { // medic
						GiveInventory("Perk_Munitionist", 1);
						TakeInventory("PerkPoint", 1);
						LocalAmbientSound("RPG/MenuChoose", 127);
					}
				}
				if(curposy == MenuListenMax[MENU_PERK].y) {
					ReturnToMain();
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_LOAD) {
			ListenInput(LISTEN_LEFT | LISTEN_RIGHT, curposx, 0, 0, MenuListenMax[MENU_LOAD].x, 0, 0);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(!curposx)
					ReturnToMain();
				else
					UpdateMenuPosition(2, 0, MENU_LOAD2);
				LocalAmbientSound("RPG/MenuChoose", 127);
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_LOAD2) {
			ListenInput(LISTEN_LEFT | LISTEN_RIGHT, curposx, 0, 0, MenuListenMax[MENU_LOAD2].x, 0, 0);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(!curposx)
					UpdateMenuPosition(1, 0, MENU_LOAD);
				else if(curposx == 1)
					ReturnToMain();
				else
					UpdateMenuPosition(2, 0, MENU_LOAD3);
				LocalAmbientSound("RPG/MenuChoose", 127);
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_LOAD3) {
			ListenInput(LISTEN_LEFT | LISTEN_RIGHT, curposx, 0, 0, MenuListenMax[MENU_LOAD3].x, 0, 0);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(!curposx)
					UpdateMenuPosition(1, 0, MENU_LOAD2);
				else if(curposx == 1)
					ReturnToMain();
				else
					UpdateMenuPosition(CurrentAccessoryIndex(0), 0, MENU_LOAD4);
				LocalAmbientSound("RPG/MenuChoose", 127);
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_LOAD4) {
			if(!curposy || curposy == 1) {
				int dir = curposx;
				ListenInput(LISTEN_UP | LISTEN_DOWN | LISTEN_LEFT | LISTEN_RIGHT | LIF_FIXATMAX_Y, curposx, curposy, 0, MenuListenMax[MENU_LOAD4].x, 0, MenuListenMax[MENU_LOAD4].y);
				if(CheckResearchStatus(RES_ACCESSORY) == RES_DONE) {
					dir -= CheckInventory("MenuPosX");
					ScrollAccessory(curposy, dir);
				}
			}
			else
				ListenInput(LISTEN_UP | LISTEN_DOWN | LISTEN_LEFT | LISTEN_RIGHT, curposx, curposy, 0, 1, 0, 2);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_LOAD4].y) {
					if(!curposx)
						UpdateMenuPosition(0, 0, MENU_LOAD3);
					else
						ReturnToMain();
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_SHOP) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, 0, 0, MenuListenMax[MENU_SHOP].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				int page = -1;
				if(!curposy)
					page = MENU_SHOP_WEAPON;
				else if(curposy == 1)
					page = MENU_SHOP_AMMO1;
				else if(curposy == 2)
					page = MENU_SHOP_ABILITY;
				else if(curposy == 3)
					page = MENU_SHOP_ARTIFACT;
				else if(curposy == 4)
					page = MENU_SHOP_TALENT;
				else if(curposy == 5)
					page = MENU_SHOP_ARMOR1;
				else if(curposy == MenuListenMax[MENU_SHOP].y)
					ReturnToMain();
				if(page != -1)
					UpdateMenuPosition(0, 0, page);
				SetInventory("MadeChoice", 0);
				LocalAmbientSound("RPG/MenuChoose", 127);
			}
		}
		else if(curopt == MENU_SHOP_WEAPON) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, 0, 0, MenuListenMax[MENU_SHOP_WEAPON].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON].y)
					UpdateMenuPosition(0, 0, MENU_SHOP);
				else if(curposy < MenuListenMax[MENU_SHOP_WEAPON].y)
					UpdateMenuPosition(0, 0, MENU_SHOP_WEAPON1 + curposy);
				LocalAmbientSound("RPG/MenuChoose", 127);
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_SHOP_WEAPON1) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, 0, 0, MenuListenMax[MENU_SHOP_WEAPON1].y);
			
			if(CheckInventory("MadeChoice") == 1) { // buy
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON1].y) {
					UpdateMenuPosition(0, 0, MENU_SHOP_WEAPON);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else {
					ProcessTrade(curposy, SHOP_WEP_CSAW, SHOP_WEP_EXCALIBAT, TRADE_BUY | TRADE_WEAPON);
				}
				SetInventory("MadeChoice", 0);
			}
			else if(CheckInventory("MadeChoice") == 2) // sell
				ProcessTrade(curposy, SHOP_WEP_CSAW, SHOP_WEP_EXCALIBAT, TRADE_SELL);
		}
		else if(curopt == MENU_SHOP_WEAPON2) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, 0, 0, MenuListenMax[MENU_SHOP_WEAPON2].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON2].y) {
					UpdateMenuPosition(0, 1, MENU_SHOP_WEAPON);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else {
					ProcessTrade(curposy, SHOP_WEP_AKIMBOPISTOL, SHOP_WEP_RESPIS1, TRADE_BUY | TRADE_WEAPON);
				}
				SetInventory("MadeChoice", 0);
			}
			else if(CheckInventory("MadeChoice") == 2)
				ProcessTrade(curposy, SHOP_WEP_AKIMBOPISTOL, SHOP_WEP_RESPIS1, TRADE_SELL);
		}
		else if(curopt == MENU_SHOP_WEAPON3) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, 0, 0, MenuListenMax[MENU_SHOP_WEAPON3].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON3].y) {
					UpdateMenuPosition(0, 2, MENU_SHOP_WEAPON);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else {
					ProcessTrade(curposy, SHOP_WEP_PURIFIER, SHOP_WEP_SLAYER, TRADE_BUY | TRADE_WEAPON);
				}
				SetInventory("MadeChoice", 0);
			}
			else if(CheckInventory("MadeChoice") == 2)
				ProcessTrade(curposy, SHOP_WEP_PURIFIER, SHOP_WEP_SLAYER, TRADE_SELL);
		}
		else if(curopt == MENU_SHOP_WEAPON4) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, 0, 0, MenuListenMax[MENU_SHOP_WEAPON4].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON4].y) {
					UpdateMenuPosition(0, 3, MENU_SHOP_WEAPON);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else {
					ProcessTrade(curposy, SHOP_WEP_HMG, SHOP_WEP_EBONY, TRADE_BUY | TRADE_WEAPON);
				}
				SetInventory("MadeChoice", 0);
			}
			else if(CheckInventory("MadeChoice") == 2)
				ProcessTrade(curposy, SHOP_WEP_HMG, SHOP_WEP_EBONY, TRADE_SELL);
		}
		else if(curopt == MENU_SHOP_WEAPON5) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, 0, 0, MenuListenMax[MENU_SHOP_WEAPON5].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON5].y) {
					UpdateMenuPosition(0, 4, MENU_SHOP_WEAPON);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else {
					ProcessTrade(curposy, SHOP_WEP_TORPEDO, SHOP_WEP_HEAVYML, TRADE_BUY | TRADE_WEAPON);
				}
				SetInventory("MadeChoice", 0);
			}
			else if(CheckInventory("MadeChoice") == 2)
				ProcessTrade(curposy, SHOP_WEP_TORPEDO, SHOP_WEP_HEAVYML, TRADE_SELL);
		}
		else if(curopt == MENU_SHOP_WEAPON6) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, 0, 0, MenuListenMax[MENU_SHOP_WEAPON6].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON6].y) {
					UpdateMenuPosition(0, 5, MENU_SHOP_WEAPON);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else {
					ProcessTrade(curposy, SHOP_WEP_NUCLEARPL, SHOP_WEP_BASILISK, TRADE_BUY | TRADE_WEAPON);
				}
				SetInventory("MadeChoice", 0);
			}
			else if(CheckInventory("MadeChoice") == 2)
				ProcessTrade(curposy, SHOP_WEP_NUCLEARPL, SHOP_WEP_BASILISK, TRADE_SELL);
		}
		else if(curopt == MENU_SHOP_WEAPON7) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, 0, 0, MenuListenMax[MENU_SHOP_WEAPON7].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON7].y) {
					UpdateMenuPosition(0, 6, MENU_SHOP_WEAPON);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else {
					ProcessTrade(curposy, SHOP_WEP_BFG, SHOP_WEP_RAIL, TRADE_BUY | TRADE_WEAPON);
				}
				SetInventory("MadeChoice", 0);
			}
			else if(CheckInventory("MadeChoice") == 2)
				ProcessTrade(curposy, SHOP_WEP_BFG, SHOP_WEP_RAIL, TRADE_SELL);
		}
		else if(curopt == MENU_SHOP_WEAPON8) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, 0, 0, MenuListenMax[MENU_SHOP_WEAPON8].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_WEAPON8].y) {
					UpdateMenuPosition(0, 7, MENU_SHOP_WEAPON);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else {
					ProcessTrade(curposy, SHOP_WEP_DEATHSTAFF, SHOP_WEP_REAVER, TRADE_BUY | TRADE_WEAPON);
				}
				SetInventory("MadeChoice", 0);
			}
			else if(CheckInventory("MadeChoice") == 2)
				ProcessTrade(curposy, SHOP_WEP_DEATHSTAFF, SHOP_WEP_REAVER, TRADE_SELL);
		}
		else if(curopt == MENU_SHOP_AMMO1) {
			ListenInput(LISTEN_UP | LISTEN_DOWN | LISTEN_LEFT | LISTEN_RIGHT, curposx, curposy, 0, MenuListenMax[MENU_SHOP_AMMO1].x, 0, MenuListenMax[MENU_SHOP_AMMO1].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_AMMO1].y) { // right move
					if(curposx == MenuListenMax[MENU_SHOP_AMMO1].x) {
						UpdateMenuPosition(0, 0, MENU_SHOP_AMMO2);
						LocalAmbientSound("RPG/MenuChoose", 127);
					}
					else { // return to shop
						UpdateMenuPosition(0, 1, MENU_SHOP);
						LocalAmbientSound("RPG/MenuChoose", 127);
					}
				}
				else {
					itemid = SHOP_FIRSTAMMO_INDEX + curposy;
					price = GetShopPrice(itemid, PRICE_CHARISMAREDUCE);
					buystatus = CanTrade(itemid, TRADE_BUY, price);
					if(!buystatus) {
						TakeInventory("Credit", price);
						LocalAmbientSound("items/ammo", 127);
						int amt = AmmoCounts[curposy];
						amt += ACS_ExecuteWithResult(918, 0, 1, amt);
						GiveInventory(AmmoInfo[curposy][AMMO_NAME], amt);
					}
					else {
						LocalAmbientSound("RPG/MenuError", 127);
						GiveInventory("DnD_ShowPopup", 1);
					}
				}
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_SHOP_AMMO2) {
			ListenInput(LISTEN_UP | LISTEN_DOWN | LISTEN_LEFT | LISTEN_RIGHT, curposx, curposy, 0, MenuListenMax[MENU_SHOP_AMMO2].x, 0, MenuListenMax[MENU_SHOP_AMMO2].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_AMMO2].y) { // return to shop
					if(curposx == MenuListenMax[MENU_SHOP_AMMO2].x) 
						UpdateMenuPosition(0, 0, MENU_SHOP_AMMO3);
					else if(curposx == 1) // back to ammo 1
						UpdateMenuPosition(0, 1, MENU_SHOP);
					else
						UpdateMenuPosition(1, 0, MENU_SHOP_AMMO1);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else {
					itemid = SHOP_FIRSTAMMO2_INDEX + curposy;
					price = GetShopPrice(itemid, PRICE_CHARISMAREDUCE);
					buystatus = CanTrade(itemid, TRADE_BUY, price);
					if(!buystatus) {
						TakeInventory("Credit", price);
						LocalAmbientSound("items/ammo", 127);
						int index = curposy + AMMO_PAGE2_BEGIN;
						int amt = AmmoCounts[index];
						amt += ACS_ExecuteWithResult(918, 0, 1, amt);
						GiveInventory(AmmoInfo[index][AMMO_NAME], amt);
					}
					else {
						LocalAmbientSound("RPG/MenuError", 127);
						GiveInventory("DnD_ShowPopup", 1);
					}
				}
				SetInventory("MadeChoice", 0);
			}
		}
        else if(curopt == MENU_SHOP_AMMO3) {
			ListenInput(LISTEN_UP | LISTEN_DOWN | LISTEN_LEFT | LISTEN_RIGHT, curposx, curposy, 0, MenuListenMax[MENU_SHOP_AMMO3].x, 0, MenuListenMax[MENU_SHOP_AMMO3].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_AMMO3].y) { // return to shop
					if(curposx == MenuListenMax[MENU_SHOP_AMMO3].x) 
						UpdateMenuPosition(0, 0, MENU_SHOP_AMMO_SPECIAL1);
					else if(curposx == 1) // back to ammo 1
						UpdateMenuPosition(0, 1, MENU_SHOP);
					else
						UpdateMenuPosition(1, 0, MENU_SHOP_AMMO2);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else {
					itemid = SHOP_FIRSTAMMO3_INDEX + curposy;
					price = GetShopPrice(itemid, PRICE_CHARISMAREDUCE);
					buystatus = CanTrade(itemid, TRADE_BUY, price);
					if(!buystatus) {
						TakeInventory("Credit", price);
						LocalAmbientSound("items/ammo", 127);
						int index = curposy + AMMO_PAGE3_BEGIN;
						int amt = AmmoCounts[index];
						amt += ACS_ExecuteWithResult(918, 0, 1, amt);
						GiveInventory(AmmoInfo[index][AMMO_NAME], amt);
					}
					else {
						LocalAmbientSound("RPG/MenuError", 127);
						GiveInventory("DnD_ShowPopup", 1);
					}
				}
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_SHOP_AMMO_SPECIAL1) {
			ListenInput(LISTEN_UP | LISTEN_DOWN | LISTEN_LEFT | LISTEN_RIGHT, curposx, curposy, 0, MenuListenMax[MENU_SHOP_AMMO_SPECIAL1].x, 0, MenuListenMax[MENU_SHOP_AMMO_SPECIAL1].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_AMMO_SPECIAL1].y) { // return to shop
					if(curposx == MenuListenMax[MENU_SHOP_AMMO_SPECIAL1].x) 
						UpdateMenuPosition(0, 1, MENU_SHOP);
					else
						UpdateMenuPosition(0, 0, MENU_SHOP_AMMO3);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else {
					itemid = SHOP_FIRSTAMMOSPECIAL_INDEX + curposy;
					price = GetShopPrice(itemid, PRICE_CHARISMAREDUCE);
					buystatus = CanTrade(itemid, TRADE_BUY, price);
					if(!buystatus) {
						TakeInventory("Credit", price);
						LocalAmbientSound("items/ammo", 127);
						int index = curposy + AMMO_PAGESPECIAL_BEGIN;
						int amt = AmmoCounts[index];
						amt += ACS_ExecuteWithResult(918, 0, 1, amt);
						GiveInventory(AmmoInfo[index][AMMO_NAME], amt);
					}
					else {
						LocalAmbientSound("RPG/MenuError", 127);
						GiveInventory("DnD_ShowPopup", 1);
					}
				}
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_SHOP_ABILITY) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, 0, 0, MenuListenMax[MENU_SHOP_ABILITY].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_ABILITY].y) {
					UpdateMenuPosition(0, 2, MENU_SHOP);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else if(curposy < MenuListenMax[MENU_SHOP_ABILITY].y) {
					itemid = SHOP_ABILITY_BEGIN + curposy;
					price = GetShopPrice(itemid, PRICE_CHARISMAREDUCE);
					buystatus = CanTrade(itemid, TRADE_BUY, price);
					if(!buystatus) {
						TakeInventory("Credit", price);
						LocalAmbientSound("Bonus/Received", 127);
						GiveInventory(AbilityInfo[itemid - SHOP_ABILITY_BEGIN], 1);
					}
					else {
						LocalAmbientSound("RPG/MenuError", 127);
						GiveInventory("DnD_ShowPopup", 1);
					}
				}
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_SHOP_ARTIFACT) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, 0, 0, MenuListenMax[MENU_SHOP_ARTIFACT].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_ARTIFACT].y) {
					UpdateMenuPosition(0, 3, MENU_SHOP);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else if(curposy < MenuListenMax[MENU_SHOP_ARTIFACT].y) {
					itemid = SHOP_FIRSTARTI_INDEX + curposy;
					price = GetShopPrice(itemid, PRICE_CHARISMAREDUCE);
					buystatus = CanTrade(itemid, TRADE_BUY, price);
					if(!buystatus) {
						TakeInventory("Credit", price);
						LocalAmbientSound("Bonus/Received", 127);
						GiveInventory(ShopItemNames[itemid][SHOPNAME_ITEM], 1);
					}
					else {
						LocalAmbientSound("RPG/MenuError", 127);
						GiveInventory("DnD_ShowPopup", 1);
					}
				}
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_SHOP_TALENT) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, 0, 0, MenuListenMax[MENU_SHOP_TALENT].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_TALENT].y) {
					UpdateMenuPosition(0, 4, MENU_SHOP);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else {
					ProcessTrade(curposy, SHOP_TALENT_BEGIN, SHOP_LASTTALENT_INDEX, TRADE_BUY | TRADE_TALENT);
				}
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_SHOP_ARMOR1) {
			ListenInput(LISTEN_UP | LISTEN_DOWN | LISTEN_LEFT | LISTEN_RIGHT, curposx, curposy, 0, MenuListenMax[MENU_SHOP_ARMOR1].x, 0, MenuListenMax[MENU_SHOP_ARMOR1].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_ARMOR1].y) {
					if(!curposx)
						UpdateMenuPosition(0, 5, MENU_SHOP);
					else
						UpdateMenuPosition(0, 0, MENU_SHOP_ARMOR2);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else {
					ProcessTrade(curposy, SHOP_ARMOR_GREEN, SHOP_ARMOR_RED, TRADE_BUY | TRADE_ARMOR);
				}
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_SHOP_ARMOR2) {
			ListenInput(LISTEN_UP | LISTEN_DOWN | LISTEN_LEFT | LISTEN_RIGHT, curposx, curposy, 0, MenuListenMax[MENU_SHOP_ARMOR2].x, 0, MenuListenMax[MENU_SHOP_ARMOR2].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_SHOP_ARMOR2].y) {
					if(curposx)
						UpdateMenuPosition(0, 5, MENU_SHOP);
					else
						UpdateMenuPosition(0, 0, MENU_SHOP_ARMOR1);
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else {
					ProcessTrade(curposy, SHOP_ARMOR_CYBERNETIC, SHOP_ARMOR_ENERGY, TRADE_BUY | TRADE_ARMOR);
				}
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_RESEARCH) {
			ListenInput(LISTEN_UP | LISTEN_DOWN | LISTEN_LEFT | LISTEN_RIGHT, curposx, curposy, 0, MenuListenMax[MENU_RESEARCH].x, 0, MenuListenMax[MENU_RESEARCH].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_RESEARCH].y) {
					LocalAmbientSound("RPG/MenuChoose", 127);
					ReturnToMain();
				}
				else if(curposy < MenuListenMax[MENU_RESEARCH].y) {
					buystatus = CanResearch(curposx);
					if(!buystatus) {
						TakeInventory("Budget", ResearchCosts[curposx]);
						LocalAmbientSound("items/research", 127);
						GiveInventory(StrParam(s:"Done_", s:Research_List[curposx]), 1);
						if(curposx == RES_MEDKITSTORE && !CheckInventory("MedkitItem"))
							GiveInventory("MedkitItem", 1);
						else if(curposx == RES_DOUBLESPECIALCAP)
							DoubleSpecialAmmoCapacity();
					}
					else {
						LocalAmbientSound("RPG/MenuError", 127);
						GiveInventory("DnD_ShowPopup", 1);
					}
				}
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_ABILITY) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, 0, 0, MenuListenMax[MENU_ABILITY].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(curposy == MenuListenMax[MENU_ABILITY].y - 1) {
					SetInventory("DashDisabled", !CheckInventory("DashDisabled"));
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				else if(curposy == MenuListenMax[MENU_ABILITY].y) {
					ReturnToMain();
					LocalAmbientSound("RPG/MenuChoose", 127);
				}
				SetInventory("MadeChoice", 0);
			}
		}
		else if(curopt == MENU_MAIN) {
			ListenInput(LISTEN_UP | LISTEN_DOWN | LIF_USEMAIN_Y, 0, mainposy, 0, 0, 0, MenuListenMax[MENU_MAIN].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(!mainposy)
					UpdateMenuPosition(0, 0, MENU_STAT1);
				else if(mainposy == 1)
					UpdateMenuPosition(0, 0, MENU_PERK);
				else if(mainposy == 2)
					UpdateMenuPosition(1, 0, MENU_LOAD);
				else if(mainposy == 3)
					UpdateMenuPosition(0, 0, MENU_SHOP);
				else if(mainposy == 4)
					UpdateMenuPosition(0, 0, MENU_RESEARCH);
				else if(mainposy == 5)
					UpdateMenuPosition(0, 0, MENU_ABILITY);
				else if(mainposy == MenuListenMax[MENU_MAIN].y)
					UpdateMenuPosition(0, 0, MENU_HELP);
				SetInventory("MadeChoice", 0);
				LocalAmbientSound("RPG/MenuChoose", 127);
			}
		}
		else if(curopt == MENU_HELP) {
			ListenInput(LISTEN_UP | LISTEN_DOWN, 0, curposy, 0, 0, 0, MenuListenMax[MENU_HELP].y);
			
			if(CheckInventory("MadeChoice") == 1) {
				if(!curposy)
					GiveInventory("SetMapInfo", 1);
				else
					ReturnToMain();
				SetInventory("MadeChoice", 0);
				LocalAmbientSound("RPG/MenuChoose", 127);
			}
		}
		Delay(1);
	}
}