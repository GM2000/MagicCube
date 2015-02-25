#include "MagicCube.h"

struct threadParam
{
	int ChunkX;
	int ChunkZ;
	int oldChunkX;
	int oldChunkZ;
	bool NeedBuild;
	bool NeedSave;
};

struct chunk
{
	int chunkX;
	int chunkZ;

	GLint BlockID[16][256][16];
	GLuint glLists;

	bool isCreateList;
	bool mustCreateListNow;
};

extern threadParam ChunkInfo[255];

extern int seed;

extern bool hasCreatList;

extern chunk Chunk[225];
extern int ChunkList[15][15];

extern int NewChunkList[15][15];

int WriteDrawPointer(int x,int y,int z,int frount,int TextureID,float ColorR,float ColorG,float ColorB,int Mode);

int getBlockID(float x,float y,float z);
void setBlockID(float x,float y,float z,int BlockID);

bool isTouch();
int InitChunk(int ChunkID,int ChunkX,int ChunkZ,bool isFirst);

void resetPlayerChunk();