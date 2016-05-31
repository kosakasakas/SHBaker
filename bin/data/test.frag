#version 410

in vec3 o_normal;
in vec2 o_texcoord;

uniform sampler2D u_SHTex;
uniform int u_Channel;

out vec4 outputColor;

const float PI = 3.141592653589793238462643383;

vec4 VisualizeSH(float val)
{
    float R = max(-val, 0.0);
    float G = max(val, 0.0);
    return vec4(R, G, 0.0, 1.0);
}

vec3 AddSign(vec4 inCol)
{
    vec3 outCol;
    int tmp = int(inCol.a *255.0);
    if (tmp / 4 == 1)
    {
        tmp -= 4;
        outCol.b = inCol.b;
    }
    else
    {
        outCol.b = -inCol.b;
    }

    if(tmp / 2 == 1)
    {
        tmp -= 2;
        outCol.g = inCol.g;
    }
    else
    {
        outCol.g = -inCol.g;
    }

    if(tmp == 1)
    {
        outCol.r = inCol.r;
    }
    else
    {
        outCol.r = -inCol.r;
    }

    return outCol;
}

vec2 GetTexCoord(vec3 dir)
{
    float theta, phi;
    if (dir.x == 0.0)
    {
        theta = 0.5 * PI;
        phi   = acos(dir.y);
    }
    else if (dir.x == 1.0)
    {
        theta   = 0.0;
        phi = 0.0;
    }
    else
    {
        theta = acos(dir.x);
        phi   = acos(dir.y / sin(theta));
    }
    vec2 coord = vec2(theta / PI, phi * 0.5 / PI);
    return coord;
}

void main()
{
    vec2 shCoord    = GetTexCoord(o_normal);
    vec4 col    = texture(u_SHTex, shCoord);
    vec3 singedCol  = AddSign(col);

    if (u_Channel == 0)
    {
        outputColor = VisualizeSH(singedCol.r);
    }
    else if (u_Channel == 1)
    {
        outputColor = VisualizeSH(singedCol.g);
    }
    else if (u_Channel  == 2)
    {
        outputColor = VisualizeSH(singedCol.b);
    }
    else
    {
        outputColor = vec4(1.0);
    }
}

