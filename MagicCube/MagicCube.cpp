#include "MagicCube.h"
#include "Setting.h"
#include "player.h"
#include "Chunk.h"
#include "Texture.h"
#include "Block.h"
#include "File.h"
#include "Gobal.h"

int HeightFPS;
int Horizon;
float fog;
int ParticleNumber;
int MaxMobNumber;

CString WorldName;

#pragma comment(lib, "gltools.lib") 

#pragma comment(lib, "glew32.lib") 

int DrawMap(int ChunkID);
int AddMCTexture();

int InitGame(char *WorldLoadName);

int mousespeed;

HGLRC           hRC=NULL;							// 窗口着色描述表句柄
HDC             hDC=NULL;							// OpenGL渲染描述表句柄
HWND            hWnd=NULL;							// 保存我们的窗口句柄
HINSTANCE       hInstance;							// 保存程序的实例

bool	active=TRUE;								// 窗口的活动标志，缺省为TRUE
bool	fullscreen=TRUE;							// 全屏标志缺省，缺省设定成全屏模式

bool	keys[256];								// 保存键盘按键的数组

bool	firstInit=TRUE;

int MagicCubeInit()
{
	ParticleNumber=100;
	HeightFPS=25;
	fog=27;
	mousespeed=50;
	player.speed=0.1;
	Horizon=4;
	MaxMobNumber=1000;
	shaking=true;
	player.fly=false;
	/*
	player.PlayerBag[0]=3;
	player.PlayerBag[1]=2;
	player.PlayerBag[2]=20;
	player.PlayerBag[3]=5;
	player.PlayerBag[4]=17;
	player.PlayerBag[5]=1;
	player.PlayerBag[6]=18;
	player.PlayerBag[7]=6;
	player.PlayerBag[8]=8;
	*/
	AddMCTexture();

	InitBlockDate();

	resetPlayerChunk();

	for (int i=0;i<225;i++)
	{
		Chunk[i].isCreateList=false;
	}
		
	return 1;
}

int InitGame(char *WorldLoadName)
{
	WorldName=WorldLoadName;
	FirstLoafFinish=false;
	if (MKDir())
	{
		srand((unsigned)time( NULL )); 
		seed=rand();
		player.x=1000;
		player.y=100;
		player.z=1000;
		writeBasicDate();
	}else{
		readBasicDate();
	}

	player.g=0.01;
	player.choiceNumber=0;

	resetPlayerChunk();

	int CID=0;

	NewChunkList[7][7]=112;
	Chunk[112].chunkX=player.ChunkX;
	Chunk[112].chunkZ=player.ChunkZ;

	for (int i=-7;i<8;i++)
	{
		for (int j=-7;j<8;j++)
		{
			InitChunk(CID,i,j,true);
			CID++;
		}
	}
	for (int i=-7;i<8;i++)
	{
		for (int j=-7;j<8;j++)
		{
			NewChunkList[7+i][7+j]=ChunkList[7+i][7+j];
		}
	}
	return TRUE;
}