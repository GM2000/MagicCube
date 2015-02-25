#include "File.h"
#include "Chunk.h"

void saveChunkToFile(chunk ChunkDat,int ChunkX,int ChunkZ);

void SaveWorld()
{
	writeBasicDate();
	for (int i=0;i<225;i++)
	{
		if (ChunkInfo[i].NeedSave)
		{
			saveChunkToFile(Chunk[i],Chunk[i].chunkX,Chunk[i].chunkZ);
			ChunkInfo[i].NeedSave=false;
		}
	}
}