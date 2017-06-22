#define MAXPLAYERS 64
#define P_TIDSTART 1000
#define TICRATE 35

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
12. 32768 = Special FX TID
*/

int total_level = 0, min_level = INT_MAX, max_level = INT_MIN;

enum {
    LEVEL_TOTAL,
    LEVEL_MIN,
    LEVEL_MAX
};

enum {
	ACC_WISDOM = 1,
	ACC_GREED,
	ACC_DEMON,
	ACC_FIRE,
	ACC_ANGELIC,
	ACC_REFLECT,
	ACC_NETHER,
	ACC_TALTOS,
	ACC_HATE,
	ACC_ARTEMIS,
	ACC_AGAMOTTO,
	ACC_GRYPHON,
	ACC_LICH
};

#define MAX_ACCESSORY ACC_LICH

int SetBit(int x, int n) {
	return x | (1 << n);
}

int ClearBit(int x, int n) {
	return x & ~(1 << n);
}

int IsSet(int x, int n) {
	return x & (1 << n);
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