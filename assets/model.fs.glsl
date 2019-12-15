#version 420 core

in VertexData
{
    vec3 vertex;
    vec3 normal;
    vec2 texCoord;

} vertexData;

in BlinnPhongData
{
    vec3 fragPos;
    vec3 normal;

} blinnPhongData;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float ambientStrength;
uniform vec3 ambientAlbedo;
uniform vec3 diffuseAlbedo;
uniform vec3 specularAlbedo;
uniform int specularPower;

layout(location = 0) out vec4 fragColor;


void flatShader()
{
    fragColor = vec4(0.2, 0.2, 0.2, 1.0);
}

void normalAsColor()
{
    fragColor = vec4(vertexData.normal, 1.0);
}

void blinn_phong()
{
    // Ambient
    vec3 ambient = ambientStrength * ambientAlbedo;

    // Diffuse
    vec3 normal_unit = normalize(blinnPhongData.normal);
    vec3 light_dir_unit = normalize(lightPos - blinnPhongData.fragPos);
    float diffuse_value = max(dot(normal_unit, light_dir_unit), 0.0);
    vec3 diffuse = diffuse_value * diffuseAlbedo;

    // Specular
    vec3 view_dir_unit = normalize(viewPos - blinnPhongData.fragPos);
    vec3 reflect_unit = reflect(-light_dir_unit, normal_unit);
    /*float specular_value = pow(   // this is Phong
        max(dot(view_dir_unit, reflect_unit), 0.0), specularPower);*/
    vec3 halfway_unit = normalize(light_dir_unit + view_dir_unit);
    float specular_value = pow(
        max(dot(normal_unit, halfway_unit), 0.0), specularPower);
    vec3 specular = specular_value * specularAlbedo;

    // Ambient + Diffuse + Specular
    float model_color = 1.0;
    vec3 mix = (ambient + diffuse + specular) * model_color;
    fragColor = vec4(mix, 1.0);
}


void main()
{
    blinn_phong();
}