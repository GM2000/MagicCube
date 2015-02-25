struct block
{
	char *BlockName;
	bool isSoil;
	bool canSee;
	bool hyaline;
	bool halfHyaline;
	bool isGrass;
	bool isLeaf;
	bool isPlant;
	bool isLiquid;
	int Hardness;
	int Texture[6];
};

void InitBlockDate();

block GetBlock(float BlockX,float BlockY,float BlockZ);

extern block MC_Block[1000];