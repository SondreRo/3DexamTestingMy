#include "Material.h"
#include <glm/gtc/type_ptr.hpp>

void Material::UseMaterial(Shader* shader)
{
	glUniform3fv(glGetUniformLocation(shader->ID, "diffuse"), 1, glm::value_ptr(diffuse));
	glUniform3fv(glGetUniformLocation(shader->ID, "specular"), 1, glm::value_ptr(specular));
	glUniform1f(glGetUniformLocation(shader->ID, "shininess"), shininess);

}
