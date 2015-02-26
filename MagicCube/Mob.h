#define MOB_FALLING_ITEM 1
#define MOB_NONE 0

struct mob
{
	int mobType;
	int mobTag[2];

	float x;
	float y;
	float z;

	float Rot;

	float xMove;
	float yMove;
	float zMove;

	bool moveTag;
};

void reSetMob();
int loadMob(int MobType,int tag,float x,float y,float z);