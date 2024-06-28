#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

layout (std140) uniform Camera
{
    mat4 projection;
    mat4 view;
}cam;

uniform mat4 u_model;

out vec3 Position;
out vec3 Normal;

void main()
{
    Normal = mat3(transpose(inverse(u_model))) * aNormal;
    Position = vec3(u_model * vec4(aPos, 1.0));
    gl_Position = cam.projection * cam.view * u_model * vec4(aPos, 1.0);
    // gl_PointSize = gl_Position.z;
}
