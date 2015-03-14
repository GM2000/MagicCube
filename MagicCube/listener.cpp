#include <time.h>
#include "player.h"
#include "MagicCube.h"
#include "OpenglWindows.h"
#include "Setting.h"
#include "Chunk.h"
#include "Block.h"
#include "Gobal.h"
#include "Mob.h"

const double PI = 3.141592653589793238462;

bool shakingDeg;//TRUE 向左;FALSE 向右
bool shakingFinish;
bool LBottom;
bool RBottom;
extern bool needShowCursor;

Player player;

int mouse()
{
	int PXM;
	int PYM;
	POINT pt;					//鼠标
	int PX;
	int PY;
	GetCursorPos(&pt);                  //获取鼠标在屏幕中的坐标
	CRect rc;
	GetWindowRect(hWnd,&rc);
	PX=(rc.right-rc.left)/2+rc.left;
	PY=(rc.bottom-rc.top)/2+rc.top;
	if (GameScrNum==1)
	{
		if (!isPause)
		{
			PXM=pt.x-PX;
			if (PXM<0)
			{
				PXM=-PXM;
				if (player.around<0)
				{
					player.around=360;
				}
				player.around-=asin(PXM*0.0001)*mousespeed*15;
			}else{
				if (player.around>360)
				{
					player.around=0;
				}
				player.around+=asin(PXM*0.0001)*mousespeed*15;
			}
			PYM=pt.y-PY;
			if (PYM<0)
			{
				PYM=-PYM;
				player.upanddown-=asin(PYM*0.0001)*mousespeed*15;
			}else{
				player.upanddown+=asin(PYM*0.0001)*mousespeed*15;
			}
			if (player.upanddown>90)
			{
				player.upanddown=90;
			}			
			if (player.upanddown<-90)
			{
				player.upanddown=-90;
			}
			if ((!PXM==0)|(!PYM==0))
			{
				SetCursorPos(PX,PY);
			}
		}else{
			///////////////////////////////////////////////////////////////////////
			if ( ( pt.x > (PX-(rc.right-rc.left)*0.29)) & ( pt.x < (PX+(rc.right-rc.left)*0.29)) & ( pt.y > (PY+(rc.bottom-rc.top)*0.14)) & ( pt.y < (PY+(rc.bottom-rc.top)*0.23)))
			{
				exitGameBottomInScr1=true;
			}else{
				exitGameBottomInScr1=false;
			}
			if ( ( pt.x > (PX-(rc.right-rc.left)*0.29)) & ( pt.x < (PX+(rc.right-rc.left)*0.29)) & ( pt.y < (PY-(rc.bottom-rc.top)*0.03)) & ( pt.y > (PY-(rc.bottom-rc.top)*0.12)))
			{
				backGameBottomInScr1=true;
			}else{
				backGameBottomInScr1=false;
			}
			///////////////////////////////////////////
			/*
			if ((pt.x>WindowsWidth/4.8+rc.left) & (pt.x<-WindowsWidth/4.8+rc.right) & (pt.y>WindowsHeight/1.165+rc.top) & (pt.y<WindowsHeight/1.044+rc.top))
			{
			exitGameBottomInScr1=true;
			}else{
			exitGameBottomInScr1=false;
			}
			*/
		}
	}else if(GameScrNum==0)
	{
		if ( ( pt.x > (PX-(rc.right-rc.left)*0.29)) & ( pt.x < (PX+(rc.right-rc.left)*0.29)) & ( pt.y > (PY+(rc.bottom-rc.top)*0.015)) & ( pt.y < (PY+(rc.bottom-rc.top)*0.11)))
		{
			startGameBottomInScr0=true;
		}else{
			startGameBottomInScr0=false;
		}
		if ( ( pt.x > (PX-(rc.right-rc.left)*0.29)) & ( pt.x < (PX-(rc.right-rc.left)*0.02)) & ( pt.y > (PY+(rc.bottom-rc.top)*0.14)) & ( pt.y < (PY+(rc.bottom-rc.top)*0.23)))
		{
			settingBottomInScr0=true;
		}else{
			settingBottomInScr0=false;
		}
		if ( ( pt.x < (PX+(rc.right-rc.left)*0.29)) & ( pt.x > (PX+(rc.right-rc.left)*0.02)) & ( pt.y > (PY+(rc.bottom-rc.top)*0.14)) & ( pt.y < (PY+(rc.bottom-rc.top)*0.23)))
		{
			exitGameBottomInScr0=true;
		}else{
			exitGameBottomInScr0=false;
		}
	}
	return 1;
}

