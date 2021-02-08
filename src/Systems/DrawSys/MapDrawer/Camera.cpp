#include"Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace DrawSys
{
    Camera::Camera() 
    {
        camerPos=glm::vec3(1.0f,0.0f,0.0f);
        camerTarget=glm::vec3(0.0f,0.0f,0.0f);
        camerDirection=glm::normalize(camerPos-camerTarget);   
        camerRight=glm::normalize(glm::cross(glm::vec3(0.0f,1.0f,0.0f),camerDirection));
        camerUp=glm::normalize(glm::cross(camerRight,camerDirection));

    }
    
    glm::vec3 Camera::GetCamerPos() 
    {
        return this->camerPos;
    }
    
    void Camera::SetCamerPos(glm::vec3 pos) 
    {
        this->camerTarget=pos;
        camerDirection=glm::normalize(camerPos-camerTarget);   
        camerRight=glm::normalize(glm::cross(glm::vec3(0.0f,1.0f,0.0f),camerDirection));
        camerUp=glm::normalize(glm::cross(camerRight,camerDirection));
    }
    
    void Camera::LookAt(int shaderprogram,glm::vec3 target) 
    {
        this->camerTarget=target;
        camerDirection=glm::normalize(camerPos-camerTarget);   
        camerRight=glm::normalize(glm::cross(glm::vec3(0.0f,1.0f,0.0f),camerDirection));
        camerUp=glm::normalize(glm::cross(camerRight,camerDirection));
        glm::mat4 view =glm::lookAt(camerPos,target,camerUp);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram, "camera"), 1, GL_FALSE, glm::value_ptr(view));
        
    }
}