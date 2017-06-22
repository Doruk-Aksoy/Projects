#include "DnD_MenuTables.h"

void UpdateMenuPosition(int x, int y, int option) {
	SetInventory("MenuPosX", x);
	SetInventory("MenuLR", 0);
	SetInventory("MenuOption", option);
	LocalAmbientSound("RPG/MenuChoose", 127);
}

str CurrentWeapon() {
	for(int i = 0; i < MAXWEPS; ++i)
		if(CheckWeapon(Weapons[i][WEAPON_TAG]))
			return Weapons[i][WEAPON_TAG];
	return " ";
}

int IsSpecialFixWeapon(int id) {
    for(int i = 0; i < MAX_SPECIALAMMOFIX_WEAPONS; ++i)
        if(SpecialAmmoFixWeapons[i][0] == id)
            return i;
    return -1;
}

int CheckItemRequirements (int req_id, int constraint) {
	int res = 1;
	for(int i = 0; i < MAX_RESEARCH_REQUIREMENTS; ++i) {
		if(ItemResearchRequirements[req_id][i] == -1)
			continue;
		if(CheckResearchStatus(ItemResearchRequirements[req_id][i]) < constraint) {
			res = 0;
			break;
		}
	}
	return res;
}

str GetTextWithResearch(str success, str fail, int req_id, int constraint) {
	if(req_id == -1 || CheckItemRequirements(req_id, constraint))
		return success;
	return fail;
}

int ParseInt(str InputString) {
    int ReturnValue = 0;
    int TempValue = 0;
    int TempInt = 0;
    int char = -65536;
    
    if(InputString == "") 
		return 0;
    
    for(int i = 0; i < StrLen(InputString); ++i) {
        char = GetChar(InputString, i);
        if(char != '1' && char != '2' &&
            char != '3' && char != '4' &&
            char != '5' && char != '6' &&
            char != '7' && char != '8' &&
            char != '9' && char != '0')
        { return 0; }
        else {
            switch(char) {
                case '0':
                    TempInt = 0;
                break;
                
                case '1':
                    TempInt = 1;
                break;
                
                case '2':
                    TempInt = 2;
                break;
                
                case '3':
                    TempInt = 3;
                break;
                
                case '4':
                    TempInt = 4;
                break;
                
                case '5':
                    TempInt = 5;
                break;
                
                case '6':
                    TempInt = 6;
                break;
                
                case '7':
                    TempInt = 7;
                break;
                
                case '8':
                    TempInt = 8;
                break;
                
                case '9':
                    TempInt = 9;
                break;
            }
            
            for(int x = ((StrLen(InputString) - 1) - i); x > 0; --x) { TempInt *= 10; }
            TempValue += TempInt;
        }
    }
    ReturnValue = TempValue;
    return ReturnValue;
}

void DeleteText(int textid) {
	HudMessage(s:""; HUDMSG_PLAIN, textid, -1, 160.0, 100.0, 0.0, 0.0);
}

void DeleteTextRange(int r1, int r2) {
	for(int i = 0; i < r2 - r1 + 1; i++)
		HudMessage(s:""; HUDMSG_PLAIN, r1 + i, -1, 160.0, 100.0, 0.0, 0.0);
}

// I seriously need to rewrite this shit...
void DrawHelpCornerMessage(int opt, int boxid) {
	int cornerid = RPGMENUHELPCORNERID;
	str toshow = "";
	if(opt == MENU_STAT1) {
		if(boxid == MBOX_1)
			toshow = "Increases\nMelee\nDamage\nby 4";
		else if(boxid == MBOX_2)
			toshow = "Increases\nTalent\nBonus\nby 0.15%";
		else if(boxid == MBOX_3)
			toshow = "Increases\nArmor\nEfficiency\nby 0.75%";
		else if(boxid == MBOX_4)
			toshow = "Reduces\nshop\nprices\nby 0.5%";
		else if(boxid == MBOX_5)
			toshow = "Increases\nHealth\nCapacity\nby 4";
		else if(boxid == MBOX_6)
			toshow = "Returns\nto Main\nMenu";
		else if(boxid == MBOX_7)
			toshow = "Stat\nGains";
	}
	else if(opt == MENU_STAT2) {
		if(boxid == MBOX_1)
			toshow = "Returns\nto Stat\nScreen";
		else if(boxid == MBOX_2)
			toshow = "Returns\nto Main\nMenu";
	}
	else if(opt == MENU_PERK) {
		switch (boxid) {
			case MBOX_1:
				toshow = "Increases\nDamage\nby 5%";
			break;
			case MBOX_2:
				toshow = "Reduces\nDamage\nTaken\nby 5%";
			break;
			case MBOX_3:
				toshow = "Increases\nexp gain\nby 10%";
			break;
			case MBOX_4:
				toshow = "Increases\ncredit\ngain by\n10%";
			break;
			case MBOX_5:
				toshow = "Increases\nHealing\nby 5";
			break;
			case MBOX_6:
				toshow = "Increases\nAmmo Ga-\nin by 10%";
			break;
			case MBOX_7:
				toshow = "Gives 2%\nChance to\nCritical\nStrike";
			break;
            case MBOX_8:
                toshow = "Returns\nto Main\nMenu";
            break;
			default:
				toshow = "";
			break;
		}
	}
	else if(opt == MENU_LOAD) {
		switch (boxid) {
			case MBOX_1:
				toshow = "Returns\nto Main\nMenu";
			break;
			case MBOX_2:
				toshow = "Goes\nto Item\nMenu";
			break;
			default:
				toshow = "";
			break;
		}
	}
	else if(opt == MENU_LOAD2) {
		switch (boxid) {
			case MBOX_1:
				toshow = "Goes\nto Weapon\nMenu";
			break;
			case MBOX_2:
				toshow = "Returns\nto Main\nMenu";
			break;
			case MBOX_3:
				toshow = "Goes\nto Talent\nMenu";
			break;
			default:
				toshow = "";
			break;
		}
	}
	else if(opt == MENU_LOAD3) {
		switch (boxid) {
			case MBOX_1:
				toshow = "Goes\nto Item\nMenu";
			break;
			case MBOX_2:
				toshow = "Returns\nto Main\nMenu";
			break;
			case MBOX_3:
				toshow = "Goes\nto Access-\nory Menu";
			break;
			default:
				toshow = "";
			break;
		}
	}
	else if(opt == MENU_LOAD4) {
		switch (boxid) {
			case MBOX_1:
					toshow = "Goes\nto Talent\nMenu";
			break;
			case MBOX_2:
					toshow = "Returns\nto Main\nMenu";
			break;
			default:
				toshow = "";
			break;
		}
	}
	else if(opt == MENU_ABILITY) {
		toshow = AbilityHelpText[boxid];
	}
	else if(opt == MENU_SHOP) {
		switch(boxid) {
			case MBOX_1:
				toshow = "Weapon\nMenu";
			break;
			case MBOX_2:
				toshow = "Ammo\nMenu";
			break;
			case MBOX_3:
				toshow = "Ability\nMenu";
			break;
			case MBOX_4:
				toshow = "Artifact\nMenu";
			break;
			case MBOX_5:
				toshow = "Talent\nMenu";
			break;
			case MBOX_6:
				toshow = "Armor\nMenu";
			break;
			case MBOX_7:
				toshow = "Returns\nto Main\nMenu";
			break;
			default:
				toshow = "";
			break;
		}
	}
	else if(opt == MENU_SHOP_WEAPON) {
		if(boxid < MBOX_9)
			toshow = StrParam(s:"Slot ", d:boxid, s:"\nMenu");
		else if(boxid == MBOX_9)
			toshow = "Returns\nto Shop\nMenu";
	}
	else if(opt >= MENU_SHOP_WEAPON1 && opt <= MENU_SHOP_WEAPON8) {
		if(boxid == MenuListenMax[opt].y + 1)
			toshow = "Returns\nto Weapon\nMenu";
	}
	else if(opt == MENU_SHOP_AMMO1) {
		if(boxid == MBOX_5)
			toshow = "Returns\nto Shop\nMenu";
		else if(boxid == MBOX_6)
			toshow = "Rare\nAmmo\nMenu 1";
	}
	else if(opt == MENU_SHOP_AMMO2) {
		if(boxid == MBOX_10)
			toshow = "Basic\nAmmo\nMenu";
		else if(boxid == MBOX_11)
			toshow = "Returns\nto Shop\nMenu";
		else if(boxid == MBOX_12)
			toshow = "Rare\nAmmo\nMenu 2";
	}
	else if(opt == MENU_SHOP_AMMO3) {
		if(boxid == MBOX_8)
			toshow = "Rare\nAmmo\nMenu 1";
		else if(boxid == MBOX_9)
			toshow = "Returns\nto Shop\nMenu";
		else if(boxid == MBOX_10)
			toshow = "Special\nAmmo\nMenu";
	}
	else if(opt == MENU_SHOP_AMMO_SPECIAL1) {
		if(boxid == MBOX_7)
			toshow = "Rare\nAmmo\nMenu 2";
		else if(boxid == MBOX_8)
			toshow = "Returns\nto Shop\nMenu";
	}
	else if(opt == MENU_SHOP_ABILITY) {
		if(boxid != MBOX_12)
			toshow = GetTextWithResearch(AbilityHelpText[boxid - 1], "N/A", SHOP_ABILITY_KICK + boxid - 1, RES_KNOWN);
		else
			toshow = "Returns\nto Shop\nMenu";
	}
	else if(opt == MENU_SHOP_ARTIFACT) {
		if(boxid == MBOX_11)
			toshow = "Returns\nto Shop\nMenu";
	}
	else if(opt == MENU_SHOP_TALENT) {
		if(boxid == MenuListenMax[MENU_SHOP_TALENT].y)
			toshow = "Returns\nto Shop\nMenu";
		else
			toshow = TalentHelpCornerMessage[boxid];
	}
	else if(opt == MENU_SHOP_ARMOR1) {
		if(boxid == MBOX_10)
			toshow = "Returns\nto Shop\nMenu";
		else if(boxid == MBOX_11)
			toshow = "Rare\nArmor\nMenu";
	}
	else if(opt == MENU_SHOP_ARMOR2) {
		if(boxid == MBOX_6)
			toshow = "Common\nArmor\nMenu";
		else if(boxid == MBOX_7)
			toshow = "Returns\nto Shop\nMenu";
	}
	else if(opt == MENU_RESEARCH) {
		if(boxid == MenuListenMax[MENU_RESEARCH].y)
			toshow = "Returns\nto Main\nMenu";
		else
			toshow = "Do a\nResearch";
	}
	else if(opt == MENU_MAIN) {
		cornerid = RPGMENUHELPCORNERIDMAIN;
		switch (boxid) {
			case MBOX_1:
				toshow = "Stat\nScreen";
			break;
			case MBOX_2:
				toshow = "Perk\nScreen";
			break;
			case MBOX_3:
				toshow = "Current\nInventory";
			break;
			case MBOX_4:
				toshow = "The\nShop";
			break;
			case MBOX_5:
				toshow = "Research\nScreen";
			break;
			case MBOX_6:
				toshow = "Abilities\nLearned";
			break;
			case MBOX_7:
				toshow = "Controls";
			break;
			default:
				toshow = "";
			break;
		}
	}
	else if(opt == MENU_HELP) {
		switch(boxid) {
			case MBOX_1:
				toshow = "Toggles\nhud map\ninfo";
			break;
			case MBOX_2:
				toshow = "Returns\nto Main\nMenu";
			break;
		}
	}
	if(boxid == MAINBOX_NONE)
		HudMessage(s:""; HUDMSG_PLAIN, cornerid, CR_CYAN, 62.1, 32.1, 0.0, 0.0);
	else
		HudMessage(s:toshow; HUDMSG_PLAIN, cornerid, CR_CYAN, 62.1, 32.1, 0.0, 0.0);
}

