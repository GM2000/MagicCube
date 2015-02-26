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
	glLoadIdentity();							// ���õ�ǰ��ģ�͹۲����
	glBindTexture(GL_TEXTURE_2D,toolbar);				// ѡ������
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
	glBindTexture(GL_TEXTURE_2D, texture);				// ѡ������
	glBegin(GL_QUADS);							//  ���ƹ�����ѡ���
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
	glLoadIdentity();							// ���õ�ǰ��ģ�͹۲����
	glBindTexture(GL_TEXTURE_2D, toolbar);				// ѡ������
	glBegin(GL_QUADS);							//  ���ƹ�����
	glTexCoord2f(0.0f, 236/256.0f); glVertex3f(-0.041f, -0.0413f,-0.1f);	// ������ı��ε�����
	glTexCoord2f(180/256.0f, 236/256.0f); glVertex3f(0.041f, -0.0413f,-0.1f);	// ������ı��ε�����
	glTexCoord2f(180/256.0f, 1.0f); glVertex3f(0.041f,-0.0322f,-0.1f);	// ������ı��ε�����
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.041f,-0.0322f,-0.1f);	// ������ı��ε�����
	glEnd();	

	glBindTexture(GL_TEXTURE_2D, toolbar);				// ѡ������
	glBegin(GL_QUADS);							//  ���ƹ�����ѡ���
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
			if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))			// ����Ϣ�ڵȴ���?
			{
				if (msg.message==WM_QUIT)				// �յ��˳���Ϣ?
				{
					done=TRUE;					// �ǣ���done=TRUE
				}
				else							// ���ǣ���������Ϣ
				{
					TranslateMessage(&msg);				// ������Ϣ
					DispatchMessage(&msg);				// ������Ϣ
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
int DrawGLScene(GLvoid)								// �����￪ʼ�������еĻ���
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// �����Ļ����Ȼ���
	if (GameScrNum==1)
	{
		if ((FirstLoafFinish) & (!saving))
		{
			float startTime = GetTickCount()*0.001f;

			glLoadIdentity();							// ���õ�ǰ��ģ�͹۲����
			glRotatef(player.upanddown,1,0,0);
			glTranslatef(shakingDegX/3,shakingDegY/3,0);						        // �����ƶ�
			glRotatef(player.around,0,1,0);
			glTranslatef(-player.x,-player.y,-player.z);						        // �����ƶ�
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
					glLoadIdentity();							// ���õ�ǰ��ģ�͹۲����
					glBindTexture(GL_TEXTURE_2D,texture);
					glBegin(GL_QUADS);
					//��ǰ��
					glColor4f(1.0,1.0,1.0,1.0);
					glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
					glVertex3f(i-4,j-4,-7);
					//��ǰ��
					glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
					glVertex3f(i-4,j-5,-7);
					//����
					glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
					glVertex3f(i-5,j-5,-7);
					//�Һ��
					glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
					glVertex3f(i-5,j-4,-7);
					glEnd();
					glEnable(GL_DEPTH_TEST);
				}
			}
			glDisable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);
			//��ǰ��
			glColor3f(1.0,1.0,1.0);
			glVertex3f(-1.5,0,-7);
			//��ǰ��
			glVertex3f(1.5,0,-7);
			//����
			glVertex3f(1.5,-0.1,-7);
			//�Һ��
			glVertex3f(-1.5,-0.1,-7);
			glEnd();
			glBegin(GL_QUADS);
			//��ǰ��
			glColor3f(0.0,1.0,0.0);
			glVertex3f(-1.5,0,-7);
			//��ǰ��
			glVertex3f(-1.5+3*loadPrecent/100.0,0,-7);
			//����
			glVertex3f(-1.5+3*loadPrecent/100.0,-0.1,-7);
			//�Һ��
			glVertex3f(-1.5,-0.1,-7);
			glEnd();
			glEnable(GL_TEXTURE_2D);
			drawChar_To_Texture("��",WindowsWidth/2.083-WindowsHeight/14-WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
			drawChar_To_Texture("��",WindowsWidth/2.083-WindowsHeight/14+WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
			drawChar_To_Texture("��",WindowsWidth/2.083+WindowsHeight/14-WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
			drawChar_To_Texture("ͼ",WindowsWidth/2.083+WindowsHeight/14+WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
		}

		if (isPause)
		{
			glBindTexture(GL_TEXTURE_2D,toolbar);

			glEnable(GL_BLEND);
			glDisable(GL_DEPTH_TEST);
			glLoadIdentity();							// ���õ�ǰ��ģ�͹۲����
			glBegin(GL_QUADS);
			glColor4f(0.3,0.3,0.3,0.3);
			glVertex3f(-1.0f, 1.0f, -1.0f);				// ����
			glVertex3f( 1.0f, 1.0f, -1.0f);				// ����
			glVertex3f( 1.0f,-1.0f, -1.0f);				// ����
			glVertex3f(-1.0f,-1.0f, -1.0f);				// ����

			if (exitGameBottomInScr1)
			{
				glColor4f(1.0,1.0,1.0,1.0);
				glTexCoord2f(0.0,194.0/256.0);
				glVertex3f(-5.0f, -1.25f, -12.0f);				// ����
				glTexCoord2f(200/256.0,194.0/256.0);
				glVertex3f( 5.0f, -1.25f, -12.0f);				// ����
				glTexCoord2f(200/256.0,174.0/256.0);
				glVertex3f( 5.0f,-2.25f, -12.0f);				// ����
				glTexCoord2f(0.0,174.0/256.0);
				glVertex3f(-5.0f,-2.25f, -12.0f);				// ����
			}else{
				glColor3f(1.0f,1.0f,1.0f);
				glTexCoord2f(0.0,214.0/256.0);
				glVertex3f(-5.0f, -1.25f, -12.0f);				// ����
				glTexCoord2f(200/256.0,214.0/256.0);
				glVertex3f( 5.0f, -1.25f, -12.0f);				// ����
				glTexCoord2f(200/256.0,194.0/256.0);
				glVertex3f( 5.0f,-2.25f, -12.0f);				// ����
				glTexCoord2f(0.0,194.0/256.0);
				glVertex3f(-5.0f,-2.25f, -12.0f);				// ����
			}
			if (backGameBottomInScr1)
			{
				glColor4f(1.0,1.0,1.0,1.0);
				glTexCoord2f(0.0,194.0/256.0);
				glVertex3f(-5.0f, 1.5f, -12.0f);				// ����
				glTexCoord2f(200/256.0,194.0/256.0);
				glVertex3f( 5.0f, 1.5f, -12.0f);				// ����
				glTexCoord2f(200/256.0,174.0/256.0);
				glVertex3f( 5.0f,0.5f, -12.0f);				// ����
				glTexCoord2f(0.0,174.0/256.0);
				glVertex3f(-5.0f,0.5f, -12.0f);				// ����
			}else{
				glColor3f(1.0f,1.0f,1.0f);
				glTexCoord2f(0.0,214.0/256.0);
				glVertex3f(-5.0f, 1.5f, -12.0f);				// ����
				glTexCoord2f(200/256.0,214.0/256.0);
				glVertex3f( 5.0f, 1.5f, -12.0f);				// ����
				glTexCoord2f(200/256.0,194.0/256.0);
				glVertex3f( 5.0f,0.5f, -12.0f);				// ����
				glTexCoord2f(0.0,194.0/256.0);
				glVertex3f(-5.0f,0.5f, -12.0f);				// ����
			}
			glEnd();

			glTranslatef(0,0,-1);

			drawChar_To_Texture("��",WindowsWidth/2.083-WindowsHeight/14-WindowsHeight/28,WindowsHeight/3.35,WindowsHeight/12);
			drawChar_To_Texture("��",WindowsWidth/2.083-WindowsHeight/14+WindowsHeight/28,WindowsHeight/3.35,WindowsHeight/12);
			drawChar_To_Texture("��",WindowsWidth/2.083+WindowsHeight/14-WindowsHeight/28,WindowsHeight/3.35,WindowsHeight/12);
			drawChar_To_Texture("Ϸ",WindowsWidth/2.083+WindowsHeight/14+WindowsHeight/28,WindowsHeight/3.35,WindowsHeight/12);

			drawChar_To_Texture("��",WindowsWidth/2.083-WindowsHeight/14-WindowsHeight/28,WindowsHeight/1.73,WindowsHeight/12);
			drawChar_To_Texture("��",WindowsWidth/2.083-WindowsHeight/14+WindowsHeight/28,WindowsHeight/1.73,WindowsHeight/12);
			drawChar_To_Texture("��",WindowsWidth/2.083+WindowsHeight/14-WindowsHeight/28,WindowsHeight/1.73,WindowsHeight/12);
			drawChar_To_Texture("Ϸ",WindowsWidth/2.083+WindowsHeight/14+WindowsHeight/28,WindowsHeight/1.73,WindowsHeight/12);

			glEnable(GL_DEPTH_TEST);
		}

		if (saving)
		{
			SetWindowText(hWnd, "��Ϸ����������");
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
					glLoadIdentity();							// ���õ�ǰ��ģ�͹۲����
					glBindTexture(GL_TEXTURE_2D,texture);
					glBegin(GL_QUADS);
					//��ǰ��
					glColor4f(1.0,1.0,1.0,1.0);
					glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
					glVertex3f(i-4,j-4,-7);
					//��ǰ��
					glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
					glVertex3f(i-4,j-5,-7);
					//����
					glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
					glVertex3f(i-5,j-5,-7);
					//�Һ��
					glTexCoord2f((TextureX+1.0)/16,(16.0-TextureZ)/16);
					glVertex3f(i-5,j-4,-7);
					glEnd();
					glEnable(GL_DEPTH_TEST);
				}
			}
			drawChar_To_Texture("��",WindowsWidth/2.083-WindowsHeight/14-WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
			drawChar_To_Texture("��",WindowsWidth/2.083-WindowsHeight/14+WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
			drawChar_To_Texture("��",WindowsWidth/2.083+WindowsHeight/14-WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
			drawChar_To_Texture("ͼ",WindowsWidth/2.083+WindowsHeight/14+WindowsHeight/28,WindowsHeight/1.9,WindowsHeight/12);
		}
	}else if (GameScrNum==0){
		SetWindowText(hWnd, "��Ϸ��ʼ�������");
		glLoadIdentity();							// ���õ�ǰ��ģ�͹۲����
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_ALPHA_TEST);
		//LOGO
		glBindTexture(GL_TEXTURE_2D,logo);
		glBegin(GL_QUADS);
		glColor4f(1.0,1.0,1.0,1.0);
		glTexCoord2f(0.0,1.0);
		glVertex3f(-7.0f, 4.0f, -12.0f);				// ����
		glTexCoord2f(1.0,1.0);
		glVertex3f( 7.0f, 4.0f, -12.0f);				// ����
		glTexCoord2f(1.0,0.0);
		glVertex3f( 7.0f,1.0f, -12.0f);				// ����
		glTexCoord2f(0.0,0.0);
		glVertex3f(-7.0f,1.0f, -12.0f);				// ����
		glEnd();


		glBindTexture(GL_TEXTURE_2D,toolbar);
		glLoadIdentity();							// ���õ�ǰ��ģ�͹۲����
		glBegin(GL_QUADS);
		//��ʼ��Ϸ
		if (startGameBottomInScr0)
		{
			glColor4f(1.0,1.0,1.0,1.0);
			glTexCoord2f(0.0,194.0/256.0);
			glVertex3f(-5.0f, 0.0f, -12.0f);				// ����
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( 5.0f, 0.0f, -12.0f);				// ����
			glTexCoord2f(200/256.0,174.0/256.0);
			glVertex3f( 5.0f,-1.0f, -12.0f);				// ����
			glTexCoord2f(0.0,174.0/256.0);
			glVertex3f(-5.0f,-1.0f, -12.0f);				// ����
		}else{
			glColor4f(1.0,1.0,1.0,1.0);
			glTexCoord2f(0.0,214.0/256.0);
			glVertex3f(-5.0f, 0.0f, -12.0f);				// ����
			glTexCoord2f(200/256.0,214.0/256.0);
			glVertex3f( 5.0f, 0.0f, -12.0f);				// ����
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( 5.0f,-1.0f, -12.0f);				// ����
			glTexCoord2f(0.0,194.0/256.0);
			glVertex3f(-5.0f,-1.0f, -12.0f);				// ����
		}
		//�˳�
		if (exitGameBottomInScr0)
		{
			glTexCoord2f(0.0,194.0/256.0);
			glVertex3f( 0.25f, -1.25f, -12.0f);				// ����
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( 5.0f, -1.25f, -12.0f);				// ����
			glTexCoord2f(200/256.0,174.0/256.0);
			glVertex3f( 5.0f,-2.25f, -12.0f);				// ����
			glTexCoord2f(0.0,174.0/256.0);
			glVertex3f( 0.25f,-2.25f, -12.0f);				// ����
		}else{
			glTexCoord2f(0.0,214.0/256.0);
			glVertex3f( 0.25f, -1.25f, -12.0f);				// ����
			glTexCoord2f(200/256.0,214.0/256.0);
			glVertex3f( 5.0f, -1.25f, -12.0f);				// ����
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( 5.0f,-2.25f, -12.0f);				// ����
			glTexCoord2f(0.0,194.0/256.0);
			glVertex3f( 0.25f,-2.25f, -12.0f);				// ����
		}
		//ѡ��
		if (settingBottomInScr0)
		{
			glTexCoord2f(0.0,194.0/256.0);
			glVertex3f( -5.0f, -1.25f, -12.0f);				// ����
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( -0.25f, -1.25f, -12.0f);				// ����
			glTexCoord2f(200/256.0,174.0/256.0);
			glVertex3f( -0.25f,-2.25f, -12.0f);				// ����
			glTexCoord2f(0.0,174.0/256.0);
			glVertex3f( -5.0f,-2.25f, -12.0f);				// ����
		}else{
			glTexCoord2f(0.0,214.0/256.0);
			glVertex3f( -5.0f, -1.25f, -12.0f);				// ����
			glTexCoord2f(200/256.0,214.0/256.0);
			glVertex3f( -0.25f, -1.25f, -12.0f);				// ����
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( -0.25f,-2.25f, -12.0f);				// ����
			glTexCoord2f(0.0,194.0/256.0);
			glVertex3f( -5.0f,-2.25f, -12.0f);				// ����
		}
		glEnd();

		drawChar_To_Texture("��",WindowsWidth/2.083-WindowsHeight/14-WindowsHeight/28,WindowsHeight/2.35,WindowsHeight/12);
		drawChar_To_Texture("ʼ",WindowsWidth/2.083-WindowsHeight/14+WindowsHeight/28,WindowsHeight/2.35,WindowsHeight/12);
		drawChar_To_Texture("��",WindowsWidth/2.083+WindowsHeight/14-WindowsHeight/28,WindowsHeight/2.35,WindowsHeight/12);
		drawChar_To_Texture("Ϸ",WindowsWidth/2.083+WindowsHeight/14+WindowsHeight/28,WindowsHeight/2.35,WindowsHeight/12);

		drawChar_To_Texture("ѡ",WindowsWidth/3.083-(WindowsHeight/14-WindowsHeight/28),WindowsHeight/3.35,WindowsHeight/12);
		drawChar_To_Texture("��",WindowsWidth/3.083+(WindowsHeight/14-WindowsHeight/28),WindowsHeight/3.35,WindowsHeight/12);

		drawChar_To_Texture("��",WindowsWidth/1.583-(WindowsHeight/14-WindowsHeight/28),WindowsHeight/3.35,WindowsHeight/12);
		drawChar_To_Texture("��",WindowsWidth/1.583+(WindowsHeight/14-WindowsHeight/28),WindowsHeight/3.35,WindowsHeight/12);

	}else if (GameScrNum==2)
	{
		///////////////////////////////////////////////////////////////////////////
		SetWindowText(hWnd, "��Ϸ���ý������");
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
				glLoadIdentity();							// ���õ�ǰ��ģ�͹۲����
				glBindTexture(GL_TEXTURE_2D,texture);
				glBegin(GL_QUADS);
				//��ǰ��
				glColor4f(1.0,1.0,1.0,1.0);
				glTexCoord2f(TextureX/16.0,(16.0-TextureZ)/16);
				glVertex3f(i-4,j-4,-7);
				//��ǰ��
				glTexCoord2f(TextureX/16.0,(15.0-TextureZ)/16);
				glVertex3f(i-4,j-5,-7);
				//����
				glTexCoord2f((TextureX+1.0)/16,(15.0-TextureZ)/16);
				glVertex3f(i-5,j-5,-7);
				//�Һ��
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
			glVertex3f(-5.0f, -3.0f, -12.0f);				// ����
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( 5.0f, -3.0f, -12.0f);				// ����
			glTexCoord2f(200/256.0,174.0/256.0);
			glVertex3f( 5.0f,-4.0f, -12.0f);				// ����
			glTexCoord2f(0.0,174.0/256.0);
			glVertex3f(-5.0f,-4.0f, -12.0f);				// ����
		}else{
			glColor3f(1.0f,1.0f,1.0f);
			glTexCoord2f(0.0,214.0/256.0);
			glVertex3f(-5.0f, -3.0f, -12.0f);				// ����
			glTexCoord2f(200/256.0,214.0/256.0);
			glVertex3f( 5.0f, -3.0f, -12.0f);				// ����
			glTexCoord2f(200/256.0,194.0/256.0);
			glVertex3f( 5.0f,-4.0f, -12.0f);				// ����
			glTexCoord2f(0.0,194.0/256.0);
			glVertex3f(-5.0f,-4.0f, -12.0f);				// ����
		}
		//////////////////////////////////////////////////////////////////////////
	}

	return TRUE;								//  һ�� OK
}