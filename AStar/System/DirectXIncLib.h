#pragma once

#include <windows.h>
#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>
#include <d3dCompiler.h>
//必要なライブラリファイルのロード
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

#define SAFE_RELEASE(x) if(x){x->Release(); x=0;}
#define SAFE_DELETE(x) if(x){delete x; x=0;}
#define SAFE_DELETE_ARRAY(x) if(x){delete[] x; x=0;}
#define MFAIL(code,string) if(FAILED(code) ) { MessageBox(0, string, L"error",MB_OK); return E_FAIL; }
#define MFALSE(code,string) if(!(code) ) { MessageBox(0, string, L"error",MB_OK); return E_FAIL; }
#define MSG(t) MessageBox(0, t, 0, MB_OK);
