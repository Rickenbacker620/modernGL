#pragma once
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "parameters.h"

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW         = -90.0f;
const float PITCH       = 0.0f;
const float SPEED       = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM        = 45.0f;

class Camera
{
  public:
    Camera();

    glm::mat4 GetViewMatrix()
    {
        return vmatrix;
    }
    glm::mat4 GetProjMatrix()
    {
        return pmatrix;
    }
    glm::vec3 GetPosition();
    void ProcessKeyboardInput(Camera_Movement direction, float deltaTime);
    void ProcessMouseInput(float &pitch, const float &yaw);
    void ProcessRollInput(float yoffset);

  private:
    bool firstMouse   = true;
    float sensitivity = 0.05;
    float speed       = 10;
    float lastX       = SCREEN_WIDTH / 2;
    float lastY       = SCREEN_HEIGHT / 2;
    float yaw         = 0;
    float pitch       = 0;
    float fov         = 45;

    glm::vec3 position  = {0, 0, 0};
    glm::vec3 direction = {0, 0, -1.0};
    glm::vec3 up        = {0, 1.0, 0};
    glm::vec3 right;
    glm::mat4 vmatrix;
    glm::mat4 pmatrix;

    void Update();
};