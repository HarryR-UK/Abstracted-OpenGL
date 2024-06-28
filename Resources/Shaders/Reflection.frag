#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 u_cameraPos;
uniform samplerCube u_skybox;

uniform float u_materialType = 1.52;

void main()
{

    float ratio = 1.0 / u_materialType;

    vec3 I = normalize(Position - u_cameraPos);
    vec3 R = refract(I, normalize(Normal), ratio);

    FragColor = vec4(texture(u_skybox, R).rgb, 1.0);
    //FragColor = vec4(gl_FragCoord.z);

}