void DrawHelpCornerImage (int opt, int posx, int posy) {
	str toshow = "";
	if(posy == MAINBOX_NONE) {
		HudMessage(s:""; HUDMSG_PLAIN, RPGMENUHELPCORNERID, CR_CYAN, 92.1, 56.1, 0.0, 0.0);
		return;
	}
	--posy;
	if(opt == MENU_LOAD4) {
		if(posy < 2)
			toshow = AccessoryImages[CurrentAccessoryIndex(posy)];
		else
			toshow = "TNT1A0";
	}
	else if(opt == MENU_SHOP_AMMO1) {
		if(posy < MenuListenMax[MENU_SHOP_AMMO1].y)
			toshow = AmmoInfo[posy][AMMO_ICON];
		else
			toshow = "TNT1A0";
	}
	else if(opt == MENU_SHOP_AMMO2) {
		if(posy < MenuListenMax[MENU_SHOP_AMMO2].y)
			toshow = GetTextWithResearch(AmmoInfo[posy + AMMO_PAGE2_BEGIN][AMMO_ICON], "TNT1A0", SHOP_AMMO_EXPSHELL + posy, RES_KNOWN);
		else
			toshow = "TNT1A0";
	}
	else if(opt == MENU_SHOP_AMMO3) {
		if(posy < MenuListenMax[MENU_SHOP_AMMO3].y)
			toshow = GetTextWithResearch(AmmoInfo[posy + AMMO_PAGE3_BEGIN][AMMO_ICON], "TNT1A0", SHOP_AMMO_PCAN + posy, RES_KNOWN);
		else
			toshow = "TNT1A0";
	}
	else if(opt == MENU_SHOP_AMMO_SPECIAL1) {
		if(posy < MenuListenMax[MENU_SHOP_AMMO_SPECIAL1].y)
			toshow = GetTextWithResearch(AmmoInfo[posy + AMMO_PAGESPECIAL_BEGIN][AMMO_ICON], "TNT1A0", SHOP_AMMO_FLECHETTE + posy, RES_KNOWN);
		else
			toshow = "TNT1A0";
	}
	else if(opt == MENU_SHOP_WEAPON1) {
		if(!posy)
			toshow = "CSW2A0";
		else if(posy == 1)
			toshow = GetTextWithResearch("SICKLICO", "TNT1A0", SHOP_WEP_SICKLE, RES_KNOWN);
		else if(posy == 2)
			toshow = GetTextWithResearch("EBATICO2", "TNT1A0", SHOP_WEP_EXCALIBAT, RES_KNOWN);
		else
			toshow = "TNT1A0";
	}
	else if(opt == MENU_SHOP_WEAPON2) {
		if(!posy)
			toshow = "AKIMICO";
		else if(posy == 1)
			toshow = "MAGNICO";
		else if(posy == 2)
			toshow = "PBLTZ0";
		else if(posy == 3)
			toshow = "SPPPA0";
		else if(posy == 4)
			toshow = GetTextWithResearch("4AFLA0", "TNT1A0", SHOP_WEP_RESPIS1, RES_KNOWN);
		else
			toshow = "TNT1A0";
	}
	else if(opt == MENU_SHOP_WEAPON3) {
		if(!posy)
			toshow = "SGP2Z0";
		else if(posy == 1)
			toshow = "UASGICO";
		else if(posy == 2)
			toshow = GetTextWithResearch("RW01X0", "TNT1A0", SHOP_WEP_RESSG1, RES_KNOWN);
		else if(posy == 3)
			toshow = GetTextWithResearch("WBOWA0", "TNT1A0", SHOP_WEP_RESSG2, RES_KNOWN);
		else if(posy == 4)
			toshow = "HSSGICO";
		else if(posy == 5)
			toshow = "ERASICO";
		else if(posy == 6)
			toshow = GetTextWithResearch("RW02]0", "TNT1A0", SHOP_WEP_RESSSG1, RES_KNOWN);
		else if(posy == 7)
			toshow = GetTextWithResearch("EXSGX0", "TNT1A0", SHOP_WEP_SILVER, RES_KNOWN);
		else if(posy == 8)
			toshow = GetTextWithResearch("SLYPA0", "TNT1A0", SHOP_WEP_SLAYER, RES_KNOWN);
		else
			toshow = "TNT1A0";
	}
	else if(opt == MENU_SHOP_WEAPON4) {
		if(!posy)
			toshow = "WSG2ICO";
		else if(posy == 1)
			toshow = "QWOPA0";
		else if(posy == 2)
			toshow = GetTextWithResearch("RW03X0", "TNT1A0", SHOP_WEP_RESMG1, RES_KNOWN);
		else if(posy == 3)
			toshow = GetTextWithResearch("RIOTI0", "TNT1A0", SHOP_WEP_RESMG2, RES_KNOWN);
		else if(posy == 4)
			toshow = GetTextWithResearch("CHNGX0", "TNT1A0", SHOP_WEP_MINIGUN, RES_KNOWN);
		else if(posy == 5)
			toshow = GetTextWithResearch("EBONICO", "TNT1A0", SHOP_WEP_EBONY, RES_KNOWN);
		else
			toshow = "TNT1A0";
	}
	else if(opt == MENU_SHOP_WEAPON5) {
		if(!posy)
			toshow = "WPPKG0";
		else if(posy == 1)
			toshow = "MERCX0";
		else if(posy == 2)
			toshow = GetTextWithResearch("RW06X0", "TNT1A0", SHOP_WEP_RESRL1, RES_KNOWN);
		else if(posy == 3)
			toshow = GetTextWithResearch("NGLPA0", "TNT1A0", SHOP_WEP_GRENADE, RES_KNOWN);
		else if(posy == 4)
			toshow = GetTextWithResearch("RTGLICO", "TNT1A0", SHOP_WEP_ROTARYGL, RES_KNOWN);
		else if(posy == 5)
			toshow = GetTextWithResearch("WMLNA0", "TNT1A0", SHOP_WEP_HEAVYML, RES_KNOWN);
		else
			toshow = "TNT1A0";
	}
	else if(opt == MENU_SHOP_WEAPON6) {
		if(!posy)
			toshow = "QNPLX0";
		else if(posy == 1)
			toshow = "TURLX0";
		else if(posy == 2)
			toshow = GetTextWithResearch("RW05X0", "TNT1A0", SHOP_WEP_RESPL1, RES_KNOWN);
		else if(posy == 3)
			toshow = GetTextWithResearch("LTGSA0", "TNT1A0", SHOP_WEP_RESPL2, RES_KNOWN);
		else if(posy == 4)
			toshow = GetTextWithResearch("NAIGA0", "TNT1A0", SHOP_WEP_NAIL, RES_KNOWN);
		else if(posy == 5)
			toshow = GetTextWithResearch("BASICO", "TNT1A0", SHOP_WEP_BASILISK, RES_KNOWN);
		else
			toshow = "TNT1A0";
	}
	else if(opt == MENU_SHOP_WEAPON7) {
		if(!posy)
			toshow = "DEBFA0";
		else if(posy == 1)
			toshow = "DEVAZ0";
		else if(posy == 2)
			toshow = "BFGPA0";
		else if(posy == 3)
			toshow = GetTextWithResearch("RW04X0", "TNT1A0", SHOP_WEP_RESBFG1, RES_KNOWN);
		else if(posy == 4)
			toshow = GetTextWithResearch("GAUSZ0", "TNT1A0", SHOP_WEP_GAUSS, RES_KNOWN);
		else if(posy == 5)
			toshow = GetTextWithResearch("WRALA0", "TNT1A0", SHOP_WEP_RAIL, RES_KNOWN);
		else 
			toshow = "TNT1A0";
	}
	else if(opt == MENU_SHOP_WEAPON8) {
		if(!posy)
			toshow = GetTextWithResearch("LICICO2", "TNT1A0", SHOP_WEP_DEATHSTAFF, RES_KNOWN);
		else if(posy == 1)
			toshow = GetTextWithResearch("WRAZA0", "TNT1A0", SHOP_WEP_RAZOR, RES_KNOWN);
		else if(posy == 2)
			toshow = GetTextWithResearch("SUNICO2", "TNT1A0", SHOP_WEP_SUN, RES_KNOWN);
		else if(posy == 3)
			toshow = GetTextWithResearch("REAVICO", "TNT1A0", SHOP_WEP_REAVER, RES_KNOWN);
		else
			toshow = "TNT1A0";
	}
	else if(opt == MENU_SHOP_ARTIFACT) {
		if(posy < MBOX_11) {
			toshow = GetTextWithResearch(ArtifactInfo[posy][ARTI_ICON], "TNT1A0", ArtifactDrawInfo[posy].res_id, RES_KNOWN);
		}
		else
			toshow = "TNT1A0";
	}
	else if(opt == MENU_SHOP_ARMOR1) {
		if(posy < MenuListenMax[MENU_SHOP_ARMOR1].y)
			toshow = GetTextWithResearch(ArmorImages[posy], "TNT1A0", ArmorDrawInfo[posy].res_id, RES_KNOWN);
		else
			toshow = "TNT1A0";
	}
	else if(opt == MENU_SHOP_ARMOR2) {
		if(posy < MenuListenMax[MENU_SHOP_ARMOR2].y)
			toshow = GetTextWithResearch(ArmorImages[posy + PAGE1_ARMOR_COUNT], "TNT1A0", ArmorDrawInfo[posy + PAGE1_ARMOR_COUNT].res_id, RES_KNOWN);
		else
			toshow = "TNT1A0";
	}
	
	SetFont(toshow);
	HudMessage(s:"A"; HUDMSG_PLAIN, RPGMENUHELPCORNERID, CR_CYAN, 92.1, 56.1, 0.0, 0.0);
	SetFont("SMALLFONT");
}

