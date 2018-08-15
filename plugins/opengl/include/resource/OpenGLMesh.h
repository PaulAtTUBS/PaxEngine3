//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_OPENGLMESH_H
#define PAXENGINE3_OPENGLMESH_H

#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <GL/glew.h>
#include <core/rendering/resource/Mesh.h>

namespace PAX {
    namespace OpenGL {
        class OpenGLMesh : public Mesh {
            bool _finalized = false;

            GLfloat* _vertexData = nullptr;
            GLint* _indexData = nullptr;
            GLuint _vao, _ibo, _vbo;
            GLenum _faceMode;

            int _numberOfVertices, _numberOfFaces, _verticesPerFace;
            std::vector<std::vector<float>> _vertices;
            std::vector<std::vector<int>> _indices;
            std::vector<std::pair<int, int>> _attributes; //offset and length
            int _currentOffset = 0;

            void initialize(std::vector<glm::vec3> &vertices);

        public:
            OpenGLMesh(std::vector<glm::vec3> &vertices, std::vector<std::vector<int>> &faces, GLenum faceMode = GL_TRIANGLES);
            OpenGLMesh(std::vector<glm::vec3> &vertices, std::vector<glm::ivec3> &faces, GLenum faceMode = GL_TRIANGLES);
            ~OpenGLMesh();

            virtual void render(RenderOptions &renderOptions) override;

            virtual void addAttribute(std::vector<float> &attrib) override;
            virtual void addAttribute(std::vector<glm::vec2> &attrib) override;
            virtual void addAttribute(std::vector<glm::vec3> &attrib) override;
            virtual void addAttribute(std::vector<glm::vec4> &attrib) override;

            virtual void finalize() override;
            virtual void upload() override;

            virtual void destroy() override;

            bool isFinalized();

            GLuint getID();
        };
    }
}
#endif //PAXENGINE3_OPENGLMESH_H