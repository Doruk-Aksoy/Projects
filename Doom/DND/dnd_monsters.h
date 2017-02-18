#define AVATAR_BASE_TID 5000
#define AVATAR_SOUL_TID 2000
#define AVATAR_CUBE_TID 6000
#define AVATAR_SOUL_COUNT 10

#define PURP_DEM_TID 13000

#define WAIT_MAX 18 // approx 2.5 seconds of flight max for jumping monsters (or lands on object and gets stuck, this is to unstuck it)

#define ZEALOT_SHIELD_TIME 4 * 35
#define ZEALOT_BASE_TID 14000
#define ZEALOT_SHIELD_TIDADD 1000 

int AvatarTID = 0;
int PurpDemTID = 0;
int ZealotTID = 0;

function void Restore_PlayerSpeed(void) {
	SetActorProperty(0, APROP_SPEED, 1.0);
}