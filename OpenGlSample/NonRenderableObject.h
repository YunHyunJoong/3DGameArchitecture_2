#pragma once

#include "Composite.h"

class NonRenderableObject : public Composite
{
public:
	NonRenderableObject();

	virtual void init() override;
	virtual void render() override;
	virtual void update() override;
	virtual void shutDown() override;
};