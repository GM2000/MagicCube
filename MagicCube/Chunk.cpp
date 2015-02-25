#include "Chunk.h"
#include "Player.h"
#include "Block.h"
#include "Particle.h"

bool hasCreatList;

int BuildTime;
int ChunkList[15][15];

chunk Chunk[225];

threadParam ChunkInfo[255];

int getBlockID(float x,float y,float z)
{
	int ChunkX;
	int ChunkZ;
	int LocChunkX;
	int LocChunkZ;
	int PlayerChunkX=player.ChunkX;
	int PlayerChunkZ=player.ChunkZ;
	if (x/16<0)
	{
		LocChunkX=x/16-1;
	}else{
		LocChunkX=x/16;
	}
	if (z/16<0)
	{
		LocChunkZ=z/16-1;
	}else{
		LocChunkZ=z/16;
	}
	/*
	if (LocChunkX>player.ChunkX)
	{
		ChunkX=player.ChunkX+1;
	}else if(LocChunkX<player.ChunkX){
		ChunkX=player.ChunkX-1;
	}else{
		ChunkX=player.ChunkX;
	}
	if (LocChunkZ>player.ChunkZ)
	{
		ChunkZ=player.ChunkZ+1;
	}else if (LocChunkZ<player.ChunkZ){
		ChunkZ=player.ChunkZ-1;
	}else{
		ChunkZ=player.ChunkZ;
	}
	*/
	int ChunkID;
	ChunkX=LocChunkX-PlayerChunkX;
	ChunkZ=LocChunkZ-PlayerChunkZ;
	if ((ChunkX<-7) | (ChunkZ<-7))
	{
		ChunkID=-1;
	}else{
		ChunkID=ChunkList[7+ChunkX][7+ChunkZ];
	}
	if ((ChunkID>-1) & (ChunkID<225))
	{
		return Chunk[ChunkID].BlockID[(int)(x-Chunk[ChunkID].chunkX*16)][(int)y][(int)(z-Chunk[ChunkID].chunkZ*16)];
	}else{
		return 0;
	}
}

