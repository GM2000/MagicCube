#include "MagicCube.h"

int DrawGLScene(GLvoid);
int InitGL(GLvoid);
GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
GLvoid KillGLWindow(GLvoid);
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag);

extern bool LBottom;
extern bool RBottom;

extern HANDLE KeyboardListener;
extern HANDLE WorldRebuild;

extern int FPS;