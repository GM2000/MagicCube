#include "Chunk.h"
#include "Texture.h"
#include "Player.h"
#include "Block.h"
#include "Particle.h"

int BreakPrecent;

//frount的注释：0:上,1:下,2:左,3:右,4:前,5:后
int GetTexture(int BlockID,int frount)
{
	return MC_Block[BlockID].Texture[frount];
}


int DrawMap(int ChunkListX,int ChunkListZ)
{
	if (player.ChooseBlockChunkID==-1)
	{
		player.BreakTime=0;
	}
	if (player.ChooseBlockChunkID==ChunkList[ChunkListX][ChunkListZ])
	{
		int ChooseBlockChunkID=player.ChooseBlockChunkID;
		int ChooseBlockX=player.ChooseBlockX;
		int ChooseBlockY=player.ChooseBlockY;
		int ChooseBlockZ=player.ChooseBlockZ;
		if (!(ChooseBlockChunkID==-1))
		{
			glEnable(GL_ALPHA_TEST);
			int MoveChooseBlockX=(ChunkListX-7)*16+player.ChunkX*16;
			int MoveChooseBlockZ=(ChunkListZ-7)*16+player.ChunkZ*16;
			glLineWidth(2.0f);
			glBegin(GL_LINES);
			WriteDrawPointer(ChooseBlockX+MoveChooseBlockX,ChooseBlockY,ChooseBlockZ+MoveChooseBlockZ,0,-1,1,1,1,0);
			glEnd();
			if (MC_Block[Chunk[ChooseBlockChunkID].BlockID[ChooseBlockX][ChooseBlockY][ChooseBlockZ]].isSoil)
			{
				if (player.BreakTime>0)
				{
					autoAddParticle(ChooseBlockX+MoveChooseBlockX,ChooseBlockY,ChooseBlockZ+MoveChooseBlockZ,1,Chunk[ChooseBlockChunkID].BlockID[ChooseBlockX][ChooseBlockY][ChooseBlockZ]);
					BreakPrecent=player.BreakTime/player.BreakTimeNeed*9.5;
					glBegin(GL_QUADS);
					WriteDrawPointer(ChooseBlockX+MoveChooseBlockX,ChooseBlockY,ChooseBlockZ+MoveChooseBlockZ,0,-2,1,1,1,0);
					glEnd();
				}
			}
		}
	}
	if (!Chunk[ChunkList[ChunkListX][ChunkListZ]].isCreateList)
	{
 		if (!hasCreatList)
		{
			if (!ChunkInfo[ChunkList[ChunkListX][ChunkListZ]].NeedBuild)
			{
				hasCreatList=true;
				Chunk[ChunkList[ChunkListX][ChunkListZ]].mustCreateListNow=false;
				Chunk[ChunkList[ChunkListX][ChunkListZ]].isCreateList=true;
				glNewList((ChunkList[ChunkListX][ChunkListZ]+1)*2,GL_COMPILE_AND_EXECUTE);
				glEnable(GL_ALPHA_TEST);
				glEnable(GL_BLEND);
				glBegin(GL_QUADS);
				int MoveX=(ChunkListX-7)*16+player.ChunkX*16;
				int MoveZ=(ChunkListZ-7)*16+player.ChunkZ*16;
				for (int cx=0;cx<16;cx++)
				{
					for (int cz=0;cz<16;cz++)
					{
						for (int cy=0;cy<256;cy++)
						{
							if ((!MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].halfHyaline) & (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].canSee))
							{
								if (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].isPlant)
								{
									WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,0,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],0),1,1,1,1);
								}else{
									if (cy+1<256)
									{
										if ((MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy+1][cz]].hyaline))
										{
											if ((MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].isGrass) | (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].isLeaf))
											{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,0,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],0),0.6,1,0.4,0);
											}else{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,0,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],0),1,1,1,0);
											}						
										}
									}
									if (cy-1>-1)
									{
										if ((MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy-1][cz]].hyaline))
										{
											if (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].isLeaf)
											{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,1,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],1),0.6,1,0.4,0);
											}else{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,1,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],1),1,1,1,0);
											}
										}
									}
									if (cx-1>-1)
									{
										if ((MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx-1][cy][cz]].hyaline))
										{
											if (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].isLeaf)
											{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,2,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],2),0.6,1,0.4,0);
											}else{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,2,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],2),1,1,1,0);
											}
										}
									}
									if (cx+1<16)
									{
										if ((MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx+1][cy][cz]].hyaline))
										{
											if (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].isLeaf)
											{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,3,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],3),0.6,1,0.4,0);
											}else{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,3,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],3),1,1,1,0);
											}
										}
									}
									if (cz+1<16)
									{
										if ((MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz+1]].hyaline))
										{
											if (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].isLeaf)
											{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,4,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],4),0.6,1,0.4,0);
											}else{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,4,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],4),1,1,1,0);
											}
										}
									}
									if (cz-1>-1)
									{
										if ((MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz-1]].hyaline))
										{
											if (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].isLeaf)
											{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,5,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],5),0.6,1,0.4,0);
											}else{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,5,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],5),1,1,1,0);
											}
										}
									}
									if (cx+1>15)
									{
										if (MC_Block[Chunk[ChunkList[ChunkListX+1][ChunkListZ]].BlockID[0][cy][cz]].hyaline)
										{
											if (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].isLeaf)
											{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,3,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],3),0.6,1,0.4,0);
											}else{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,3,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],3),1,1,1,0);
											}
										}
									}
									if (cx-1<0)
									{
										if (MC_Block[Chunk[ChunkList[ChunkListX-1][ChunkListZ]].BlockID[15][cy][cz]].hyaline)
										{
											if (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].isLeaf)
											{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,2,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],2),0.6,1,0.4,0);
											}else{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,2,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],2),1,1,1,0);
											}
										}
									}
									if (cz+1>15)
									{
										if (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ+1]].BlockID[cx][cy][0]].hyaline)
										{
											if (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].isLeaf)
											{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,4,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],4),0.6,1,0.4,0);
											}else{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,4,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],4),1,1,1,0);
											}
										}
									}
									if (cz-1<0)
									{
										if (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ-1]].BlockID[cx][cy][15]].hyaline)
										{
											if (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].isLeaf)
											{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,5,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],5),0.6,1,0.4,0);
											}else{
												WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,5,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],5),1,1,1,0);
											}
										}
									}
									if (cy==255)
									{
										if (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].isLeaf)
										{
											WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,0,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][255][cz],0),0.6,1,0.4,0);
										}else{
											WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,0,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][255][cz],0),1,1,1,0);
										}
									}
									if (cy==0)
									{
										if (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].isLeaf)
										{
											WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,1,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],1),0.6,1,0.4,0);
										}else{
											WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,1,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],1),1,1,1,0);
										}
									}
								}
							}
						}
					}
				}
				glEnd();
				glEndList();
				glNewList((ChunkList[ChunkListX][ChunkListZ]+1)*2+1,GL_COMPILE);
				glDepthMask(GL_FALSE);
				glDisable(GL_ALPHA_TEST);
				glBegin(GL_QUADS);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				for (int cx=0;cx<16;cx++)
				{
					for (int cz=0;cz<16;cz++)
					{
						for (int cy=0;cy<256;cy++)
						{
							if ((MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].halfHyaline) & (MC_Block[Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz]].canSee))
							{
								if (cy+1<256)
								{
									if (Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy+1][cz]==0)
									{
										WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,0,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],0),1,1,1,2);						
									}
								}
								if (cy-1>-1)
								{
									if (Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy-1][cz]==0)
									{
										WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,1,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],1),1,1,1,2);
									}
								}
								if (cx-1>-1)
								{
									if (Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx-1][cy][cz]==0)
									{
										WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,2,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],2),1,1,1,2);
									}
								}
								if (cx+1<16)
								{
									if (Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx+1][cy][cz]==0)
									{
										WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,3,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],3),1,1,1,2);
									}
								}
								if (cz+1<16)
								{
									if (Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz+1]==0)
									{
										WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,4,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],4),1,1,1,2);
									}
								}
								if (cz-1>-1)
								{
									if (Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz-1]==0)
									{
										WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,5,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],5),1,1,1,2);
									}
								}
								if (cx+1>15)
								{
									if (Chunk[ChunkList[ChunkListX+1][ChunkListZ]].BlockID[0][cy][cz]==0)
									{
										WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,3,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],3),1,1,1,2);
									}
								}
								if (cx-1<0)
								{
									if (Chunk[ChunkList[ChunkListX-1][ChunkListZ]].BlockID[15][cy][cz]==0)
									{
										WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,2,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],2),1,1,1,2);
									}
								}
								if (cz+1>15)
								{
									if (Chunk[ChunkList[ChunkListX][ChunkListZ+1]].BlockID[cx][cy][0]==0)
									{
										WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,4,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],4),1,1,1,2);
									}
								}
								if (cz-1<0)
								{
									if (Chunk[ChunkList[ChunkListX][ChunkListZ-1]].BlockID[cx][cy][15]==0)
									{
										WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,5,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],5),1,1,1,2);
									}
								}
								if (cy+1>255)
								{
									WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,0,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][255][cz],0),1,1,1,2);
								}
								if (cy-1<0)
								{
									WriteDrawPointer(cx+MoveX,cy,cz+MoveZ,1,GetTexture(Chunk[ChunkList[ChunkListX][ChunkListZ]].BlockID[cx][cy][cz],1),1,1,1,2);
								}
							}
						}
					}
				}
				glEnd();
				glDepthMask(GL_TRUE);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				glEndList();
				glDisable(GL_BLEND);
			}
		}
	}
	return TRUE;
}

