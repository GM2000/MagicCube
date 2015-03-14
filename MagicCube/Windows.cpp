#include "MagicCube.h"
#include "OpenglWindows.h"
#include "Listener.h"
#include "Player.h"
#include "Gobal.h"
#include "Chunk.h"


bool done=FALSE;							// �����˳�ѭ����Bool ����
bool LeftBottom;
bool RightBottom;
bool saving=false;
bool isPause;
bool needShowCursor=true;

int WindowsHeight;
int WindowsWidth;
int GameScrNum;

void LoadChunk();

HANDLE KeyboardListener;
HANDLE gobalListener;
HANDLE WorldRebuild;

int MouseTimer;

GLvoid KillFont(GLvoid);					// ɾ����ʾ�б�

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);				// WndProc�Ķ���

GLvoid KillGLWindow(GLvoid)							// �������ٴ���
{
	if (fullscreen)								// ���Ǵ���ȫ��ģʽ��?
	{
		ChangeDisplaySettings(NULL,0);					// �ǵĻ����л�������
	}
	if (hRC)								// ����ӵ��OpenGL��Ⱦ��������?
	{
		if (!wglMakeCurrent(NULL,NULL))					// �����ܷ��ͷ�DC��RC������?
		{
			MessageBox(NULL,"�ͷ�DC��RCʧ�ܡ�","�رմ���",MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC))					// �����ܷ�ɾ��RC?
		{
			MessageBox(NULL,"�ͷ�RCʧ�ܡ�","�رմ���",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;							// ��RC��Ϊ NULL
	}
	if (hDC && !ReleaseDC(hWnd,hDC))					// �����ܷ��ͷ� DC?
	{
		MessageBox(NULL,"�ͷ�DCʧ�ܡ�","�رմ���",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;							// �� DC ��Ϊ NULL
	}
	if (hWnd && !DestroyWindow(hWnd))					// �ܷ����ٴ���?
	{
		MessageBox(NULL,"�ͷŴ��ھ��ʧ�ܡ�","�رմ���",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;							// �� hWnd ��Ϊ NULL
	}
	if (!UnregisterClass("MagicCube",hInstance))				// �ܷ�ע����?
	{
		MessageBox(NULL,"����ע�������ࡣ","�رմ���",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;							// �� hInstance ��Ϊ NULL
	}
}

LRESULT CALLBACK WndProc(	HWND	hWnd,					// ���ڵľ��
				UINT	uMsg,					// ���ڵ���Ϣ
				WPARAM	wParam,					// ���ӵ���Ϣ����
				LPARAM	lParam)					// ���ӵ���Ϣ����
{
	switch (uMsg)								// ���Windows��Ϣ
	{
		case WM_ACTIVATE:						// ���Ӵ��ڼ�����Ϣ
		{
			if (!HIWORD(wParam))					// �����С��״̬
			{
				active=TRUE;					// �����ڼ���״̬
			}
			else
			{
				active=FALSE;					// �����ټ���
			}
			return 0;						// ������Ϣѭ��
		}
		case WM_SYSCOMMAND:						// ϵͳ�ж�����
		{
			switch (wParam)						// ���ϵͳ����
			{
				case SC_SCREENSAVE:				// ����Ҫ����?
				case SC_MONITORPOWER:				// ��ʾ��Ҫ����ڵ�ģʽ?
				return 0;					// ��ֹ����
			}
			break;							// �˳�
		}
		case WM_CLOSE:							// �յ�Close��Ϣ?
		{
			PostQuitMessage(0);					// �����˳���Ϣ
			return 0;						// ����
		}
		case WM_KEYDOWN:						// �м�����ô?
		{
			if ((wParam==VK_ESCAPE) | (wParam==81))				// ESC ������ô?
			{
				if ((GameScrNum==1) & (FirstLoafFinish))
				{
					isPause=!isPause;				// ESC �����ź�
					ShowCursor(isPause);
					needShowCursor=isPause;
				}else if (GameScrNum==0)
				{
					LeaveGame();
					done=true;
				}
			}
			keys[wParam] = TRUE;					// ����ǣ���ΪTRUE
			return 0;						// ����
		}
		case WM_KEYUP:							// �м��ſ�ô?
		{
			keys[wParam] = FALSE;					// ����ǣ���ΪFALSE
			return 0;						// ����
		}
		case WM_SIZE:							// ����OpenGL���ڴ�С
		{
			WindowsHeight=HIWORD(lParam);
			WindowsWidth=LOWORD(lParam);
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));		// LoWord=Width,HiWord=Height
			return 0;						// ����
		}
		case WM_LBUTTONDOWN:
		{
			player.BreakTime=0;
			MouseTimer=14;
			LBottom=true;
			break;
		}
		case WM_RBUTTONDOWN:
		{
			MouseTimer=14;
			RBottom=true;
			break;
		}
		case WM_LBUTTONUP:
		{
			LBottom=false;
			break;
		}
		case WM_RBUTTONUP:
		{
			RBottom=false;
			break;
		}
		case WM_MOUSEWHEEL:
		{
			int zDelta = (short) HIWORD(wParam); 
			if(zDelta == 120)
			{
				if (player.choiceNumber==0)
				{
					player.choiceNumber=8;
				}else{
					player.choiceNumber-=1;
				}
			}
			if(zDelta == -120)
			{
				if (player.choiceNumber==8)
				{
					player.choiceNumber=0;
				}else{
					player.choiceNumber+=1;
				}
			}
			RBottom=false;
			break;
		}
	}
	// �� DefWindowProc��������δ�������Ϣ��
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	int winWidth = GetSystemMetrics ( SM_CXSCREEN ); 
	int winHeight= GetSystemMetrics ( SM_CYSCREEN );

	GLuint		PixelFormat;						// �������ƥ��Ľ��
	WNDCLASS	wc;							// ������ṹ
	DWORD		dwExStyle;						// ��չ���ڷ��
	DWORD		dwStyle;						// ���ڷ��
	RECT WindowRect;							// ȡ�þ��ε����ϽǺ����½ǵ�����ֵ
	WindowRect.left=(long)0;						// ��Left   ��Ϊ 0
	WindowRect.right=(long)width;						// ��Right  ��ΪҪ��Ŀ��
	WindowRect.top=(long)0;							// ��Top    ��Ϊ 0
	WindowRect.bottom=(long)height;						// ��Bottom ��ΪҪ��ĸ߶�
	fullscreen=fullscreenflag;						// ����ȫ��ȫ����־
	hInstance		= GetModuleHandle(NULL);			// ȡ�����Ǵ��ڵ�ʵ��
	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// �ƶ�ʱ�ػ�����Ϊ����ȡ��DC
	wc.lpfnWndProc		= (WNDPROC) WndProc;				// WndProc������Ϣ
	wc.cbClsExtra		= 0;						// �޶��ⴰ������
	wc.cbWndExtra		= 0;						// �޶��ⴰ������
	wc.hInstance		= hInstance;					// ����ʵ��
	wc.hIcon		= LoadIcon(NULL, IDI_WINLOGO);			// װ��ȱʡͼ��
	wc.hCursor		= LoadCursor(NULL, IDC_ARROW);			// װ�����ָ��
	wc.hbrBackground	= NULL;						// GL����Ҫ����
	wc.lpszMenuName		= NULL;						// ����Ҫ�˵�
	wc.lpszClassName	= "MagicCube";					// �趨������
	if (!RegisterClass(&wc))						// ����ע�ᴰ����
	{
		MessageBox(NULL,"ע�ᴰ��ʧ��","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// �˳�������FALSE
	}

	if (fullscreen)								// Ҫ����ȫ��ģʽ��?
	{
		DEVMODE dmScreenSettings;						// �豸ģʽ
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));			// ȷ���ڴ����Ϊ��
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);			// Devmode �ṹ�Ĵ�С
		dmScreenSettings.dmPelsWidth	= width;				// ��ѡ��Ļ���
		dmScreenSettings.dmPelsHeight	= height;				// ��ѡ��Ļ�߶�
		dmScreenSettings.dmBitsPerPel	= bits;					// ÿ������ѡ��ɫ�����
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
		// ����������ʾģʽ�����ؽ����ע: CDS_FULLSCREEN ��ȥ��״̬����
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// ��ģʽʧ�ܣ��ṩ����ѡ��˳����ڴ��������С�
			if (MessageBox(NULL,"ȫ��ģʽ�ڵ�ǰ�Կ�������ʧ�ܣ�\nʹ�ô���ģʽ��","NeHe G",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;				// ѡ�񴰿�ģʽ(Fullscreen=FALSE)
			}
			else
			{
				// ����һ���Ի��򣬸����û��������
				MessageBox(NULL,"���򽫱��ر�","����",MB_OK|MB_ICONSTOP);
				return FALSE;					//  �˳������� FALSE
			}
		}
	}
	if (fullscreen)								// �Դ���ȫ��ģʽ��?
	{
		dwExStyle=WS_EX_APPWINDOW;					// ��չ������
		dwStyle=WS_POPUP;						// ������
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// ��չ������
		dwStyle=WS_OVERLAPPEDWINDOW;					//  ������
	}
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// �������ڴﵽ����Ҫ��Ĵ�С
	int winX=winWidth/2-width/2,WinY=winHeight/2-height/2;
	if (fullscreen)
	{
		winX=0;
		WinY=0;
	}
	if (!(hWnd=CreateWindowEx(	dwExStyle,				// ��չ������
					"MagicCube",				// ������
					title,					// ���ڱ���
					WS_CLIPSIBLINGS |			// ����Ĵ���������
					WS_CLIPCHILDREN |			// ����Ĵ���������
					dwStyle,				// ѡ��Ĵ�������
					winX, WinY,					// ����λ��
					WindowRect.right-WindowRect.left,	// ��������õĴ��ڿ��
					WindowRect.bottom-WindowRect.top,	// ��������õĴ��ڸ߶�
					NULL,					// �޸�����
					NULL,					// �޲˵�
					hInstance,				// ʵ��
					NULL)))					// ����WM_CREATE�����κζ���
	{
		KillGLWindow();							// ������ʾ��
		MessageBox(NULL,"���ܴ���һ�������豸������","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// ���� FALSE
	}
	static	PIXELFORMATDESCRIPTOR pfd=					// /pfd ���ߴ���������ϣ���Ķ�����������ʹ�õ����ظ�ʽ
	{
		sizeof(PIXELFORMATDESCRIPTOR),					// ������ʽ�������Ĵ�С
		1,								// �汾��
		PFD_DRAW_TO_WINDOW |						// ��ʽ֧�ִ���
		PFD_SUPPORT_OPENGL |						// ��ʽ����֧��OpenGL
		PFD_DOUBLEBUFFER,						// ����֧��˫����
		PFD_TYPE_RGBA,							// ���� RGBA ��ʽ
		bits,								// ѡ��ɫ�����
		0, 0, 0, 0, 0, 0,						// ���Ե�ɫ��λ
		0,								// ��Alpha����
		0,								// ����Shift Bit
		0,								// ���ۼӻ���
		0, 0, 0, 0,							// ���Ծۼ�λ
		16,								// 16λ Z-���� (��Ȼ���)
		0,								// ���ɰ建��
		0,								// �޸�������
		PFD_MAIN_PLANE,							// ����ͼ��
		0,								// Reserved
		0, 0, 0								// ���Բ�����
	};
	if (!(hDC=GetDC(hWnd)))							// ȡ���豸��������ô?
	{
		KillGLWindow();							// ������ʾ��
		MessageBox(NULL,"���ܴ���һ����ƥ������ظ�ʽ","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// ���� FALSE
	}
	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))				// Windows �ҵ���Ӧ�����ظ�ʽ����?
	{
		KillGLWindow();							// ������ʾ��
		MessageBox(NULL,"�����������ظ�ʽ","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// ���� FALSE
	}
	if(!SetPixelFormat(hDC,PixelFormat,&pfd))				// �ܹ��������ظ�ʽô?
	{
		KillGLWindow();							// ������ʾ��
		MessageBox(NULL,"�����������ظ�ʽ","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// ���� FALSE
	}
	if (!(hRC=wglCreateContext(hDC)))					// �ܷ�ȡ����ɫ������?
	{
		KillGLWindow();							// ������ʾ��
		MessageBox(NULL,"���ܴ���OpenGL��Ⱦ������","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// ���� FALSE
	}
	if(!wglMakeCurrent(hDC,hRC))						// ���Լ�����ɫ������
	{
		KillGLWindow();							// ������ʾ��
		MessageBox(NULL,"���ܼ��ǰ��OpenGL��Ȼ������","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// ���� FALSE
	}
	ShowWindow(hWnd,SW_SHOW);						// ��ʾ����
	SetForegroundWindow(hWnd);						// ����������ȼ�
	SetFocus(hWnd);								// ���ü��̵Ľ������˴���
	ReSizeGLScene(width, height);						// ����͸�� GL ��Ļ
	if (!InitGL())								// ��ʼ���½���GL����
	{
		KillGLWindow();							// ������ʾ��
		MessageBox(NULL,"��ʼ��Opengl����","����",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// ���� FALSE
	}
	return TRUE;								// �ɹ�
}

int WINAPI WinMain(	HINSTANCE	hInstance,				// ��ǰ����ʵ��
			HINSTANCE	hPrevInstance,				// ǰһ������ʵ��
			LPSTR		lpCmdLine,				// �����в���
			int		nCmdShow)				// ������ʾ״̬
{
	int winWidth = GetSystemMetrics ( SM_CXSCREEN ); 
	int winHeight= GetSystemMetrics ( SM_CYSCREEN ); 

	MSG	msg;								// Windowsx��Ϣ�ṹ
	// ��ʾ�û�ѡ������ģʽ
	if (MessageBox(NULL,"������ȫ��ģʽ������ô��", "����ȫ��ģʽ",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;						// FALSEΪ����ģʽ
	}
	// ����OpenGL����
	if (fullscreen)
	{
		if (!CreateGLWindow(MCTitle MCVersion,winWidth,winHeight,16,fullscreen))//��������
			return 0;				// �������δ�ܴ����������˳�
	}else{
		if (!CreateGLWindow(MCTitle MCVersion,870,518,16,fullscreen))//��������
			return 0;				// �������δ�ܴ����������˳�
	}

	isPause=false;

	gobalListener=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GobalListener,NULL,0,NULL);

	KeyboardListener=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)KeyBoardListener,NULL,0,NULL);

	WorldRebuild=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)LoadChunk,NULL,0,NULL);

	while(!done)								// ����ѭ��ֱ�� done=TRUE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))			// ����Ϣ�ڵȴ���?
		{

			if (msg.message==WM_QUIT)				// �յ��˳���Ϣ?
			{
				if (GameScrNum==1)
				{
					LeaveGame();
				}
				done=TRUE;					// �ǣ���done=TRUE
			}
			else							// ���ǣ���������Ϣ
			{
				TranslateMessage(&msg);				// ������Ϣ
				DispatchMessage(&msg);				// ������Ϣ
			}
		}
		else								// ���û����Ϣ
		{
			// ���Ƴ���������ESC��������DrawGLScene()���˳���Ϣ
			if (active)						// ���򼤻��ô?
			{
				DrawGLScene();				// ���Ƴ���
				SwapBuffers(hDC);			// �������� (˫����)
			}
			if (keys[VK_F11])					// F1��������ô?
			{
				keys[VK_F11]=FALSE;				// ���ǣ�ʹ��Ӧ��Key�����е�ֵΪ FALSE
				KillGLWindow();					// ���ٵ�ǰ�Ĵ���
				fullscreen=!fullscreen;				// �л� ȫ�� / ���� ģʽ
				// �ؽ� OpenGL ����
				if (fullscreen)
				{
					int winWidth = GetSystemMetrics ( SM_CXSCREEN ); 
					int winHeight= GetSystemMetrics ( SM_CYSCREEN ); 

					if (!CreateGLWindow(MCTitle MCVersion,winWidth,winHeight,16,fullscreen))//��������
						done=true;				// �������δ�ܴ����������˳�
				}else{
					if (!CreateGLWindow(MCTitle MCVersion,870,518,16,fullscreen))//��������
						done=true;				// �������δ�ܴ����������˳�
				}
			}
			if (MouseTimer>13)
			{
				MouseEvent();
				MouseTimer=0;
			}
		}
	}
	// �رճ���
	KillGLWindow();								// ���ٴ���
	ShowCursor(true);						// ��ʾ���ָ��
	return (msg.wParam);							// �˳�����
}