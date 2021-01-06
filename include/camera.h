#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "parameters.h"

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

constexpr float YAW         = -90.0f;
constexpr float PITCH       = 0.0f;
constexpr float SPEED       = 2.5f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM        = 45.0f;

class Camera
{
  public:
    Camera();

    glm::mat4 GetViewMatrix() const
    {
        return vmatrix;
    }
    glm::mat4 GetProjMatrix() const
    {
        return pmatrix;
    }
    glm::vec3 GetPosition() const
    {
        return position;
    }

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