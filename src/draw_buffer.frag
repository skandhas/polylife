/*
 
 Copyright (c) 2013 h2so5 <mail@h2so5.net>
 
 This software is provided 'as-is', without any express or implied
 warranty. In no event will the authors be held liable for any damages
 arising from the use of this software.
 
 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:
 
 1. The origin of this software must not be misrepresented; you must not
 claim that you wrote the original software. If you use this software
 in a product, an acknowledgment in the product documentation would be
 appreciated but is not required.
 
 2. Altered source versions must be plainly marked as such, and must not be
 misrepresented as being the original software.
 
 3. This notice may not be removed or altered from any source
 distribution.
 
 */

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