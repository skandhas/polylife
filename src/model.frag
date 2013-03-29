#version 150 core
out vec4 fc;
uniform sampler2D texture_id;
smooth in vec4 out_color;
void main(void)
{
    fc = out_color;
}