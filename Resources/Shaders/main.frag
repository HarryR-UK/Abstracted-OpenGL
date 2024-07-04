#version 330 core

out vec4 FragColor;

in VS_OUT
{
    vec2 texCoords;
    vec3 normal;
    vec3 fragPos;
}fs_in;

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    vec3 diffuse;
    float shininess;
};

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;

uniform DirectionalLight directionalLight;

uniform vec3 u_cameraPos;

vec3 calcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    vec3 halfwayDir = normalize(lightDir + viewDir);


    float diff = max(dot(normal, lightDir), 0.0);


    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

    vec3 diffuse = light.diffuse * diff * material.diffuse;// * texture(material.texture_diffuse1, fs_in.texCoords).rgb;
    vec3 ambient = light.ambient * material.diffuse;//texture(material.texture_diffuse1, fs_in.texCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.texture_specular1, fs_in.texCoords).rgb;

    return (ambient + diffuse + specular);
}

void main()
{
    vec3 norm = normalize(fs_in.normal);
    vec3 viewDir = normalize(u_cameraPos - fs_in.fragPos);
    vec3 result = calcDirectionalLight(directionalLight, norm, viewDir);

    FragColor = vec4(result, 1.0);

}