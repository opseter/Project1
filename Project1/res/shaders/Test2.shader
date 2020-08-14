#shader vertex
#version 330 core
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 u_MVP;
out vec2 TexCoord;

void main()
{
	gl_Position = u_MVP*aPos ;

	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
#shader fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;


void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = texture(texture1, TexCoord);
}

