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
