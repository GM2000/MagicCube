#define _WIN32_WINNT 0x0502
#define GLEW_STATIC
#include <afxwin.h>		// Windows的头文件
#include "gl\glew.h"		// 包含最新的gl.h,glu.h库
#include "gl\glut.h"		// 包含OpenGL实用库
#include <math.h>

#define MCTitle "Magic Cube"
#define MCVersion "beta 0.0.0"

extern CString WorldName;

extern HGLRC hRC;							// 窗口着色描述表句柄
extern HDC hDC;							// OpenGL渲染描述表句柄
extern HWND hWnd;							// 保存我们的窗口句柄
extern HINSTANCE hInstance;							// 保存程序的实例

extern bool done;
extern bool FirstLoafFinish;
extern bool	keys[256];								// 保存键盘按键的数组
extern bool	LeftBottom;								// 保存鼠标按键
extern bool	RightBottom;								// 保存鼠标按键
extern bool	active;								// 窗口的活动标志，缺省为TRUE
extern bool	fullscreen;							// 全屏标志缺省，缺省设定成全屏模式

extern float shakingDegX;
extern float shakingDegY;

extern int WindowsHeight;
extern int WindowsWidth;