str CurrentAccessoryName (int slot, int type) {
	str tocheck = "Accessory_Top_Index";
	if(slot)
		tocheck = "Accessory_Bot_Index";
	if(type == 1)
		return AccessoryNames[CheckInventory(tocheck)];
	return AccessoryExplanation[CheckInventory(tocheck)];
}

int CurrentAccessoryIndex (int slot) {
	if(!slot)
		return CheckInventory("Accessory_Top_Index");
	return CheckInventory("Accessory_Bot_Index");
}

// gets item type
int GetItemType(int id) {
	if(id <= SHOP_LASTWEP_INDEX)
		return TYPE_WEAPON;
	else if(id <= SHOP_LASTAMMO_SPECIALINDEX)
		return TYPE_AMMO;
	else if(id <= SHOP_LASTABILITY_INDEX)
		return TYPE_ABILITY;
	else if(id <= SHOP_LASTTALENT_INDEX)
		return TYPE_TALENT;
	else if(id <= SHOP_LASTARMOR_INDEX)
		return TYPE_ARMOR;
	else
		return TYPE_ARTI;
	return TYPE_WEAPON;
}

int ShopScale(int amount, int id) {
	int type = GetItemType(id);
	switch(type) {
		case TYPE_WEAPON:
		return amount * Clamp_Between(GetCVar("dnd_shop_wep_scale"), 1, SHOP_SCALE_MAX);
		case TYPE_AMMO:
		return amount * Clamp_Between(GetCVar("dnd_shop_ammo_scale"), 1, SHOP_SCALE_MAX);
		case TYPE_ABILITY:
		return amount * Clamp_Between(GetCVar("dnd_shop_ability_scale"), 1, SHOP_SCALE_MAX);
		case TYPE_TALENT:
		return amount * Clamp_Between(GetCVar("dnd_shop_talent_scale"), 1, SHOP_SCALE_MAX);
		case TYPE_ARTI:
		return amount * Clamp_Between(GetCVar("dnd_shop_artifact_scale"), 1, SHOP_SCALE_MAX);
		case TYPE_ARMOR:
		return amount * Clamp_Between(GetCVar("dnd_shop_armor_scale"), 1, SHOP_SCALE_MAX);
	}
	return 1;
}

