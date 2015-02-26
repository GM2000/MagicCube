#include "MagicCube.h"
#include "Gobal.h"
#include "Texture.h"
#include "Block.h"
#include "Player.h"
#include "Chunk.h"
#include <time.h>
#include "OpenglWindows.h"
#include "Setting.h"
#include "Particle.h"
#include "Mob.h"

int FPSTime=0;
float currentTime = GetTickCount()*0.001f;

int PlayerBlockSelectX;
int PlayerBlockSelectY;
int PlayerBlockSelectZ;

bool backGameBottomInScr1=false;
bool backGameBottomInScr2=false;
bool exitGameBottomInScr1=false;
bool exitGameBottomInScr0=false;
bool startGameBottomInScr0=false;
bool settingBottomInScr0=false;
bool shaking;

float shakingDegX;
float shakingDegY;

GLuint drawChar_To_Texture(const char* s,float TX,float TZ,float FontSize);

int DrawMap(int ChunkListX,int ChunkListZ);

int FPS=0;

int SZZX()
{
	glEnable( GL_BLEND );
	glLoadIdentity();							// 重置当前的模型观察矩阵
	glBindTexture(GL_TEXTURE_2D,toolbar);				// 选择纹理
	glBegin(GL_QUADS); 
	glTexCoord2f(22/256.0f, 236/256.0f); 
	glVertex3f(0.0017f, 0.0017f, -0.1f);  

	glTexCoord2f(22/256.0f, 214/256.0f);
	glVertex3f(0.0017f, -0.0017f, -0.1f);

	glTexCoord2f(44/256.0f, 214/256.0f); 
	glVertex3f(-0.0017f, -0.0017f, -0.1f); 

	glTexCoord2f(44/256.0f, 236/256.0f); 
	glVertex3f(-0.0017f, 0.0017f, -0.1f);
	glEnd();
	glDisable( GL_BLEND );
	return 1;
}

int DrawCube(int X,int TextureID)
{
	int TextureX;
	int TextureZ;
	TextureZ=TextureID/16;
	TextureX=TextureID-TextureZ*16;
	glBindTexture(GL_TEXTURE_2D, texture);				// 选择纹理
	glBegin(GL_QUADS);							//  绘制工具栏选择框
	glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
	glVertex3f((X-1)*20*0.000455-0.039f-0.000455, -0.039755f,-0.1f);
	glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
	glVertex3f((X)*20*0.000455-0.043f+0.000455, -0.039755f,-0.1f);
	glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16); 
	glVertex3f((X)*20*0.000455-0.043f+0.000455,-0.033745f,-0.1f);
	glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
	glVertex3f((X-1)*20*0.000455-0.039f-0.000455,-0.033745f,-0.1f);
	glEnd();	
	return TRUE;
}

int ToolBar()
{
	glEnable( GL_BLEND );
	glLoadIdentity();							// 重置当前的模型观察矩阵
	glBindTexture(GL_TEXTURE_2D, toolbar);				// 选择纹理
	glBegin(GL_QUADS);							//  绘制工具栏
	glTexCoord2f(0.0f, 236/256.0f); glVertex3f(-0.041f, -0.0413f,-0.1f);	// 纹理和四边形的左下
	glTexCoord2f(180/256.0f, 236/256.0f); glVertex3f(0.041f, -0.0413f,-0.1f);	// 纹理和四边形的右下
	glTexCoord2f(180/256.0f, 1.0f); glVertex3f(0.041f,-0.0322f,-0.1f);	// 纹理和四边形的右上
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.041f,-0.0322f,-0.1f);	// 纹理和四边形的左上
	glEnd();	

	glBindTexture(GL_TEXTURE_2D, toolbar);				// 选择纹理
	glBegin(GL_QUADS);							//  绘制工具栏选择框
	glTexCoord2f(0.0f, 214/256.0f); 
	glVertex3f((player.choiceNumber)*20*0.000455-0.041f-0.000455, -0.041755f,-0.1f);
	glTexCoord2f(22/256.0f, 214/256.0f); 
	glVertex3f((player.choiceNumber+1)*20*0.000455-0.041f+0.000455, -0.041755f,-0.1f);
	glTexCoord2f(22/256.0f, 236/256.0f); 
	glVertex3f((player.choiceNumber+1)*20*0.000455-0.041f+0.000455,-0.031745f,-0.1f);
	glTexCoord2f(0.0f, 236/256.0f); 
	glVertex3f((player.choiceNumber)*20*0.000455-0.041f-0.000455,-0.031745f,-0.1f);
	glEnd();	
	/////////////////////////////////////////////////////////////////////////
	DrawCube(1,0);
	DrawCube(2,1);
	DrawCube(3,16);
	DrawCube(4,17);
	DrawCube(5,3);
	DrawCube(6,5);
	DrawCube(7,18);
	DrawCube(8,19);
	DrawCube(9,6);
	/////////////////////////////////////////////////////////////////////////
	glDisable( GL_BLEND );
	return 1;
}

