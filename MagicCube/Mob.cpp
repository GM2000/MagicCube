#include "Chunk.h"
#include "Block.h"
#include "Mob.h"
#include "Setting.h"
#include "Player.h"

mob Mob[10000];
int NowMobNumber=0;

int drawMob(int i)
{
	if (Mob[i].mobType==MOB_FALLING_ITEM)
	{
		int TextureID=MC_Block[Mob[i].mobTag[0]].Texture[0];
		int TextureZ=TextureID/16;
		int TextureX=TextureID-TextureZ*16;
		float x=Mob[i].x;
		float y=Mob[i].y;
		float z=Mob[i].z;

		glBegin(GL_QUADS);
		if ((MC_Block[Mob[i].mobTag[0]].isGrass) | (MC_Block[Mob[i].mobTag[0]].isLeaf))
		{
			glColor3f(0.6f,1.0f,0.4f);				// 设置当前色为黑
		}else{
			glColor3f(1.0f,1.0f,1.0f);				// 设置当前色为黑
		}
		//右前点
		glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
		glVertex3f(x,y+0.25,z);
		//左前点
		glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
		glVertex3f(x,y+0.25,z+0.25);
		//左后点
		glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
		glVertex3f(x+0.25,y+0.25,z+0.25);
		//右后点
		glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
		glVertex3f(x+0.25,y+0.25,z);

		TextureID=MC_Block[Mob[i].mobTag[0]].Texture[1];
		TextureZ=TextureID/16;
		TextureX=TextureID-TextureZ*16;

		if (!MC_Block[Mob[i].mobTag[0]].isLeaf)
		{
			glColor3f(1.0f,1.0f,1.0f);				// 设置当前色为黑
		}

		glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
		glVertex3f(x,y,z);
		//左前点
		glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
		glVertex3f(x,y,z+0.25);
		//左后点
		glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
		glVertex3f(x+0.25,y,z+0.25);
		//右后点
		glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
		glVertex3f(x+0.25,y,z);

		TextureID=MC_Block[Mob[i].mobTag[0]].Texture[2];
		TextureZ=TextureID/16;
		TextureX=TextureID-TextureZ*16;

		glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
		glVertex3f(x,y+0.25,z+0.25);
		//左前点
		glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
		glVertex3f(x,y,z+0.25);
		//左后点
		glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
		glVertex3f(x,y,z);
		//右后点
		glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
		glVertex3f(x,y+0.25,z);

		TextureID=MC_Block[Mob[i].mobTag[0]].Texture[3];
		TextureZ=TextureID/16;
		TextureX=TextureID-TextureZ*16;

		glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
		glVertex3f(x+0.25,y+0.25,z+0.25);
		//左前点
		glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
		glVertex3f(x+0.25,y,z+0.25);
		//左后点
		glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
		glVertex3f(x+0.25,y,z);
		//右后点
		glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
		glVertex3f(x+0.25,y+0.25,z);

		TextureID=MC_Block[Mob[i].mobTag[0]].Texture[4];
		TextureZ=TextureID/16;
		TextureX=TextureID-TextureZ*16;

		glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
		glVertex3f(x+0.25,y+0.25,z+0.25);
		//左前点
		glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
		glVertex3f(x+0.25,y,z+0.25);
		//左后点
		glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
		glVertex3f(x,y,z+0.25);
		//右后点
		glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
		glVertex3f(x,y+0.25,z+0.25);

		TextureID=MC_Block[Mob[i].mobTag[0]].Texture[5];
		TextureZ=TextureID/16;
		TextureX=TextureID-TextureZ*16;

		glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
		glVertex3f(x+0.25,y+0.25,z);
		//左前点
		glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
		glVertex3f(x+0.25,y,z);
		//左后点
		glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
		glVertex3f(x,y,z);
		//右后点
		glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
		glVertex3f(x,y+0.25,z);

		glColor3f(1.0f,1.0f,1.0f);				// 设置当前色为黑

		glEnd();
	}
	return TRUE;
}

void reSetMob()
{
	for (int i=0;i<MaxMobNumber;i++)
	{
		if (Mob[i].mobType==MOB_FALLING_ITEM)
		{
			if (!MC_Block[getBlockID(Mob[i].x,Mob[i].y-0.4,Mob[i].z)].isSoil)
			{
				Mob[i].y-=0.1;
			}else{
				if (Mob[i].yMove>0.07)
				{
					Mob[i].moveTag=true;
				}else if (Mob[i].yMove<-0.07){
					Mob[i].moveTag=false;
				}
				if (Mob[i].moveTag)
				{
					Mob[i].yMove-=0.003;
				}else{
					Mob[i].yMove+=0.003;
				}
			}
			Mob[i].y+=Mob[i].yMove;
			drawMob(i);
			Mob[i].y-=Mob[i].yMove;
		}
	}
}

int loadMob(int MobType,int tag,float x,float y,float z)
{
	if (NowMobNumber>MaxMobNumber)
	{
		NowMobNumber=0;
	}
	Mob[NowMobNumber].mobType=MobType;
	Mob[NowMobNumber].mobTag[0]=tag;
	Mob[NowMobNumber].x=x;
	Mob[NowMobNumber].y=y;
	Mob[NowMobNumber].z=z;
	NowMobNumber++;
	return TRUE;
}

