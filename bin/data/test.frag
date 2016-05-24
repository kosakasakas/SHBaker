#version 410

in vec3 o_normal;
in vec2 o_texcoord;

out vec4 outputColor;

void main()
{
    outputColor = vec4(o_normal, 1.0);
}

