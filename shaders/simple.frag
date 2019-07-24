//Made by Daniel McGuinness
//31/10/18

#version 450 core

in vec4 fragColour;
in vec2 fragTex; 

uniform sampler2D texColour; 
uniform uint texMode; 

out vec4 outputColour;

void main()
{
	
	if(texMode == 0){
		outputColour = texture(texColour, fragTex) * fragColour; 
	} else {
		outputColour= fragColour; 
	}
}