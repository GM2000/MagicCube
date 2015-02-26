#include "Gobal.h"
#include "Chunk.h"
#include "Texture.h"


GLuint drawChar_To_Texture(const char* s,float TX,float TZ,float FontSize);

void SaveWorld();

extern bool needShowCursor;

int InitGame(char *WorldLoadName);

void LeaveGame()
{
	SetWindowText(hWnd, "��Ϸ����������");
	///////////////////////////////////////////////������Ϣ����

	/////////////////////////////////////////////////////
	saving=true;
	SaveWorld();
	GameScrNum=0;
	saving=false;
	isPause=false;
	if (!needShowCursor)
	{
		ShowCursor(true);
		needShowCursor=true;
	}
	for (int i=0;i<225;i++)
	{
		Chunk[i].chunkX=0;
		Chunk[i].chunkZ=0;
		Chunk[i].isCreateList=false;
		Chunk[i].mustCreateListNow=false;
	}
	glDeleteLists(0,450);
}

int LoadGame(char *GameName)
{
	if (needShowCursor)
	{
		ShowCursor(false);
		needShowCursor=false;
	}
	isPause=false;
	InitGame(GameName);
	GameScrNum=1;
	return 1;
}