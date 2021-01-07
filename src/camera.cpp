#include "camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

using std::cout;
using std::endl;

Camera::Camera()
{
    right   = glm::normalize(glm::cross(direction, glm::vec3{0.0, 1.0, 0.0}));
    up      = glm::normalize(glm::cross(right, direction));
    vmatrix = glm::lookAt(position, position + direction, up);
    pmatrix = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
}

void
Camera::ProcessKeyboardInput(CamDir dir, float deltaTime)
{
    float velocity = speed * deltaTime;
    if (dir == CamDir::FORWARD)
        position += direction * velocity;
    if (dir == CamDir::BACKWARD)
        position -= direction * velocity;
    if (dir == CamDir::LEFT)
        position -= right * velocity;
    if (dir == CamDir::RIGHT)
        position += right * velocity;
    Update();
}

void
Camera::ProcessMouseInput(float &xoffset, const float &yoffset)
{
    yaw += xoffset * sensitivity;
    pitch += yoffset * sensitivity;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    Update();
}

void
Camera::ProcessRollInput(float yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
    Update();
}

void
Camera::Update()
{
    right   = glm::normalize(glm::cross(direction, glm::vec3{0.0, 1.0, 0.0}));
    up      = glm::normalize(glm::cross(right, direction));
    vmatrix = glm::lookAt(position, position + direction, up);
    pmatrix = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
}
