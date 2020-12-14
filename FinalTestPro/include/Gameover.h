#pragma once

#include "RenderableObject.h"

class Gameover : public RenderableObject
{
public:
	virtual void init() override;
	virtual void render() override;
	virtual void update() override;
	virtual void shutDown() override;
	
	virtual void setPosition(float x, float y, float z) override;
	virtual void setRotation(float speed, float x, float y, float z) override;
	virtual void setScale(float x, float y, float z) override;
	virtual void setCameraPos(float x, float y, float z) override;

	virtual void AddChild(Composite* _addObj) override;

	bool getGameover();
	void setGameover(bool _isGame);

private:
	bool isGame;
};