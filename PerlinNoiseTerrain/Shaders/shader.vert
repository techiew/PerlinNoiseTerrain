#version 330 core

in vec3 position;
in vec2 texCoord;
in vec3 normal;

out vec2 f_texCoord;
out vec3 f_normal;
out vec3 f_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	f_texCoord = texCoord;
	//f_normal = normalize((transpose(inverse(view * model)) * vec4(normal, 1.0)).xyz);
	f_normal = normalize(model * vec4(normal, 0)).xyz;
	gl_Position = projection * view * model * vec4(position, 1.0);
	f_position = (model * vec4(position, 1)).xyz;
}