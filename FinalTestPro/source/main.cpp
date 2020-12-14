#include "Renderer.h"
#include "Time.h"
#include "NonRenderableObject.h"
#include "Composite.h"

#include "../FinalTestPro/include/Human.h"
#include "../FinalTestPro/include/Star.h"
#include "../FinalTestPro/include/Gameover.h"

bool CheckCollision(Composite* one, Composite* two)
{
	bool collisionX = one->position.x + 1 >= (two->position.x) / 2 && (two->position.x) / 2 + 1 >= one->position.x;
	bool collisionY = one->position.y + 1 >= (two->position.y) / 2 && (two->position.y) / 2 + 1 >= one->position.y;
	
	return collisionX && collisionY;
}

int main(void)
{
	Time* time = new Time();
	Renderer* renderer = Renderer::instance();

	Human* human = new Human();
	Gameover* gameover = new Gameover();

	std::vector<Star*>* star = new std::vector<Star*>();

	for (int i = 0; i < 20; i++)
	{
		star->push_back(new Star());
	}

	renderer->init();

	human->setScale(0.2f, 0.2f, 0.2f);
	
	for (
		std::vector<Star*>::const_iterator it = star->begin();
		it != star->end();
		++it
		)
	{
		(*it)->setScale(0.1f, 0.1f, 0.1f);
	}

	while (glfwGetKey(renderer->window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(renderer->window) == 0)
	{
		renderer->renderClear();

		if (time->isRenderTiming())
		{
			renderer->update();
		}

		renderer->render();

		for (
			std::vector<Star*>::const_iterator it = star->begin();
			it != star->end();
			++it
			)
		{
			if (CheckCollision(human, (*it)))
			{
				human->setPosition(0.0f, -15.0f, 0.0f);
				human->setLife(false);
				gameover->setGameover(false);
			}
		}

		if (gameover->getGameover() && human->getLife() == false)
		{
			human->init();

			for (
				std::vector<Star*>::const_iterator it = star->begin();
				it != star->end();
				++it
				)
			{
				(*it)->init();
			}
		}

		renderer->renderOff();
	}

	renderer->shutDown();

	for (
		std::vector<Star*>::const_iterator it = star->begin();
		it != star->end();
		++it
		)
	{
		delete (*it);
	}

	delete star;
	delete human;
	delete gameover;

	return 0;
}
