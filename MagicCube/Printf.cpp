#include "MagicCube.h"

void selectFont(int size, int charset, const char* face) {
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
        charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}

GLuint drawChar_To_Texture(const char* s,float TX,float TZ,float FontSize) {
	selectFont(FontSize*0.85, ANSI_CHARSET, "΢���ź�");
    wchar_t w;
    HDC hDC = wglGetCurrentDC();
    // ѡ�������ֺš���ɫ
	//��Ӱ//
	glColor3f(0.0f, 0.0f, 0.0f);
    // ת��Ϊ���ַ�
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, s, 2, &w, 1);
    // ������Ƶ�λ��
    {
        int width, x, y;
        GetCharWidth32W(hDC, w, w, &width);    // ȡ���ַ��Ŀ��
        x = (FontSize - width) / 2+TX;
        y = FontSize / 8+TZ;
        glWindowPos2iARB(x+1, y-1); // һ����չ����
    }
    // �����ַ�
    // ����ǰӦ�ý����ֿ���Ӱ���ַ���ɫ��Ч���ر�
    // �Ա�֤�ܹ����Ƴ���ɫ���ַ�
    {
        GLuint list = glGenLists(1);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_FOG);
        glDisable(GL_TEXTURE_2D);
        wglUseFontBitmapsW(hDC, w, 1, list);
        glCallList(list);
        glDeleteLists(list, 1);
    }
	    glColor3f(1.0f, 1.0f, 1.0f);
    // ת��Ϊ���ַ�
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, s, 2, &w, 1);
    // ������Ƶ�λ��
    {
        int width, x, y;
        GetCharWidth32W(hDC, w, w, &width);    // ȡ���ַ��Ŀ��
        x = (FontSize - width) / 2+TX;
        y = FontSize / 8+TZ;
        glWindowPos2iARB(x, y); // һ����չ����
    }
    // �����ַ�
    // ����ǰӦ�ý����ֿ���Ӱ���ַ���ɫ��Ч���ر�
    // �Ա�֤�ܹ����Ƴ���ɫ���ַ�
    {
        GLuint list = glGenLists(1);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_FOG);
        glDisable(GL_TEXTURE_2D);
        wglUseFontBitmapsW(hDC, w, 1, list);
        glCallList(list);
        glDeleteLists(list, 1);
    }

	glEnable(GL_DEPTH_TEST);
    glEnable(GL_FOG);
    glEnable(GL_TEXTURE_2D);

    return TRUE;
}