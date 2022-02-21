#version 330 core
layout (location = 0) in vec4 vertex; 

out vec2 TexCoords;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float height;

void main()
{
    TexCoords = vertex.zw;
    gl_Position = projection * view * model * vec4(vertex.x, height, vertex.y, 1.0);
    FragPos = vec3(model * vec4(vertex.x, height, vertex.y, 1.0));
}