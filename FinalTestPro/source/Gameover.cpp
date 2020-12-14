#include "../FinalTestPro/include/Gameover.h"
#include "FileManager.h"
#include "Renderer.h"

void Gameover::init()
{
	FileManager* filemgr = FileManager::instance();
	filemgr->loadObj(this, "gameover.obj", "red.bmp", "20161651_vs.shader", "20161651_fs.shader");
	this->setPosition(10, 0, 0);
	this->setCameraPos(0, 0, 0);
	this->setScale(0, 0, 0);

	isGame = true;
}

void Gameover::render()
{
	Renderer* renderer = Renderer::instance();

	if (glfwGetKey(renderer->window, GLFW_KEY_R) == GLFW_PRESS) {
		if (isGame == false)
		{
			this->setPosition(0, 10, 0);
			isGame = true;
		}
	}

	if (isGame == false)
	{
		this->setScale(1, 1, 1);
		this->setPosition(-1.7, 0, 0);

	}

	glUseProgram(this->programID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->Texture);
	glUniform1i(this->TextureID, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	// 2nd attribute buffer : UVs
	glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glBindBuffer(GL_ARRAY_BUFFER, this->normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glm::mat4 moveCameraPos = glm::mat4(1.0f);
	moveCameraPos = glm::translate(moveCameraPos, this->cameraPos);

	ProjectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	glm::vec3 direction(
		cos(0.0f) * sin(3.14f),
		sin(0.0f),
		cos(0.0f) * cos(3.14f)
	);

	glm::vec3 right = glm::vec3(
		sin(3.14f - 3.14f / 2.0f),
		0,
		cos(3.14f - 3.14f / 2.0f)
	);

	glm::vec3 position = glm::vec3(0, 0, 5);

	glm::vec3 up = glm::cross(right, direction);

	ViewMatrix = glm::lookAt(
		position,
		position + direction,
		up
	);

	ModelMatrix = glm::mat4(1.0f);

	glm::mat4 MVP;

	if (rotateSpeed > 0.0f)
	{
		Rotate = glm::rotate(Rotate, glm::radians(rotateSpeed), RotateVector);
	}

	movePos = glm::mat4(1.0f);
	movePos = glm::translate(movePos, this->position);
	Translate = Scale * movePos * Rotate * ModelMatrix;

	View = ViewMatrix;

	MVP = ProjectionMatrix * moveCameraPos * WorldView * WorldTranslate;

	glUniformMatrix4fv(this->MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	if (Parent)
	{
		WorldTranslate = Parent->WorldTranslate * Translate;
		WorldView = Parent->WorldView;
	}
	else
	{
		WorldTranslate = Translate;
		WorldView = View;
	}
}

void Gameover::update()
{

}

void Gameover::shutDown()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteProgram(MatrixID);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
}

void Gameover::setPosition(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
}

void Gameover::setRotation(float speed, float x, float y, float z)
{
	rotateSpeed = speed;
	RotateVector = glm::vec3(x, y, z);
}

void Gameover::setScale(float x, float y, float z)
{
	ScaleVector = glm::vec3(x, y, z);
	if (ScaleVector.x != 0.0f || ScaleVector.y != 0.0f || ScaleVector.z != 0.0f)
	{
		Scale = glm::scale(Scale, ScaleVector);
	}
}

void Gameover::setCameraPos(float x, float y, float z)
{
	cameraPos = glm::vec3(-x, -y, -z);
}

void Gameover::AddChild(Composite* addObj)
{
	composite->push_back(addObj);
	addObj->Parent = this;
}

bool Gameover::getGameover()
{
	return isGame;
}

void Gameover::setGameover(bool _isGame)
{
	isGame = _isGame;
}