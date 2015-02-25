#include "MagicCube.h"
#include "GLTools.h"

float textureEach;		// ����ߴ�

GLuint texture;	// �洢����
GLuint toolbar;	// �洢����
GLuint logo;	// �洢����

void AddTexture()
{
	GLbyte *pBytes;
	GLint iWidth,iHeight,iComponents; 
	GLenum eFormat;

	glGenTextures(1, &texture);					// ��������
	glBindTexture(GL_TEXTURE_2D, texture);
	CString FileName;
	FileName="resourcepacks/Texture.tga"; 
	pBytes=gltReadTGABits(FileName,&iWidth,&iHeight,&iComponents,&eFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0,GL_BGRA, GL_UNSIGNED_BYTE, pBytes);
	textureEach=iWidth/16;
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA  );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	// �����˲�
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	// �����˲�
	free(pBytes);
}

void AddToolBar()
{
	GLbyte *pBytes;
	GLint iWidth,iHeight,iComponents; 
	GLenum eFormat;

	glGenTextures(1, &toolbar);					// ��������
	glBindTexture(GL_TEXTURE_2D, toolbar);
	CString FileName;
	FileName="resourcepacks/ToolBar.tga"; 
	pBytes=gltReadTGABits(FileName,&iWidth,&iHeight,&iComponents,&eFormat);
	for (int i=0;i<iWidth;i++)
	{
		for (int j=0;j<iHeight;j++)
		{
			
		}
	}
	glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0,GL_BGRA, GL_UNSIGNED_BYTE, pBytes);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA  );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	// �����˲�
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	// �����˲�
	free(pBytes);
}

void AddLogo()
{
	GLbyte *pBytes;
	GLint iWidth,iHeight,iComponents; 
	GLenum eFormat;

	glGenTextures(1, &logo);					// ��������
	glBindTexture(GL_TEXTURE_2D, logo);
	CString FileName;
	FileName="resourcepacks/Logo.tga"; 
	pBytes=gltReadTGABits(FileName,&iWidth,&iHeight,&iComponents,&eFormat);
	for (int i=0;i<iWidth;i++)
	{
		for (int j=0;j<iHeight;j++)
		{
			
		}
	}
	glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0,GL_BGRA, GL_UNSIGNED_BYTE, pBytes);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA  );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	// �����˲�
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	// �����˲�
	free(pBytes);
}

int AddMCTexture()
{
	AddToolBar();
	AddTexture();
	AddLogo();
	return 1;
}
