#version 330 core

in vec4 oColor;
in vec2 oUV;

out vec4 FragColor;

void main()
{
    FragColor = oColor + vec4(oUV.x, oUV.y, 0, 0);
} 