void DrawMap()
{

	glBindTexture(GL_TEXTURE_2D,texture);

	hasCreatList=false;

	MSG msg;

	for (int i=5-Horizon;i<10+Horizon;i++)
	{
		for (int j=5-Horizon;j<10+Horizon;j++)
		{
			DrawMap(i,j);
		}
	}

	for (int i=5-Horizon;i<10+Horizon;i++)
	{
		for (int j=5-Horizon;j<10+Horizon;j++)
		{
			if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))			// 有消息在等待吗?
			{
				if (msg.message==WM_QUIT)				// 收到退出消息?
				{
					done=TRUE;					// 是，则done=TRUE
				}
				else							// 不是，处理窗口消息
				{
					TranslateMessage(&msg);				// 翻译消息
					DispatchMessage(&msg);				// 发送消息
				}
			}
			glCallList((ChunkList[i][j]+1)*2);
		}
	}

	for (int i=5-Horizon;i<10+Horizon;i++)
	{
		for (int j=5-Horizon;j<10+Horizon;j++)
		{
			glCallList((ChunkList[i][j]+1)*2+1);
		}
	}
	Particles();
	reSetMob();
}
int DrawGLScene(GLvoid)								// 从这里开始进行所有的绘制
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// 清除屏幕和深度缓存
	if (GameScrNum==1)
	{
		if ((FirstLoafFinish) & (!saving))
		{
			float startTime = GetTickCount()*0.001f;

			glLoadIdentity();							// 重置当前的模型观察矩阵
			glRotatef(player.upanddown,1,0,0);
			glTranslatef(shakingDegX/3,shakingDegY/3,0);						        // 人物移动
			glRotatef(player.around,0,1,0);
			glTranslatef(-player.x,-player.y,-player.z);						        // 人物移动
			DrawMap();

			float nowTime = GetTickCount()*0.001f;   

			while (!(nowTime-startTime>1.0/HeightFPS))
			{
				nowTime = GetTickCount()*0.001f; 
			}

			if (!isPause)
			{
				ToolBar();
				SZZX();
			}
			if (nowTime-startTime>0)
			{
				FPS=FPSTime/(nowTime-currentTime);
				currentTime = GetTickCount()*0.001f;
				FPSTime=0;
			}

			FPSTime+=1;

			CString strFrameRate;
			strFrameRate.Format("%d", FPS);
			SetWindowText(hWnd, strFrameRate);

		}else if (!FirstLoafFinish)
		{
			int TextureX=0;
			int TextureZ=0;
			int WinWN=WindowsWidth/87+3;
			int WinHN=WindowsHeight/74+3;
			for (int i=-WinWN;i<WinWN;i++)
			{
				for (int j=0;j<WinHN;j++)
				{
					glEnable(GL_BLEND);
					glDisable(GL_DEPTH_TEST);
					glLoadIdentity();							// 重置当前的模型观察矩阵
					glBindTexture(GL_TEXTURE_2D,texture);
					glBegin(GL_QUADS);
					//右前点
					glColor4f(1.0,1.0,1.0,1.0);
					glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
					glVertex3f(i-4,j-4,-7);
					//左前点
					glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
					glVertex3f(i-4,j-5,-7);
					//左后点
					glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
					glVertex3f(i-5,j-5,-7);
					//右后点
					glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
					glVertex3f(i-5,j-4,-7);
					glEnd();
					glEnable(GL_DEPTH_TEST);
				}
			}
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
			//右前点
			glColor3f(1.0,1.0,1.0);
			glVertex3f(-1.5,0,-7);
			//左前点
			glVertex3f(1.5,0,-7);
			//左后点
			glVertex3f(1.5,-0.1,-7);
			//右后点
			glVertex3f(-1.5,-0.1,-7);
			glEnd();
			glBegin(GL_QUADS);
			//右前点
			glColor3f(0.0,1.0,0.0);
			glVertex3f(-1.5,0,-7);
			//左前点
			glVertex3f(-1.5+3*loadPrecent/100.0,0,-7);
			//左后点
			glVertex3f(-1.5+3*loadPrecent/100.0,-0.1,-7);
			//右后点
			glVertex3f(-1.5,-0.1,-7);
			glEnd();
			glEnable(GL_TEXTURE_2D);
			drawChar_To_Texture("载",WindowsWidth/2.083-WindowsHeight/14-WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
			drawChar_To_Texture("入",WindowsWidth/2.083-WindowsHeight/14+WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
			drawChar_To_Texture("地",WindowsWidth/2.083+WindowsHeight/14-WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
			drawChar_To_Texture("图",WindowsWidth/2.083+WindowsHeight/14+WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
		}

		if (isPause)
		{
			glBindTexture(GL_TEXTURE_2D,toolbar);

			glEnable(GL_BLEND);
			glDisable(GL_DEPTH_TEST);
			glLoadIdentity();							// 重置当前的模型观察矩阵
			glBegin(GL_QUADS);
			glColor4f(0.3,0.3,0.3,0.3);
			glVertex3f(-1.0f, 1.0f, -1.0f);				// 左上
			glVertex3f( 1.0f, 1.0f, -1.0f);				// 右上
			glVertex3f( 1.0f,-1.0f, -1.0f);				// 左下
			glVertex3f(-1.0f,-1.0f, -1.0f);				// 右下

			if (exitGameBottomInScr1)
			{
				glColor4f(1.0,1.0,1.0,1.0);
				glTexCoord2f(0.0,194.0/256.0);
				glVertex3f(-5.0f, -1.25f, -12.0f);				// 左上
				glTexCoord2f(200/256.0,194.0/256.0);
				glVertex3f( 5.0f, -1.25f, -12.0f);				// 右上
				glTexCoord2f(200/256.0,174.0/256.0);
				glVertex3f( 5.0f,-2.25f, -12.0f);				// 右下
				glTexCoord2f(0.0,174.0/256.0);
				glVertex3f(-5.0f,-2.25f, -12.0f);				// 左下
			}else{
				glColor3f(1.0f,1.0f,1.0f);
				glTexCoord2f(0.0,214.0/256.0);
				glVertex3f(-5.0f, -1.25f, -12.0f);				// 左上
				glTexCoord2f(200/256.0,214.0/256.0);
				glVertex3f( 5.0f, -1.25f, -12.0f);				// 右上
				glTexCoord2f(200/256.0,194.0/256.0);
				glVertex3f( 5.0f,-2.25f, -12.0f);				// 右下
				glTexCoord2f(0.0,194.0/256.0);
				glVertex3f(-5.0f,-2.25f, -12.0f);				// 左下
			}
			if (backGameBottomInScr1)
			{
				glColor4f(1.0,1.0,1.0,1.0);
				glTexCoord2f(0.0,194.0/256.0);
				glVertex3f(-5.0f, 1.5f, -12.0f);				// 左上
				glTexCoord2f(200/256.0,194.0/256.0);
				glVertex3f( 5.0f, 1.5f, -12.0f);				// 右上
				glTexCoord2f(200/256.0,174.0/256.0);
				glVertex3f( 5.0f,0.5f, -12.0f);				// 右下
				glTexCoord2f(0.0,174.0/256.0);
				glVertex3f(-5.0f,0.5f, -12.0f);				// 左下
			}else{
				glColor3f(1.0f,1.0f,1.0f);
				glTexCoord2f(0.0,214.0/256.0);
				glVertex3f(-5.0f, 1.5f, -12.0f);				// 左上
				glTexCoord2f(200/256.0,214.0/256.0);
				glVertex3f( 5.0f, 1.5f, -12.0f);				// 右上
				glTexCoord2f(200/256.0,194.0/256.0);
				glVertex3f( 5.0f,0.5f, -12.0f);				// 右下
				glTexCoord2f(0.0,194.0/256.0);
				glVertex3f(-5.0f,0.5f, -12.0f);				// 左下
			}
			glEnd();

			glTranslatef(0,0,-1);

			drawChar_To_Texture("结",WindowsWidth/2.083-WindowsHeight/14-WindowsHeight/28,WindowsHeight/3.35,WindowsHeight/12);
			drawChar_To_Texture("束",WindowsWidth/2.083-WindowsHeight/14+WindowsHeight/28,WindowsHeight/3.35,WindowsHeight/12);
			drawChar_To_Texture("游",WindowsWidth/2.083+WindowsHeight/14-WindowsHeight/28,WindowsHeight/3.35,WindowsHeight/12);
			drawChar_To_Texture("戏",WindowsWidth/2.083+WindowsHeight/14+WindowsHeight/28,WindowsHeight/3.35,WindowsHeight/12);

			drawChar_To_Texture("返",WindowsWidth/2.083-WindowsHeight/14-WindowsHeight/28,WindowsHeight/1.73,WindowsHeight/12);
			drawChar_To_Texture("回",WindowsWidth/2.083-WindowsHeight/14+WindowsHeight/28,WindowsHeight/1.73,WindowsHeight/12);
			drawChar_To_Texture("游",WindowsWidth/2.083+WindowsHeight/14-WindowsHeight/28,WindowsHeight/1.73,WindowsHeight/12);
			drawChar_To_Texture("戏",WindowsWidth/2.083+WindowsHeight/14+WindowsHeight/28,WindowsHeight/1.73,WindowsHeight/12);

			glEnable(GL_DEPTH_TEST);
		}

		if (saving)
		{
			SetWindowText(hWnd, "游戏保存界面测试");
			int TextureX=0;
			int TextureZ=0;
			int WinWN=WindowsWidth/87+3;
			int WinHN=WindowsHeight/74+3;
			for (int i=-WinWN;i<WinWN;i++)
			{
				for (int j=0;j<WinHN;j++)
				{
					glEnable(GL_BLEND);
					glDisable(GL_DEPTH_TEST);
					glLoadIdentity();							// 重置当前的模型观察矩阵
					glBindTexture(GL_TEXTURE_2D,texture);
					glBegin(GL_QUADS);
					//右前点
					glColor4f(1.0,1.0,1.0,1.0);
					glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
					glVertex3f(i-4,j-4,-7);
					//左前点
					glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
					glVertex3f(i-4,j-5,-7);
					//左后点
					glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
					glVertex3f(i-5,j-5,-7);
					//右后点
					glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
					glVertex3f(i-5,j-4,-7);
					glEnd();
					glEnable(GL_DEPTH_TEST);
				}
			}
			drawChar_To_Texture("保",WindowsWidth/2.083-WindowsHeight/14-WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
			drawChar_To_Texture("存",WindowsWidth/2.083-WindowsHeight/14+WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
			drawChar_To_Texture("地",WindowsWidth/2.083+WindowsHeight/14-WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
			drawChar_To_Texture("图",WindowsWidth/2.083+WindowsHeight/14+WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
		}
	}else if (GameScrNum==0){
		SetWindowText(hWnd, "游戏开始界面测试");
		glLoadIdentity();							// 重置当前的模型观察矩阵
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_ALPHA_TEST);
		//LOGO
		glBindTexture(GL_TEXTURE_2D,logo);
		glBegin(GL_QUADS);
		glColor4f(1.0,1.0,1.0,1.0);
		glTexCoord2f(0.0,1.0);
		glVertex3f(-7.0f, 4.0f, -12.0f);				// 左上
		glTexCoord2f(1.0,1.0);
		glVertex3f( 7.0f, 4.0f, -12.0f);				// 右上
		glTexCoord2f(1.0,0.0);
		glVertex3f( 7.0f,1.0f, -12.0f);				// 右下
		glTexCoord2f(0.0,0.0);
		glVertex3f(-7.0f,1.0f, -12.0f);				// 左下
		glEnd();


		glBindTexture(GL_TEXTURE_2D,toolbar);
		glLoadIdentity();							// 重置当前的模型观察矩阵
		glBegin(GL_QUADS);
		//开始游戏
		if (startGameBottomInScr0)
		{
			glColor4f(1.0,1.0,1.0,1.0);
			glTexCoord2f(0.0,194.0/256.0);
			glVertex3f(-5.0f, 0.0f, -12.0f);				// 左上
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( 5.0f, 0.0f, -12.0f);				// 右上
			glTexCoord2f(200/256.0,174.0/256.0);
			glVertex3f( 5.0f,-1.0f, -12.0f);				// 右下
			glTexCoord2f(0.0,174.0/256.0);
			glVertex3f(-5.0f,-1.0f, -12.0f);				// 左下
		}else{
			glColor4f(1.0,1.0,1.0,1.0);
			glTexCoord2f(0.0,214.0/256.0);
			glVertex3f(-5.0f, 0.0f, -12.0f);				// 左上
			glTexCoord2f(200/256.0,214.0/256.0);
			glVertex3f( 5.0f, 0.0f, -12.0f);				// 右上
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( 5.0f,-1.0f, -12.0f);				// 右下
			glTexCoord2f(0.0,194.0/256.0);
			glVertex3f(-5.0f,-1.0f, -12.0f);				// 左下
		}
		//退出
		if (exitGameBottomInScr0)
		{
			glTexCoord2f(0.0,194.0/256.0);
			glVertex3f( 0.25f, -1.25f, -12.0f);				// 左上
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( 5.0f, -1.25f, -12.0f);				// 右上
			glTexCoord2f(200/256.0,174.0/256.0);
			glVertex3f( 5.0f,-2.25f, -12.0f);				// 右下
			glTexCoord2f(0.0,174.0/256.0);
			glVertex3f( 0.25f,-2.25f, -12.0f);				// 左下
		}else{
			glTexCoord2f(0.0,214.0/256.0);
			glVertex3f( 0.25f, -1.25f, -12.0f);				// 左上
			glTexCoord2f(200/256.0,214.0/256.0);
			glVertex3f( 5.0f, -1.25f, -12.0f);				// 右上
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( 5.0f,-2.25f, -12.0f);				// 右下
			glTexCoord2f(0.0,194.0/256.0);
			glVertex3f( 0.25f,-2.25f, -12.0f);				// 左下
		}
		//选项
		if (settingBottomInScr0)
		{
			glTexCoord2f(0.0,194.0/256.0);
			glVertex3f( -5.0f, -1.25f, -12.0f);				// 左上
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( -0.25f, -1.25f, -12.0f);				// 右上
			glTexCoord2f(200/256.0,174.0/256.0);
			glVertex3f( -0.25f,-2.25f, -12.0f);				// 右下
			glTexCoord2f(0.0,174.0/256.0);
			glVertex3f( -5.0f,-2.25f, -12.0f);				// 左下
		}else{
			glTexCoord2f(0.0,214.0/256.0);
			glVertex3f( -5.0f, -1.25f, -12.0f);				// 左上
			glTexCoord2f(200/256.0,214.0/256.0);
			glVertex3f( -0.25f, -1.25f, -12.0f);				// 右上
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( -0.25f,-2.25f, -12.0f);				// 右下
			glTexCoord2f(0.0,194.0/256.0);
			glVertex3f( -5.0f,-2.25f, -12.0f);				// 左下
		}
		glEnd();

		drawChar_To_Texture("开",WindowsWidth/2.083-WindowsHeight/14-WindowsHeight/28,WindowsHeight/2.35,WindowsHeight/12);
		drawChar_To_Texture("始",WindowsWidth/2.083-WindowsHeight/14+WindowsHeight/28,WindowsHeight/2.35,WindowsHeight/12);
		drawChar_To_Texture("游",WindowsWidth/2.083+WindowsHeight/14-WindowsHeight/28,WindowsHeight/2.35,WindowsHeight/12);
		drawChar_To_Texture("戏",WindowsWidth/2.083+WindowsHeight/14+WindowsHeight/28,WindowsHeight/2.35,WindowsHeight/12);

		drawChar_To_Texture("选",WindowsWidth/3.083-(WindowsHeight/14-WindowsHeight/28),WindowsHeight/3.35,WindowsHeight/12);
		drawChar_To_Texture("项",WindowsWidth/3.083+(WindowsHeight/14-WindowsHeight/28),WindowsHeight/3.35,WindowsHeight/12);

		drawChar_To_Texture("退",WindowsWidth/1.583-(WindowsHeight/14-WindowsHeight/28),WindowsHeight/3.35,WindowsHeight/12);
		drawChar_To_Texture("出",WindowsWidth/1.583+(WindowsHeight/14-WindowsHeight/28),WindowsHeight/3.35,WindowsHeight/12);

	}else if (GameScrNum==2)
	{
		///////////////////////////////////////////////////////////////////////////
		SetWindowText(hWnd, "游戏设置界面测试");
		int TextureX=0;
		int TextureZ=0;
		int WinWN=WindowsWidth/87+3;
		int WinHN=WindowsHeight/74+3;
		for (int i=-WinWN;i<WinWN;i++)
		{
			for (int j=0;j<WinHN;j++)
			{
				glEnable(GL_BLEND);
				glDisable(GL_DEPTH_TEST);
				glLoadIdentity();							// 重置当前的模型观察矩阵
				glBindTexture(GL_TEXTURE_2D,texture);
				glBegin(GL_QUADS);
				//右前点
				glColor4f(1.0,1.0,1.0,1.0);
				glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
				glVertex3f(i-4,j-4,-7);
				//左前点
				glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
				glVertex3f(i-4,j-5,-7);
				//左后点
				glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
				glVertex3f(i-5,j-5,-7);
				//右后点
				glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
				glVertex3f(i-5,j-4,-7);
				glEnd();
				glEnable(GL_DEPTH_TEST);
			}
		}
		if (backGameBottomInScr2)
		{
			glColor4f(1.0,1.0,1.0,1.0);
			glTexCoord2f(0.0,194.0/256.0);
			glVertex3f(-5.0f, -3.0f, -12.0f);				// 左上
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( 5.0f, -3.0f, -12.0f);				// 右上
			glTexCoord2f(200/256.0,174.0/256.0);
			glVertex3f( 5.0f,-4.0f, -12.0f);				// 右下
			glTexCoord2f(0.0,174.0/256.0);
			glVertex3f(-5.0f,-4.0f, -12.0f);				// 左下
		}else{
			glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0,214.0/256.0);
			glVertex3f(-5.0f, -3.0f, -12.0f);				// 左上
			glTexCoord2f(200/256.0,214.0/256.0);
			glVertex3f( 5.0f, -3.0f, -12.0f);				// 右上
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( 5.0f,-4.0f, -12.0f);				// 右下
			glTexCoord2f(0.0,194.0/256.0);
			glVertex3f(-5.0f,-4.0f, -12.0f);				// 左下
		}
		//////////////////////////////////////////////////////////////////////////
	}

	return TRUE;								//  一切 OK
}