#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

layout(std140) uniform Camera
{
    mat4 projection;
    mat4 view;
} cam;


uniform mat4 u_model;

void main()
{
    gl_Position = cam.projection * cam.view * u_model * vec4(aPos, 1.0);
    gl_PointSize = (1 / gl_Position.z) * 50;
}