#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_Textures[16];
in vec2  v_TexCoord;
in vec4  v_Color;
in float v_TexIndex;

void main()
{
    color = texture(u_Textures[int(v_TexIndex)], v_TexCoord) * v_Color;
}