void KeyBoardListener()
{
	float KeyBoardTick=GetTickCount();   
	while (!done)
	{
		if ((GetTickCount()-KeyBoardTick>13) & FirstLoafFinish & (!isPause))
		{
			bool isKeyDown=false;
			float needAddTime=(GetTickCount()-KeyBoardTick)/13;
			MouseTimer++;
			KeyBoardTick=GetTickCount();

			float xMove;
			float yMove;
			float zMove;

			//按键检测在此！
			if (keys[49])//1
			{
				player.choiceNumber=0;
			}
			if (keys[50])//2
			{
				player.choiceNumber=1;
			}
			if (keys[51])//3
			{
				player.choiceNumber=2;
			}
			if (keys[52])//4
			{
				player.choiceNumber=3;
			}
			if (keys[53])//5
			{
				player.choiceNumber=4;
			}
			if (keys[54])//6
			{
				player.choiceNumber=5;
			}
			if (keys[55])//7
			{
				player.choiceNumber=6;
			}
			if (keys[56])//8
			{
				player.choiceNumber=7;
			}
			if (keys[57])//9
			{
				player.choiceNumber=8;
			}

			if (keys[87])//W
			{
				isKeyDown=true;
				if (player.inWater)
				{
					player.speed=0.05;
					player.y+=player.speed*needAddTime/5;
					if (isTouch())
					{
						player.y-=player.speed*needAddTime/5;
					}
				}else{
					player.speed=0.1;
				}

				xMove=sin(player.around*(PI/180))*(player.speed*needAddTime);
				zMove=-cos(player.around*(PI/180))*(player.speed*needAddTime);

				player.x+=xMove;

				if (isTouch())
				{
					player.x-=xMove;
				}
				player.z+=zMove;
				if (isTouch())
				{
					player.z-=zMove;
				}
			}
			if (keys[83])//S
			{
				isKeyDown=true;
				if (player.inWater)
				{
					player.speed=0.05;
					player.y+=player.speed*needAddTime/5;
					if (isTouch())
					{
						player.y-=player.speed*needAddTime/5;
					}
				}else{
					player.speed=0.1;
				}

				xMove=-sin(player.around*(PI/180))*(player.speed*needAddTime);
				zMove=cos(player.around*(PI/180))*(player.speed*needAddTime);

				player.x+=xMove;

				if (isTouch())
				{
					player.x-=xMove;
				}
				player.z+=zMove;
				if (isTouch())
				{
					player.z-=zMove;
				}
			}
			if (keys[65])//A
			{
				isKeyDown=true;
				if (player.inWater)
				{
					player.speed=0.05;
					player.y+=player.speed*needAddTime/5;
					if (isTouch())
					{
						player.y-=player.speed*needAddTime/5;
					}
				}else{
					player.speed=0.1;
				}

				xMove=-cos(player.around*(PI/180))*(player.speed*needAddTime);
				zMove=-sin(player.around*(PI/180))*(player.speed*needAddTime);

				player.x+=xMove;

				if (isTouch())
				{
					player.x-=xMove;
				}
				player.z+=zMove;
				if (isTouch())
				{
					player.z-=zMove;
				}
			}
			if (keys[68])//D
			{
				isKeyDown=true;
				if (player.inWater)
				{
					player.speed=0.05;
					player.y+=player.speed*needAddTime/5;
					if (isTouch())
					{
						player.y-=player.speed*needAddTime/5;
					}
				}else{
					player.speed=0.1;
				}

				xMove=-cos((player.around+180)*(PI/180))*(player.speed*needAddTime);
				zMove=-sin((player.around+180)*(PI/180))*(player.speed*needAddTime);

				player.x+=xMove;

				if (isTouch())
				{
					player.x-=xMove;
				}
				player.z+=zMove;
				if (isTouch())
				{
					player.z-=zMove;
				}
			}
			if (player.fly)
			{
				if (keys[16])//shift
				{
					yMove=-player.speed*needAddTime;
					player.y+=yMove;
					if (isTouch())
					{
						player.y-=yMove;

					}
				}
				if (keys[32])//space
				{
					yMove=player.speed*needAddTime;
					player.y+=yMove;
					if (isTouch())
					{
						player.y-=yMove;
					}
				}
			}else{
 				if ((keys[32]) & (!player.isJumping) & (player.onGround))//space
				{
					if (player.inWater)
					{
						player.y+=0.03*needAddTime/5;
					}
					else if ((!MC_Block[getBlockID(player.x+0.2,player.y+0.1,player.z+0.2)].isSoil) & (!MC_Block[getBlockID(player.x-0.2,player.y+0.1,player.z-0.2)].isSoil) & (!MC_Block[getBlockID(player.x+0.2,player.y+0.1,player.z-0.2)].isSoil) & (!MC_Block[getBlockID(player.x-0.2,player.y+0.1,player.z+0.2)].isSoil))
					{
						player.isJumping=true;
						player.onGround=false;
						player.jumpSpeed=0.1;
					}
				}
				if ((!player.inWater) & (player.isJumping))
				{
					player.jumpSpeed-=0.006;
					player.y+=player.jumpSpeed*1.6;
					if ((MC_Block[getBlockID(player.x+0.2,player.y+0.1,player.z+0.2)].isSoil)|(MC_Block[getBlockID(player.x-0.2,player.y+0.1,player.z-0.2)].isSoil)|(MC_Block[getBlockID(player.x+0.2,player.y+0.1,player.z-0.2)].isSoil)|(MC_Block[getBlockID(player.x-0.2,player.y+0.1,player.z+0.2)].isSoil)|(MC_Block[getBlockID(player.x+0.2,player.y-1.6,player.z+0.2)].isSoil)|(MC_Block[getBlockID(player.x-0.2,player.y-1.6,player.z-0.2)].isSoil)|(MC_Block[getBlockID(player.x+0.2,player.y-1.6,player.z-0.2)].isSoil)|(MC_Block[getBlockID(player.x-0.2,player.y-1.6,player.z+0.2)].isSoil))
					{
						player.y-=player.jumpSpeed*1.6;
						player.isJumping=false;
					}
				}else if ((player.inWater) & (!isKeyDown)){
					player.y-=0.02;
					player.onGround=false;
					if ((MC_Block[getBlockID(player.x-0.2,player.y-1.6,player.z-0.2)].isSoil)|(MC_Block[getBlockID(player.x-0.2,player.y-1.6,player.z+0.2)].isSoil)|(MC_Block[getBlockID(player.x+0.2,player.y-1.6,player.z-0.2)].isSoil)|(MC_Block[getBlockID(player.x+0.2,player.y-1.6,player.z+0.2)].isSoil))
					{
						player.y+=0.02;
						player.onGround=true;
					}
				}else if (!player.inWater){
					player.dropSpeed+=player.g*1.02;
					player.y-=player.dropSpeed;
					player.onGround=false;
					if ((MC_Block[getBlockID(player.x-0.2,player.y-1.6,player.z-0.2)].isSoil)|(MC_Block[getBlockID(player.x-0.2,player.y-1.6,player.z+0.2)].isSoil)|(MC_Block[getBlockID(player.x+0.2,player.y-1.6,player.z-0.2)].isSoil)|(MC_Block[getBlockID(player.x+0.2,player.y-1.6,player.z+0.2)].isSoil))
					{
						player.y+=player.dropSpeed;
						player.dropSpeed=0;
						player.onGround=true;
					}
				}
			}
			if ((shaking) & (!player.fly) & (!player.inWater))
			{
				if((keys[87])|(keys[83])|(keys[65])|(keys[68])|(!shakingFinish))
				{
					if((keys[87])|(keys[83])|(keys[65])|(keys[68])|(!shakingFinish))
					{
						if (shakingDeg)
						{
							if ((shakingDegX>-0.0001) & (shakingDegX<0.0001))
							{
								shakingFinish=true;
							}else{
								shakingFinish=false;
							}
							shakingDegX+=0.005;
							shakingDegY=50*shakingDegX*shakingDegX;
							if (shakingDegX>0.05)
							{
								shakingDeg=false;
								shakingDegX=0.05;
							}
						}else
						{
							if ((shakingDegX>-0.00001) & (shakingDegX<0.00001))
							{
								shakingFinish=true;
							}else{
								shakingFinish=false;
							}
							shakingDegX-=0.005;
							shakingDegY=50*shakingDegX*shakingDegX;
							if (shakingDegX<-0.05)
							{
								shakingDeg=true;
								shakingDegX=-0.05;
							}
						}
					}
				}else if(shakingFinish)
				{
					shakingDegX=0;
					shakingDegY=0;
				}
			}
			resetPlayerChunk();
		}
	}
}

