#pragma once
#include <glm/glm.hpp>

class CameraInterface
{
public:
	virtual ~CameraInterface() = default;
	virtual glm::mat4 RenderFromCam(int screenWidth, int screenHeight, glm::vec3& camPos)
	{
		return glm::mat4(1);
	}
};

