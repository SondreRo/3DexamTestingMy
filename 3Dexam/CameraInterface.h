#pragma once
#include <glm/glm.hpp>

class CameraInterface
{
public:
	virtual ~CameraInterface() = default;
	virtual glm::mat4 RenderFromCam(int screenWidth, int screenHeight)
	{
		return glm::mat4(1);
	}
};

