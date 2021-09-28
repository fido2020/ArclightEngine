#pragma once

#include <Arclight/Graphics/Rendering/Shader.h>

#include <GLES3/gl3.h>

#include <string>

#define SHADER_LOG_MAX_LENGTH 4096

namespace Arclight::Rendering {

class GLPipeline {
public:
    GLPipeline(const Shader& vertexShader, const Shader& fragmentShader);
    ~GLPipeline();

private:
    static std::string GetShaderCompilationLog(GLuint shader); 

    GLuint m_compiledVertexShader;
    GLuint m_compiledFragmentShader;

    GLuint m_program;
};

}