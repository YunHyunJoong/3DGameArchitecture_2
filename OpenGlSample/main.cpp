#define _CRT_SECURE_NO_WARINGS

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")

#include "FileManager.h"
#include "Object.h"
#include "Renderer.h"
#include "RenderableObject.h"
#include "NonRenderableObject.h"
#include "Human.h"
#include "Time.h"

int main()
{
	FileManager* filemgr = FileManager::instance();
	Time* time = new Time();

	Renderer* renderer = Renderer::instance();

	NonRenderableObject* non_render_obj = new NonRenderableObject();

	Human* human = new Human();

	renderer->init();

	while (true)
	{
		renderer->renderClear();

		renderer->render();

		if (time->isRenderTiming())
		{
			renderer->update();
		}

		renderer->renderOff();
	}

	human->shutDown();
	renderer->shutDown();

	delete human;
	delete non_render_obj;

	return 0;
}