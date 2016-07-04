#version 410

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 texcoord;

out vec2 o_texcoord;

void main()
{
    gl_Position = position;
    o_texcoord  = 0.5 * position.xy + 0.5;
}