int GetShopPrice (int id, int priceflag) {
	int res = 0;
	if(id < MAXSHOPITEMS)
		res = ShopInfo[id][SHOPINFO_PRICE] * Clamp_Between(GetCVar("dnd_shop_scale"), 1, SHOP_SCALE_MAX);
	res = ShopScale(res, id);
	if(GetItemType(id) == TYPE_TALENT)
		res += TALENT_COST_INCREASE * CheckInventory(TalentNames[id - SHOP_TALENT_BEGIN]);
	if(priceflag & PRICE_CHARISMAREDUCE) {
		res -= (res * CheckInventory("PSTAT_Charisma")) / (100 * CHARISMA_REDUCE);
	}
	return res;
}


// returns 0 for buy being possible
int CanResearch(int res_id) {
	int finish_check = !CheckInventory(StrParam(s:"Done_", s:Research_List[res_id]));
	int found_check = CheckInventory(StrParam(s:"Research_", s:Research_List[res_id]));
	int budget_check = CheckInventory("Budget") >= ResearchCosts[res_id];
	if(finish_check && found_check && budget_check)
		return 0;
	GiveInventory("DnD_PopupError", 1);
	if(!found_check)
		SetInventory("DnD_PopupId", POPUP_NEEDDISCOVER);
	else if(!finish_check)
		SetInventory("DnD_PopupId", POPUP_ALREADYRESEARCHED);
	else
		SetInventory("DnD_PopupId", POPUP_NOBUDGET);
	return 1;
}

// returns 0 for buy being possible, read end of function for other details
int CanTrade (int id, int tradeflag, int price) {
	int credit = CheckInventory("Credit"), cond1, cond2, cond3 = 1, isammo = 0, res = 0, type = 0;
	
	if(!price)
		price = GetShopPrice(id, PRICE_CHARISMAREDUCE);
		
	cond1 = credit >= price;
		
	str item = "";
	str wepcheck = "";
	
	type = GetItemType(id);
	
	if(type == TYPE_ARTI)
		item = ArtifactInfo[id + MAXARTIFACTS - MAXSHOPITEMS][ARTI_NAME]; // put it in the artifact info range
	else if(type == TYPE_TALENT)
		item = ShopItemNames[id][SHOPNAME_ITEM];
	else if(type == TYPE_ARMOR)
		item = "Armor";
	else {
		item = ShopItemNames[id][SHOPNAME_ITEM];
		wepcheck = ShopItemNames[id][SHOPNAME_CONDITION];
	}
	
	if(tradeflag & TRADE_BUY) {
		if(type == TYPE_AMMO) // ammo
			cond2 = (CheckInventory(item) < GetAmmoCapacity(item));
		else if(type == TYPE_TALENT) // talent
			cond2 = CheckInventory(item) < TALENT_CAP;
		else if(type == TYPE_ARMOR) // armor
			cond2 = CheckInventory(item) < ArmorCapacities[id - SHOP_FIRSTARMOR_INDEX];
		else if(type != TYPE_WEAPON) { // item
			if(id != SHOP_ARTI_BACKPACK)
				cond2 = (CheckInventory(item) < ShopInfo[id][SHOPINFO_MAX]);
			else
				cond2 = ACS_ExecuteWithResult(994, 0);
		}
		else { // weapon
			cond3 = !CheckInventory(item);
			cond2 = cond3 && !CheckInventory(wepcheck);
		}
		
		if(cond1) { // I have credits
			if(!cond3) // got credit but i have this weapon
				res = 3;
			else if(!cond2) // got credit but maxed
				res = 2;
		}
		else {
			if(!cond3) // no credits and but already owning the item
				res = 3;
			else if(!cond2)
				res = 2;
			else
				res = 1; // no credits
		}
		
		if(res) {
			GiveInventory("DnD_PopupError", 1);
			SetInventory("DnD_PopupId", res);
		}
	}
	else { // SELL
		res = CheckInventory(item); // if you have the weapon, you can sell it so return 1 if you have the item
	}

	return res;
}

void DecideAccessories () {
	int this = ActivatorTID();
	if(IsAccessoryEquipped(this, ACC_FIRE))
		GiveInventory("Accessory_FireProtection", 1);
	else
		TakeInventory("Accessory_FireProtection", 1);
		
	if(IsAccessoryEquipped(this, ACC_ANGELIC)) {
		if(!CheckInventory("Intervened")) {
			SetPlayerProperty(0, 1, PROP_BUDDHA);
			GiveInventory("CanIntervene", 1);
		}
	}
	else {
		SetPlayerProperty(0, 0, PROP_BUDDHA);
		TakeInventory("CanIntervene", 1);
	}
	
	if(IsAccessoryEquipped(this, ACC_REFLECT))
		GiveInventory("CanDeflect", 1);
	else
		TakeInventory("CanDeflect", 1);
		
	if(IsAccessoryEquipped(this, ACC_NETHER))
		GiveInventory("NetherCheck", 1);
	else
		TakeInventory("NetherCheck", 1);
		
	if(IsAccessoryEquipped(this, ACC_TALTOS)) {
		GiveInventory("TaltosEffect", 1);
		GiveInventory("TaltosUp", 1);
	}
	else {
		GiveInventory("TaltosUnsetEffect", 1);
		TakeInventory("TaltosUp", 1);
	}
	
	if(IsAccessoryEquipped(this, ACC_HATE)) {
		GiveInventory("HateCheck", 1);
		GiveInventory("PowerReflection", 1);
	}
	else {
		TakeInventory("PowerReflection", 1);
		TakeInventory("HateCheck", 1);
	}
	
	if(IsAccessoryEquipped(this, ACC_ARTEMIS)) {
		GiveInventory("ArtemisPower", 1);
		GiveInventory("ArtemisCheck", 1);
	}
	else {
		TakeInventory("ArtemisPower", 1);
		TakeInventory("ArtemisCheck", 1);
	}
	
	if(IsAccessoryEquipped(this, ACC_AGAMOTTO))
		GiveInventory("AgamottoCheck", 1);
	else
		TakeInventory("AgamottoCheck", 1);
	
	if(IsAccessoryEquipped(this, ACC_GRYPHON)) {
		GiveInventory("CurseImmunity", 1);
		GiveInventory("GryphonCheck", 1);
		GiveInventory("GryphonSpeed", 1);
	}
	else {
		TakeInventory("CurseImmunity", 1);
		TakeInventory("GryphonCheck", 1);
		TakeInventory("GryphonSpeed", 1);
	}
	
	if(IsAccessoryEquipped(this, ACC_LICH)) {
		GiveInventory("LichCheck", 1);
		GiveInventory("LichPower", 1);
		SetAmmoCapacity("Souls", 150);
	}
	else {
		TakeInventory("LichCheck", 1);
		TakeInventory("LichPower", 1);
		if(CheckInventory("Souls") > 75) // yea this is bad but o well
			SetInventory("Souls", 75);
		SetAmmoCapacity("Souls", 75);
	}
}

void ProcessScrollOption (int curindex, int set, int slot) {
	if(!slot)
		SetInventory("Accessory_Top_Index", set);
	else
		SetInventory("Accessory_Bot_Index", set);
}

void ScrollAccessory(int slot, int dir) {
	int curindex,  i;
	int this = ActivatorTID();
	if(!slot)
		curindex = CheckInventory("Accessory_Top_Index");
	else
		curindex = CheckInventory("Accessory_Bot_Index");
		
	if(dir == -1) { // right
		for(i = curindex + 1; i < MAX_ACCESSORY + 1; ++i) {
			// if I have this item and I don't currently have it selected
			if(CheckInventory(StrParam(s:"Accessory_", d:i)) && !IsAccessoryEquipped(this, i)) {
				if(i == ACC_ANGELIC)
					GiveInventory("InterventionSelected", 1);
				ProcessScrollOption(curindex, i, slot);
				break;
			}
		}
	}
	else if(dir == 1) { // left
		for(i = curindex - 1; i > -1; --i) {
			if(CheckInventory(StrParam(s:"Accessory_", d:i)) && !IsAccessoryEquipped(this, i)) {
				if(i == ACC_ANGELIC)
					GiveInventory("InterventionSelected", 1);
				ProcessScrollOption(curindex, i, slot);
				break;
			}
		}
	}
}

