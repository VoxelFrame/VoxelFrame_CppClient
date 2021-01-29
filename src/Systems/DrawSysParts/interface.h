#include <iostream>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glad/glad.h>
using namespace std;

namespace DrawSys
{
    namespace interface
    {
        void initInterface();
        void drawText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
    } // namespace interface

} // namespace DrawSys
