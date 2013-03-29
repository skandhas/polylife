#ifdef _WINDOWS
#include <Windows.h>
#include <tchar.h>
#endif

#ifdef _WINDOWS
#define MAIN WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
#else
#define MAIN main(int argc,char *argv[])
#endif

#include "app.h"

int MAIN
{
    App app;
    app.set_executable_path(argv[0]);
    return app.Run();
}