//frount的注释：0:上,1:下,2:左,3:右,4:前,5:后
int WriteDrawPointer(int x,int y,int z,int frount,int TextureID,float ColorR,float ColorG,float ColorB,int Mode)
{
	ColorR=1-ColorR;
	ColorG=1-ColorG;
	ColorB=1-ColorB;
	int TextureX;
	int TextureZ;
	TextureZ=TextureID/16;
	TextureX=TextureID-TextureZ*16;
	if ((TextureID>-1))
	{
		if (Mode==0)
		{
			if (frount==0)
			{
			
				glColor3f(1.0f-ColorR,1.0f-ColorG,1.0f-ColorB);				// 设置当前色为黑
				//右前点
				glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
				glVertex3f(x,y+1,z);
				//左前点
				glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
				glVertex3f(x,y+1,z+1);
				//左后点
				glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
				glVertex3f(x+1,y+1,z+1);
				//右后点
				glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
				glVertex3f(x+1,y+1,z);
				glColor3f(1.0f,1.0f,1.0f);				// 设置当前色为黑

			}else if (frount==1){

				//右前点
				glColor3f(0.86f-ColorR,0.86f-ColorG,0.86f-ColorB);				// 设置当前色为黑
				glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
				glVertex3f(x,y,z);
				//左前点
				glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
				glVertex3f(x,y,z+1);
				//左后点
				glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
				glVertex3f(x+1,y,z+1);
				//右后点
				glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
				glVertex3f(x+1,y,z);
				glColor3f(1.0f,1.0f,1.0f);				// 设置当前色为黑

			}else if (frount==2){
				//右前点
				glColor3f(0.86f-ColorR,0.86f-ColorG,0.86f-ColorB);				// 设置当前色为黑
				glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
				glVertex3f(x,y+1,z+1);
				//左前点
				glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
				glVertex3f(x,y,z+1);
				//左后点
				glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
				glVertex3f(x,y,z);
				//右后点
				glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
				glVertex3f(x,y+1,z);
				glColor3f(1.0f,1.0f,1.0f);				// 设置当前色为黑

			}else if (frount==3){
				//右前点
				glColor3f(0.86f-ColorR,0.86f-ColorG,0.86f-ColorB);				// 设置当前色为黑
				glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
				glVertex3f(x+1,y+1,z+1);
				//左前点
				glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
				glVertex3f(x+1,y,z+1);
				//左后点
				glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
				glVertex3f(x+1,y,z);
				//右后点
				glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
				glVertex3f(x+1,y+1,z);
				glColor3f(1.0f,1.0f,1.0f);				// 设置当前色为黑

			}else if (frount==4){
				//右前点
				glColor3f(1.0f-ColorR,1.0f-ColorG,1.0f-ColorB);				// 设置当前色为黑
				glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
				glVertex3f(x+1,y+1,z+1);
				//左前点
				glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
				glVertex3f(x+1,y,z+1);
				//左后点
				glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
				glVertex3f(x,y,z+1);
				//右后点
				glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
				glVertex3f(x,y+1,z+1);
				glColor3f(1.0f,1.0f,1.0f);				// 设置当前色为黑

			}else if (frount==5){
				//右前点
				glColor3f(1.0f-ColorR,1.0f-ColorG,1.0f-ColorB);				// 设置当前色为黑
				glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
				glVertex3f(x+1,y+1,z);
				//左前点
				glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
				glVertex3f(x+1,y,z);
				//左后点
				glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
				glVertex3f(x,y,z);
				//右后点
				glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
				glVertex3f(x,y+1,z);
				glColor3f(1.0f,1.0f,1.0f);				// 设置当前色为黑

			}
		}else if(Mode==1){
		//右前点
			glColor3f(1.0f-ColorR,1.0f-ColorG,1.0f-ColorB);				// 设置当前色为黑
			glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
			glVertex3f(x+1,y+1,z);
			//左前点
			glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
			glVertex3f(x+1,y,z);
			//左后点
			glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
			glVertex3f(x,y,z+1);
			//右后点
			glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
			glVertex3f(x,y+1,z+1);
			glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
			glVertex3f(x+1,y+1,z+1);
			//左前点
			glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
			glVertex3f(x+1,y,z+1);
			//左后点
			glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
			glVertex3f(x,y,z);
			//右后点
			glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
			glVertex3f(x,y+1,z);
			glColor3f(1.0f,1.0f,1.0f);				// 设置当前色为黑
		}else if(Mode==2){

			if (frount==0)
			{
			
				glColor4f(1.0f-ColorR,1.0f-ColorG,1.0f-ColorB,1.0f);				// 设置当前色为黑
				//右前点
				glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
				glVertex3f(x,y+1,z);
				//左前点
				glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
				glVertex3f(x,y+1,z+1);
				//左后点
				glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
				glVertex3f(x+1,y+1,z+1);
				//右后点
				glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
				glVertex3f(x+1,y+1,z);
				glColor4f(1.0f,1.0f,1.0f,1.0f);				// 设置当前色为黑

			}else if (frount==1){

				//右前点
				glColor4f(1.0f-ColorR,1.0f-ColorG,1.0f-ColorB,1.0f);				// 设置当前色为黑
				glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
				glVertex3f(x,y,z);
				//左前点
				glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
				glVertex3f(x,y,z+1);
				//左后点
				glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
				glVertex3f(x+1,y,z+1);
				//右后点
				glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
				glVertex3f(x+1,y,z);
				glColor4f(1.0f,1.0f,1.0f,1.0f);				// 设置当前色为黑

			}else if (frount==2){
				//右前点
				glColor4f(1.0f-ColorR,1.0f-ColorG,1.0f-ColorB,1.0f);				// 设置当前色为黑
				glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
				glVertex3f(x,y+1,z+1);
				//左前点
				glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
				glVertex3f(x,y,z+1);
				//左后点
				glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
				glVertex3f(x,y,z);
				//右后点
				glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
				glVertex3f(x,y+1,z);
				glColor4f(1.0f,1.0f,1.0f,1.0f);				// 设置当前色为黑

			}else if (frount==3){
				//右前点
				glColor4f(1.0f-ColorR,1.0f-ColorG,1.0f-ColorB,1.0f);				// 设置当前色为黑
				glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
				glVertex3f(x+1,y+1,z+1);
				//左前点
				glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
				glVertex3f(x+1,y,z+1);
				//左后点
				glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
				glVertex3f(x+1,y,z);
				//右后点
				glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
				glVertex3f(x+1,y+1,z);
				glColor4f(1.0f,1.0f,1.0f,1.0f);				// 设置当前色为黑

			}else if (frount==4){
				//右前点
				glColor4f(1.0f-ColorR,1.0f-ColorG,1.0f-ColorB,1.0f);				// 设置当前色为黑
				glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
				glVertex3f(x+1,y+1,z+1);
				//左前点
				glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
				glVertex3f(x+1,y,z+1);
				//左后点
				glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
				glVertex3f(x,y,z+1);
				//右后点
				glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
				glVertex3f(x,y+1,z+1);
				glColor4f(1.0f,1.0f,1.0f,1.0f);				// 设置当前色为黑

			}else if (frount==5){
				//右前点
				glColor4f(1.0f-ColorR,1.0f-ColorG,1.0f-ColorB,1.0f);				// 设置当前色为黑
				glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
				glVertex3f(x+1,y+1,z);
				//左前点
				glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
				glVertex3f(x+1,y,z);
				//左后点
				glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
				glVertex3f(x,y,z);
				//右后点
				glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
				glVertex3f(x,y+1,z);
				glColor4f(1.0f,1.0f,1.0f,1.0f);				// 设置当前色为黑
			}
		}
	}
	else if (TextureID==-1)
	{
		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
		//右前点
		glVertex3f(x-0.005,y+1.005,z-0.005);
		//左前点
		glVertex3f(x-0.005,y+1.005,z+1.005);
		//左后点
		glVertex3f(x+1.005,y+1.005,z+1.005);
		//右后点
		glVertex3f(x+1.005,y+1.005,z-0.005);
		//下
		//右前点
		glVertex3f(x-0.005,y-0.005,z-0.005);
		//左前点
		glVertex3f(x-0.005,y-0.005,z+1.005);
		//左后点
		glVertex3f(x+1.005,y-0.005,z+1.005);
		//右后点
		glVertex3f(x+1.005,y-0.005,z-0.005);
		//左
		glVertex3f(x-0.005,y+1.005,z+1.005);
		//左前点
		glVertex3f(x-0.005,y-0.005,z+1.005);
		//左后点
		glVertex3f(x-0.005,y-0.005,z-0.005);
		//右后点
		glVertex3f(x-0.005,y+1.005,z-0.005);
		//右
		glVertex3f(x+1.005,y+1.005,z+1.005);
		//左前点
		glVertex3f(x+1.005,y-0.005,z+1.005);
		//左后点
		glVertex3f(x+1.005,y-0.005,z-0.005);
		//右后点
		glVertex3f(x+1.005,y+1.005,z-0.005);
		//前
		glVertex3f(x+1.005,y+1.005,z+1.005);
		//左前点
		glVertex3f(x-0.005,y+1.005,z+1.005);
		//右后点
		glVertex3f(x+1.005,y-0.005,z+1.005);
		//左后点
		glVertex3f(x-0.005,y-0.005,z+1.005);
		//后
		glVertex3f(x+1.005,y+1.005,z-0.005);
		//左前点
		glVertex3f(x-0.005,y+1.005,z-0.005);
		//右后点
		glVertex3f(x+1.005,y-0.005,z-0.005);
		//左后点
		glVertex3f(x-0.005,y-0.005,z-0.005);
		glColor4f(1.0f,1.0f,1.0f,1.0f);				// 设置当前色为黑
	}else if (TextureID==-2)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		TextureZ=15;
		if (BreakPrecent>0)
		{
			TextureX=BreakPrecent;
		}
		if (TextureX>11)
		{
			TextureX=11;
		}
		if (TextureX<0)
		{
			TextureX=0;
		}
		//右前点
		glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);glVertex3f(x-0.005,y+1.005,z-0.005);
		//左前点
		glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);glVertex3f(x-0.005,y+1.005,z+1.005);
		//左后点
		glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);glVertex3f(x+1.005,y+1.005,z+1.005);
		//右后点
		glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);glVertex3f(x+1.005,y+1.005,z-0.005);
		//下

		//右前点
		glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);glVertex3f(x-0.005,y-0.005,z-0.005);
		//左前点
		glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);glVertex3f(x-0.005,y-0.005,z+1.005);
		//左后点
		glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);glVertex3f(x+1.005,y-0.005,z+1.005);
		//右后点
		glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);glVertex3f(x+1.005,y-0.005,z-0.005);
		//左

		glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);glVertex3f(x-0.005,y+1.005,z+1.005);
		//左前点
		glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);glVertex3f(x-0.005,y-0.005,z+1.005);
		//左后点
		glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);glVertex3f(x-0.005,y-0.005,z-0.005);
		//右后点
		glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);glVertex3f(x-0.005,y+1.005,z-0.005);
		//右

		glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);glVertex3f(x+1.005,y+1.005,z+1.005);
		//左前点
		glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);glVertex3f(x+1.005,y-0.005,z+1.005);
		//左后点
		glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);glVertex3f(x+1.005,y-0.005,z-0.005);
		//右后点
		glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);glVertex3f(x+1.005,y+1.005,z-0.005);

		//前
		glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);glVertex3f(x+1.005,y+1.005,z+1.005);
		//左前点
		glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);glVertex3f(x+1.005,y-0.005,z+1.005);
		//右后点
		glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);glVertex3f(x-0.005,y-0.005,z+1.005);
		//左后点
		glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);glVertex3f(x-0.005,y+1.005,z+1.005);
		//后

		glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);glVertex3f(x+1.005,y+1.005,z-0.005);
		//左前点
		glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);glVertex3f(x+1.005,y-0.005,z-0.005);
		//右后点
		glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);glVertex3f(x-0.005,y-0.005,z-0.005);
		//左后点
		glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);glVertex3f(x-0.005,y+1.005,z-0.005);
	}
	return true;
}