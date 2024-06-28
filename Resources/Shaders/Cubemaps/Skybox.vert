#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

layout (std140) uniform Camera
{
    mat4 projection;
    mat4 view;
}cam;

void main()
{
    TexCoords = aPos;

    mat4 newView = mat4(mat3(cam.view));
    vec4 pos = cam.projection * newView * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
} 