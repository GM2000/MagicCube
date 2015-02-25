#include "Chunk.h"
#include "Player.h"

int NewChunkList[15][15];

void LoadChunk(int ChunkID,int ChunkX,int ChunkZ);

void resetChunkList()
{
	for (int i=0;i<15;i++)
	{
		for (int j=0;j<15;j++)
		{
	 		ChunkList[i][j]=NewChunkList[i][j];
		}
	}
}

void resetChunk(int NewPlayerChunkX,int NewPlayerChunkZ)
{
	int OldPlayerChunkX=player.ChunkX;
	int OldPlayerChunkZ=player.ChunkZ;
	if (player.ChunkX>NewPlayerChunkX)
	{
		NewChunkList[7][7]=ChunkList[6][7];
		for (int i=0;i<15;i++)
		{
			for (int j=0;j<15;j++)
			{
				if (i==0)
				{
					player.ChunkX=NewPlayerChunkX;
					player.ChunkZ=NewPlayerChunkZ;
					NewChunkList[0][j]=ChunkList[14][j];
					InitChunk(ChunkList[14][j],-7,j-7,false);
					Chunk[ChunkList[13][j]].isCreateList=false;
					player.ChunkX=OldPlayerChunkX;
					player.ChunkZ=OldPlayerChunkZ;
				}else
				{
					NewChunkList[i][j]=ChunkList[i-1][j];
				}
			}
		}
	}else if (player.ChunkX<NewPlayerChunkX)
	{
		NewChunkList[7][7]=ChunkList[8][7];
		for (int i=0;i<15;i++)
		{
			for (int j=0;j<15;j++)
			{
				if (i==14)
				{
					player.ChunkX=NewPlayerChunkX;
					player.ChunkZ=NewPlayerChunkZ;
					NewChunkList[14][j]=ChunkList[0][j];
					InitChunk(ChunkList[0][j],7,j-7,false);
					Chunk[ChunkList[1][j]].isCreateList=false;
					player.ChunkX=OldPlayerChunkX;
					player.ChunkZ=OldPlayerChunkZ;
				}else
				{
					NewChunkList[i][j]=ChunkList[i+1][j];
				}
			}
		}
	}
	if (player.ChunkZ>NewPlayerChunkZ)
	{
		NewChunkList[7][7]=ChunkList[7][6];
		for (int i=0;i<15;i++)
		{
			for (int j=0;j<15;j++)
			{
				if (j==0)
				{
					player.ChunkX=NewPlayerChunkX;
					player.ChunkZ=NewPlayerChunkZ;
					NewChunkList[i][0]=ChunkList[i][14];
					InitChunk(ChunkList[i][14],i-7,-7,false);
					Chunk[ChunkList[i][13]].isCreateList=false;
					player.ChunkX=OldPlayerChunkX;
					player.ChunkZ=OldPlayerChunkZ;
				}else
				{
					NewChunkList[i][j]=ChunkList[i][j-1];
				}
			}
		}
	}else if (player.ChunkZ<NewPlayerChunkZ)
	{
		NewChunkList[7][7]=ChunkList[7][8];
		for (int i=0;i<15;i++)
		{
			for (int j=0;j<15;j++)
			{
				if (j==14)
				{
					player.ChunkX=NewPlayerChunkX;
					player.ChunkZ=NewPlayerChunkZ;
					NewChunkList[i][14]=ChunkList[i][0];
					InitChunk(ChunkList[i][0],i-7,7,false);
					Chunk[ChunkList[i][1]].isCreateList=false;
					player.ChunkX=OldPlayerChunkX;
					player.ChunkZ=OldPlayerChunkZ;
				}else
				{
					NewChunkList[i][j]=ChunkList[i][j+1];
				}
			}
		}
	}

	resetChunkList();
}

void resetPlayerChunk()
{
	int NewPlayerChunkX=player.ChunkX;
	int NewPlayerChunkZ=player.ChunkZ;

	if ((player.x/16<0) & (player.ChunkX!=(int)player.x/16-1))
	{
		NewPlayerChunkX=(int)player.x/16-1;
		resetChunk(NewPlayerChunkX,NewPlayerChunkZ);
		player.ChunkX=NewPlayerChunkX;
	}else if ((player.x/16>0) & (player.ChunkX!=(int)player.x/16))
	{
		NewPlayerChunkX=(int)player.x/16;
 		resetChunk(NewPlayerChunkX,NewPlayerChunkZ);
		player.ChunkX=NewPlayerChunkX;
	}
	if ((player.z/16<0) & (player.ChunkZ!=(int)player.z/16-1))
	{
		NewPlayerChunkZ=(int)player.z/16-1;
		resetChunk(NewPlayerChunkX,NewPlayerChunkZ);
		player.ChunkZ=NewPlayerChunkZ;
	}else if ((player.z/16>0) & (player.ChunkZ!=(int)player.z/16))
	{
		NewPlayerChunkZ=(int)player.z/16;
		resetChunk(NewPlayerChunkX,NewPlayerChunkZ);
		player.ChunkZ=NewPlayerChunkZ;
	}
}