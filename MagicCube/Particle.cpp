#include "Setting.h"
#include "Particle.h"
#include "Chunk.h"
#include "Block.h"
#include "Texture.h"
#include "Gobal.h"

particle Particle[1000];
int drawParticle(int i);
int ParticleAddNumber=0;

void Particles()
{
	if ((GameScrNum==1) & (!isPause))
	{
		glBindTexture(GL_TEXTURE_2D,texture);
		glBegin(GL_QUADS);
		for (int i=0;i<ParticleNumber;i++)
		{
			if (Particle[i].isLive)
			{
				drawParticle(i);
				if (!MC_Block[getBlockID(Particle[i].x,Particle[i].y+Particle[i].yMove,Particle[i].z)].isSoil)
				{
					Particle[i].y+=Particle[i].yMove;
					Particle[i].yMove-=0.01;
				}else{
					Particle[i].xMove=0;
					Particle[i].zMove=0;
				}
				if (!MC_Block[getBlockID(Particle[i].x+Particle[i].xMove,Particle[i].y,Particle[i].z)].isSoil)
				{
					Particle[i].x+=Particle[i].xMove;
					if (Particle[i].xMove>0)
					{
						Particle[i].xMove-=0.01;
					}else{
						Particle[i].xMove+=0.01;
					}
				}
				if (!MC_Block[getBlockID(Particle[i].x,Particle[i].y,Particle[i].z+Particle[i].zMove)].isSoil)
				{
					Particle[i].z+=Particle[i].zMove;
					if (Particle[i].zMove>0)
					{
						Particle[i].zMove-=0.01;
					}else{
						Particle[i].zMove+=0.01;
					}
				}
				Particle[i].health--;
				if (Particle[i].health==0)
				{
					Particle[i].isLive=false;
				}
			}
		}
		glEnd();
	}
}
int drawParticle(int i)
{
	if (Particle[i].hasColor)
	{
		glColor3f(0.6f,1.0f,0.4f);				// 设置当前色为黑
	}else{
		glColor3f(1.0f,1.0f,1.0f);				// 设置当前色为黑
	}
	//右前点
	glTexCoord2f(Particle[i].TextureX/(textureEach*16.0),((textureEach*16.0)-Particle[i].TextureZ)/(textureEach*16.0));
	glVertex3f(Particle[i].x,Particle[i].y+0.006,Particle[i].z);
	//左前点
	glTexCoord2f(Particle[i].TextureX/(textureEach*16.0),((textureEach*16.0)-Particle[i].TextureZ2)/(textureEach*16.0));
	glVertex3f(Particle[i].x,Particle[i].y+0.006,Particle[i].z+Particle[i].sizeZ);
	//左后点
	glTexCoord2f((Particle[i].TextureX2)/(textureEach*16.0),((textureEach*16.0)-Particle[i].TextureZ2)/(textureEach*16.0));
	glVertex3f(Particle[i].x+Particle[i].sizeX,Particle[i].y+0.006,Particle[i].z+Particle[i].sizeZ);
	//右后点
	glTexCoord2f((Particle[i].TextureX2)/(textureEach*16.0),((textureEach*16.0)-Particle[i].TextureZ)/(textureEach*16.0));
	glVertex3f(Particle[i].x+Particle[i].sizeX,Particle[i].y+0.006,Particle[i].z);
	glColor3f(1.0f,1.0f,1.0f);				// 设置当前色为黑
	return TRUE;
}

int AddParticle(float x,float y,float z,int type,int TextureID,bool hasColor)
{
	int TextureX;
	int TextureZ;
	TextureZ=TextureID/16*textureEach;
	TextureX=(TextureID-TextureID/16*16)*textureEach;
	Particle[ParticleAddNumber].x=x;
	Particle[ParticleAddNumber].y=y;
	Particle[ParticleAddNumber].z=z;
	Particle[ParticleAddNumber].TextureX=TextureX+rand()%(int)(textureEach/2);
	Particle[ParticleAddNumber].TextureZ=TextureZ+rand()%(int)(textureEach/2);
	Particle[ParticleAddNumber].TextureX2=TextureX+rand()%(int)(textureEach/2);
	Particle[ParticleAddNumber].TextureZ2=TextureZ+rand()%(int)(textureEach/2);
	Particle[ParticleAddNumber].sizeX=(Particle[ParticleAddNumber].TextureX2-Particle[ParticleAddNumber].TextureX)/textureEach/1.8;
	Particle[ParticleAddNumber].sizeZ=(Particle[ParticleAddNumber].TextureX2-Particle[ParticleAddNumber].TextureX)/textureEach/1.8;
	Particle[ParticleAddNumber].hasColor=hasColor;
	bool isBigThan0;
	if (rand()%100>50)
	{
		isBigThan0=true;
	}else{
		isBigThan0=false;
	}
	if (isBigThan0)
	{
		Particle[ParticleAddNumber].xMove=rand()%10/100.0;
	}else{
		Particle[ParticleAddNumber].xMove=-rand()%10/100.0;
	}
	if (type==1)
	{
		Particle[ParticleAddNumber].yMove=0.01;
	}else{
		Particle[ParticleAddNumber].yMove=-0.01;
	}
	if (rand()%100>50)
	{
		isBigThan0=true;
	}else{
		isBigThan0=false;
	}
	if (isBigThan0)
	{
		Particle[ParticleAddNumber].zMove=rand()%10/100.0;
	}else{
		Particle[ParticleAddNumber].zMove=-rand()%10/100.0;
	}

	Particle[ParticleAddNumber].health=50;
	Particle[ParticleAddNumber].isLive=true;
	ParticleAddNumber+=1;
	if (ParticleAddNumber>ParticleNumber)
	{
		ParticleAddNumber=0;
	}
	return TRUE;
}

int autoAddParticle(int x,int y,int z,int type,int BlockID)
{
	bool hasColor;
	if ((MC_Block[BlockID].isGrass) | (MC_Block[BlockID].isLeaf))
	{
		hasColor=true;
	}else{
		hasColor=false;
	}
	if (type==0)
	{
		AddParticle(x+0.4,y+0.5,z+0.4,type,MC_Block[BlockID].Texture[0],hasColor);
	}else if (type==1)
	{
		AddParticle(x+0.4,y+1.2,z+0.4,type,MC_Block[BlockID].Texture[0],hasColor);
	}
	return TRUE;
}