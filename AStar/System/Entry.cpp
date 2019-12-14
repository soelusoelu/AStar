#include <Windows.h>
#include "Game.h"
//メモリリーク検出用
#ifdef _DEBUG
#include <stdlib.h>
#include <crtdbg.h>
#endif // _DEBUG
//#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT) {
    Game* game = new Game();
    if (game == nullptr) {
        MessageBox(0, L"クラス生成失敗 アプリを終了します", NULL, MB_OK);
        return 0;
    }

    game->run(hInstance);

    delete game;

    //メモリリーク検出関数
    _CrtDumpMemoryLeaks();

    return 0;
}