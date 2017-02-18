#define MAXWEAPONS MAXCLASSES * 4
#define MAXCLASSTIP MAXCLASSES * 2

str Weapon_Messages[MAXWEAPONS] = {
	// Zealot Weapons
	// crusader
	"\cdPrimary:\c- Melee attack (50 - 70 / 65 - 105). Every 3rd hit creates a lightning storm (64).\n               Empower increases damage and 2 hits creates lightning.\n               \ciCost\c-: None.",
	"\cfAltFire:\c- Shield to reduce damage by 25%. Empowers all attacks for the duration.\n               Heals after duration, capped at 85.\n               \ciCost\c-: 8 second cooldown after shield.",
	
	"\cdPrimary:\c- A burst of flame on impact (15 - 40), creates flames around target (5 - 10).\n               Empower rains flames. (5 - 10)\n               \ciCost\c-: \cf30 Energy.\c-",
	"\cfAltFire:\c- Jets of flames from left and right (6). Creates flames on ground (1 - 10).\n               Empower creates an arc of flames (2 - 5).\n               \ciCost\c-: 8 second cooldown.",
	
	// prophet
	"\cdPrimary:\c- Pinpoint accurate shot (85). Reloads every 6 shots or manually (bind key).\n               \ciCost\c-: \cu1 Bullet\c-.",
	"\cfAltFire:\c- Shoots a holy missile. Enemies lose 10% (+10%) max health. Allies gain\n               33% resist and 33% damage amp for 3 seconds, one after another.\n               \ciCost\c-: \cf50 Energy\c- and 9 second cooldown.",
	
	"\cdPrimary:\c- Pinpoint accurate shot (85). Reloads every 6 shots or manually (bind key).\n               \ciCost\c-: \cu1 Bullet\c-.",
	"\cfAltFire:\c- Shoots 2 (+1) souls that rip enemies (1). Lasts 3 (+1) seconds.\n               \ciCost\c-: \cf50 Energy\c- and 7 second cooldown.",
	
	// demon hunter
	"\cdPrimary:\c- Shotgun attack (8.0, 6.4, 12 bullets, 12 (+6) damage each).\n               Reloads every 8 shots or manually (bind key).\n               \ciCost\c-: \cf1 Shell\c-.",
	"\cfAltFire:\c- Shoots blades in an arc (8 + 12% of enemy missing health in 2 seconds).\n               \ciCost\c-: \cf30 Energy\c- and 3 second cooldown.",
	
	"\cdPrimary:\c- Places a bear trap that snares enemies for 2 seconds (50 damage).\n               \ciCost\c-: 6 second cooldown.",
	"\cfAltFire:\c- Places a gun trap that shoots bullets for 3 seconds in 4 directions (10).\n               \ciCost\c-: 18 second cooldown.",
	
	// warlock
	"\cdPrimary:\c- Launches a fireball (80 + 84 area damage) that creates 7 tiny fireballs\n               around (10). Can charge to shoot seeking fireballs (18 + 18 area damage).\n               \ciCost\c-: \cf25 (+25) Energy.\c-",
	"\cfAltFire:\c- Creates a magical orb (25), on hit shoots projectiles towards you (20)\n               for 3 seconds.\n               \ciCost\c-: \ck25 Mana\c- and 12 second cooldown.",
	
	"\cdPrimary:\c- Creates magical blades (4 + 1 per soul) to cut your enemies.\n               Charge to release an explosive magic ball (Approx 100+ damage).\n               \ciCost\c-: \ck20 (+25) Mana.\c-",
	"\cfAltFire:\c- Creates a magical shield for 4.5 seconds, blocking (100 + 25 per soul)\n               damage.\n               \ciCost\c-: \cf40 Energy\c- and \ck40 Mana.\c-",
	
	// Golgoth Weapons
	
	// azagoth
	"\cdPrimary:\c- Creates a cone of lightning (15 - 25) for 1.5 seconds.\n               Can not recover energy while charging.\n               \ciCost\c-: \cf25 Energy.\c-",
	"\cfAltFire:\c- Creates a magical lash of lightning that rotates around you (10).\n               \ciCost\c-: 7 second cooldown.",
	
	"\cdPrimary:\c- Launches a seeking curse ball, on impact (5) makes you drain life\n               from the victim for 4 seconds.\n               \ciCost\c-: \cf30 Energy\c- and 5 second cooldown.",
	"\cfAltFire:\c- Launches a curse ball, on impact (15 + 5 area damage) makes\n               victims lose health for moving for 4 seconds.\n               \ciCost\c-: \cf35 Energy\c- and 5 second cooldown.",
	
	// bane
	"\cdPrimary:\c- Shoots 2 small (25 + 18 area damage) and 1\n               big (50 + 56 area damage) meteors in quick succession.\n               \ciCost\c-: \cf25 Energy.\c-",
	"\cfAltFire:\c- Creates a volcanic zone in front of you, exploding after 1.5 seconds (20).\n               \ciCost\c-: 6 second cooldown.",
	
	"\cdPrimary:\c- Sets target on flame (1) for 2 seconds, after which a meteor lands in\n               target area (100 + 160 area damage).\n               \ciCost\c-: \cf35 Energy\c- and 2 second cooldown.",
	"\cfAltFire:\c- Launches a chain of torment (10), slowing target gradually for 1.5\n               seconds, after which it snares the target for 1.5 seconds.\n               \ciCost\c-: 6 second cooldown.",
	
	// colossus
	"\cdPrimary:\c- Melee attack (75) in a cone in front of you.\n               \ciCost\c-: \cf10 Energy.\c-",
	"\cfAltFire:\c- Leaps. Deals 40 (+8) area damage and stuns enemies.\n               \ciCost\c-: \cf35 Energy\c- and 6 second cooldown.",
	
	"\cdPrimary:\c- Launches 3 projectiles (15) that converge. Slows enemies by 30% for 3 seconds.\n               \ciCost\c-: \cf40 Energy.\c-",
	"\cfAltFire:\c- Magical short range area attack (10 + 16 area damage)\n               increasing damage enemies take by 50% for 3 seconds.\n               \ciCost\c-: 5 second cooldown.",
	
	// kjaroch
	"\cdPrimary:\c- Shoots a meteor (40 + 4 area damage on flight + 30 area damage\n               on impact). Releases flames (2) on impact for 1.5 seconds.\n               \ciCost\c-: \cf30 Energy.\c-",
	"\cfAltFire:\c- Creates two twisters (3) that seek enemies and disorient them\n               when they hit. Lasts 3 seconds.\n               \ciCost\c-: 8 second cooldown.",
	
	"\cdPrimary:\c- Artillery mode, gaining 6 shots of 6 explosions (14 + 24 after delay\n               area damage). Can cancel by using \cvalt fire\c- key.\n               \ciCost\c-: \cf60 Energy.\c-",
	"\cfAltFire:\c- Bouncing orb (25 + 48 area damage if destroyed) releasing 4\n               smaller orbs (5-8) periodically. When orb hits a target\n               returns to release flames (64).\n               \ciCost\c-: 12 second cooldown."
};

