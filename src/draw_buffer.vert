#version 150 core
in vec4 pv;
void main(void)
{
    gl_Position.zw = vec2(1.0, 1.0);
    
    switch (gl_VertexID)
    {
        case 0:
            gl_Position.xy = vec2(-1.0f,  1.0f);
            break;

        case 1:
            gl_Position.xy = vec2(-1.0f, -1.0f);
            break;

        case 2:
            gl_Position.xy = vec2(1.0f, -1.0f);
            break;

        case 3:
            gl_Position.xy = vec2(1.0f,  1.0f);
            break;

        case 4:
            gl_Position.xy = vec2(-1.0f,  1.0f);
            break;

        case 5:
            gl_Position.xy = vec2(1.0f, -1.0f);
            break;
    }
}