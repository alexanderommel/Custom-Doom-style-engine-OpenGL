#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 plane_color;
uniform float x_scale_factor;
uniform float y_scale_factor;
uniform float ambientStrength;
uniform vec3 aNormal;
uniform vec3 lightPos; 
uniform vec3 lightColor; 
in vec3 FragPos;
uniform vec3 viewPos;
float specularStrength = 0.55;
uniform int noSpecular;
uniform int num_lights;

// Directional Light struct
struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

// Point lights struct
struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define NR_POINT_LIGHTS 30
uniform PointLight pointLights[NR_POINT_LIGHTS];

// material ambient and diffuse is equal to surface color
struct Material {
    vec3 specular;
    float shininess;
}; 
  
uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 colorx);  
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 color); 

void main()
{    

    vec2 scaled_coordinates = vec2(x_scale_factor * TexCoords.x , y_scale_factor * TexCoords.y);
    vec4 surface_color4 = texture(image, scaled_coordinates);
    vec3 surface_color = vec3(surface_color4);

    // properties
    vec3 norm = normalize(aNormal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // directional lights
    vec3 result = CalcDirLight(dirLight, norm, viewDir, surface_color );
    // point lights
    for(int i = 0; i<num_lights+1; i++){
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir, surface_color );
    }

    color = vec4(result, 1.0);

    
} 


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 colorx){
    
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient  * colorx;
    vec3 diffuse = light.diffuse * diff * colorx;
    vec3 specular;
    if(noSpecular==1){
	specular = light.specular * spec * colorx;
	}else{
	specular = light.specular * spec * material.specular;
    }
    
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, 
vec3 viewDir, vec3 color){
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = light.ambient * color;
    vec3 diffuse = light.diffuse * diff * color;
    vec3 specular;
    if(noSpecular==1){
	specular = light.specular * spec * color;
	}else{
	specular = light.specular * spec * material.specular;
    }
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}