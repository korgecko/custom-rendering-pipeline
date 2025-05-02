#include "EngineLoop.h"

extern LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// 정적 멤버 정의
URenderer FEngineLoop::renderer;

FEngineLoop::FEngineLoop()
{
}

FEngineLoop::~FEngineLoop()
{
}

int32 FEngineLoop::PreInit()
{
	return 0;
}

ID3D11Buffer* vertexBufferSphere;
UINT numVerticesSphere = sizeof(sphere_vertices) / sizeof(FVertexSimple);
const float leftBorder = -1.0f;
const float rightBorder = 1.0f;
const float topBorder = -1.0f;
const float bottomBorder = 1.0f;
float gravityStrength = -0.005f;  // 기본 중력 값
FVector3 Gravity(0.0f, gravityStrength, 0.0f); // 중력 벡터
float bounciness = 1.0f; // 1.0 = 완전 탄성 충돌, 0.0 = 완전 비탄성 충돌
bool bEnableGravity = false; // 중력 활성화 여부

bool bUseCustomColor = false;
float BallColor[3] = { 1.0f, 1.0f, 1.0f }; // 기본 흰색 (RGB)

class UBall
{
public:
	// 클래스 이름과, 아래 두개의 변수 이름은 변경하지 않습니다.
	FVector3 Location;
	FVector3 Velocity;
	float Radius;
	float Mass;

	UBall* NextBall;

	// 이후 추가할 변수와 함수 이름은 자유롭게 정하세요.

	// 예:1
	//float Index;

	// 예:2
	//int NumHits;
	UBall() {
		Radius = ((rand() % 50) + 10) / 40.0f / 10.0f; // (0.25 ~ 1.5)/10
		Mass = Radius * 2.0f;
		Location = FVector3(((rand() % 100) / 50.0f) - 1.0f, (rand() % 100) / 100.0f, 0.0f);
		Velocity = FVector3(((rand() % 100 - 50) / 1000.0f), ((rand() % 100 - 50) / 1000.0f), 0.0f);
		NextBall = NULL;
	}
	// 예:3
	void Render(URenderer* renderer)
	{
		FVector3 Color = bUseCustomColor ? FVector3(BallColor[0], BallColor[1], BallColor[2]) : FVector3(-1.0f, -1.0f, -1.0f);
		renderer->UpdateConstant(Location, Radius, Color);
		renderer->RenderPrimitive(vertexBufferSphere, numVerticesSphere);
	}
	void CheckBorder() {
		float renderRadius = Radius;
		if (Location.x < leftBorder + renderRadius)
		{
			Location.x = leftBorder + renderRadius;
			Velocity.x *= -bounciness;
		}
		if (Location.x > rightBorder - renderRadius)
		{
			Location.x = rightBorder - renderRadius;
			Velocity.x *= -bounciness;
		}
		if (Location.y < topBorder + renderRadius)
		{
			Location.y = topBorder + renderRadius;
			Velocity.y *= -bounciness;
		}
		if (Location.y > bottomBorder - renderRadius)
		{
			Location.y = bottomBorder - renderRadius;
			Velocity.y *= -bounciness;
		}
	}
	// 예:5
	void Move()
	{
		ApplyGravity();
		Location.x += Velocity.x;
		Location.y += Velocity.y;
		CheckBorder();
	}
	void ApplyGravity() {
		if (bEnableGravity) {
			Velocity += FVector3(0.0f, gravityStrength, 0.0f);
		}
	}
	// 예:6
	void Update()
	{
	}
};
class UBallManager
{
public:
	UBall* HeadBall; // 리스트의 첫 번째 공
	int BallCount;   // 현재 공 개수

	UBallManager() : HeadBall(nullptr), BallCount(0) {}

	// 새로운 공을 추가하는 함수
	void AddBall()
	{
		UBall* NewBall = new UBall();
		NewBall->NextBall = HeadBall;
		HeadBall = NewBall;
		BallCount++;
	}

	// 랜덤한 공을 삭제하는 함수
	void RemoveBall()
	{
		if (!HeadBall) return; // 리스트가 비어 있으면 리턴

		int TargetIndex = rand() % BallCount;
		UBall* Prev = nullptr;
		UBall* Current = HeadBall;

		for (int i = 0; i < TargetIndex; i++)
		{
			Prev = Current;
			Current = Current->NextBall;
		}

		// 첫 번째 공을 제거하는 경우
		if (!Prev)
		{
			HeadBall = Current->NextBall;
		}
		else
		{
			Prev->NextBall = Current->NextBall;
		}

		delete Current;
		BallCount--;
	}

	// 모든 공을 업데이트 (이동)
	void UpdateBalls()
	{
		UBall* Current = HeadBall;
		while (Current)
		{
			Current->Move();
			Current = Current->NextBall;
		}
		for (UBall* ball1 = HeadBall; ball1 != nullptr; ball1 = ball1->NextBall) {
			for (UBall* ball2 = ball1->NextBall; ball2 != nullptr; ball2 = ball2->NextBall) {
				if (IsColliding(*ball1, *ball2)) {
					HandleCollision(*ball1, *ball2);
				}
			}
		}
	}

