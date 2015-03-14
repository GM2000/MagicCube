#include "Block.h"
#include "Chunk.h"
#include "Texture.h"

block MC_Block[1000];

void InitBlockDate()
{
	for (int i=0;i<1000;i++)
	{
		MC_Block[i].BlockName="";
		
		MC_Block[i].isSoil=true;
		MC_Block[i].isGrass=false;
		MC_Block[i].isLeaf=false;
		MC_Block[i].isLiquid=false;
		MC_Block[i].isPlant=false;

		MC_Block[i].hyaline=false;
		MC_Block[i].halfHyaline=false;
		MC_Block[i].canSee=true;
		MC_Block[i].Hardness=-1;
		MC_Block[i].Texture[0]=-1;
		MC_Block[i].Texture[1]=-1;
		MC_Block[i].Texture[2]=-1;
		MC_Block[i].Texture[3]=-1;
		MC_Block[i].Texture[4]=-1;
		MC_Block[i].Texture[5]=-1;
		MC_Block[i].itemType=MC_BLOCK;
	}

	MC_Block[0].hyaline=true;
	MC_Block[0].isSoil=false;
	MC_Block[0].canSee=false;

	//1
	MC_Block[1].BlockName="Ê¯Í·";
		
	MC_Block[1].isSoil=true;
	MC_Block[1].isGrass=false;
	MC_Block[1].isLeaf=false;
	MC_Block[1].isLiquid=false;
	MC_Block[1].isPlant=false;

	MC_Block[1].hyaline=false;
	MC_Block[1].halfHyaline=false;
	MC_Block[1].canSee=true;
	MC_Block[1].Hardness=15;

	MC_Block[1].Texture[0]=STONE;
	MC_Block[1].Texture[1]=STONE;
	MC_Block[1].Texture[2]=STONE;
	MC_Block[1].Texture[3]=STONE;
	MC_Block[1].Texture[4]=STONE;
	MC_Block[1].Texture[5]=STONE;
	//2
	MC_Block[2].BlockName="²Ý";
		
	MC_Block[2].isSoil=true;
	MC_Block[2].isGrass=true;
	MC_Block[2].isLeaf=false;
	MC_Block[2].isLiquid=false;
	MC_Block[2].isPlant=false;

	MC_Block[2].hyaline=false;
	MC_Block[2].halfHyaline=false;
	MC_Block[2].canSee=true;
	MC_Block[2].Hardness=3;

	MC_Block[2].Texture[0]=GRASS_TOP;
	MC_Block[2].Texture[1]=DIRT;
	MC_Block[2].Texture[2]=GRASS_SIDE;
	MC_Block[2].Texture[3]=GRASS_SIDE;
	MC_Block[2].Texture[4]=GRASS_SIDE;
	MC_Block[2].Texture[5]=GRASS_SIDE;
	//3
	MC_Block[3].BlockName="ÄàÍÁ";
		
	MC_Block[3].isSoil=true;
	MC_Block[3].isGrass=false;
	MC_Block[3].isLeaf=false;
	MC_Block[3].isLiquid=false;
	MC_Block[3].isPlant=false;

	MC_Block[3].hyaline=false;
	MC_Block[3].halfHyaline=false;
	MC_Block[3].canSee=true;
	MC_Block[3].Hardness=3;

	MC_Block[3].Texture[0]=DIRT;
	MC_Block[3].Texture[1]=DIRT;
	MC_Block[3].Texture[2]=DIRT;
	MC_Block[3].Texture[3]=DIRT;
	MC_Block[3].Texture[4]=DIRT;
	MC_Block[3].Texture[5]=DIRT;
	//5
	MC_Block[5].BlockName="Ä¾°å";
		
	MC_Block[5].isSoil=true;
	MC_Block[5].isGrass=false;
	MC_Block[5].isLeaf=false;
	MC_Block[5].isLiquid=false;
	MC_Block[5].isPlant=false;

	MC_Block[5].hyaline=false;
	MC_Block[5].halfHyaline=false;
	MC_Block[5].canSee=true;
	MC_Block[5].Hardness=5;

	MC_Block[5].Texture[0]=PLANKS_BIRCH;
	MC_Block[5].Texture[1]=PLANKS_BIRCH;
	MC_Block[5].Texture[2]=PLANKS_BIRCH;
	MC_Block[5].Texture[3]=PLANKS_BIRCH;
	MC_Block[5].Texture[4]=PLANKS_BIRCH;
	MC_Block[5].Texture[5]=PLANKS_BIRCH;
	//6
	MC_Block[6].BlockName="Ê÷Ãç";
		
	MC_Block[6].isSoil=false;
	MC_Block[6].isGrass=false;
	MC_Block[6].isLeaf=false;
	MC_Block[6].isLiquid=false;
	MC_Block[6].isPlant=true;

	MC_Block[6].hyaline=true;
	MC_Block[6].halfHyaline=false;
	MC_Block[6].canSee=true;
	MC_Block[6].Hardness=0;

	MC_Block[6].Texture[0]=SAPLING_BIRCH;

	MC_Block[6].itemType=MC_ITEM;
	//8
	MC_Block[8].BlockName="Ë®";
	
	MC_Block[8].isSoil=false;
	MC_Block[8].isGrass=false;
	MC_Block[8].isLeaf=false;
	MC_Block[8].isLiquid=true;
	MC_Block[8].isPlant=false;

	MC_Block[8].hyaline=true;
	MC_Block[8].halfHyaline=true;
	MC_Block[8].canSee=true;
	MC_Block[8].Hardness=-1;

	MC_Block[8].Texture[0]=WATER_STILL;
	MC_Block[8].Texture[1]=WATER_STILL;
	MC_Block[8].Texture[2]=WATER_STILL;
	MC_Block[8].Texture[3]=WATER_STILL;
	MC_Block[8].Texture[4]=WATER_STILL;
	MC_Block[8].Texture[5]=WATER_STILL;
	//17
	MC_Block[17].BlockName="Ô²Ä¾";
	
	MC_Block[17].isSoil=true;
	MC_Block[17].isGrass=false;
	MC_Block[17].isLeaf=false;
	MC_Block[17].isLiquid=false;
	MC_Block[17].isPlant=false;

	MC_Block[17].hyaline=false;
	MC_Block[17].halfHyaline=false;
	MC_Block[17].canSee=true;
	MC_Block[17].Hardness=5;

	MC_Block[17].Texture[0]=LOG_BIRCH_TOP;
	MC_Block[17].Texture[1]=LOG_BIRCH_TOP;
	MC_Block[17].Texture[2]=LOG_BIRCH;
	MC_Block[17].Texture[3]=LOG_BIRCH;
	MC_Block[17].Texture[4]=LOG_BIRCH;
	MC_Block[17].Texture[5]=LOG_BIRCH;
	//18
	MC_Block[18].BlockName="Ê÷Ò¶";
	
	MC_Block[18].isSoil=true;
	MC_Block[18].isGrass=false;
	MC_Block[18].isLeaf=true;
	MC_Block[18].isLiquid=false;
	MC_Block[18].isPlant=false;

	MC_Block[18].hyaline=true;
	MC_Block[18].halfHyaline=false;
	MC_Block[18].canSee=true;
	MC_Block[18].Hardness=1;

	MC_Block[18].Texture[0]=LEAVES_BIRCH;
	MC_Block[18].Texture[1]=LEAVES_BIRCH;
	MC_Block[18].Texture[2]=LEAVES_BIRCH;
	MC_Block[18].Texture[3]=LEAVES_BIRCH;
	MC_Block[18].Texture[4]=LEAVES_BIRCH;
	MC_Block[18].Texture[5]=LEAVES_BIRCH;
	//20
	MC_Block[20].BlockName="²£Á§";
	
	MC_Block[20].isSoil=true;
	MC_Block[20].isGrass=false;
	MC_Block[20].isLeaf=false;
	MC_Block[20].isLiquid=false;
	MC_Block[20].isPlant=false;

	MC_Block[20].hyaline=true;
	MC_Block[20].halfHyaline=false;
	MC_Block[20].canSee=true;
	MC_Block[20].Hardness=3;

	MC_Block[20].Texture[0]=GLASS;
	MC_Block[20].Texture[1]=GLASS;
	MC_Block[20].Texture[2]=GLASS;
	MC_Block[20].Texture[3]=GLASS;
	MC_Block[20].Texture[4]=GLASS;
	MC_Block[20].Texture[5]=GLASS;

}