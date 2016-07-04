#version 410
#
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 texcoord;

out vec3 o_normal;
out vec2 o_texcoord;
out vec2 o_texcoordSH;

void main()
{
    gl_Position = modelViewProjectionMatrix * position;
    mat3 mv3    = mat3(modelViewMatrix);
    mat3 NMat = transpose(inverse(mv3)); 
    o_normal    = normalize(NMat * normal.rgb);
    o_texcoord  = texcoord;
    o_texcoordSH = 0.5 * vec2(normal.x + 1.0, 1.0 - normal.y);
}

