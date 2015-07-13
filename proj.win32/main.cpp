#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
 
//------------------------------------------------------------------------
#if defined( DEBUG ) || defined( _DEBUG )
#   define _CRTDBG_MAP_ALLOC
#   include <crtdbg.h>
#   define DEBUG_NORMALBLOCK new ( _NORMAL_BLOCK, __FILE__, __LINE__ )
#       ifdef new
#           undef new
#       endif // new
#   define new DEBUG_NORMALBLOCK
#endif // DEBUG
 
//------------------------------------------------------------------------
USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
#if defined( DEBUG ) || defined( _DEBUG )
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif // DEBUG
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