	// 모든 공을 렌더링
	void RenderBalls(URenderer* renderer)
	{
		UBall* Current = HeadBall;
		while (Current)
		{
			Current->Render(renderer);
			Current = Current->NextBall;
		}
	}

	// 메모리 해제
	void ClearBalls()
	{
		while (HeadBall)
		{
			UBall* Temp = HeadBall;
			HeadBall = HeadBall->NextBall;
			delete Temp;
		}
		BallCount = 0;
	}
	bool IsColliding(const UBall& ball1, const UBall& ball2) {
		FVector3 delta = ball1.Location - ball2.Location;
		float distanceSquared = delta.x * delta.x + delta.y * delta.y;  // 제곱 연산 최적화
		float radiusSum = ball1.Radius + ball2.Radius;
		return distanceSquared < (radiusSum * radiusSum);
	}

	void HandleCollision(UBall& ball1, UBall& ball2) {
		FVector3 delta = ball1.Location - ball2.Location;
		float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
		FVector3 normal = delta / distance;  // 정규화된 방향 벡터

		FVector3 relativeVelocity = ball1.Velocity - ball2.Velocity;
		float velocityAlongNormal = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

		if (velocityAlongNormal > 0) return;  // 이미 멀어지는 경우 충돌 처리 안 함

		float m1 = ball1.Mass;
		float m2 = ball2.Mass;

		// 탄성도 적용 (기존 e=1.0을 bounciness 변수로 변경)
		float impulse = (-(1 + bounciness) * velocityAlongNormal) / (1 / m1 + 1 / m2);
		FVector3 impulseVector = normal * impulse;

		ball1.Velocity += impulseVector / m1;
		ball2.Velocity -= impulseVector / m2;

		// 공 위치 보정 (겹쳐짐 방지)
		float overlap = (ball1.Radius + ball2.Radius) - distance;
		FVector3 correction = normal * (overlap / 2);
		ball1.Location += correction;
		ball2.Location -= correction;
	}



};

UBallManager uBallManager;

int32 FEngineLoop::Init(HINSTANCE hInstance)
{
	int screenWidth, screenHeight;
	bool fullScreen;

	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	fullScreen = false;

	

	//LoadEngineConfig(screenWidth, screenHeight, fullScreen);
	//WindowInit(hInstance, screenWidth, screenHeight);

	//graphicDevice.Initialize(hWnd);

	//renderer.Initialize(&graphicDevice);

	//UIManager = new UImGuiManager();
	//UIManager->Initialize(hWnd, graphicDevice.Device, graphicDevice.DeviceContext);

	//resourceManager.Initialize(&renderer);

	//GWorld = new UWorld;
	//GWorld->Initialize();
	
	LARGE_INTEGER frequency;
	const double targetFrameTime = 1000.0 / targetFPS; // 한 프레임의 목표 시간 (밀리초 단위)

	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER startTime, endTime;
	double elapsedTime = 1.0;

	srand(time(NULL));
	// 윈도우 클래스 이름
    
	WindowInit(hInstance, screenWidth, screenHeight);

	//bool bIsExit = false;

	// 각종 생성하는 코드를 여기에 추가합니다.
	// Renderer Class를 생성합니다.
	//URenderer renderer; 지역 변수를 지웠다. 
	// D3D11 생성하는 함수를 호출합니다.
	renderer.Create(hWnd);
	// 렌더러 생성 직후에 쉐이더를 생성하는 함수를 호출합니다.
	renderer.CreateShader();
	renderer.CreateConstantBuffer();

	// 여기에서 ImGui를 생성합니다.
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init((void*)hWnd);
	ImGui_ImplDX11_Init(renderer.Device, renderer.DeviceContext);


	uBallManager.AddBall();
	// 실습2 마지막장에서 삼각형을 그릴 때 버텍스 버퍼 생성 하는 부분을 아래와 같이 수정합니다.
	// Vertex 배열 변수 이름이 triangle_vertices에서 cube_vertices로 변경된것 입니다.
	/*
		FVertexSimple* vertices = triangle_vertices;
		UINT ByteWidth = sizeof(triangle_vertices);
		UINT numVertices = sizeof(triangle_vertices) / sizeof(FVertexSimple);
	*/

	// 버텍스 버퍼로 넘기기 전에 Scale Down합니다.
	//float scaleMod = 0.1f;
	//UINT numVerticesTriangle = sizeof(triangle_vertices) / sizeof(FVertexSimple);
	//UINT numVerticesCube = sizeof(cube_vertices) / sizeof(FVertexSimple);
	//UINT numVerticesSphere = sizeof(sphere_vertices) / sizeof(FVertexSimple);
	/*
	for (UINT i = 0; i < numVerticesSphere; ++i)
	{
		sphere_vertices[i].x *= scaleMod;
		sphere_vertices[i].y *= scaleMod;
		sphere_vertices[i].z *= scaleMod;
	}*/
	//ID3D11Buffer* vertexBufferTriangle = renderer.CreateVertexBuffer(triangle_vertices, sizeof(triangle_vertices));
	//ID3D11Buffer* vertexBufferCube = renderer.CreateVertexBuffer(cube_vertices, sizeof(cube_vertices));


	vertexBufferSphere = renderer.CreateVertexBuffer(sphere_vertices, sizeof(sphere_vertices));

	return 0;
}