void GobalListener()
{
	float lastTime = GetTickCount()*0.001f;;
	while (!done)
	{
		mouse();
		if (GameScrNum==1)
		{
			if ((!isPause) & (FirstLoafFinish))
			{
				float nowTime = GetTickCount()*0.001f;
				if ((LBottom) & (nowTime-lastTime>0.1))
				{
					player.BreakTime+=nowTime-lastTime;
					lastTime = GetTickCount()*0.001f;
				}
				if (!LBottom)
				{
					lastTime = GetTickCount()*0.001f;
				}
				bool hasGetBlock=false;
				for (float getLong=0;getLong<7;getLong+=0.01)
				{
					if ((getBlockID(player.x+getLong*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180)),player.y-getLong*sin(player.upanddown*(PI/180)),player.z-getLong*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180)))!=0) & (!MC_Block[getBlockID(player.x+getLong*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180)),player.y-getLong*sin(player.upanddown*(PI/180)),player.z-getLong*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180)))].isLiquid))
					{
						int ChooseBlockX=player.x+getLong*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180));
						int ChooseBlockY=player.y-getLong*sin(player.upanddown*(PI/180));
						int ChooseBlockZ=player.z-getLong*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180));
						int BehindBlockX=player.x+(getLong-0.01)*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180));
						int BehindBlockY=player.y-(getLong-0.01)*sin(player.upanddown*(PI/180));
						int BehindBlockZ=player.z-(getLong-0.01)*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180));
						if (ChooseBlockY<BehindBlockY)
						{
							player.ChooseBlockFrount=0;
						}
						if (ChooseBlockY>BehindBlockY)
						{
							player.ChooseBlockFrount=1;
						}
						if (ChooseBlockX>BehindBlockX)
						{
							player.ChooseBlockFrount=2;
						}
						if (ChooseBlockX<BehindBlockX)
						{
							player.ChooseBlockFrount=3;
						}
						if (ChooseBlockZ>BehindBlockZ)
						{
							player.ChooseBlockFrount=4;
						}
						if (ChooseBlockZ<BehindBlockZ)
						{
							player.ChooseBlockFrount=5;
						}
						setBlockID(player.x+getLong*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180)),player.y-getLong*sin(player.upanddown*(PI/180)),player.z-getLong*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180)),-1);
						hasGetBlock=true;
						break;
					}
				}
				if (!hasGetBlock)
				{
					player.ChooseBlockChunkID=-1;
				}
			}
		}
	}
}

