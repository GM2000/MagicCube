#include "Chunk.h"
#include "Player.h"
#include "Block.h"

bool isTouch()
{
	float x=player.x;
	float y=player.y;
	float z=player.z;
	if ((MC_Block[getBlockID(x+0.2,y-1.6,z+0.2)].isSoil)|(MC_Block[getBlockID(x+0.2,y-0.75,z+0.2)].isSoil)|(MC_Block[getBlockID(x+0.2,y+0.1,z+0.2)].isSoil)|(MC_Block[getBlockID(x-0.2,y-1.6,z+0.2)].isSoil)|(MC_Block[getBlockID(x-0.2,y-0.75,z+0.2)].isSoil)|(MC_Block[getBlockID(x-0.2,y+0.1,z+0.2)].isSoil)|(MC_Block[getBlockID(x+0.2,y-1.6,z-0.2)].isSoil)|(MC_Block[getBlockID(x+0.2,y-0.75,z-0.2)].isSoil)|(MC_Block[getBlockID(x+0.2,y+0.1,z-0.2)].isSoil)|(MC_Block[getBlockID(x-0.2,y-1.6,z-0.2)].isSoil)|(MC_Block[getBlockID(x-0.2,y-0.75,z-0.2)].isSoil)|(MC_Block[getBlockID(x-0.2,y+0.1,z-0.2)].isSoil))
	{
		return true;
	}else{
		return false;
	}
}