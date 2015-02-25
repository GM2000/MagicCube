#include "MagicCube.h"
#include "Setting.h"

int MagicCubeInit();

int InitGL(GLvoid)								// �˴���ʼ��OpenGL������������
{
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL,1.0f);
	glewInit();
	glEnable(GL_TEXTURE_2D);						// ��������ӳ��
	glShadeModel(GL_SMOOTH);						// ������Ӱƽ��
	glClearColor(0.3f, 0.6f, 1.0f, 0.0f);					// ��ɫ����
	glClearDepth(1.0f);							// ������Ȼ���
	glEnable(GL_DEPTH_TEST);						// ������Ȳ���
	glClear(GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LEQUAL);							// ������Ȳ��Ե�����
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// ����ϵͳ��͸�ӽ�������(Ӱ�����ܣ�)
	glClear(GL_DEPTH_BUFFER_BIT);
	glewInit();
	if (MagicCubeInit()==false)
	{
		return FALSE;								// ��ʼ�� ʧ��
	}
	///////////////////////��/////////////////////////

	GLfloat fogColor[4] = {0.3f, 0.6f, 1.0f, 0.0f};
	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR,fogColor);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 10.0f+Horizon*16);
	glFogf(GL_FOG_END, 27.0f+Horizon*16);
	glHint(GL_FOG_HINT, GL_DONT_CARE);

	////////////////////////////////////////////////
	return TRUE;								// ��ʼ�� OK
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)				// ����OpenGL���ڴ�С
{
	if (height==0)								// ��ֹ�����
	{
		height=1;							// ��Height��Ϊ1
	}
	glViewport(0, 0, width, height);					// ���õ�ǰ���ӿ�
	glMatrixMode(GL_PROJECTION);						// ѡ��ͶӰ����
	glLoadIdentity();							// ����ͶӰ����
	// �����ӿڵĴ�С
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,200.0f);
	glMatrixMode(GL_MODELVIEW);						// ѡ��ģ�͹۲����
	glLoadIdentity();							// ����ģ�͹۲����
}
