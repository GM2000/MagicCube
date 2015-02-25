#include <time.h>
#include <stdlib.h>
#include "OpenglWindows.h"
#include "Gobal.h"
#include "Chunk.h"
#include "Player.h"
#include "Setting.h"
#include "File.h"

void saveChunkToFile(chunk ChunkDat,int ChunkX,int ChunkZ);

bool getChunkFormFile(int ChunkID,int ChunkX,int ChunkZ);

float persistence = 1.3f;

int Number_Of_Octaves = 3;
int loadPrecent;
int seed;

bool FirstLoafFinish;

//1376312589

float PerlinNoise_2D(float x, float y);

//一个噪声发生器
float Noise1(int x, int y)
{
	if (seed<0)
	{
		seed=-seed;
	}
	int n = x + y * 57;
	n = n + ((n + seed)*n - seed) * seed;
	n = (n<<13) ^ n;
	return ( 1.0f - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f); 
}

bool NoiseTree(int x, int y)
{
	if (seed<0)
	{
		seed=-seed;
	}
	int n = x + y * 57;
	n = n + ((n + seed)*n - seed) * (seed+n);
	n = (n<<13) ^ n;
	if ((1.0f - ( (n * (n * n * 15731 + 789221) + 23456432245) & 0x7fffffff) / 1073741824.0f>0.994))
	{
		if (50-PerlinNoise_2D(x,y)>50)
		{
			return TRUE;
		}else{
			return FALSE;
		}
	}else{
		return FALSE;
	}
}

//一个光滑噪声发生器
float SmoothNoise_1(int x, int y)
{
	float corners = ( Noise1(x-1, y-1)+Noise1(x+1, y-1)+Noise1(x-1, y+1)+Noise1(x+1, y+1) ) / 16.0f;
	float sides   = ( Noise1(x-1, y)  +Noise1(x+1, y)  +Noise1(x, y-1)  +Noise1(x, y+1) ) /  8.0f;
	float center  =  Noise1(x, y) / 4.0f;
	return corners + sides + center;
}

//插值函数
float Cosine_Interpolate(float a, float b, float x)
{
	double ft = x * 3.1415927;
	double f = (1 - cos(ft)) * 0.5f;

	return  a*(1-f) + b*f;

}



//插值噪声发生器
float InterpolatedNoise_1(float x, float y)
{

	int integer_X    = int(x);
	float fractional_X = x - integer_X;

	int integer_Y    = int(y);
	float fractional_Y = y - integer_Y;

	float v1 = SmoothNoise_1(integer_X,     integer_Y);
	float v2 = SmoothNoise_1(integer_X + 1, integer_Y);
	float v3 = SmoothNoise_1(integer_X,     integer_Y + 1);
	float v4 = SmoothNoise_1(integer_X + 1, integer_Y + 1);

	float i1 = Cosine_Interpolate(v1 , v2 , fractional_X);
	float i2 = Cosine_Interpolate(v3 , v4 , fractional_X);

	return Cosine_Interpolate(i1 , i2 , fractional_Y);
}

//最终的PERLIN NOISE
float PerlinNoise_2D(float x, float y)
{
	x=x/50;
	y=y/50;
	float total = 0.0f;
	float p = persistence;
	int n = Number_Of_Octaves - 1;

	for(int i=0;i<=n;i++)
	{
		float frequency = pow((float)2,i);
		float amplitude = pow(p,i);

		total = total + InterpolatedNoise_1(x * frequency, y * frequency) * amplitude;
	}

	return total;
} 

