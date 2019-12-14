#pragma once

#include "DirectXIncLib.h"

#define TITLE L"DirectX Practice"

class Direct3D11;
class Main;
class Window;

class Game {
public:
    Game();
    ~Game();
    void run(HINSTANCE);
    HRESULT init();
    void mainLoop();
    void fixFPS60();

public:
    static const int WINDOW_WIDTH = 1024; //64 * 16
    static const int WINDOW_HEIGHT = 576; // 64 * 9

private:
    Window* mWindow;
    Direct3D11* mD3D11;
    HINSTANCE mInstance;
    HWND mhWnd;
    Main* mMain;
};

//プロトタイプ
void initDirectory(WCHAR* root);
void setRootDirectory();
void setAssetsDirectory();
void setShaderDirectory();
void setTextureDirectory();
void setSoundDirectory();
void setDataDirectory();
