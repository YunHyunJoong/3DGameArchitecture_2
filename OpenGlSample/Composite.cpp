#include <iostream>

#include "Composite.h"

Composite::Composite()
{
	composite = new std::vector<Composite*>();
	Parent = nullptr;
}

Composite::~Composite()
{
	for (
		std::vector<Composite*>::const_iterator it = composite->begin();
		it != composite->end();
		++it
		)
	{
		delete (*it);
	}
	composite->clear();

	delete composite;
}


void Composite::AddChild(Composite* addObj)
{
	composite->push_back(addObj);

	addObj->Parent = this;
}

void Composite::update()
{
	if (Parent)
	{
		WorldTranslate = Parent->WorldTranslate * Translate;
	}
	else
	{
		WorldTranslate = Translate;
	}
}