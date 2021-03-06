#ifndef DND_COMMON_IN
#define DND_COMMON_IN

#define DND_AFTER50_INCREMENT_DAMAGE 0.33

#define MAXLEVELS 100
#define DND_MAX_MONSTERLVL MAXLEVELS

#define MAXPLAYERS 64
#define P_TIDSTART 1000
#define TICRATE 35

#define DND_MONSTERTID_BEGIN 66000

#define DND_BASE_HEALTH 100

#define DND_DROP_TID 343 // some dumb number

#define ZEALOT_BASE_TID 14000
#define AVATAR_BASE_TID 5000
#define PURP_DEM_TID 13000

/*
////////////////
// TID RANGES //
////////////////

1. 1000 - 1063 = Players
2. 1200 - 1263 = Player temporary weapon drop ids (only at the moment of drop, cleared the next tic)
3. 3000 - 3063 = Initial railgun trail ID
4. 3500 - 3563 = In-between trails ID for railgun
5. 5000+ = Avatar TID
6. 7000+ = Avatar soul projectiles TID
7. 11000+ = Avatar Cubes TID
8. 13000+ = Nhumcign TID
9. 14000+ = Zealot TID
10. 15000+ = Zealot Shield TID
11. 17000 - 19048 = Shared item IDs
12. 19049 - 29049 = Limited Respawn Ammos
13. 29050 - 29150 = Charm drops on field
14. 32768 = Special FX TID
15. 32769 = Thunder Staff temporary damager tid
16. 40000 - 42048 = Thunder Staff Ring tid
17. 42049 - Talisman Mark tid
18. Anything above 66000 => any monster tid
*/

int AvatarTID = 0;
int PurpDemTID = 0;
int ZealotTID = 0;

global int 0: MapChanged;
global int 5: HardcoreSet;

int screenres1 = -1, screenres2 = -1;
int total_level = 0, min_level = INT_MAX, max_level = INT_MIN;
int active_quest_id = -1;
int dnd_monster_tid = DND_MONSTERTID_BEGIN;

void GiveMonsterTID (void) {
	Thing_ChangeTID(0, dnd_monster_tid++);
}

enum {
    LEVEL_TOTAL,
    LEVEL_MIN,
    LEVEL_MAX
};

int SetBit(int x, int n) {
	return x | (1 << n);
}

int ClearBit(int x, int n) {
	return x & ~(1 << n);
}

int IsSet(int x, int n) {
	return x & (1 << n);
}

int ResetBits(int val, int begin, int end) {
	for(int i = begin; i < end + 1; ++i)
		val &= ~(1 << i);
	return val;
}

// only positive
int getpow2 (int x) {
	int res = 0;
	while((x >>= 1))
		res++;
	return res;
}

int pow (int x, int n) {
	int y = 1;
	while (n-- > 0) y *= x;
	return y;
}

int abs (int x) {
	if(x < 0)
		return -x;
	return x;
}

int fdistance (int tid1, int tid2) {
	int len;
	int y = getactory(tid1) - getactory(tid2);
	int x = getactorx(tid1) - getactorx(tid2);
	int z = getactorz(tid1) - getactorz(tid2);

	int ang = vectorangle(x,y);
	if(((ang+0.125)%0.5) > 0.25) len = fixeddiv(y, sin(ang));
	else len = fixeddiv(x, cos(ang));

	ang = vectorangle(len, z);
	if(((ang+0.125)%0.5) > 0.25) len = fixeddiv(z, sin(ang));
	else len = fixeddiv(len, cos(ang));

	return len;
}

// takes deltax and deltay as parameter for actor comparisons
int AproxDistance (int dx, int dy) {
	dx = abs(dx);
	dy = abs(dy);

	if (dx < dy)
		return dx + dy - (dx >> 1);

	return dx + dy - (dy >> 1);
}

int SetInventory (str item, int count) {
	int n = count - CheckInventory (item);
	if (n > 0)
		GiveInventory (item, n);
	else if (n < 0)
		TakeInventory (item, -n);
	return n;
}

int SetActorInventory (int tid, str item, int count) {
	int n = count - CheckActorInventory (tid, item);
	if (n > 0)
		GiveActorInventory (tid, item, n);
	else if (n < 0)
		TakeActorInventory (tid, item, -1 * n);
	return n;
}

int Clamp_Between(int x, int low, int high) {
	if(x < low)
		return low;
	if(x > high)
		return high;
	return x;
}

int IsAlive() {
	return GetActorProperty(0, APROP_HEALTH) > 0;
}

int IsActorAlive(int tid) {
	return GetActorProperty(tid, APROP_HEALTH) > 0;
}

int GetGameLevelInfo(int type) {
    switch(type) {
        case LEVEL_TOTAL:
            return total_level;
        case LEVEL_MIN:
            return min_level;
        case LEVEL_MAX:
            return max_level;
    }
	return total_level;
}

// Copied from ZDWiki.
// Fixed-point version, only works up to 30,000 or so:
int fsqrt(int number) 
{ 
  int samples = 15; // Samples for accuracy

  if (number == 1.0) return 1.0; 
  if (number <= 0) return 0;
  int val = samples<<17 + samples<<19; // x*10 = x<<1 + x<<3
  for (int i=0; i<samples; ++i) 
    val = (val + FixedDiv(number, val)) >> 1;

  return val; 
}

int sqrt_z(int number)
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

int Min(int x, int y) {
	if(x < y)
		return x;
	return y;
}

int magnitudeThree(int x, int y, int z)
{
    return sqrt_z(x*x + y*y + z*z);
}

int smart_mul(int x, int y) {
	if(x >= 1.0 && y >= 1.0)
		return FixedMul(x, y);
	return x * y;
}

int IsDigit(int c) {
	return c >= '0' && c <= '9';
}

// improve sens as parameter later?
int ftrunc(int x) {
	return (x + 0.05) & 0xFFFFF000;
}

void SpawnDrop(str actor, int zoffset, int thrust, int setspecial) {
	SpawnForced(actor, GetActorX(0), GetActorY(0), GetActorZ(0) + zoffset, DND_DROP_TID);
	ThrustThing(random(0, 255), random(2, 5), 0, DND_DROP_TID);
	ThrustThingZ(DND_DROP_TID, thrust, 0, 0);
	SetActorProperty(DND_DROP_TID, APROP_MASS, setspecial);
	Thing_ChangeTID(DND_DROP_TID, 0);
}

// put here because acs doesnt recognize the below 3 variables have changed
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

#endif