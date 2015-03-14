#include "Chunk.h"
#include "Player.h"
#include "Block.h"

bool isTouch()
{
	float x=player.x;
	float y=player.y;
	float z=player.z;
	if ((MC_Block[getBlockID(x+0.2,y-1,z+0.2)].isLiquid)|(MC_Block[getBlockID(x+0.2,y-0.75,z+0.2)].isLiquid)|(MC_Block[getBlockID(x+0.2,y+0.1,z+0.2)].isLiquid)|(MC_Block[getBlockID(x-0.2,y-1,z+0.2)].isLiquid)|(MC_Block[getBlockID(x-0.2,y-0.75,z+0.2)].isLiquid)|(MC_Block[getBlockID(x-0.2,y+0.1,z+0.2)].isLiquid)|(MC_Block[getBlockID(x+0.2,y-1,z-0.2)].isLiquid)|(MC_Block[getBlockID(x+0.2,y-0.75,z-0.2)].isLiquid)|(MC_Block[getBlockID(x+0.2,y+0.1,z-0.2)].isLiquid)|(MC_Block[getBlockID(x-0.2,y-1,z-0.2)].isLiquid)|(MC_Block[getBlockID(x-0.2,y-0.75,z-0.2)].isLiquid)|(MC_Block[getBlockID(x-0.2,y+0.1,z-0.2)].isLiquid))	
	{
		player.inWater=true;
		player.isJumping=false;
		player.onGround=true;
	}else if (!((MC_Block[getBlockID(x+0.2,y-1.7,z+0.2)].isLiquid)|(MC_Block[getBlockID(x+0.2,y-0.75,z+0.2)].isLiquid)|(MC_Block[getBlockID(x+0.2,y+0.1,z+0.2)].isLiquid)|(MC_Block[getBlockID(x-0.2,y-1.7,z+0.2)].isLiquid)|(MC_Block[getBlockID(x-0.2,y-0.75,z+0.2)].isLiquid)|(MC_Block[getBlockID(x-0.2,y+0.1,z+0.2)].isLiquid)|(MC_Block[getBlockID(x+0.2,y-1.7,z-0.2)].isLiquid)|(MC_Block[getBlockID(x+0.2,y-0.75,z-0.2)].isLiquid)|(MC_Block[getBlockID(x+0.2,y+0.1,z-0.2)].isLiquid)|(MC_Block[getBlockID(x-0.2,y-1.7,z-0.2)].isLiquid)|(MC_Block[getBlockID(x-0.2,y-0.75,z-0.2)].isLiquid)|(MC_Block[getBlockID(x-0.2,y+0.1,z-0.2)].isLiquid)))
	{
		if (player.inWater)
		{
			player.inWater=false;
			player.jumpSpeed=0.001;
			player.onGround=false;
			player.isJumping=true;
		}
	}
	if ((MC_Block[getBlockID(x+0.2,y-1.6,z+0.2)].isSoil)|(MC_Block[getBlockID(x+0.2,y-0.75,z+0.2)].isSoil)|(MC_Block[getBlockID(x+0.2,y+0.1,z+0.2)].isSoil)|(MC_Block[getBlockID(x-0.2,y-1.6,z+0.2)].isSoil)|(MC_Block[getBlockID(x-0.2,y-0.75,z+0.2)].isSoil)|(MC_Block[getBlockID(x-0.2,y+0.1,z+0.2)].isSoil)|(MC_Block[getBlockID(x+0.2,y-1.6,z-0.2)].isSoil)|(MC_Block[getBlockID(x+0.2,y-0.75,z-0.2)].isSoil)|(MC_Block[getBlockID(x+0.2,y+0.1,z-0.2)].isSoil)|(MC_Block[getBlockID(x-0.2,y-1.6,z-0.2)].isSoil)|(MC_Block[getBlockID(x-0.2,y-0.75,z-0.2)].isSoil)|(MC_Block[getBlockID(x-0.2,y+0.1,z-0.2)].isSoil))
	{
		return true;
	}else{
		return false;
	}
}