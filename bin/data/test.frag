#version 410

in vec3 o_normal;
in vec2 o_texcoord;

uniform sampler2D tex0;
uniform sampler2D u_textureA;

out vec4 outputColor;

void main()
{
    vec4 col    = texture(tex0, o_texcoord);
    outputColor = vec4(col.rgb, 1.0);
}

