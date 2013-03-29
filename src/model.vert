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
in vec3 pv;
in vec4 cv;
uniform sampler2D texture_id;
uniform int texture_size;
uniform mat4 mvpMatrix;
smooth out vec4 out_color;

void main(void)
{
    vec3 invLight = normalize(inverse(mvpMatrix) * vec4(1.0, 1.0, 0.0, 0.0)).xyz;
    float diffuse = clamp(dot(cv.xyz, invLight), 0.1, 0.9);
    out_color = vec4(vec3(0.3, 0.3, 0.3) * diffuse, 1.0);
    gl_Position = mvpMatrix * vec4(pv.xyz, 1.0);
    
    int face_index = int(cv.w);
    vec2 tex_pos = vec2(face_index % texture_size, face_index / texture_size) * 1.0 / texture_size;
    
    vec4 col = texture(texture_id, tex_pos);
    if (col.r != 0.0)
    {
        out_color += vec4(col.r, diffuse, 0.8 * (1.0 - diffuse), 1.0);
    }
    else
    {
        out_color.a = 0.2;
    }
}