// Draws a toggled image that changes color depending on given scenarios
// By default, if insufficient credits occur, it will be gray. If credits are sufficient but objectflag has OBJ_HASCHOICE, that means you have to choose between one of the options
// of it's kind. For example, there are 2 weapons that replace the shotgun. You can have only one, so you set this flag, and set choicename to P_Slot3Replaced. One of the two will be
// red if the other is bought. The item that is bought will be green.
void DrawToggledImage(int itemid, int onposy, int objectflag, int offcolor, int oncolor, str choicename, int choicecount, int choicecolor) {
	// first of all check research (assuming the player can't own this item without having it researched)
	int res_state = 1;
	if(objectflag & OBJ_RESEARCH)
		res_state = CheckItemRequirements(itemid, RES_KNOWN); // if not known, draw nothing
	int curposy = CheckInventory("ActiveBox") - 1;
	if(!res_state) {
		if(curposy == onposy) {
			HudMessage(s:"\c[B1]---- N/A ----"; HUDMSG_PLAIN, RPGMENUITEMID - 2 * onposy - 1, CR_WHITE, 192.1, 80.0 + 16.0 * onposy, 0.0, 0.0);
			HudMessage(s:"\c[B1]--> $ ???"; HUDMSG_PLAIN, RPGMENUITEMID - 2 * onposy - 2, CR_WHITE, 440.2, 80.0 + 16.0 * onposy, 0.0, 0.0);
		}
		else {
			HudMessage(s:"\c[G8]---- N/A ----"; HUDMSG_PLAIN, RPGMENUITEMID - 2 * onposy - 1, CR_WHITE, 192.1, 80.0 + 16.0 * onposy, 0.0, 0.0);
			HudMessage(s:"\c[G8]$ ???"; HUDMSG_PLAIN, RPGMENUITEMID - 2 * onposy - 2, CR_WHITE, 440.2, 80.0 + 16.0 * onposy, 0.0, 0.0);
		}
	}
	else {
		res_state = CheckItemRequirements(itemid, RES_DONE); // check if it is actually done
		int color = offcolor;
		str toshow = "\c[Y5]", colorprefix = "\cj", weptype = ""; // textcolor colors don't work for some reason
		int price = GetShopPrice(itemid, PRICE_CHARISMAREDUCE);
		int sellstate = 0;
		int curcredit = CheckInventory("Credit");
		str itemtag = ShopItemNames[itemid][SHOPNAME_TAG];
		str itemname = ShopItemNames[itemid][SHOPNAME_ITEM];
		
		if(objectflag & OBJ_RESEARCH && !res_state) {
			toshow = "\c[W3]";
			colorprefix = "\c[W3]";
		}
		else {
			// if not ammo, talent or armor
			if(!(objectflag & (OBJ_AMMO | OBJ_TALENT | OBJ_ARMOR))) {
				// if not artifact and owning it (basically has weapon)
				if(!(objectflag & OBJ_ARTI) && CheckInventory(itemname)) {
					color = oncolor;
					colorprefix = "\c[M3]";
					toshow = "\c[M3]";
					sellstate = 1;
				}
				else { // no?
					if(price > curcredit) {
						color = CR_BLACK;
						colorprefix = "\c[G8]";
						toshow = "\c[G8]";
					} // if I have options color others
					else if((objectflag & OBJ_HASCHOICE && CheckInventory(choicename) == choicecount) || (itemid == SHOP_ARTI_BACKPACK && !ACS_ExecuteWithResult(994, 0))) {
						// if has choice and count met or this is a backpack and limit reached on it (backpack limit has to be checked dynamically due to classic backpack cvar)
						color = choicecolor;
						colorprefix = "\c[Q2]";
						toshow = "\c[Q2]";
					}
				}
			}
			else { // ammo, talent or armor
				if(price > curcredit) {
					color = CR_BLACK;
					colorprefix = "\c[G8]";
					toshow = "\c[G8]";
				}
				else if(!(objectflag & OBJ_AMMO) && CheckInventory(choicename) >= choicecount) {
					color = choicecolor;
					colorprefix = "\c[Q2]";
					toshow = "\c[Q2]";
				}
			}
		}
		
		if(objectflag & OBJ_WEP) {
			if(!ParseInt(ShopItemNames[itemid][SHOPNAME_TYPE]))
				weptype = "\c[J7][\c[S7]R\c[J7]] ";
			else
				weptype = "\c[J7][\c[E3]L\c[J7]] ";
		}
		
		if(curposy == onposy) {
			if(objectflag & OBJ_WEP) {
				if(sellstate)
					HudMessage(s:"\c[M1]--> Sells for:\c- $", d:GetShopPrice(itemid, 0) / 2; HUDMSG_PLAIN, RPGMENUITEMID - 41, CR_WHITE, 192.1, 200.1, 0.0, 0.0);
				HudMessage(s:"* ", s:WeaponExplanation[itemid]; HUDMSG_PLAIN, RPGMENUITEMID - 40, CR_WHITE, 184.1, 216.1, 0.0, 0.0);
			}
			else if(objectflag & OBJ_AMMO) {
				int amt = AmmoCounts[itemid - SHOP_FIRSTAMMO_INDEX];
				HudMessage(s:"* ", s:"Gives \cf", d:amt + ACS_ExecuteWithResult(918, 0, 1, amt), s:"\c- ", s:AmmoExplanation[itemid - SHOP_FIRSTAMMO_INDEX]; HUDMSG_PLAIN, RPGMENUITEMID - 40, CR_WHITE, 192.1, 232.1, 0.0, 0.0);
			}
			else if(objectflag & OBJ_ARTI)
				HudMessage(s:"* ", s:ArtifactExplanation[curposy]; HUDMSG_PLAIN, RPGMENUITEMID - 40, CR_WHITE, 192.1, 232.1, 0.0, 0.0);
			else if(objectflag & OBJ_TALENT)
				HudMessage(s:"* ", s:"Increases damage of ", s:TalentTypeNames[onposy], s:"\nweapons by \cf", f:DND_TALENT_INCREASE + DND_DEX_GAIN * CheckInventory("PSTAT_Dexterity"), s:"%\c-."; HUDMSG_PLAIN, RPGMENUITEMID - 40, CR_WHITE, 192.1, 232.1, 0.0, 0.0);
			else if(objectflag & OBJ_ARMOR)
				HudMessage(s:"* ", s:ArmorExplanation[itemid - SHOP_FIRSTARMOR_INDEX]; HUDMSG_PLAIN, RPGMENUITEMID - 40, CR_WHITE, 192.1, 232.1, 0.0, 0.0);
			HudMessage(s:weptype, s:"\c[B1]", s:itemtag; HUDMSG_PLAIN, RPGMENUITEMID - 2 * onposy - 1, CR_WHITE, 192.1, 80.0 + 16.0 * onposy, 0.0, 0.0);
			HudMessage(s:colorprefix, s:"--> $", d:price; HUDMSG_PLAIN, RPGMENUITEMID - 2 * onposy - 2, color, 440.2, 80.0 + 16.0 * onposy, 0.0, 0.0);
		}
		else {
			HudMessage(s:weptype, s:toshow, s:itemtag; HUDMSG_PLAIN, RPGMENUITEMID - 2 * onposy - 1, CR_WHITE, 192.1, 80.0 + 16.0 * onposy, 0.0, 0.0);
			HudMessage(s:colorprefix, s:"$", d:price; HUDMSG_PLAIN, RPGMENUITEMID - 2 * onposy - 2, color, 440.2, 80.0 + 16.0 * onposy, 0.0, 0.0);
		}
	}
}

