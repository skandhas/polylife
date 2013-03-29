#version 150 core
uniform sampler2D texture_id;
uniform vec2 screen;
uniform int mode;
out vec4 fc;

vec4 getfc(int x, int y)
{
    return texture(texture_id, (vec2(gl_FragCoord.x + x, gl_FragCoord.y + y) / screen));
}

void main(void)
{
    vec2 tex_pos;
    int i, j;
    vec4 col = texture(texture_id,gl_FragCoord.xy / screen);
    
    switch(mode)
    {
        case 0:
            fc = col;
            break;
        case 1:
            if (col.g < 0.5f)
            {
                for (i = -2; i < 5; ++i)
                {
                    for (j = -2; j < 5; ++j)
                    {
                        fc += getfc(i, j);
                    }
                }
                    
                fc /= 20;
                fc.a = max(fc.a - fc.g, 0.1);
            }
            else
            {
                fc = col;
            }
            
            break;
    }
}