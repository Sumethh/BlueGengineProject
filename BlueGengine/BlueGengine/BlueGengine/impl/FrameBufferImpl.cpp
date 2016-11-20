#include "FrameBufferImpl.h"
#include <gl/glew.h>
#include "../ApplicationWindow.h"
#define SCR_WIDTH 1280
#define SCR_HEIGHT 720


namespace BlueGengine
{
	OpenGLFrameBuffer::OpenGLFrameBuffer()
	{
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{

	}

	void OpenGLFrameBuffer::Recreate()
	{
		if (mFB)
		{
			glDeleteFramebuffers(1, &mFB);
		}

		glGenFramebuffers(1, &mFB);
		CreateColorBuffers();
	}

	void OpenGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFB);
	}

	void OpenGLFrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLFrameBuffer::CreateColorBuffers()
	{
		ApplicationWindow* currentWindow = ApplicationWindow::GetCurrentWindow();

		uint32 w = currentWindow->GetWindowWidth();
		uint32 h = currentWindow->GetWindowHeight();
		// - Position color buffer
		glGenTextures(1, &mPosition);
		glBindTexture(GL_TEXTURE_2D, mPosition);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, w, h, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mPosition, 0);

		// - Normal color buffer
		glGenTextures(1, &mNormal);
		glBindTexture(GL_TEXTURE_2D, mNormal);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, w, h, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, mNormal, 0);

		// - Color + Specular color buffer
		glGenTextures(1, &mColorSpec);
		glBindTexture(GL_TEXTURE_2D, mColorSpec);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, mColorSpec, 0);

		// - Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
		GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
		glDrawBuffers(3, attachments);
	}

}