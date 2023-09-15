#type vertex
#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec4 a_Colour;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjectionMatrix;

out vec4 v_Colour;
//out vec2 v_TexCoord;

void main() {
	gl_Position = u_ViewProjectionMatrix * vec4(a_Pos, 1.0);
	//v_TexCoord = a_TexCoord;
	v_Colour = a_Colour;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Colour;
//in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main() {
	// color = texture(u_Texture, v_TexCoord) * v_Colour;
	color = v_Colour;
}
