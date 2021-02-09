#ifndef __CAMER_H__
#define __CAMER_H__

#include<glm/glm.hpp>
namespace DrawSys
{
    class Camera
    {
        private:
            glm::vec3 camerPos;
            glm::vec3 camerTarget;
            glm::vec3 camerUp;
        public:
            Camera();
            glm::vec3 GetCameraPos();
            glm::vec3 GetCameraTarget();
            void SetCameraPos(glm::vec3 pos);
            void SetCameraTarget(glm::vec3 target);
            void LookAt(int shaderprogram,glm::vec3 target);
            void SetViewRange(int shaderprogram,float angle,float height,float width);
            
    };
}
#endif // __CAMER_H__