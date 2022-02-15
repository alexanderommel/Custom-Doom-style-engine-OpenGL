#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 plane_color;
uniform float x_scale_factor;
uniform float y_scale_factor;
uniform float ambientStrength;

void main()
{    
    vec3 ambient = ambientStrength * vec3(1.0,1.0,1.0);
    vec2 scaled_coordinates = vec2(x_scale_factor * TexCoords.x , y_scale_factor * TexCoords.y);
    color = vec4(ambient,1.0) * texture(image, scaled_coordinates);
} 