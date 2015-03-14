#include "MagicCube.h"
#include "OpenglWindows.h"
#include "Listener.h"
#include "Player.h"
#include "Gobal.h"
#include "Chunk.h"


bool done=FALSE;							// 用来退出循环的Bool 变量
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

GLvoid KillFont(GLvoid);					// 删除显示列表

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);				// WndProc的定义

GLvoid KillGLWindow(GLvoid)							// 正常销毁窗口
{
	if (fullscreen)								// 我们处于全屏模式吗?
	{
		ChangeDisplaySettings(NULL,0);					// 是的话，切换回桌面
	}
	if (hRC)								// 我们拥有OpenGL渲染描述表吗?
	{
		if (!wglMakeCurrent(NULL,NULL))					// 我们能否释放DC和RC描述表?
		{
			MessageBox(NULL,"释放DC或RC失败。","关闭错误",MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC))					// 我们能否删除RC?
		{
			MessageBox(NULL,"释放RC失败。","关闭错误",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;							// 将RC设为 NULL
	}
	if (hDC && !ReleaseDC(hWnd,hDC))					// 我们能否释放 DC?
	{
		MessageBox(NULL,"释放DC失败。","关闭错误",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;							// 将 DC 设为 NULL
	}
	if (hWnd && !DestroyWindow(hWnd))					// 能否销毁窗口?
	{
		MessageBox(NULL,"释放窗口句柄失败。","关闭错误",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;							// 将 hWnd 设为 NULL
	}
	if (!UnregisterClass("MagicCube",hInstance))				// 能否注销类?
	{
		MessageBox(NULL,"不能注销窗口类。","关闭错误",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;							// 将 hInstance 设为 NULL
	}
}

LRESULT CALLBACK WndProc(	HWND	hWnd,					// 窗口的句柄
				UINT	uMsg,					// 窗口的消息
				WPARAM	wParam,					// 附加的消息内容
				LPARAM	lParam)					// 附加的消息内容
{
	switch (uMsg)								// 检查Windows消息
	{
		case WM_ACTIVATE:						// 监视窗口激活消息
		{
			if (!HIWORD(wParam))					// 检查最小化状态
			{
				active=TRUE;					// 程序处于激活状态
			}
			else
			{
				active=FALSE;					// 程序不再激活
			}
			return 0;						// 返回消息循环
		}
		case WM_SYSCOMMAND:						// 系统中断命令
		{
			switch (wParam)						// 检查系统调用
			{
				case SC_SCREENSAVE:				// 屏保要运行?
				case SC_MONITORPOWER:				// 显示器要进入节电模式?
				return 0;					// 阻止发生
			}
			break;							// 退出
		}
		case WM_CLOSE:							// 收到Close消息?
		{
			PostQuitMessage(0);					// 发出退出消息
			return 0;						// 返回
		}
		case WM_KEYDOWN:						// 有键按下么?
		{
			if ((wParam==VK_ESCAPE) | (wParam==81))				// ESC 按下了么?
			{
				if ((GameScrNum==1) & (FirstLoafFinish))
				{
					isPause=!isPause;				// ESC 发出信号
					ShowCursor(isPause);
					needShowCursor=isPause;
				}else if (GameScrNum==0)
				{
					LeaveGame();
					done=true;
				}
			}
			keys[wParam] = TRUE;					// 如果是，设为TRUE
			return 0;						// 返回
		}
		case WM_KEYUP:							// 有键放开么?
		{
			keys[wParam] = FALSE;					// 如果是，设为FALSE
			return 0;						// 返回
		}
		case WM_SIZE:							// 调整OpenGL窗口大小
		{
			WindowsHeight=HIWORD(lParam);
			WindowsWidth=LOWORD(lParam);
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));		// LoWord=Width,HiWord=Height
			return 0;						// 返回
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
	// 向 DefWindowProc传递所有未处理的消息。
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	int winWidth = GetSystemMetrics ( SM_CXSCREEN ); 
	int winHeight= GetSystemMetrics ( SM_CYSCREEN );

	GLuint		PixelFormat;						// 保存查找匹配的结果
	WNDCLASS	wc;							// 窗口类结构
	DWORD		dwExStyle;						// 扩展窗口风格
	DWORD		dwStyle;						// 窗口风格
	RECT WindowRect;							// 取得矩形的左上角和右下角的坐标值
	WindowRect.left=(long)0;						// 将Left   设为 0
	WindowRect.right=(long)width;						// 将Right  设为要求的宽度
	WindowRect.top=(long)0;							// 将Top    设为 0
	WindowRect.bottom=(long)height;						// 将Bottom 设为要求的高度
	fullscreen=fullscreenflag;						// 设置全局全屏标志
	hInstance		= GetModuleHandle(NULL);			// 取得我们窗口的实例
	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// 移动时重画，并为窗口取得DC
	wc.lpfnWndProc		= (WNDPROC) WndProc;				// WndProc处理消息
	wc.cbClsExtra		= 0;						// 无额外窗口数据
	wc.cbWndExtra		= 0;						// 无额外窗口数据
	wc.hInstance		= hInstance;					// 设置实例
	wc.hIcon		= LoadIcon(NULL, IDI_WINLOGO);			// 装入缺省图标
	wc.hCursor		= LoadCursor(NULL, IDC_ARROW);			// 装入鼠标指针
	wc.hbrBackground	= NULL;						// GL不需要背景
	wc.lpszMenuName		= NULL;						// 不需要菜单
	wc.lpszClassName	= "MagicCube";					// 设定类名字
	if (!RegisterClass(&wc))						// 尝试注册窗口类
	{
		MessageBox(NULL,"注册窗口失败","错误",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// 退出并返回FALSE
	}

	if (fullscreen)								// 要尝试全屏模式吗?
	{
		DEVMODE dmScreenSettings;						// 设备模式
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));			// 确保内存清空为零
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);			// Devmode 结构的大小
		dmScreenSettings.dmPelsWidth	= width;				// 所选屏幕宽度
		dmScreenSettings.dmPelsHeight	= height;				// 所选屏幕高度
		dmScreenSettings.dmBitsPerPel	= bits;					// 每象素所选的色彩深度
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
		// 尝试设置显示模式并返回结果。注: CDS_FULLSCREEN 移去了状态条。
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// 若模式失败，提供两个选项：退出或在窗口内运行。
			if (MessageBox(NULL,"全屏模式在当前显卡上设置失败！\n使用窗口模式？","NeHe G",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;				// 选择窗口模式(Fullscreen=FALSE)
			}
			else
			{
				// 弹出一个对话框，告诉用户程序结束
				MessageBox(NULL,"程序将被关闭","错误",MB_OK|MB_ICONSTOP);
				return FALSE;					//  退出并返回 FALSE
			}
		}
	}
	if (fullscreen)								// 仍处于全屏模式吗?
	{
		dwExStyle=WS_EX_APPWINDOW;					// 扩展窗体风格
		dwStyle=WS_POPUP;						// 窗体风格
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// 扩展窗体风格
		dwStyle=WS_OVERLAPPEDWINDOW;					//  窗体风格
	}
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// 调整窗口达到真正要求的大小
	int winX=winWidth/2-width/2,WinY=winHeight/2-height/2;
	if (fullscreen)
	{
		winX=0;
		WinY=0;
	}
	if (!(hWnd=CreateWindowEx(	dwExStyle,				// 扩展窗体风格
					"MagicCube",				// 类名字
					title,					// 窗口标题
					WS_CLIPSIBLINGS |			// 必须的窗体风格属性
					WS_CLIPCHILDREN |			// 必须的窗体风格属性
					dwStyle,				// 选择的窗体属性
					winX, WinY,					// 窗口位置
					WindowRect.right-WindowRect.left,	// 计算调整好的窗口宽度
					WindowRect.bottom-WindowRect.top,	// 计算调整好的窗口高度
					NULL,					// 无父窗口
					NULL,					// 无菜单
					hInstance,				// 实例
					NULL)))					// 不向WM_CREATE传递任何东东
	{
		KillGLWindow();							// 重置显示区
		MessageBox(NULL,"不能创建一个窗口设备描述表","错误",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// 返回 FALSE
	}
	static	PIXELFORMATDESCRIPTOR pfd=					// /pfd 告诉窗口我们所希望的东东，即窗口使用的像素格式
	{
		sizeof(PIXELFORMATDESCRIPTOR),					// 上述格式描述符的大小
		1,								// 版本号
		PFD_DRAW_TO_WINDOW |						// 格式支持窗口
		PFD_SUPPORT_OPENGL |						// 格式必须支持OpenGL
		PFD_DOUBLEBUFFER,						// 必须支持双缓冲
		PFD_TYPE_RGBA,							// 申请 RGBA 格式
		bits,								// 选定色彩深度
		0, 0, 0, 0, 0, 0,						// 忽略的色彩位
		0,								// 无Alpha缓存
		0,								// 忽略Shift Bit
		0,								// 无累加缓存
		0, 0, 0, 0,							// 忽略聚集位
		16,								// 16位 Z-缓存 (深度缓存)
		0,								// 无蒙板缓存
		0,								// 无辅助缓存
		PFD_MAIN_PLANE,							// 主绘图层
		0,								// Reserved
		0, 0, 0								// 忽略层遮罩
	};
	if (!(hDC=GetDC(hWnd)))							// 取得设备描述表了么?
	{
		KillGLWindow();							// 重置显示区
		MessageBox(NULL,"不能创建一种相匹配的像素格式","错误",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// 返回 FALSE
	}
	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))				// Windows 找到相应的象素格式了吗?
	{
		KillGLWindow();							// 重置显示区
		MessageBox(NULL,"不能设置像素格式","错误",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// 返回 FALSE
	}
	if(!SetPixelFormat(hDC,PixelFormat,&pfd))				// 能够设置象素格式么?
	{
		KillGLWindow();							// 重置显示区
		MessageBox(NULL,"不能设置像素格式","错误",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// 返回 FALSE
	}
	if (!(hRC=wglCreateContext(hDC)))					// 能否取得着色描述表?
	{
		KillGLWindow();							// 重置显示区
		MessageBox(NULL,"不能创建OpenGL渲染描述表","错误",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// 返回 FALSE
	}
	if(!wglMakeCurrent(hDC,hRC))						// 尝试激活着色描述表
	{
		KillGLWindow();							// 重置显示区
		MessageBox(NULL,"不能激活当前的OpenGL渲然描述表","错误",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// 返回 FALSE
	}
	ShowWindow(hWnd,SW_SHOW);						// 显示窗口
	SetForegroundWindow(hWnd);						// 略略提高优先级
	SetFocus(hWnd);								// 设置键盘的焦点至此窗口
	ReSizeGLScene(width, height);						// 设置透视 GL 屏幕
	if (!InitGL())								// 初始化新建的GL窗口
	{
		KillGLWindow();							// 重置显示区
		MessageBox(NULL,"初始化Opengl错误","错误",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// 返回 FALSE
	}
	return TRUE;								// 成功
}

int WINAPI WinMain(	HINSTANCE	hInstance,				// 当前窗口实例
			HINSTANCE	hPrevInstance,				// 前一个窗口实例
			LPSTR		lpCmdLine,				// 命令行参数
			int		nCmdShow)				// 窗口显示状态
{
	int winWidth = GetSystemMetrics ( SM_CXSCREEN ); 
	int winHeight= GetSystemMetrics ( SM_CYSCREEN ); 

	MSG	msg;								// Windowsx消息结构
	// 提示用户选择运行模式
	if (MessageBox(NULL,"你想在全屏模式下运行么？", "设置全屏模式",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;						// FALSE为窗口模式
	}
	// 创建OpenGL窗口
	if (fullscreen)
	{
		if (!CreateGLWindow(MCTitle MCVersion,winWidth,winHeight,16,fullscreen))//创建窗体
			return 0;				// 如果窗口未能创建，程序退出
	}else{
		if (!CreateGLWindow(MCTitle MCVersion,870,518,16,fullscreen))//创建窗体
			return 0;				// 如果窗口未能创建，程序退出
	}

	isPause=false;

	gobalListener=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)GobalListener,NULL,0,NULL);

	KeyboardListener=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)KeyBoardListener,NULL,0,NULL);

	WorldRebuild=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)LoadChunk,NULL,0,NULL);

	while(!done)								// 保持循环直到 done=TRUE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))			// 有消息在等待吗?
		{

			if (msg.message==WM_QUIT)				// 收到退出消息?
			{
				if (GameScrNum==1)
				{
					LeaveGame();
				}
				done=TRUE;					// 是，则done=TRUE
			}
			else							// 不是，处理窗口消息
			{
				TranslateMessage(&msg);				// 翻译消息
				DispatchMessage(&msg);				// 发送消息
			}
		}
		else								// 如果没有消息
		{
			// 绘制场景。监视ESC键和来自DrawGLScene()的退出消息
			if (active)						// 程序激活的么?
			{
				DrawGLScene();				// 绘制场景
				SwapBuffers(hDC);			// 交换缓存 (双缓存)
			}
			if (keys[VK_F11])					// F1键按下了么?
			{
				keys[VK_F11]=FALSE;				// 若是，使对应的Key数组中的值为 FALSE
				KillGLWindow();					// 销毁当前的窗口
				fullscreen=!fullscreen;				// 切换 全屏 / 窗口 模式
				// 重建 OpenGL 窗口
				if (fullscreen)
				{
					int winWidth = GetSystemMetrics ( SM_CXSCREEN ); 
					int winHeight= GetSystemMetrics ( SM_CYSCREEN ); 

					if (!CreateGLWindow(MCTitle MCVersion,winWidth,winHeight,16,fullscreen))//创建窗体
						done=true;				// 如果窗口未能创建，程序退出
				}else{
					if (!CreateGLWindow(MCTitle MCVersion,870,518,16,fullscreen))//创建窗体
						done=true;				// 如果窗口未能创建，程序退出
				}
			}
			if (MouseTimer>13)
			{
				MouseEvent();
				MouseTimer=0;
			}
		}
	}
	// 关闭程序
	KillGLWindow();								// 销毁窗口
	ShowCursor(true);						// 显示鼠标指针
	return (msg.wParam);							// 退出程序
}