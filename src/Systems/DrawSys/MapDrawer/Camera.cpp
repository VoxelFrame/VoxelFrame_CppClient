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
        camerPos=glm::vec3(0.0f,5.0f,10.0f);
        camerTarget=glm::vec3(0.0f,0.0f,0.0f);
        camerUp=glm::vec3(0.0f,1.0f,0.0f);     
    }
    
    glm::vec3 Camera::GetCameraPos() 
    {
        return this->camerPos;
    }
    
    glm::vec3 Camera::GetCameraTarget() 
    {
        return this->camerTarget;
    }
    
    void Camera::SetCameraPos(glm::vec3 pos) 
    {
        this->camerPos=pos;
    }
    
    void Camera::SetCameraTarget(glm::vec3 target) 
    {
        this->camerTarget=target;
    }
    
    void Camera::LookAt(int shaderprogram,glm::vec3 target) 
    {
        this->camerTarget=target;
        glm::mat4 view =glm::lookAt(camerPos,target,camerUp);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram, "camera"), 1, GL_FALSE, glm::value_ptr(view));
        
    }
    
    void Camera::SetViewRange(int shaderprogram,float angle,float height,float width) 
    {
        glm::mat4 projection=glm::perspective(glm::radians(angle),width/height,0.1f,100.0f);
        glUniformMatrix4fv(glGetUniformLocation(shaderprogram, "projection"),1, GL_FALSE, glm::value_ptr(projection));
    }
}