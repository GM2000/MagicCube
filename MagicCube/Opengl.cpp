#include "MagicCube.h"
#include "Setting.h"

int MagicCubeInit();

int InitGL(GLvoid)								// 此处开始对OpenGL进行所有设置
{
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL,1.0f);
	glewInit();
	glEnable(GL_TEXTURE_2D);						// 启用纹理映射
	glShadeModel(GL_SMOOTH);						// 启用阴影平滑
	glClearColor(0.3f, 0.6f, 1.0f, 0.0f);					// 蓝色背景
	glClearDepth(1.0f);							// 设置深度缓存
	glEnable(GL_DEPTH_TEST);						// 启用深度测试
	glClear(GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LEQUAL);							// 所作深度测试的类型
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// 告诉系统对透视进行修正(影响性能！)
	glClear(GL_DEPTH_BUFFER_BIT);
	glewInit();
	if (MagicCubeInit()==false)
	{
		return FALSE;								// 初始化 失败
	}
	///////////////////////雾/////////////////////////

	GLfloat fogColor[4] = {0.3f, 0.6f, 1.0f, 0.0f};
	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR,fogColor);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 10.0f+Horizon*16);
	glFogf(GL_FOG_END, 27.0f+Horizon*16);
	glHint(GL_FOG_HINT, GL_DONT_CARE);

	////////////////////////////////////////////////
	return TRUE;								// 初始化 OK
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)				// 重置OpenGL窗口大小
{
	if (height==0)								// 防止被零除
	{
		height=1;							// 将Height设为1
	}
	glViewport(0, 0, width, height);					// 重置当前的视口
	glMatrixMode(GL_PROJECTION);						// 选择投影矩阵
	glLoadIdentity();							// 重置投影矩阵
	// 设置视口的大小
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,200.0f);
	glMatrixMode(GL_MODELVIEW);						// 选择模型观察矩阵
	glLoadIdentity();							// 重置模型观察矩阵
}
