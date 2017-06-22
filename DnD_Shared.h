#define SHARED_ITEM_TID_BEGIN 17000
#define SHARED_ITEM_TID_MAX 2048

enum {
	SHI_STIMPACK,
	SHI_MEDKIT
};

#define MAX_SHARED_ITEM_TYPES SHI_MEDKIT + 1
str SharedItemMessage[MAX_SHARED_ITEM_TYPES] = { 
	"\ccHealth pickup : \c[Y5]Stimpack x 10\c-",
	"\ccHealth pickup : \c[Y5]Medikit x 25\c-"
};

struct sif {
	bool semaphore[MAXPLAYERS];
	bool pickup_state[MAXPLAYERS];
};

int shared_item_counter = 0;
struct sif Shared_Item_Info[SHARED_ITEM_TID_MAX];

// allow max 16 items
int shared_item_queue_count = 0;
int shared_item_clientside_queue[16];

// expects player tid for now
int GetClosestSharedItem(int tid) {
	int closest = -1;
	int mindist = INT_MAX, curdist = 0, i = 0;
	for(i = 0; i < shared_item_counter; ++i) {
		curdist = fdistance(tid, SHARED_ITEM_TID_BEGIN + i);
		if(curdist < mindist) {
			mindist = curdist;
			closest = i;
		}
	}
	// if this is picked, search again for another candidate on the same dist (handles corner case: stacked item)
	if(Shared_Item_Info[closest].pickup_state[tid - P_TIDSTART]) {
		for(i = 0; i < shared_item_counter; ++i) {
			if(Shared_Item_Info[i].pickup_state[tid - P_TIDSTART])
				continue;
			curdist = fdistance(tid, SHARED_ITEM_TID_BEGIN + i);
			if(curdist == mindist)
				closest = i;
		}
	}
	return closest;
}