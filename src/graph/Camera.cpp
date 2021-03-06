// #include <glad/glad.h>
#include "Camera.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
namespace DrawSys
{
    Camera::Camera()
    {
        pitch = -45.0f;
        yaw = -90.0f;
        camerPos = glm::vec3(0.0f, 5.0f, 10.0f);
        cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        cameraFront.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        cameraFront.y = sin(glm::radians(pitch));
        cameraFront.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        cameraFront = glm::normalize(cameraFront);
        cameraTarget = camerPos + cameraFront;
    }

    Camera &Camera::GetInstance()
    {
        static Camera camera;
        return camera;
    }

    glm::vec3 Camera::GetCameraPos()
    {
        return this->camerPos;
    }

    glm::vec3 Camera::GetCameraTarget()
    {
        return this->cameraTarget;
    }

    void Camera::SetCameraPos(glm::vec3 pos)
    {
        this->camerPos = pos;
        cameraFront = cameraTarget - camerPos;
    }

    void Camera::LookAt(int shaderprogram, glm::vec3 target)
    {
        this->cameraTarget = target;
        cameraFront = glm::normalize(cameraTarget - camerPos);
        glm::mat4 view = glm::lookAt(camerPos, target, cameraUp);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram, "camera"), 1, GL_FALSE, glm::value_ptr(view));
    }

    void Camera::SetViewRange(int shaderprogram, float angle, float height, float width)
    {
        glm::mat4 projection = glm::perspective(glm::radians(angle), width / height, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    }

    void Camera::ChangeView(int shaderprogram, float xoffset, float yoffset)
    {
        yaw += xoffset;
        pitch += yoffset;
        if (yaw > 89.0f)
            yaw = 89.0f;
        if (pitch > 89.0f)
            pitch = 89.0f;
        glm::vec3 front;
        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        front.y = sin(glm::radians(pitch));
        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        cameraFront = glm::normalize(front);
        cameraTarget = camerPos + cameraFront;
        glm::mat4 view = glm::lookAt(camerPos, cameraTarget, cameraUp);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram, "camera"), 1, GL_FALSE, glm::value_ptr(view));
    }
}