//void FEngineLoop::RenderUI()

void FEngineLoop::Tick()
{
	// FPS 제한을 위한 설정
	const int targetFPS = 30;
	const double targetFrameTime = 1000.0 / targetFPS; // 한 프레임의 목표 시간 (밀리초 단위)

	// 고성능 타이머 초기화
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER startTime, endTime;
	double elapsedTime = 0.0;

	// Main Loop (Quit Message가 들어오기 전까지 아래 Loop를 무한히 실행하게 됨)
	while (bIsExit == false)
	{
		QueryPerformanceCounter(&startTime);
		MSG msg;

		// 처리할 메시지가 더 이상 없을때 까지 수행
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// 키 입력 메시지를 번역
			TranslateMessage(&msg);

			// 메시지를 적절한 윈도우 프로시저에 전달, 메시지가 위에서 등록한 WndProc 으로 전달됨
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				bIsExit = true;
				break;
			}
			else if (msg.message == WM_KEYDOWN) // 키보드 눌렸을 때
			{

			}
		}
		////////////////////////////////////////////
		// 매번 실행되는 코드를 여기에 추가합니다.
		// 준비 작업
		renderer.Prepare();
		renderer.PrepareShader();
		uBallManager.UpdateBalls();
		uBallManager.RenderBalls(&renderer);
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Jungle Property Window");
		//ImGui::Checkbox("Gravity", &bEnableGravity);
		//ImGui::SameLine();
		//ImGui::SliderFloat("Gravity Strength", &gravityStrength, -0.05f, 0.05f, "%.3f");
		//Gravity.y = gravityStrength;  // 중력 값 적용
		//int newBallCount = uBallManager.BallCount;
		//ImGui::InputInt("Number of Balls", &newBallCount);
		//if (newBallCount < 0) {
		//	newBallCount = 0;
		//}
		////if (ImGui::Button("+"))	uBallManager.AddBall();
		//// 현재 공 개수보다 크면 공 추가

		//while (newBallCount > uBallManager.BallCount) {
		//	uBallManager.AddBall();
		//}

		//// 현재 공 개수보다 작으면 공 제거
		//while (newBallCount < uBallManager.BallCount) {
		//	uBallManager.RemoveBall();
		//}
		//ImGui::SliderFloat("Bounciness", &bounciness, 0.0f, 1.0f, "%.2f");

		//ImGui::Checkbox("Use Custom Color", &bUseCustomColor);
		//if (bUseCustomColor) {
		//	ImGui::SliderFloat("R", &BallColor[0], 0.0f, 1.0f, "%.2f");
		//	ImGui::SliderFloat("G", &BallColor[1], 0.0f, 1.0f, "%.2f");
		//	ImGui::SliderFloat("B", &BallColor[2], 0.0f, 1.0f, "%.2f");
		//}
		ImGui::End();

		ImGui::Render();

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		// 현재 화면에 보여지는 버퍼와 그리기 작업을 위한 버퍼를 서로 교환합니다.
		renderer.SwapBuffer();
		////////////////////////////////////////////
		do
		{
			Sleep(0);

			// 루프 종료 시간 기록
			QueryPerformanceCounter(&endTime);

			// 한 프레임이 소요된 시간 계산 (밀리초 단위로 변환)
			elapsedTime = (endTime.QuadPart - startTime.QuadPart) * 1000.0 / frequency.QuadPart;

		} while (elapsedTime < targetFrameTime);

	}



	//return 1;
}

void FEngineLoop::Exit()
{ 
	uBallManager.ClearBalls();
	// 여기에서 ImGui 소멸
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	// D3D11 소멸 시키는 함수를 호출합니다.
	// 렌더러 소멸 직전에 쉐이더를 소멸 시키는 함수를 호출합니다.
	// 버텍스 버퍼 소멸은 Renderer 소멸전에 처리합니다.
	renderer.ReleaseVertexBuffer(vertexBufferSphere);

	renderer.ReleaseConstantBuffer();
	renderer.ReleaseShader();
	renderer.Release();
}

void FEngineLoop::WindowInit(HINSTANCE hInstance, int screenWidth, int screenHeight)
{
	WCHAR WindowClass[] = L"JungleWindowClass";

	// 윈도우 타이틀바에 표시될 이름
	WCHAR Title[] = L"Game Tech Lab";

	// 각종 메시지를 처리할 함수인 WndProc의 함수 포인터를 WindowClass 구조체에 넣는다.
	WNDCLASSW wndclass = { 0, WndProc, 0, 0, 0, 0, 0, 0, 0, WindowClass };

	// 윈도우 클래스 등록
	RegisterClassW(&wndclass);

	// 1024 x 1024 크기에 윈도우 생성
	hWnd = CreateWindowExW(0, WindowClass, Title, WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, screenWidth, screenHeight,
		nullptr, nullptr, hInstance, nullptr);
}



