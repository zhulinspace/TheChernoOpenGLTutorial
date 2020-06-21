#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out  vec2 v_TexCoord;
out vec3 v_FragPos;
out vec3 v_Normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	v_FragPos = vec3( u_Model * vec4( position, 1.0 ));
	v_Normal = mat3( transpose( inverse( u_Model ) ) ) * normal;
	v_TexCoord = texCoord;

	gl_Position = u_Projection * u_View  *  vec4(v_FragPos, 1.0);
};

#shader fragment
#version 330 core

out vec4 color;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in  vec2 v_TexCoord;
in vec3 v_FragPos;
in vec3 v_Normal;

uniform vec3 u_viewPos;
uniform Material u_material;
uniform Light u_light;

//uniform sampler2D u_Texture;

void main()
{
	//ambient
	vec3 ambient = u_light.ambient * texture(u_material.diffuse, v_TexCoord).rgb;

	//diffuse
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize( u_light.position - v_FragPos);
	float diff = max( dot(norm, lightDir) , 0.0);
	vec3 diffuse = u_light.diffuse *diff *  texture(u_material.diffuse, v_TexCoord).rgb;

	//specular 
	vec3 viewDir = normalize(u_viewPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
	vec3 specular = u_light.specular * spec * texture (u_material.specular, v_TexCoord).rgb;

	vec3 res = ambient + diffuse + specular;
	color = vec4(res, 1.0);

	/*vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor;*/
};

