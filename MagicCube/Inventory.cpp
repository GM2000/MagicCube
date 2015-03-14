#include "Player.h"

bool addInventory(int BlockID,int Number)
{
	for (int i=0;i<9;i++)
	{
		if (player.PlayerBag[i]==0)
		{
			player.PlayerBag[i]=BlockID;
			return 1;
		}
	}
	return 0;
}