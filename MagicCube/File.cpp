#include "File.h"
#include "chunk.h"
#include "Player.h"
#include "Setting.h"

bool MKDir()
{
	CString pathName;
	CString savePath;

	savePath="save";
	pathName.Format("%s%s","save\\",WorldName);

	if(!PathFileExists(savePath))//文件夹不存在则创建
	{
		CreateDirectory(savePath,NULL);
	}

	if(!PathFileExists(pathName))//文件夹不存在则创建
	{
		CreateDirectory(pathName,NULL);
		return true;
	}
	return false;
}

void readBasicDate()
{
	CFile bmd;

	char *saveSeed=new char[100];

	char *saveplayerX=new char[100];
	char *saveplayerY=new char[100];
	char *saveplayerZ=new char[100];

	char *playerPosX=new char[100];
	char *playerPosZ=new char[100];

	CString pathName;
	pathName.Format("%s%s%s","save\\",WorldName,"\\Date.bmd");
	bmd.Open(pathName,CFile::modeRead|CFile::typeBinary);

	bmd.Read(saveSeed,100);
	bmd.Read(saveplayerX,100);
	bmd.Read(saveplayerY,100);
	bmd.Read(saveplayerZ,100);
	bmd.Read(playerPosX,100);
	bmd.Read(playerPosZ,100);

	bmd.Close();

	seed=atoi(saveSeed);

	player.x=atof(saveplayerX);
	player.y=atof(saveplayerY);
	player.z=atof(saveplayerZ);

	player.around=atoi(playerPosX);
	player.upanddown=atoi(playerPosZ);
}

void writeBasicDate()
{
	CFile bmd;  
	float seeds=seed;

	char *saveSeed=new char[100];

	char *savePlayerX=new char[100];
	char *savePlayerY=new char[100];
	char *savePlayerZ=new char[100];

	char *playerPosX=new char[100];
	char *playerPosZ=new char[100];

	CString CsaveSeed;
	CsaveSeed.Format("%i",seed);

	CString CplayerPosX;
	CplayerPosX.Format("%f",player.around);
	CString CplayerPosZ;
	CplayerPosZ.Format("%f",player.upanddown);

	CString CsavePlayerX;
	CsavePlayerX.Format("%f",player.x);
	CString CsavePlayerY;
	CsavePlayerY.Format("%f",player.y);
	CString CsavePlayerZ;
	CsavePlayerZ.Format("%f",player.z);

	saveSeed=CsaveSeed.GetBuffer(CsaveSeed.GetLength());

	savePlayerX=CsavePlayerX.GetBuffer(CsavePlayerX.GetLength());
	savePlayerY=CsavePlayerY.GetBuffer(CsavePlayerY.GetLength());
	savePlayerZ=CsavePlayerZ.GetBuffer(CsavePlayerZ.GetLength());

	playerPosX=CplayerPosX.GetBuffer(CplayerPosX.GetLength());
	playerPosZ=CplayerPosZ.GetBuffer(CplayerPosZ.GetLength());

	CString pathName;
	pathName.Format("%s%s%s","save\\",WorldName,"\\Date.bmd");
	bmd.Open(pathName,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary);

	bmd.Write(saveSeed,100);
	bmd.Write(savePlayerX,100);
	bmd.Write(savePlayerY,100);
	bmd.Write(savePlayerZ,100);
	bmd.Write(playerPosX,100);
	bmd.Write(playerPosZ,100);

	bmd.Close();
}

void saveChunkToFile(chunk ChunkDat,int ChunkX,int ChunkZ)
{
	CFile CSD;  

	CString datePathName;
	datePathName.Format("%s%s%s%i%s%i%s","save\\",WorldName,"\\",ChunkX,"-",ChunkZ,".mcc");

	CSD.Open(datePathName,CFile::modeCreate|CFile::modeWrite|CFile::typeBinary);

	
	for (int i=0;i<16;i++)
	{
		for (int j=0;j<256;j++)
		{
			for (int k=0;k<16;k++)
			{
				char *chunkLevelDat=new char[10];

				CString CchunkLevelDat;
				CchunkLevelDat.Format("%i",ChunkDat.BlockID[i][j][k]);

				chunkLevelDat=CchunkLevelDat.GetBuffer(CchunkLevelDat.GetLength());
				CSD.Write(chunkLevelDat,10);
			}
		}
	}
	CSD.Close();
}

bool getChunkFormFile(int ChunkID,int ChunkX,int ChunkZ)
{
	CFile CSD;  

	CString datePathName;
	datePathName.Format("%s%s%s%i%s%i%s","save\\",WorldName,"\\",ChunkX,"-",ChunkZ,".mcc");

	if (PathFileExists(datePathName))
	{
		CSD.Open(datePathName,CFile::modeRead|CFile::typeBinary);

		for (int i=0;i<16;i++)
		{
			for (int j=0;j<256;j++)
			{
				for (int k=0;k<16;k++)
				{
					char *chunkLevelDat=new char[10];

					CSD.Read(chunkLevelDat,10);

					Chunk[ChunkID].BlockID[i][j][k]=atoi(chunkLevelDat);
				}
			}
		}
		CSD.Close();
		return true;
	}
	return false;
}