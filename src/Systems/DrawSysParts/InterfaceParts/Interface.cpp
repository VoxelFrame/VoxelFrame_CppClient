#include "../interface.h"
#include "Shader.h"
namespace DrawSys
{
    namespace interface
    {
        // Shader shaderF;
        void initFont();
        void initInterface()
        {
            initFont();
        }
        void initFont()
        {
            // shaderF.use();
            // glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(Width), 0.0f, static_cast<GLfloat>(Height));
            // glUniformMatrix4fv(glGetUniformLocation(shaderF.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
            // FT_Library ft;
            // if (FT_Init_FreeType(&ft))
            //     std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

            // FT_Face face;
            // if (FT_New_Face(ft, "./resource/Other/arial.ttf", 0, &face))
            //     std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

            // FT_Set_Char_Size(face, 16 * 64, 16 * 64, 96, 96);
            // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            // for (GLubyte c = 0; c < 128; c++)
            // {
            //     if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            //     {
            //         std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            //         continue;
            //     }

            //     glGenTextures(1, &textureF);
            //     glBindTexture(GL_TEXTURE_2D, textureF);
            //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
            //                  face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
            //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            //     Character character = {textureF, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            //                            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), glm::qualifier(face->glyph->advance.x)};
            //     Characters.insert(std::pair<GLchar, Character>(c, character));
            // }

            // FT_Done_Face(face);
            // FT_Done_FreeType(ft);

            // glGenVertexArrays(1, &VAO_F);
            // glGenBuffers(1, &VBO_F);
            // glBindVertexArray(VAO_F);
            // glBindBuffer(GL_ARRAY_BUFFER, VBO_F);
            // glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
            // glEnableVertexAttribArray(0);
            // glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
            // glBindBuffer(GL_ARRAY_BUFFER, 0);
            // glBindVertexArray(0);
        }
        void drawText(string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
        {
            // shaderF.use();
            // glUniform3f(glGetUniformLocation(shaderF.ID, "textColor"), color.x, color.y, color.z);
            // glActiveTexture(GL_TEXTURE0);
            // glBindTexture(GL_TEXTURE_2D, textureF);
            // glBindVertexArray(VAO_F);

            // std::string::const_iterator c;
            // for (c = text.begin(); c != text.end(); c++)
            // {
            //     Character ch = Characters[*c];

            //     GLfloat xpos = x + ch.offset.x * scale;
            //     GLfloat ypos = y - (ch.size.y - ch.offset.y) * scale;

            //     GLfloat w = ch.size.x * scale;
            //     GLfloat h = ch.size.y * scale;

            //     GLfloat vertices[6][4] =
            //         {
            //             {xpos, ypos + h, 0.0, 0.0},
            //             {xpos, ypos, 0.0, 1.0},
            //             {xpos + w, ypos, 1.0, 1.0},

            //             {xpos, ypos + h, 0.0, 0.0},
            //             {xpos + w, ypos, 1.0, 1.0},
            //             {xpos + w, ypos + h, 1.0, 0.0}};

            //     glBindTexture(GL_TEXTURE_2D, ch.textureID);

            //     glBindBuffer(GL_ARRAY_BUFFER, VBO_F);
            //     glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            //     glBindBuffer(GL_ARRAY_BUFFER, 0);
            //     glDrawArrays(GL_TRIANGLES, 0, 6);
            //     x += (ch.advance >> 6) * scale;
            // }
        }
    } // namespace interface

} // namespace DrawSys