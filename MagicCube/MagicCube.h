#define _WIN32_WINNT 0x0502
#define GLEW_STATIC
#include <afxwin.h>		// Windows��ͷ�ļ�
#include "gl\glew.h"		// �������µ�gl.h,glu.h��
#include "gl\glut.h"		// ����OpenGLʵ�ÿ�
#include <math.h>

#define MCTitle "Magic Cube"
#define MCVersion "beta 0.0.0"

extern CString WorldName;

extern HGLRC hRC;							// ������ɫ��������
extern HDC hDC;							// OpenGL��Ⱦ��������
extern HWND hWnd;							// �������ǵĴ��ھ��
extern HINSTANCE hInstance;							// ��������ʵ��

extern bool done;
extern bool FirstLoafFinish;
extern bool	keys[256];								// ������̰���������
extern bool	LeftBottom;								// ������갴��
extern bool	RightBottom;								// ������갴��
extern bool	active;								// ���ڵĻ��־��ȱʡΪTRUE
extern bool	fullscreen;							// ȫ����־ȱʡ��ȱʡ�趨��ȫ��ģʽ

extern float shakingDegX;
extern float shakingDegY;

extern int WindowsHeight;
extern int WindowsWidth;