int mouseLeftClick()
{
	if (GameScrNum==1)
	{
		if (!isPause)
		{
			for (float getLong=0;getLong<7;getLong+=0.01)
			{
				if ((getBlockID(player.x+getLong*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180)),player.y-getLong*sin(player.upanddown*(PI/180)),player.z-getLong*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180)))!=0) & (!MC_Block[getBlockID(player.x+getLong*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180)),player.y-getLong*sin(player.upanddown*(PI/180)),player.z-getLong*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180)))].isLiquid))
				{
					if (MC_Block[getBlockID(player.x+getLong*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180)),player.y-getLong*sin(player.upanddown*(PI/180)),player.z-getLong*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180)))].Hardness<=player.BreakTime)
					{
						player.BreakTime=0;
						loadMob(1,getBlockID(player.x+getLong*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180)),player.y-getLong*sin(player.upanddown*(PI/180)),player.z-getLong*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180))),player.x+getLong*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180)),player.y-getLong*sin(player.upanddown*(PI/180)),player.z-getLong*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180)));
						setBlockID(player.x+getLong*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180)),player.y-getLong*sin(player.upanddown*(PI/180)),player.z-getLong*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180)),0);
					}
					break;
				}
			}
		}else{
			if (exitGameBottomInScr1)
			{
				LeaveGame();
			}else if (backGameBottomInScr1)
			{
				isPause=false;
				if (needShowCursor)
				{
					ShowCursor(false);
					needShowCursor=false;
				}
			}
		}
	}else if (GameScrNum==0){
		if (startGameBottomInScr0)
		{
			LoadGame("TEXT");
		}else if(exitGameBottomInScr0)
		{
			done=true;
		}else if(settingBottomInScr0)
		{
			GameScrNum=2;
		}
		LBottom=false;
		RBottom=false;
	}
	return TRUE;
}

