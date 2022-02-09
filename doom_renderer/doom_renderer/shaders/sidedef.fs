#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 sidedef_color;
uniform float x_scale_factor;
uniform float y_scale_factor;

void main()
{    
    vec2 scaled_coordinates = vec2(x_scale_factor * TexCoords.x , y_scale_factor * TexCoords.y);
    
    color = vec4(sidedef_color, 1.0) * texture(image, scaled_coordinates) ;
} 