str Class_Tip[MAXCLASSTIP] = {
	// Zealot Tips
	//crusader
	"\cfPassive:\c- Debuffs last only 50% of their time.",
	"\cvUltimate:\c- Heal allies for 10 health every second (twice as fast for you).\n                 Deal 10% of the enemies' max health.\n                 Slows enemies and hastes allies by 25% for 5 seconds.",
	
	// prophet
	"\cfPassive:\c- Gain 1% more damage for each 1% health missing.",
	"\cvUltimate:\c- Reveal all enemies and lock onto them when firing the Farseer.\n                 Holy missile deals an additional 10% and 3 souls are summoned\n                 that last a second longer. Reload is 75% faster.",

	// demon hunter
	"\cfPassive:\c- Dash around for 20 Energy with 1.5 second cooldown. (Bind a key)",
	"\cvUltimate:\c- No reload, 50% faster shotguns doing 50% more damage.\n                 Blades and dashing cost no Energy. Dash cooldown becomes 0.5 seconds.",
	
	// warlock
	"\cfPassive:\c- Gain power as you gather souls of your enemies, more\n              mana regen and more weapon effectiveness.",
	"\cvUltimate:\c- Summon a ray of death for 5 (+0.5 for each soul) seconds\n                 doing immense damage.",
	
	// azagoth
	"\cfPassive:\c- Gain 25% Energy and restore 35% of missing health for each kill.",
	"\cvUltimate:\c- Launch an orb of void energy, that on impact pulls enemies\n                 towards it for 3 seconds.",
	
	// bane
	"\cfPassive:\c- Set enemies on fire for 2 seconds dealing 6 damage over\n              the duration, when you hurt them.",
	"\cvUltimate:\c- Summons 10 dark souls in a line doing (128 area damage)\n                 when they appear and when they stop in the air.\n                 They will seek enemies after 2 seconds.",
	
	// colossus
	"\cfPassive:\c- Health < 75% => Physical attacks do 15% more damage.\n              < 50% => Run 15% faster. < 25% => Restore 10 Energy from 5.",
	"\cvUltimate:\c- Charge and gain 20% speed every second up to 80%. Run over\n                 anyone after the 1st second of cast. Stop when you hit terrain.",
	
	// kjaroch
	"\cfPassive:\c- Gain 1% movement speed for each 1% health\n              missing, up to 50%. At 50%, become immune to debuffs and transparent.",
	"\cvUltimate:\c- Summon servants for each enemy alive. If out of sight, servant\n                 appears behind them. If in sight, servant appears near you.\n                 Servants restore health if they kill their target.\n                 Gain up to 50% resist for each servant up.",
};