// will process item selections depending on given valid range
// support for selling other stuff is here, it's just a few extra lines in the serverside script to handle the process
void ProcessTrade (int posy, int low, int high, int tradeflag) {
	int itemid, price, buystatus;
	if(tradeflag & TRADE_BUY) {
		itemid = low + posy;
		if(itemid <= high && CheckInventory("MadeChoice") == 1) {
			// consider the research if this item has any
			if(!CheckItemRequirements(itemid, RES_DONE)) {
				// not done, so we can't give this
				LocalAmbientSound("RPG/MenuError", 127);
				GiveInventory("DnD_ShowPopup", 1);
				GiveInventory("DnD_PopupError", 1);
				SetInventory("DnD_PopupId", POPUP_NEEDRESEARCH); // popup for research
			}
			else {
				// now consider money adn other things as factors
				price = GetShopPrice(itemid, PRICE_CHARISMAREDUCE);
				buystatus = CanTrade(itemid, tradeflag, price);
				if(!buystatus) {
					// consider researches before handing out
					TakeInventory("Credit", price);
					GiveInventory(ShopItemNames[itemid][SHOPNAME_ITEM], 1);
					if(tradeflag & TRADE_WEAPON) {
						LocalAmbientSound("weapons/pickup", 127);
						TakeInventory(ShopWeaponTake[itemid], 1);	
						GiveInventory(ShopItemNames[itemid][SHOPNAME_CONDITION], 1);
						SetWeapon(ShopItemNames[itemid][SHOPNAME_ITEM]);
                        // fix special ammo cursor
                        int fix = IsSpecialFixWeapon(itemid);
                        if(fix != -1) {
                            int weptype = SpecialAmmoFixWeapons[fix][1];
                            SetInventory(StrParam(s:"SpecialAmmoMode", s:GetSpecialAmmoSuffix(weptype)), SpecialAmmoBase[SpecialAmmoFixWeapons[fix][2]]);
                        }
                    }
					else if(tradeflag & TRADE_AMMO)
						LocalAmbientSound("items/ammo", 127);
					else if(tradeflag & (TRADE_ABILITY | TRADE_ARTIFACT | TRADE_TALENT))
						LocalAmbientSound("Bonus/Received", 127);
					else if(tradeflag & TRADE_ARMOR)
						LocalAmbientSound("items/armor", 127);
				}
				else {
					LocalAmbientSound("RPG/MenuError", 127);
					GiveInventory("DnD_ShowPopup", 1);
				}
			}
		}
		SetInventory("MadeChoice", 0);
	}
	else if(tradeflag & TRADE_SELL) {
		itemid = low + posy;
		if(itemid <= high && CheckInventory("MadeChoice") == 2) {
			if(!CheckInventory("DnD_SellConfirm")) { // confirmation screen did not pop
				buystatus = CanTrade(itemid, TRADE_SELL, 0);
				if(buystatus) {
					LocalAmbientSound("RPG/MenuSellConfirm", 127);
					GiveInventory("DnD_SellConfirm", 1);
					TakeInventory("DnD_ShowPopup", 1);
					TakeInventory("DnD_PopupError", 1);
					GiveInventory("DnD_PopupSell", 1);
					GiveInventory("DnD_ShowSellPopup", 1);
					SetInventory("DnD_PopupID", itemid);
				}
				else {
					GiveInventory("DnD_ShowPopup", 1);
					GiveInventory("DnD_PopupError", 1);
					SetInventory("DnD_PopupId", POPUP_DONTOWN);
					LocalAmbientSound("RPG/MenuError", 127);
				}
			}
			else {
				price = GetShopPrice(itemid, 0) / 2;
				TakeInventory("DnD_SellConfirm", 1);
				TakeInventory("DnD_PopupSell", 1);
				TakeInventory("DnD_ShowSellPopup", 1);
				SetInventory("DnD_PopupID", 0);
				str totake = ShopWeaponTake[itemid];
				if(StrCmp(totake, " "))
					GiveInventory(totake, 1);
				TakeInventory(ShopItemNames[itemid][SHOPNAME_CONDITION], 1);
				TakeInventory(ShopItemNames[itemid][SHOPNAME_ITEM], 1);
				GiveInventory("Credit", price);
			}
		}
		TakeInventory("MadeChoice", 2);
	}
}

// 0 for buy being possible, 2 if credits was not enough, 1 if credits was enough but you are maxed on the item and 3 if neither were satisfied 4 if item can't be sold
void HandlePopups(int id) {
	if(!CheckInventory("DnD_ShowPopup") && !CheckInventory("DnD_ShowSellPopup"))
		return;
	int popuptype = POPUP_ERROR;
	if(CheckInventory("DnD_PopupSell"))
		popuptype = POPUP_SELL;

	SetHudSize(480, 320, 1);
	SetFont("DND_ERR");
	HudMessage(s:"A"; HUDMSG_FADEOUT, RPGMENUITEMID - 45, -1, 216.1, 128.1, 1.0, 1.0);
	SetFont("SMALLFONT");
	str toshow = "", title = " ";
	if(popuptype == POPUP_ERROR) {
		title = "\c[Q2]ERROR";
		// id is minimum 1
		toshow = PopupText[id];
	}
	else if(popuptype == POPUP_SELL) {
		title = "\c[Q2]CONFIRM";
		toshow = StrParam(s:"Are you sure you\nwant to sell your\n\cd", s:ShopItemNames[id][SHOPNAME_TAG], s:"\c- ?");
	}
	
	HudMessage(s:title; HUDMSG_FADEOUT, RPGMENUITEMID - 46, -1, 316.4, 136.1, 1.0, 1.0);
	HudMessage(s:toshow; HUDMSG_FADEOUT, RPGMENUITEMID - 47, CR_GOLD, 224.1, 160.1, 1.0, 1.0);
}

void DrawHighLightBar (int posy, int drawlit) {
	if(posy == MAINBOX_NONE)
		HudMessage(s:""; HUDMSG_PLAIN, RPGMENULISTID - 7, -1, 47.1, 99.1, 0.0, 0.0);
	else {
		--posy;
		int yadd = 0;
		if(posy > 0)
			yadd = 11 * posy;
		if(posy > 3)
			yadd += 8;
		SetHudSize(384, 200, 1);
		if(drawlit)
			SetFont("BARHIGHL");
		else
			SetFont("BARHIGH");
		HudMessage(s:"A"; HUDMSG_PLAIN, RPGMENULISTID - 7, -1, 47.1, 99.1 + 1.0 * yadd, 0.0, 0.0);
	}
}

void ReturnToMain() {
	SetInventory("MenuOption", MENU_MAIN);
	SetInventory("MenuPosX", 0);
	LocalAmbientSound("RPG/MenuChoose", 127);
}

void ListenInput () {
	int bpress = GetPlayerInput(-1, INPUT_BUTTONS);
	int obpress = GetPlayerInput(-1, INPUT_OLDBUTTONS);
	
	if(!CheckInventory("DnD_ClickTicker") && (IsButtonPressed(bpress, obpress, BT_USE) || IsButtonPressed(bpress, obpress, BT_ATTACK))) {
		GiveInventory("DnD_ClickTicker", 1);
		if(CheckInventory("DnD_SellConfirm")) {
			SetInventory("DnD_SellConfirm", 0);
			SetInventory("DnD_ShowPopup", 0);
			SetInventory("DnD_ShowSellPopup", 0);
			SetInventory("MadeChoice", 0);
		}
		else
			SetInventory("MadeChoice", 1);
	}
	if(!CheckInventory("DnD_ClickTicker") && IsButtonPressed(bpress, obpress, BT_ALTATTACK)) {
		GiveInventory("DnD_ClickTicker", 1);
		SetInventory("MadeChoice", 2);
	}
}

