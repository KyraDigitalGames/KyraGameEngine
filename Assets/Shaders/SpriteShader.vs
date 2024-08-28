#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUV;

out vec4 oColor;
out vec2 oUV;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 1.0, 1.0);
	oColor = aColor;
	oUV = aUV;
}