struct Player
{
	float x;
	float y;
	float z;

	int ChunkZ;
	int ChunkX;

	int ChooseBlockChunkID;
	int ChooseBlockX;
	int ChooseBlockY;
	int ChooseBlockZ;
	int ChooseBlockFrount;

	int PlayerBag[9];

	float BreakTime;
	float BreakTimeNeed;

	float around;
	float upanddown;

	float speed;
	float g;
	float dropSpeed;

	bool fly;
	bool isJumping;
	bool onGround;
	bool inWater;

	float jumpSpeed;

	int choiceNumber;
};
extern Player player;