// includes left right shortcuts
void ListenInputLR(int listenflag, int curposx, int condx_min, int condx_max) {
	int bpress = GetPlayerInput(-1, INPUT_BUTTONS);
	int obpress = GetPlayerInput(-1, INPUT_OLDBUTTONS);
	if(!CheckInventory("DnD_SellConfirm")) { // if waiting for sell confirmation do not let movement in menu
		if(listenflag & LISTEN_LEFT && IsButtonPressed(bpress, obpress, settings[1][0])) {
			if(curposx > condx_min) {
				TakeInventory("MenuPosX", 1);
				LocalAmbientSound("RPG/MenuMove", 127);
			}
			SetInventory("MenuLR", 1);
		}
		if(listenflag & LISTEN_RIGHT && IsButtonPressed(bpress, obpress, settings[3][0])) {
			if(curposx < condx_max) {
				GiveInventory("MenuPosX", 1);
				LocalAmbientSound("RPG/MenuMove", 127);
			}
			SetInventory("MenuLR", 2);
		}
	}
	
	if(!CheckInventory("DnD_ClickTicker") && (IsButtonPressed(bpress, obpress, BT_USE) || IsButtonPressed(bpress, obpress, BT_ATTACK))) {
		GiveInventory("DnD_ClickTicker", 1);
		if(CheckInventory("DnD_SellConfirm")) {
			SetInventory("DnD_SellConfirm", 0);
			SetInventory("DnD_ShowPopup", 0);
			SetInventory("DnD_ShowSellPopup", 0);
			SetInventory("MadeChoice", 0);
		}
		else
			SetInventory("MadeChoice", 1);
	}
	if(!CheckInventory("DnD_ClickTicker") && IsButtonPressed(bpress, obpress, BT_ALTATTACK)) {
		GiveInventory("DnD_ClickTicker", 1);
		SetInventory("MadeChoice", 2);
	}
}

void HandleAmmoPurchase(int boxid, int index_beg, int arr_index, bool givefull) {
	int itemid = index_beg + boxid - 1;
	int price = GetShopPrice(itemid, PRICE_CHARISMAREDUCE);
	int buystatus = CanTrade(itemid, TRADE_BUY, price);
	if(!buystatus) {
		int amt = AmmoCounts[arr_index], count = 1;
		amt += ACS_ExecuteWithResult(918, 0, 1, amt);
		
		// if we are maxing the ammo
		if(givefull) {
			count += (GetAmmoCapacity(AmmoInfo[arr_index][AMMO_NAME]) - CheckInventory(AmmoInfo[arr_index][AMMO_NAME])) / amt;
			price = price * count;
			if(price > CheckInventory("Credit")) {
				count = CheckInventory("Credit") / GetShopPrice(itemid, PRICE_CHARISMAREDUCE);
				price = count * GetShopPrice(itemid, PRICE_CHARISMAREDUCE);
			}
		}
		// check how much of this we can really afford
		
		TakeInventory("Credit", price);
		LocalAmbientSound("items/ammo", 127);
		GiveInventory(AmmoInfo[arr_index][AMMO_NAME], amt * count);
	}
	else {
		LocalAmbientSound("RPG/MenuError", 127);
		GiveInventory("DnD_ShowPopup", 1);
	}
}

str GetResearchImage(int pos) {
    return Research_Images[pos];
}

int GetCursorPos(int input, int mt) {
	int res = 0, speed, ds;
	switch(mt) {
		case MOUSE_INPUT_X:
			res = CheckInventory("Mouse_X");
			speed = FixedDiv(1.0, FixedMul(GetCVar("m_yaw"), GetCVar("mouse_sensitivity")));
			speed = FixedMul(speed * 2, HUDMAX_XF) / (HUDMAX_X * 100);
			ds = input * speed;
			res = Clamp_Between(res + ds, 0, HUDMAX_XF);
			break;
		case MOUSE_INPUT_Y:
			res = CheckInventory("Mouse_Y");
			speed = FixedDiv(1.0, FixedMul(GetCVar("m_pitch"), GetCVar("mouse_sensitivity")));
			speed = FixedMul(speed * 2, HUDMAX_YF) / (HUDMAX_X / 2 * 100);
			if (GetCVar("invertmouse"))
				speed *= -1;
			ds = input * speed;
			res = Clamp_Between(res + ds, 0, HUDMAX_YF);
			break;
	}
	return res;
}

void DrawCursor() {
	static int cursor_anim = 0;
	if(cursor_anim < 8)
		SetFont("DND_CUR5");
	else
		SetFont(StrParam(s:"DND_CUR", d:cursor_anim / 4 - 1));
	cursor_anim = (cursor_anim + 1) % 24;
	// Log(f:CheckInventory("Mouse_X"), s: " ", f:CheckInventory("Mouse_Y"));
	HudMessage(s:"A"; HUDMSG_PLAIN, RPGMENUCURSORID, -1, HUDMAX_XF - ((CheckInventory("Mouse_X") & MMASK)) + 0.1, HUDMAX_YF - ((CheckInventory("Mouse_Y") & MMASK)) + 0.1, 0.2, 0.0);
}

// since we use top left corner as 1:1, directions are changed
bool point_in_box(rect_T? box, int mx, int my) {
	return (mx <= box.topleft_x && mx >= box.botright_x && my <= box.topleft_y && my >= box.botright_y);
}

menu_pane_T& GetPane() {
	static menu_pane_T pane;
	return pane;
}

void AddBoxToPane(menu_pane_T& p, rect_T? box, int lbl) {
	if(p.cursize < MAX_MENU_BOXES)
		p.MenuRectangles[p.cursize++] = box;
	else
		Log(s:"Menu box limit exceeded.");
	//Log(d:p.cursize);
}

void ResetPane(menu_pane_T& p) {
	p.cursize = 0;
}

rect_T& GetMainBox(int id) {
	static rect_T MainBoxList[MAX_MAIN_BOXES] = { 
		{ 419.0, 158.0, 348.0, 147.0 },
		{ 419.0, 141.0, 348.0, 130.0 },
		{ 419.0, 124.0, 348.0, 113.0 },
		{ 419.0, 107.0, 348.0, 96.0  },
		
		{ 419.0, 75.0,  348.0, 64.0  },
		{ 419.0, 58.0,  348.0, 47.0  },
		{ 419.0, 41.0,  348.0, 30.0  }
	};
	return MainBoxList[id];
}

