//Made by Daniel McGuinness

#version 450 core

layout(location = 0) in vec3 position; 
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv; 

//MVP vars
uniform mat4 modelview; 
uniform mat4 projection; 

uniform uint lightMode; 

out vec4 fragColour;
out vec2 fragTex; 

void main(){	

	vec3 direction = vec3(1.0f, 0.0f, 10.0f);
	vec4 homocoord = vec4(position, 1.0f);
	vec4 diffuseCol = vec4(1.0, 1.0, 1.0, 1.0); 

	//Diffuse Lighting
	mat3 matNorm = transpose(inverse(mat3(modelview)));
	vec3 normie = matNorm * normal; 
	normie = normalize(normie);
	direction = normalize(direction);
	float dotProd = max(dot(normie, direction), 0.0);
	vec4 diffuseL = dotProd * diffuseCol; 

	//Specular Lighting calcluations
	vec4 spec_col = vec4(1.0f, 0.0f, 1.0f, 1.0f); 
	float shine = 8; 
	vec4 mv_hom = modelview * homocoord;
	vec3 A = normalize(-mv_hom.xyz); 
	vec3 B = reflect(-direction, normie); 
	vec4 spec = pow(max(dot(B, A), 0), shine) * spec_col;

	if(lightMode == 0){
		fragColour = diffuseCol; 
	}
	else if(lightMode == 1){
		fragColour = (diffuseCol * 0.6) * diffuseL;
	}
	else if(lightMode == 2){
		fragColour = (diffuseCol * 0.6) * spec; 
	}

	//Combine Model-View-Projection model
	gl_Position =  projection * modelview * homocoord; 
	fragTex = uv; 

}