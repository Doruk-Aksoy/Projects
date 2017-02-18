#define MAXPLAYERS 64
#define P_TIDSTART 1000
#define TICRATE 35

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

function int pow (int x, int n) {
	int y = 1;
	while (n-- > 0) y *= x;
	return y;
}

function int abs (int x) {
	if(x < 0)
		return -x;
	return x;
}

function int fdistance (int tid1, int tid2) {
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
function int AproxDistance (int dx, int dy) {
	dx = abs(dx);
	dy = abs(dy);

	if (dx < dy)
		return dx + dy - (dx >> 1);

	return dx + dy - (dy >> 1);
}

function int SetInventory (str item, int count) {
	int n = count - CheckInventory (item);
	if (n > 0)
		GiveInventory (item, n);
	else if (n < 0)
		TakeInventory (item, -n);
	return n;
}

function int SetActorInventory (int tid, str item, int count) {
	int n = count - CheckActorInventory (tid, item);
	if (n > 0)
		GiveActorInventory (tid, item, n);
	else if (n < 0)
		TakeActorInventory (tid, item, -1 * n);
	return n;
}

function int Clamp_Between(int x, int low, int high) {
	if(x < low)
		return low;
	if(x > high)
		return high;
	return x;
}

function int IsAlive() {
	return GetActorProperty(0, APROP_HEALTH) > 0;
}

function int IsActorAlive(int tid) {
	return GetActorProperty(tid, APROP_HEALTH) > 0;
}

function int GetGameLevelInfo(int type) {
    switch(type) {
        case LEVEL_TOTAL:
            return total_level;
        case LEVEL_MIN:
            return min_level;
        case LEVEL_MAX:
            return max_level;
    }
}