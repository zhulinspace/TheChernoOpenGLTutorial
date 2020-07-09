#pragma once
#include "GLErrorMessage.h"
struct SimpleTextureStruct
{
	unsigned int id;
	std::string type;
	std::string path;
};
class Texture
{
private:
	
	unsigned char *m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	
public:
	//SimpleTextureStruct m_Texture;

	unsigned int m_RendererID;
	std::string m_FilePath;
	std::string m_TextureMapType;//纹理贴图的类型 

	Texture():m_RendererID(0), m_FilePath(""), m_LocalBuffer(nullptr), m_Height(0), m_Width(0), m_BPP(0) {}
	Texture(const std::string &path);
	~Texture();

	void Bind(unsigned int slot=0) const;
	void Unbind()const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

protected:
};



