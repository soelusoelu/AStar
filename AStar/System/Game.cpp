#include "Game.h"
#include "Direct3D11.h"
#include "Window.h"
#include "../Main.h"
#include "../Device/Random.h"
#include "../Device/Sound.h"
#include "../Scene/GamePlay.h"
#include "../UI/Texture.h"
#include "../Utility/Input.h"
#include "../Utility/Singleton.h"

WCHAR szRootPath[1024] = { 0 };

Game::Game() {
    ZeroMemory(this, sizeof(Game));
}

Game::~Game() {
    SAFE_DELETE(mMain);
    SAFE_DELETE(mD3D11);
    SAFE_DELETE(mWindow);
    Texture::end();
    Input::end();
    Sound::end();
    SingletonFinalizer::finalize();
}

void Game::run(HINSTANCE hInstance) {
    WCHAR dir[1024];
    GetCurrentDirectory(sizeof(dir), dir);
    initDirectory(dir);

    mInstance = hInstance;
    if (FAILED(init())) {
        return;
    }
    ShowWindow(mhWnd, SW_SHOW);
    UpdateWindow(mhWnd);
    // メッセージループ
    MSG msg = { 0 };
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            mainLoop();
        }
    }
}

HRESULT Game::init() {
    //window
    mWindow = new Window();
    if (!mWindow) {
        return E_FAIL;
    }
    MFAIL(mWindow->initWindow(mInstance, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, TITLE), L"ウィンドウ作成失敗");
    mhWnd = mWindow->gethWnd();
    //direct3D11
    mD3D11 = new Direct3D11();
    if (!mD3D11) {
        MSG(L"Direct3Dの初期化失敗");
        return E_FAIL;
    }
    MFALSE(mD3D11->init(mhWnd), L"Direct3D初期化失敗");

    MFAIL(Input::init(mhWnd), L"DirectInput初期化失敗");

    MFAIL(Sound::init(), L"XAudio2初期化失敗");

    Random::init();

    mMain = new Main();

    return S_OK;
}

void Game::mainLoop() {
    mD3D11->clear();

    Input::update();

    mMain->update();
    mMain->draw();

    fixFPS60();
    mD3D11->present();
}

void Game::fixFPS60() {
    static int frames = 0, fps = 0;
    static LARGE_INTEGER frq = { 0 }, previousTime = { 0 }, currentTime = { 0 };
    DOUBLE time = 0;
    char sz[10] = { 0 };

    while (time < 16.6666)//1000ms / 60frame=16.6666 
    {
        QueryPerformanceFrequency(&frq);

        QueryPerformanceCounter(&currentTime);
        time = currentTime.QuadPart - previousTime.QuadPart;
        time *= 1000.0 / static_cast<DOUBLE>(frq.QuadPart);
    }
    previousTime = currentTime;
}



void initDirectory(WCHAR* root) {
    wcsncpy_s(szRootPath, root, wcslen(root));
}

void setRootDirectory() {
    SetCurrentDirectory(szRootPath);
}

void setAssetsDirectory() {
    WCHAR tmp[1024] = { 0 };
    wcsncpy_s(tmp, szRootPath, wcslen(szRootPath));
    wcscat_s(tmp, L"\\Assets");
    SetCurrentDirectory(tmp);
}

void setShaderDirectory() {
    WCHAR tmp[1024] = { 0 };
    wcsncpy_s(tmp, szRootPath, wcslen(szRootPath));
    wcscat_s(tmp, L"\\Shader");
    SetCurrentDirectory(tmp);
}

void setTextureDirectory() {
    WCHAR tmp[1024] = { 0 };
    wcsncpy_s(tmp, szRootPath, wcslen(szRootPath));
    wcscat_s(tmp, L"\\Assets/Texture");
    SetCurrentDirectory(tmp);
}

void setSoundDirectory() {
    WCHAR tmp[1024] = { 0 };
    wcsncpy_s(tmp, szRootPath, wcslen(szRootPath));
    wcscat_s(tmp, L"\\Assets/Sound");
    SetCurrentDirectory(tmp);
}

void setDataDirectory() {
    WCHAR tmp[1024] = { 0 };
    wcsncpy_s(tmp, szRootPath, wcslen(szRootPath));
    wcscat_s(tmp, L"\\Assets/Data");
    SetCurrentDirectory(tmp);
}
