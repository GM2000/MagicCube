#include "MagicCube.h"

void selectFont(int size, int charset, const char* face) {
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
        charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}

GLuint drawChar_To_Texture(const char* s,float TX,float TZ,float FontSize) {
	selectFont(FontSize*0.85, ANSI_CHARSET, "微软雅黑");
    wchar_t w;
    HDC hDC = wglGetCurrentDC();
    // 选择字体字号、颜色
	//阴影//
	glColor3f(0.0f, 0.0f, 0.0f);
    // 转化为宽字符
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, s, 2, &w, 1);
    // 计算绘制的位置
    {
        int width, x, y;
        GetCharWidth32W(hDC, w, w, &width);    // 取得字符的宽度
        x = (FontSize - width) / 2+TX;
        y = FontSize / 8+TZ;
        glWindowPos2iARB(x+1, y-1); // 一个扩展函数
    }
    // 绘制字符
    // 绘制前应该将各种可能影响字符颜色的效果关闭
    // 以保证能够绘制出白色的字符
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
    // 转化为宽字符
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, s, 2, &w, 1);
    // 计算绘制的位置
    {
        int width, x, y;
        GetCharWidth32W(hDC, w, w, &width);    // 取得字符的宽度
        x = (FontSize - width) / 2+TX;
        y = FontSize / 8+TZ;
        glWindowPos2iARB(x, y); // 一个扩展函数
    }
    // 绘制字符
    // 绘制前应该将各种可能影响字符颜色的效果关闭
    // 以保证能够绘制出白色的字符
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