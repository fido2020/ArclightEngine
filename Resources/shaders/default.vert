#version 450
#extension GL_ARB_separate_shader_objects : enable

layout( push_constant ) uniform Transform {
    mat4 transform;
};

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 colour;

layout(location = 0) out vec4 fragColour;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    gl_Position = transform * vec4(position, 0.0, 1.0);
    fragColour = colour;
    fragTexCoord = texCoord;
}
