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
            glm::vec3 camerDirection;
            glm::vec3 camerRight;
            glm::vec3 camerUp;
        public:
            Camera();
            glm::vec3 GetCamerPos();
            void SetCamerPos(glm::vec3 pos);
            void LookAt(int shaderprogram,glm::vec3 target);
            
    };
}
#endif // __CAMER_H__