int mouseRightClick()
{
	if (GameScrNum==1)
	{
		if (!isPause)
		{
			for (float getLong=0;getLong<7;getLong+=0.01)
			{
				if ((!MC_Block[getBlockID(player.x+getLong*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180)),player.y-getLong*sin(player.upanddown*(PI/180)),player.z-getLong*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180)))].isLiquid) & (getBlockID(player.x+getLong*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180)),player.y-getLong*sin(player.upanddown*(PI/180)),player.z-getLong*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180)))!=0))
				{
					getLong-=0.01;
					/////////////////////////
					float BlockX=player.x+getLong*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180));
					float BlockY=player.y-getLong*sin(player.upanddown*(PI/180));
					float BlockZ=player.z-getLong*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180));
					if (((((int)player.x==(int)BlockX) & ((int)player.z==(int)BlockZ)) & (((int)(player.y-1.6)==(int)BlockY) | ((int)(player.y-0.75)==(int)BlockY) | ((int)(player.y+0.1)==(int)BlockY))) | ((((int)(player.x-0.2)==(int)BlockX) & ((int)player.z==(int)BlockZ)) & (((int)(player.y-1.6)==(int)BlockY) | ((int)(player.y-0.75)==(int)BlockY) | ((int)(player.y+0.1)==(int)BlockY))) | ((((int)(player.x+0.2)==(int)BlockX) & ((int)player.z==(int)BlockZ)) & (((int)(player.y-1.6)==(int)BlockY) | ((int)(player.y-0.75)==(int)BlockY) | ((int)(player.y+0.1)==(int)BlockY))) | ((((int)player.x==(int)BlockX) & ((int)(player.z+0.2)==(int)BlockZ)) & (((int)(player.y-1.6)==(int)BlockY) | ((int)(player.y-0.75)==(int)BlockY) | ((int)(player.y+0.1)==(int)BlockY))) | ((((int)player.x==(int)BlockX) & ((int)(player.z-0.2)==(int)BlockZ)) & (((int)(player.y-1.6)==(int)BlockY) | ((int)(player.y-0.75)==(int)BlockY) | ((int)(player.y+0.1)==(int)BlockY))) | ((((int)(player.x+0.2)==(int)BlockX) & ((int)(player.z+0.2)==(int)BlockZ)) & (((int)(player.y-1.6)==(int)BlockY) | ((int)(player.y-0.75)==(int)BlockY) | ((int)(player.y+0.1)==(int)BlockY))) | ((((int)(player.x-0.2)==(int)BlockX) & ((int)(player.z-0.2)==(int)BlockZ))  & (((int)(player.y-1.6)==(int)BlockY) | ((int)(player.y-0.75)==(int)BlockY) | ((int)(player.y+0.1)==(int)BlockY))) | ((((int)(player.x+0.2)==(int)BlockX) & ((int)(player.z-0.2)==(int)BlockZ)) & (((int)(player.y-1.6)==(int)BlockY) | ((int)(player.y-0.75)==(int)BlockY) | ((int)(player.y+0.1)==(int)BlockY))) | ((((int)(player.x-0.2)==(int)BlockX) & ((int)(player.z+0.2)==(int)BlockZ)) & (((int)(player.y-1.6)==(int)BlockY) | ((int)(player.y-0.75)==(int)BlockY) | ((int)(player.y+0.1)==(int)BlockY))))
					{
						if (!MC_Block[player.PlayerBag[player.choiceNumber]].isSoil)
						{
							setBlockID(player.x+getLong*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180)),player.y-getLong*sin(player.upanddown*(PI/180)),player.z-getLong*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180)),player.PlayerBag[player.choiceNumber]);
						}
					}else{
						/////////////////////////
						setBlockID(player.x+getLong*cos(player.upanddown*(PI/180))*sin(player.around*(PI/180)),player.y-getLong*sin(player.upanddown*(PI/180)),player.z-getLong*cos(player.upanddown*(PI/180))*cos(player.around*(PI/180)),player.PlayerBag[player.choiceNumber]);
					}
					break;
				}
			}
		}
	}
	return TRUE;
}

void MouseEvent()
{
	if (LBottom)
	{
		mouseLeftClick();
	}else if (RBottom)
	{
		mouseRightClick();
	}else if(!LBottom)
	{
		player.BreakTime=0;
	}
}