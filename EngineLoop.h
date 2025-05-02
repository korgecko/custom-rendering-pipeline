#pragma once

#include <Windows.h>
#include <fstream>

#include "Define.h"
#include "vector_utils.h"

#include "Renderer.h"

#include "ImGui/imgui.h"
//#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_dx11.h"
#include "imGui/imgui_impl_win32.h"

#include "Sphere.h"
#include "Triangle.h"
#include "Cube.h"

using int32 = int;
using uint32 = unsigned int;

class FEngineLoop
{
public:
	FEngineLoop();
	~FEngineLoop();



	int32 PreInit();
	int32 Init(HINSTANCE hInsatnce);
	void Tick();
	void Exit();

private:
	void WindowInit(HINSTANCE hInstance, int screenWidth, int screenHeight);
//	void LoadEngineConfig(int& screenWidth, int& screenHeight, bool& fullScreen);
//	void Render();

public:
	static URenderer renderer;
	HWND hWnd;
	//FMatrix View;
	//FMatrix Projection;
	float aspectRatio = 1.0f;

//private:
public:
	//UImGuiManager* UIManager;
	//UWorld* GWorld;
	bool bIsExit = false;
	const int32 targetFPS = 60;
	
public:
	//UWorld* GetWorld() { return GWorld; }
};