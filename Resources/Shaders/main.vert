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

out VS_OUT{
    vec2 texCoords;
    vec3 normal;
    vec3 fragPos;
}vs_out;


void main()
{
    gl_Position = cam.projection * cam.view * u_model * vec4(aPos, 1.0);
    vs_out.texCoords = aTexCoords;

    vs_out.normal = mat3(transpose(inverse(u_model))) * aNormal;

    vs_out.fragPos = vec3(u_model * vec4(aPos, 1.0));

}

