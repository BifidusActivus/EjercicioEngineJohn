#include "precompiledHeader.h"
#include "JonaModule1.h"

extern Mesh cube;
extern Mesh Sphere;
void JonaModule1::start()
{

	cam = new Camera();

	glm::vec2 viewport = Engine::get().getRender().getViewport();

	cam->setProjectionParams((float)glm::radians(45.0f),
		viewport.x / viewport.y,
		0.1f,
		500.0f);
	window = Engine::get().getRender().getCtxWindow()->getWindowGL();
	Engine::get().SetCamera(cam);
	cam->getTransform().setPosition(0, 0, 8);
	cam->lookAt(glm::vec3(0, 0, 8), glm::vec3(0, 0, 0));

	pos = cam->getPosition();
	front = glm::vec3(0, 0, 1);
	initCameras();
}

void JonaModule1::stop()
{

	for (int i = 0; i < cameras.size(); i++)
		delete cameras[i];
}

void JonaModule1::update(float elapsed)
{
	glm::vec3 euler = cubetransform.getEulerAngles();

	cubetransform.setPosition(glm::vec3(0, 0, 0));
	cubetransform.setEulerAngles(glm::radians(euler.x + glfwGetTime() * 10), euler.y, euler.z);
	cubetransform.setScale(1.0f);
	
	cameraController();

	//glm::vec3 front = cam->getFront();
	cam->lookAt(pos, target);
}

void JonaModule1::initCameras()
{
	cameras.push_back(new Camera());
	cameras.push_back(new Camera());
	cameras.push_back(new Camera());
	cameras.push_back(new Camera());
	cameras.push_back(cam);
	glm::vec2 viewport = Engine::get().getRender().getViewport();

	cameras[0]->setProjectionParams((float)glm::radians(15.0f),
		viewport.x / viewport.y,
		0.1f,
		500.0f);
	cameras[0]->lookAt(glm::vec3(14.5f, 0, 1.42883f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	cameras[1]->setProjectionParams((float)glm::radians(45.0f),
		viewport.x / viewport.y,
		0.1f,
		500.0f);
	cameras[1]->lookAt(glm::vec3(0, 8, 25), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	cameras[2]->setProjectionParams((float)glm::radians(45.0f),
		viewport.x / viewport.y,
		0.1f,
		500.0f);
	cameras[2]->lookAt(glm::vec3(0, 90, 25), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	cameras[3]->setProjectionParams((float)glm::radians(120.0f),
		viewport.x / viewport.y,
		0.1f,
		500.0f);
	cameras[3]->lookAt(glm::vec3(0, 5, 1.25), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	Engine::get().SetCamera(cameras[0]);
}

void JonaModule1::cameraController()
{
	front = glm::vec3(0, 0, 1);
	glm::vec3 euler = cam->getTransform().getEulerAngles();



	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		newAngle += glm::radians(5.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		newAngle -= glm::radians(5.0f);
	}
	//cam->getTransform().yawPitchToVector(front ,newAngle, 0.0f);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		pos -= 0.1f * cam->getFront();//cam->getFront();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		pos += 0.1f * cam->getFront();
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		newPitch += glm::radians(5.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		newPitch += glm::radians(-5.0f);
	}
	if (canPress && glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		actualCamera++;
		actualCamera %= cameras.size();
		Engine::get().SetCamera(cameras[actualCamera]);
		canPress = false;
	}
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE)
	{
		canPress = true;
	}



	target = pos + glm::vec3(sinf(newAngle) * cosf(newPitch),
		sinf(newPitch), cosf(newAngle) * cosf(newPitch));
	glm::vec3 front = cam->getFront();

	cam->getTransform().setPosition(pos);

	std::cout << cameras[0]->getTransform().getPosition().x << " " <<
		cameras[0]->getTransform().getPosition().y << " "
		<< cameras[0]->getTransform().getPosition().z << std::endl;
}

void JonaModule1::renderDebug()
{
	Engine::get().setModelObjectConstants(cubetransform.asMatrix(), glm::vec4(1, 0, 1, 1.0f));
	cubetransform.setScale(1.0f);
	cube.render();
}


JonaModule1::JonaModule1()
{
}


JonaModule1::~JonaModule1()
{
}