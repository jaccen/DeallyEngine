#ifndef ENGINE_FRAMEBUFFER_H
#define ENGINE_FRAMEBUFFER_H
#include "Utils.h"

class FrameBuffer
{
public:
    FrameBuffer();
    virtual ~FrameBuffer();

public:
    bool CreateFBO(GLuint m_width, GLuint m_height);
    void UseFBO();
    void EndFBO();
    void DestroyFBO();
    bool SaveToBmp(const char* filename, GLuint TextureId, GLuint width, GLint height);
public:
    const GLuint  GetTextureId() const
    {
        return m_textureid;
    }
    const GLuint GetWidth() const
    {
        return m_Width;
    }
    const GLuint GetHeight() const
    {
        return m_Height;
    }
    const GLuint GetDepthTextureId() const
    {
        return m_depthrbo;
    }
    const GLuint GetFBOId() const
    {
        return m_fbo;
    }
    const char* GetBufferTexData()const
    {
        return m_BufferData;
    }
    // 将TexId数据写到FBo绑定的Tex中
    void  TransferFromTexture(GLuint m_texId, GLuint x, GLuint y, GLuint m_width, GLuint m_height, GLuint desX, GLuint desY);
protected:
    char* GetTexData(GLuint m_texId, GLuint x, GLuint y, GLuint width, GLuint height);
private:
    char*  m_BufferData = nullptr;
    GLuint m_fbo = 0;
    GLuint m_textureid = 0;
    GLuint m_depthrbo = 0;
    GLuint m_Width;
    GLuint m_Height;
};
#endif