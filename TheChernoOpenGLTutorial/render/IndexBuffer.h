#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int *data, unsigned int count);
	//������������������65535��Ҳ����unsigned short ��Լ�ڴ�
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	// const means in this function it won't modify anything 

	inline unsigned int GetCount() const { return m_Count; }
	// TODO: lock and unlocks
protected:

};