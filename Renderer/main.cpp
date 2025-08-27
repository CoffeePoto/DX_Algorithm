#include "Engine.h"
#include "Level/RectLevel.h"
#include <Windows.h>
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    Engine* engine = new Engine(800, 600, hInstance);
    engine->AddLevel(new RectLevel());
    engine->Run();
}