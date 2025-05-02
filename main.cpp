
#include <windows.h>
// D3D 사용에 필요한 라이브러리들을 링크합니다.
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include "define.h"
#include "vector_utils.h"
#include "Renderer.h"
#include "matrix_utils.h"
//#include "math_utils.h"


// 여기에 아래 코드를 추가 합니다.



// D3D 사용에 필요한 헤더파일들을 포함합니다.
#include <d3d11.h>
#include <d3dcompiler.h>
#include <ctime>

#include <cmath>

//#include "ImGui/imgui.h"
////#include "ImGui/imgui_internal.h"
//#include "ImGui/imgui_impl_dx11.h"
//#include "imGui/imgui_impl_win32.h"


//#include "Sphere.h"
//#include "Triangle.h"
//#include "Cube.h"


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// 각종 메시지를 처리할 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
	{
		return true;
	}
	switch (message)
	{
	case WM_DESTROY:
		// Signal that the app should quit
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

#include "EngineLoop.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	FEngineLoop engine;
	engine.PreInit();

	//if (!FEngineLoop::renderer.Create(hwnd))  // ← 호출하고 성공 여부 확인
	//	return 0;

	engine.Init(hInstance);
	engine.Tick();
	engine.Exit();
	return 0;
}