void LoadPane(menu_pane_T& p, int menu_page) {
	static rect_T bp[MAX_MENU_BOXPAGES][MAX_MENU_BOXES] = {
		// null
		{
			{ -1, -1, -1, -1 }
		},
		// stat 1
		{
			{ 288.0, 164.0, 216.0, 157.0 }, // str
			{ 149.0, 164.0, 72.0, 157.0 }, // dex
			{ 288.0, 148.0, 213.0, 141.0 }, // bul
			{ 149.0, 148.0, 78.0, 141.0 }, // chr
			{ 210.0, 131.0, 146.0, 125.0 }, // vit
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ 130.0, 50.0, 120.0, 45.0 }, // rarr
			{ -1, -1, -1, -1 }
		},
		// stat 2
		{
			{ 210.0, 50.0, 200.0, 45.0 }, // larr
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// perk
		{
			{ 296.0, 243.0, 184.0, 237.0 }, // sharp
			{ 296.0, 228.0, 214.0, 222.0 }, // end
			{ 296.0, 213.0, 243.0, 206.0 }, // wis
			{ 296.0, 196.0, 247.0, 189.0 }, // greed
			{ 296.0, 181.0, 252.0, 173.0 }, // med
			{ 296.0, 163.0, 211.0, 158.0 }, // mun
			{ 296.0, 145.0, 209.0, 140.0 }, // ded
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// loadout 1
		{
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ 130.0, 50.0, 120.0, 45.0 }, // rarr
			{ -1, -1, -1, -1 }
		},
		// loadout 2
		{
			{ 210.0, 50.0, 200.0, 45.0 }, // larr
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ 130.0, 50.0, 120.0, 45.0 }, // rarr
			{ -1, -1, -1, -1 }
		},
		// loadout 3
		{
			{ 210.0, 50.0, 200.0, 45.0 }, // larr
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ 130.0, 50.0, 120.0, 45.0 }, // rarr
			{ -1, -1, -1, -1 }
		},
		// loadout 4
		{
			{ 295.0, 227.0, 76.0, 221.0 }, // acc1
			{ 295.0, 196.0, 76.0, 190.0 }, // acc2
			{ 295.0, 196.0, 76.0, 190.0 }, // acc2
			{ 210.0, 50.0, 200.0, 45.0 }, // larr
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// shop
		{
			{ 289.0, 229.0, 179.0, 222.0 }, // wep
			{ 289.0, 211.0, 162.0, 206.0 }, // ammo
			{ 289.0, 195.0, 178.0, 190.0 }, // ability
			{ 289.0, 181.0, 169.0, 174.0 }, // arti
			{ 289.0, 164.0, 183.0, 158.0 }, // talent
			{ 289.0, 148.0, 188.0, 142.0 }, // armor
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// wep
		{
			{ 289.0, 229.0, 240.0, 220.0 }, // s1
			{ 289.0, 213.0, 240.0, 204.0 }, // s2
			{ 289.0, 197.0, 240.0, 189.0 }, // s3
			{ 289.0, 181.0, 240.0, 172.0 }, // s4
			{ 289.0, 165.0, 240.0, 156.0 }, // s5
			{ 289.0, 149.0, 240.0, 140.0 }, // s6
			{ 289.0, 133.0, 240.0, 124.0 }, // s7
			{ 289.0, 117.0, 240.0, 108.0 }, // s8
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// wep 1
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// wep 2
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 289.0, 181.0, 120.0, 175.0 }, // w5
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// wep 3
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 289.0, 181.0, 120.0, 175.0 }, // w5
			{ 289.0, 165.0, 120.0, 159.0 }, // w6
			{ 289.0, 149.0, 120.0, 143.0 }, // w7
			{ 289.0, 133.0, 120.0, 127.0 }, // w8
			{ 289.0, 117.0, 120.0, 111.0 }, // w9
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// wep 4
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 289.0, 181.0, 120.0, 175.0 }, // w5
			{ 289.0, 165.0, 120.0, 159.0 }, // w6
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// wep 5
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 289.0, 181.0, 120.0, 175.0 }, // w5
			{ 289.0, 165.0, 120.0, 159.0 }, // w6
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// wep 6
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 289.0, 181.0, 120.0, 175.0 }, // w5
			{ 289.0, 165.0, 120.0, 159.0 }, // w6
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// wep 7
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 289.0, 181.0, 120.0, 175.0 }, // w5
			{ 289.0, 165.0, 120.0, 159.0 }, // w6
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// wep 8
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// ammo 1
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ 130.0, 50.0, 120.0, 45.0 }, // rarr
			{ -1, -1, -1, -1 }
		},
		// ammo 2
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 289.0, 181.0, 120.0, 175.0 }, // w5
			{ 289.0, 165.0, 120.0, 159.0 }, // w6
			{ 289.0, 149.0, 120.0, 143.0 }, // w7
			{ 289.0, 133.0, 120.0, 127.0 }, // w8
			{ 289.0, 117.0, 120.0, 111.0 }, // w9
			{ 210.0, 50.0, 200.0, 45.0 }, // larr
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ 130.0, 50.0, 120.0, 45.0 }, // rarr
			{ -1, -1, -1, -1 }
		},
		// ammo 3
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 289.0, 181.0, 120.0, 175.0 }, // w5
			{ 289.0, 165.0, 120.0, 159.0 }, // w6
			{ 289.0, 149.0, 120.0, 143.0 }, // w7
			{ 210.0, 50.0, 200.0, 45.0 }, // larr
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ 130.0, 50.0, 120.0, 45.0 }, // rarr
			{ -1, -1, -1, -1 }
		},
		// ammo special
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 289.0, 181.0, 120.0, 175.0 }, // w5
			{ 289.0, 165.0, 120.0, 159.0 }, // w6
			{ 210.0, 50.0, 200.0, 45.0 }, // larr
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// ability shop
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 289.0, 181.0, 120.0, 175.0 }, // w5
			{ 289.0, 165.0, 120.0, 159.0 }, // w6
			{ 289.0, 149.0, 120.0, 143.0 }, // w7
			{ 289.0, 133.0, 120.0, 127.0 }, // w8
			{ 289.0, 117.0, 120.0, 111.0 }, // w9
			{ 289.0, 101.0, 104.0, 95.0 }, // w10
			{ 289.0, 85.0, 104.0, 79.0 }, // w11
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// artifact shop
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 289.0, 181.0, 120.0, 175.0 }, // w5
			{ 289.0, 165.0, 120.0, 159.0 }, // w6
			{ 289.0, 149.0, 120.0, 143.0 }, // w7
			{ 289.0, 133.0, 120.0, 127.0 }, // w8
			{ 289.0, 117.0, 120.0, 111.0 }, // w9
			{ 289.0, 101.0, 104.0, 95.0 }, // w10
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// talent
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 289.0, 181.0, 120.0, 175.0 }, // w5
			{ 289.0, 165.0, 120.0, 159.0 }, // w6
			{ 289.0, 149.0, 120.0, 143.0 }, // w7
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// armor 1
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 289.0, 181.0, 120.0, 175.0 }, // w5
			{ 289.0, 165.0, 120.0, 159.0 }, // w6
			{ 289.0, 149.0, 120.0, 143.0 }, // w7
			{ 289.0, 133.0, 120.0, 127.0 }, // w8
			{ 289.0, 117.0, 120.0, 111.0 }, // w9
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ 130.0, 50.0, 120.0, 45.0 }, // rarr
			{ -1, -1, -1, -1 }
		},
		// armor 2
		{
			{ 289.0, 245.0, 120.0, 239.0 }, // w1
			{ 289.0, 229.0, 120.0, 223.0 }, // w2
			{ 289.0, 213.0, 120.0, 207.0 }, // w3
			{ 289.0, 197.0, 120.0, 191.0 }, // w4
			{ 289.0, 181.0, 120.0, 175.0 }, // w5
			{ 210.0, 50.0, 200.0, 45.0 }, // larr
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// research
		{
			{ 202.0, 84.0, 128.0, 76.0 }, // res
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// main
		{
			{ -1, -1, -1, -1 }
		},
		// help
		{
			{ 296.0, 81.0, 182.0, 73.0 }, // show info
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		},
		// ability
		{
			{ 289.0, 69.0, 104.0, 63.0 }, // dash
			{ 193.0, 50.0, 137.0, 45.0 }, // ret
			{ -1, -1, -1, -1 }
		}
	};
	for(int i = 0; i < MAX_MENU_BOXES && bp[menu_page][i].topleft_x != -1; ++i) {
//		Log(s:"Adding box: ", f:bp[menu_page][i].topleft_x, s: " ", f:bp[menu_page][i].topleft_y, s: " ", f:bp[menu_page][i].botright_x, s: " ", f:bp[menu_page][i].botright_y);
		AddBoxToPane(p, bp[menu_page][i], menu_page);
	}
}


int GetTriggeredBoxOnPane(menu_pane_T& p, int mx, int my) {
	if(mx >= 348.0)
		return MAINBOX_NONE;
	for(int i = 0; i < p.cursize; ++i) {
		if(point_in_box(p.MenuRectangles[i], mx, my))
			return i + 1;
	}
	return MAINBOX_NONE;
}

int GetTriggeredBoxOnMainPane(int mx, int my) {
	if(mx < 348.0 || my > 158.0)
		return MAINBOX_NONE;
	for(int i = 0; i < MAX_MAIN_BOXES; ++i) {
		if(point_in_box(GetMainBox(i), mx, my))
			return i + 1;
	}
	return MAINBOX_NONE;
}

void DrawBoxText(str msg, int boxid, int thisboxid, int id, int x, int y, str hcolor, str lcolor) {
	if(boxid == thisboxid)
		HudMessage(s:hcolor, s:msg, s:"\c-"; HUDMSG_PLAIN, id, CR_WHITE, x, y, 0.0, 0.0);
	else
		HudMessage(s:lcolor, s:msg, s:"\c-"; HUDMSG_PLAIN, id, CR_WHITE, x, y, 0.0, 0.0);
}