#pragma once
#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../render/Shader.h"
#include"../render/VertexArray.h"
#include"../render/VertexBuffer.h"
#include"../render/VertexBufferLayout.h"
#include"../render/Renderer.h"
#include"../render/Texture.h"
#include <GL/glew.h>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 tangent;
	glm::vec3 bitangent;

};



class Mesh
{
public:
	std::vector<Vertex>		vertices;
	std::vector<unsigned int>indices;
	std::vector<SimpleTextureStruct>		textures;
	unsigned int VAO;
	//VertexArray *va;
	Mesh(std::vector<Vertex>vertices, std::vector<unsigned int>indices, std::vector<SimpleTextureStruct>textures);
	void Draw(Shader shader);
private:
	unsigned int  VBO, EBO;
	/*VertexBuffer *vb;
	IndexBuffer *ib;*/
	void SetUpMesh();
};

