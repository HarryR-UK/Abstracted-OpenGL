#version 330 core

out vec4 FragColor;

in vec2 texCoords;

uniform int u_screenWidth;
uniform int u_screenHeight;

uniform sampler2D screenTexture;


void main()
{
    float xOffset = 1.0 / (u_screenWidth);
    float yOffset = 1.0 / (u_screenHeight);

    vec2 offsets[9] = vec2[]
    (
        vec2(-xOffset, yOffset), vec2(0.0, yOffset), vec2(xOffset, yOffset),
        vec2(-xOffset, 0.0), vec2(0.0, 0.0), vec2(xOffset, 0.0),
        vec2(-xOffset, -yOffset), vec2(0.0, -yOffset), vec2(xOffset, -yOffset)
    );

    float kernel[9] = float[]
    (
        1, 1, 1,
        1, -8, 1,
        1, 1, 1
    );


    vec3 color = vec3(0.0);
    for (int i = 0; i < 9; ++i)
    {
        color += vec3(texture(screenTexture, texCoords.st + offsets[i])) * kernel[i];
    }

    //FragColor = vec4(color, 1.0);
    FragColor = vec4(texture(screenTexture, texCoords).rgb, 1.0);

}