void setBlockID(float x,float y,float z,int BlockID)
{
	int ChunkX;
	int ChunkZ;
	int LocChunkX;
	int LocChunkZ;
	if (x/16<0)
	{
		LocChunkX=x/16-1;
	}else{
		LocChunkX=x/16;
	}
	if (z/16<0)
	{
		LocChunkZ=z/16-1;
	}else{
		LocChunkZ=z/16;
	}
	if (LocChunkX>player.ChunkX)
	{
		ChunkX=player.ChunkX+1;
	}else if(LocChunkX<player.ChunkX){
		ChunkX=player.ChunkX-1;
	}else{
		ChunkX=player.ChunkX;
	}
	if (LocChunkZ>player.ChunkZ)
	{
		ChunkZ=player.ChunkZ+1;
	}else if (LocChunkZ<player.ChunkZ){
		ChunkZ=player.ChunkZ-1;
	}else{
		ChunkZ=player.ChunkZ;
	}
	int ChunkID=ChunkList[7+ChunkX-player.ChunkX][7+ChunkZ-player.ChunkZ];
	int NowBlockID=Chunk[ChunkID].BlockID[(int)(x-Chunk[ChunkID].chunkX*16)][(int)y][(int)(z-Chunk[ChunkID].chunkZ*16)];
	if ((ChunkID>-1) & (ChunkID<225))
	{
		if (!MC_Block[Chunk[ChunkID].BlockID[(int)(x-Chunk[ChunkID].chunkX*16)][(int)y-1][(int)(z-Chunk[ChunkID].chunkZ*16)]].isPlant)
		{
			if (BlockID>-1)
			{
				ChunkInfo[ChunkID].NeedSave=true;
				ChunkInfo[ChunkID].oldChunkX=Chunk[ChunkID].chunkX;
				ChunkInfo[ChunkID].oldChunkZ=Chunk[ChunkID].chunkZ;
				////////////////////////////Á£×Ó²âÊÔ
				/*
					Particle[0].x=x;
					Particle[0].y=y;
					Particle[0].z=z;
					Particle[0].sizeX=0.2;
					Particle[0].sizeZ=0.2;
					Particle[0].xMove=0.1;
					Particle[0].yMove=-0.15;
					Particle[0].zMove=0.1;
					Particle[0].health=100;
					Particle[0].TextureX=0;
					Particle[0].TextureZ=0;
					Particle[0].TextureX2=32;
					Particle[0].TextureZ2=32;
					Particle[0].isLive=true;
				*/
				autoAddParticle(x,y,z,0,NowBlockID);
				////////////////////////////END
				Chunk[ChunkID].BlockID[(int)(x-Chunk[ChunkID].chunkX*16)][(int)y][(int)(z-Chunk[ChunkID].chunkZ*16)]=BlockID;
				if (MC_Block[Chunk[ChunkID].BlockID[(int)(x-Chunk[ChunkID].chunkX*16)][(int)y+1][(int)(z-Chunk[ChunkID].chunkZ*16)]].isPlant)
				{
					Chunk[ChunkID].BlockID[(int)(x-Chunk[ChunkID].chunkX*16)][(int)y+1][(int)(z-Chunk[ChunkID].chunkZ*16)]=0;
				}
				Chunk[ChunkList[7+ChunkX-player.ChunkX][7+ChunkZ-player.ChunkZ]].isCreateList=false;
				Chunk[ChunkList[7+ChunkX-player.ChunkX][7+ChunkZ-player.ChunkZ+1]].isCreateList=false;
				Chunk[ChunkList[7+ChunkX-player.ChunkX][7+ChunkZ-player.ChunkZ-1]].isCreateList=false;
				Chunk[ChunkList[7+ChunkX-player.ChunkX+1][7+ChunkZ-player.ChunkZ]].isCreateList=false;
				Chunk[ChunkList[7+ChunkX-player.ChunkX-1][7+ChunkZ-player.ChunkZ]].isCreateList=false;
				Chunk[ChunkList[7+ChunkX-player.ChunkX][7+ChunkZ-player.ChunkZ]].mustCreateListNow=true;
				Chunk[ChunkList[7+ChunkX-player.ChunkX][7+ChunkZ-player.ChunkZ+1]].mustCreateListNow=true;
				Chunk[ChunkList[7+ChunkX-player.ChunkX][7+ChunkZ-player.ChunkZ-1]].mustCreateListNow=true;
				Chunk[ChunkList[7+ChunkX-player.ChunkX+1][7+ChunkZ-player.ChunkZ]].mustCreateListNow=true;
				Chunk[ChunkList[7+ChunkX-player.ChunkX-1][7+ChunkZ-player.ChunkZ]].mustCreateListNow=true;
			}else if (BlockID=-1){
				if ((player.ChooseBlockChunkID!=ChunkList[7+ChunkX-player.ChunkX][7+ChunkZ-player.ChunkZ]) | (player.ChooseBlockX!=(int)(x-Chunk[ChunkID].chunkX*16)) | (player.ChooseBlockY!=(int)y) | (player.ChooseBlockZ!=(int)(z-Chunk[ChunkID].chunkZ*16)))
				{
					player.BreakTime=0;
					player.ChooseBlockChunkID=ChunkList[7+ChunkX-player.ChunkX][7+ChunkZ-player.ChunkZ];
					player.ChooseBlockX=(int)(x-Chunk[ChunkID].chunkX*16);
					player.ChooseBlockY=(int)y;
					player.ChooseBlockZ=(int)(z-Chunk[ChunkID].chunkZ*16);
					player.BreakTimeNeed=MC_Block[Chunk[player.ChooseBlockChunkID].BlockID[player.ChooseBlockX][player.ChooseBlockY][player.ChooseBlockZ]].Hardness;
				}
			}
		}
	}
}

int InitChunk(int ChunkID,int ChunkX,int ChunkZ,bool isFirst)
{
	Chunk[ChunkID].isCreateList=false;
	Chunk[ChunkID].mustCreateListNow=false;
	if (isFirst)
	{
		ChunkInfo[ChunkID].NeedSave=false;
	}
	ChunkInfo[ChunkID].oldChunkX=Chunk[ChunkID].chunkX;
	ChunkInfo[ChunkID].oldChunkZ=Chunk[ChunkID].chunkZ;
	ChunkInfo[ChunkID].ChunkX=Chunk[NewChunkList[7][7]].chunkX+ChunkX;
	ChunkInfo[ChunkID].ChunkZ=Chunk[NewChunkList[7][7]].chunkZ+ChunkZ;
	ChunkInfo[ChunkID].NeedBuild=true;
	//LoadChunk(ChunkID,Chunk[NewChunkList[7][7]].chunkX+ChunkX,Chunk[NewChunkList[7][7]].chunkZ+ChunkZ);
	Chunk[ChunkID].chunkX=player.ChunkX+ChunkX;
	Chunk[ChunkID].chunkZ=player.ChunkZ+ChunkZ;
	if (isFirst)
	{
		ChunkList[ChunkX+7][ChunkZ+7]=ChunkID;
	}
	return TRUE;
}