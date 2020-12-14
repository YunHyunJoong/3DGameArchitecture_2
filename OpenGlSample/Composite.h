#pragma once

#include <vector>

#include "Object.h"
#include "FileManager.h"

class Composite : public Object
{
public:
	Composite();
	~Composite();
	virtual void init() override {};
	virtual void render() override {};
	virtual void update() override;
	virtual void shutDown() override {};

	virtual void AddChild(Composite* _addObj);

	Composite* Parent;
	glm::mat4 WorldTranslate;
	glm::mat4 Translate;
	glm::mat4 WorldView;
	glm::mat4 View;

protected:
	float rotateSpeed;

	std::vector<Composite*>* composite;

	glm::mat4 Scale;
	glm::vec3 ScaleVector;
	glm::mat4 Rotate;
	glm::vec3 RotateVector;

	glm::vec3 cameraPos;
	glm::mat4 movePos;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;

public:
	glm::vec3 position;
};