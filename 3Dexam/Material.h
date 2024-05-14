#pragma once
#include <glm/vec3.hpp>

#include "Shader.h"

struct Material
{

	glm::vec3 diffuse = glm::vec3(0.f,1,0.f);
	glm::vec3 specular = glm::vec3(0.5);
	float shininess = 64;

	void UseMaterial(Shader* shader);

};

