#include "RenderableObject.h"
#include "Renderer.h"

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h" 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

RenderableObject::RenderableObject()
{
	Renderer* renderer = Renderer::instance();
	renderer->addRenderableObject(this);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	RotateVector = glm::vec3(0.0f, 0.0f, 0.0f);
	ScaleVector = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotate = glm::mat4(1.0f);
	Scale = glm::mat4(1.0f);
	rotateSpeed = 0.0f;
}