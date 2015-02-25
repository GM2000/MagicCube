struct particle
{
	float x;
	float y;
	float z;

	float sizeX;
	float sizeZ;

	float xMove;
	float yMove;
	float zMove;

	int health;

	float TextureX;
	float TextureZ;
	float TextureX2;
	float TextureZ2;

	bool isLive;

	bool hasColor;
};

extern particle Particle[1000];

void Particles();

int autoAddParticle(int x,int y,int z,int type,int BlockID);