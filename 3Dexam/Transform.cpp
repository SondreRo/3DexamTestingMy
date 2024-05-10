#include "Transform.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>


glm::mat4 Transform::GetMatrix()
{

    glm::mat4 ModelMatrix = glm::mat4(1);

    ModelMatrix = glm::translate(ModelMatrix, Location);
    ModelMatrix = glm::scale(ModelMatrix, Scale);

    glm::vec3 eulerAngles = glm::eulerAngles(orientation);
    eulerAngles.x = glm::radians(Pitch); 
    eulerAngles.y = glm::radians(Yaw);
    eulerAngles.z = glm::radians(Roll);
    orientation = glm::quat(eulerAngles);

    ModelMatrix *= (glm::mat4)orientation;

    return ModelMatrix;

}

glm::vec3 Transform::GetLocation()
{
    return Location;
}

glm::vec3 Transform::GetScale()
{
    return Scale;
}

glm::vec3 Transform::GetRotation()
{
    return glm::vec3(Pitch, Yaw, Roll);
}

void Transform::SetLocation(glm::vec3 inLocation)
{
    Location = inLocation;
}

void Transform::SetScale(glm::vec3 inScale)
{
    Scale = inScale;
}

void Transform::SetRotation(glm::vec3 inRotation)
{
    Pitch = inRotation[0];
    Yaw = inRotation[1];
    Roll = inRotation[2];
}

void Transform::AddLocation(glm::vec3 inLocation)
{
    Location += inLocation;
}

void Transform::AddScale(glm::vec3 inScale)
{
    Scale += inScale;
}

void Transform::AddRotation(glm::vec3 inRotation)
{
    Pitch += inRotation[0];
    Yaw += inRotation[1];
    Roll += inRotation[2];
}

