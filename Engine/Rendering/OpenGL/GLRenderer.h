#pragma once

#include <Arclight/Graphics/Rendering/Renderer.h>
#include <Arclight/Graphics/Transform.h>
#include <Arclight/Platform/Platform.h>

// OpenGL ES / WebGL Renderer
// Desktop OpenGL not supported at this time,
// due to Vulkan support

#include <GLES3/gl3.h>

#include <SDL2/SDL_opengles2.h>
#include <SDL2/SDL_video.h>

#include <cassert>
#include <mutex>

namespace Arclight::Rendering {

class GLRenderer final : public Renderer {
public:
    GLRenderer() = default;
    ~GLRenderer() override;

    int initialize(class WindowContext* context) override;

    void wait_device_idle() const override { glFinish(); }

    void render() override;

    void clear() override;

    void resize_viewport(const Vector2i& pixelSize) override;

    RenderPipeline::PipelineHandle
    create_pipeline(const Shader&, const Shader&,
                   const RenderPipeline::PipelineFixedConfig&) override;

    void destroy_pipeline(RenderPipeline::PipelineHandle) override;
    RenderPipeline& default_pipeline() override;

    void bind_pipeline(RenderPipeline::PipelineHandle pipeline) override;
    void bind_texture(Texture::TextureHandle texture) override;

    void draw(const Vertex* vertices, unsigned vertexCount, const Matrix4& transform = Matrix4()) override;
    Texture::TextureHandle allocate_texture(const Vector2u& size, Texture::Format format) override;
    void update_texture(Texture::TextureHandle, const void*) override;
    void destroy_texture(Texture::TextureHandle) override;

    const std::string& get_name() const override { return m_name; }
    
    constexpr GLenum TextureToGLFormat(Texture::Format format) {
        switch (format) {
        case Texture::Format_RGBA8_SRGB:
            return GL_RGBA8;
        case Texture::Format_RGB8_SRGB:
            return GL_RGB8;
        case Texture::Format_A8_SRGB:
            return GL_R8;
        default:
            assert(!"Invalid texture format");
            return GL_RGBA8;
        }
    }

private:
    struct GLTexture {
        GLuint id;

        Vector2u size;
        GLenum format;

        Texture::Format arclightFormat;
    };

    struct GLVBO {
        GLuint id;
    };

    // Update the viewport transform,
    // called on init and resize
    void UpdateViewportTransform();

    // Helps prevent rebinding the program across draw calls
    GLuint m_lastProgram;
    class GLPipeline* m_boundPipeline;

    // Uniform Buffer Object for the viewport transform
    GLuint m_transformUBO;

    GLVBO GetVertexBufferObject(unsigned vertexCount);
    GLuint m_vbo;

    WindowContext* m_windowContext;
    Transform m_viewportTransform;

    SDL_GLContext m_glContext;

    std::mutex m_glMutex;

#ifdef ARCLIGHT_PLATFORM_WASM
    const std::string m_name = "WebGL 2 (emulating OpenGL ES 3.0)";
#else
    const std::string m_name = "OpenGL ES 3.0";
#endif

    std::unique_ptr<RenderPipeline> m_defaultPipeline;
    std::set<class GLPipeline*> m_pipelines;

    std::set<GLTexture*> m_textures;
};

} // namespace Arclight::Rendering