void LoadChunk()
{
	int i=0;
	while (!done)
	{
		if (GameScrNum==1)
		{
			if (!FirstLoafFinish)
			{
				loadPrecent=i/225.0*100;
				CString strFrameRate;
				strFrameRate.Format("%s%d%s","生成世界中:",loadPrecent,"%");
				SetWindowText(hWnd, strFrameRate);
			}
			if (i==224)
			{
				i=0;
				FirstLoafFinish=true;
			}else{
				i=i+1;
			}
			if (ChunkInfo[i].NeedBuild)
			{
				if (ChunkInfo[i].NeedSave)
				{
					ChunkInfo[i].NeedSave=false;
					saveChunkToFile(Chunk[i],ChunkInfo[i].oldChunkX,ChunkInfo[i].oldChunkZ);
				}
				ChunkInfo[i].NeedBuild=false;
				int ChunkX=ChunkInfo[i].ChunkX;
				int ChunkZ=ChunkInfo[i].ChunkZ;
				int ChunkID=i;

				if (!getChunkFormFile(ChunkID,ChunkX,ChunkZ))
				{
					int h;
					for (int ci=0;ci<16;ci++)
					{
						for (int cj=0;cj<256;cj++)
						{
							for (int ck=0;ck<16;ck++)
							{
								Chunk[ChunkID].BlockID[ci][cj][ck]=0;
							}
						}
					}
					for (int i=0;i<16;i++)
					{
						for (int j=0;j<16;j++)
						{
							bool isEdig=false;
							if ((ChunkX<0) | (ChunkZ<0))
							{
								isEdig=true;
							}
							h=50-PerlinNoise_2D(i+ChunkX*16,j+ChunkZ*16)*10;

							//////////////////////////树木///////////////////////////
							if (NoiseTree(i+ChunkX*16,j+ChunkZ*16))
							{
								Chunk[ChunkID].BlockID[i][h+1][j]=17;
								Chunk[ChunkID].BlockID[i][h+2][j]=17;
								Chunk[ChunkID].BlockID[i][h+3][j]=17;
								Chunk[ChunkID].BlockID[i][h+4][j]=17;
								Chunk[ChunkID].BlockID[i][h+5][j]=17;
								Chunk[ChunkID].BlockID[i][h+6][j]=17;
								Chunk[ChunkID].BlockID[i][h+7][j]=18;
							}
							else if (NoiseTree(1+i+ChunkX*16,j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(1+i+ChunkX*16,j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+6][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+7][j]=18;
							}
							else if (NoiseTree(-1+i+ChunkX*16,j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(-1+i+ChunkX*16,j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+6][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+7][j]=18;
							}
							else if (NoiseTree(i+ChunkX*16,1+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(i+ChunkX*16,1+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+6][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+7][j]=18;
							}
							else if (NoiseTree(i+ChunkX*16,-1+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(i+ChunkX*16,-1+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+6][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+7][j]=18;
							}
							else if (NoiseTree(1+i+ChunkX*16,1+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(1+i+ChunkX*16,1+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+6][j]=18;
							}
							else if (NoiseTree(-1+i+ChunkX*16,1+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(-1+i+ChunkX*16,1+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+6][j]=18;
							}
							else if (NoiseTree(-1+i+ChunkX*16,-1+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(-1+i+ChunkX*16,-1+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+6][j]=18;
							}
							else if (NoiseTree(1+i+ChunkX*16,-1+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(1+i+ChunkX*16,-1+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+6][j]=18;
							}
							else if (NoiseTree(2+i+ChunkX*16,-1+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(2+i+ChunkX*16,-1+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
							}
							else if (NoiseTree(2+i+ChunkX*16,0+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(2+i+ChunkX*16,0+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
							}
							else if (NoiseTree(2+i+ChunkX*16,1+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(2+i+ChunkX*16,1+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
							}
							else if (NoiseTree(-2+i+ChunkX*16,-1+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(-2+i+ChunkX*16,-1+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
							}
							else if (NoiseTree(-2+i+ChunkX*16,0+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(-2+i+ChunkX*16,0+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
							}
							else if (NoiseTree(-2+i+ChunkX*16,1+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(-2+i+ChunkX*16,1+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
							}
							else if (NoiseTree(-1+i+ChunkX*16,2+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(-1+i+ChunkX*16,2+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
							}
							else if (NoiseTree(0+i+ChunkX*16,2+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(0+i+ChunkX*16,2+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
							}
							else if (NoiseTree(1+i+ChunkX*16,2+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(1+i+ChunkX*16,2+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
							}
							else if (NoiseTree(-1+i+ChunkX*16,-2+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(-1+i+ChunkX*16,-2+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
							}
							else if (NoiseTree(0+i+ChunkX*16,-2+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(0+i+ChunkX*16,-2+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
							}
							else if (NoiseTree(1+i+ChunkX*16,-2+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(1+i+ChunkX*16,-2+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
								Chunk[ChunkID].BlockID[i][TreeH+5][j]=18;
							}
							else if (NoiseTree(2+i+ChunkX*16,2+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(2+i+ChunkX*16,2+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
							}
							else if (NoiseTree(2+i+ChunkX*16,-2+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(2+i+ChunkX*16,-2+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
							}
							else if (NoiseTree(-2+i+ChunkX*16,2+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(-2+i+ChunkX*16,2+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
							}
							else if (NoiseTree(-2+i+ChunkX*16,-2+j+ChunkZ*16))
							{
								int TreeH=50-PerlinNoise_2D(-2+i+ChunkX*16,-2+j+ChunkZ*16)*10;
								Chunk[ChunkID].BlockID[i][TreeH+4][j]=18;
							}
							/////////////////////////结束/////////////////////////

							if (h<50)
							{
								for (int k=50;k>h;k--)
								{
									Chunk[ChunkID].BlockID[i][k][j]=8;
								}
							}
							for (int k=0;k<h+1;k++)
							{
								if ((k<h) & (k>h-6))
								{
									Chunk[ChunkID].BlockID[i][k][j]=3;
								}else if (k<h-5)
								{
									Chunk[ChunkID].BlockID[i][k][j]=1;
								}else if (k==h)
								{
									if (h<50)
									{
										Chunk[ChunkID].BlockID[i][k][j]=3;
									}else{
										Chunk[ChunkID].BlockID[i][k][j]=2;
									}
								}
							}
						}
					}
				}
			}
		}else if (GameScrNum==0){
			i=0;
		}
	}
} 