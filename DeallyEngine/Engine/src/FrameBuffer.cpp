#include "FrameBuffer.h"
#include "Commendefine.h"
FrameBuffer::FrameBuffer() : m_textureid(0), m_fbo(0), m_BufferData(NULL)
{
}

FrameBuffer::~FrameBuffer()
{
	if (m_BufferData)
	{
		delete[] m_BufferData;
		m_BufferData = NULL;
	}

	DestroyFBO();
	glDeleteTextures(1, &m_textureid);
	m_textureid = 0;
}



bool FrameBuffer::CreateFBO(GLuint m_width, GLuint m_height)
{
	GLint maxRenderbufferSize = 0;
	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderbufferSize);

	if ((maxRenderbufferSize <= m_width) || (maxRenderbufferSize <= m_height))
	{
		return false;
	}

	// 创建FBO
	glGenFramebuffers(1, &m_fbo);
	glGenRenderbuffers(1, &m_depthrbo);
	//创建Texture
	glGenTextures(1, &m_textureid);
	glBindTexture(GL_TEXTURE_2D, m_textureid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	// 绑定rbo创建一个16-bit depthbuffer
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthrbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_width, m_height);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	//Texture 作为color attachment
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureid, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthrbo);
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		return false;
	}

	m_Width = m_width;
	m_Height = m_height;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}

void FrameBuffer::UseFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void FrameBuffer::EndFBO()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::DestroyFBO()
{
	if (m_fbo != 0)
	{
		glDeleteFramebuffers(1, &m_fbo);
		m_fbo = 0;
	}
}



bool FrameBuffer::SaveToBmp(const char* filename, GLuint TextureId, GLuint width, GLint height)
{
	GLint maxRenderbufferSize = 0;
	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderbufferSize);

	if ((maxRenderbufferSize <= width) || (maxRenderbufferSize <= height))
	{
		return false;
	}

	if (filename == NULL || TextureId == 0 || width == 0 || height == 0)
	{
		return false;
	}

	GLuint offscreen_framebuffer = 0;
	//unsigned char* output_image = new unsigned char[width * height * 3];
	GLint pixelLength = width * height * sizeof(GLubyte) * 3;
	GLubyte * pixelDate = NULL;
	FILE * wfile = NULL;
	//打开文件
	wfile = fopen(filename, "wb");
	fwrite(head, 54, 1, wfile);
	//更改grab.bmp的头文件中的高度和宽度
	fseek(wfile, 0x0012, SEEK_SET);
	fwrite(&width, sizeof(width), 1, wfile);
	fwrite(&height, sizeof(height), 1, wfile);
	//为像素分配内存
	pixelDate = (GLubyte*)malloc(pixelLength);

	if (pixelDate == 0)
	{
		//printf("/a/n分配内存失败!");
	}

	glBindTexture(GL_TEXTURE_2D, TextureId);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, pixelDate);
	//写入像素数据
	fseek(wfile, 0, SEEK_END);
	fwrite(pixelDate, pixelLength, 1, wfile);
	fclose(wfile);
	free(pixelDate);
}

char* FrameBuffer::GetTexData(GLuint m_texId, GLuint x, GLuint y, GLuint width, GLuint height)
{
	GLuint mfbo = 0;
	GLuint sizeLenth = (width) * (height) * 3 * sizeof(char);

	if (x > width)
	{
		x = 0;
	}

	if (y > height)
	{
		y = 0;
	}

	if (m_BufferData == NULL)
	{
		m_BufferData = new char[sizeLenth];
		memset(m_BufferData, 255, sizeLenth);
	}

	//
	//生成FBO
	//glClear(GL_COLOR_BUFFER_BIT);
	//Generate a new FBO. It will contain your texture.
	glGenFramebuffers(1, &mfbo);
	glBindFramebuffer(GL_FRAMEBUFFER, mfbo);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texId);
	//Bind the texture to your FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texId, 0);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthrbo);
	//Test if everything failed
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		return NULL;
	}

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//Bind the FBO
	glBindFramebuffer(GL_FRAMEBUFFER, mfbo);
	// set the viewport as the FBO won't be the same dimension as the screen
	//glViewport(0, 0, width, height);
	// 读取像素
	//获取Texture数据
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glReadPixels(x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, m_BufferData);
	//
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &mfbo);
	return  m_BufferData;
}

//将m_texId写到绑定到FBO的m_textureid中，[x, y, m_width,m_height]为区域位置 [desX, desY]为在大图中的偏移
void FrameBuffer::TransferFromTexture(GLuint m_texId, GLuint x, GLuint y, GLuint m_width, GLuint m_height, GLuint desX, GLuint desY)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	char *data = GetTexData(m_texId, x, y, m_width, m_height);
	glBindTexture(GL_TEXTURE_2D, m_textureid);
	glTexSubImage2D(GL_TEXTURE_2D, 0, desX, desY, (m_width), (m_height), GL_RGB, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
}