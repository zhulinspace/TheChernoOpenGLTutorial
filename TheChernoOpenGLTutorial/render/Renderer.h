#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"
class Renderer
{
private:

public:
	void Draw(const VertexArray &va,const IndexBuffer &ib, const Shader& shader)const;
	void Draw(const VertexArray &va, const VertexBuffer &vb, const Shader &shader)const;

	void Clear()const;
};