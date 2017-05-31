#include "GraphicsDevice/OpenGlGraphicsDevice.h"
#include "Core/Log.h"
#include "GraphicsDevice/DataDescriptor.h"

#include <gl/glew.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.inl>


static GLenum bufferBits[] =
{
	GL_DEPTH_BUFFER_BIT,
	GL_COLOR_BUFFER_BIT
};


int GetGlEnumFromBufferBit(BufferBit aBit)
{
	int returningValue = 0;

	if (((uint8)aBit & (uint8)BufferBit::Color) != 0)
	{
		returningValue |= GL_COLOR_BUFFER_BIT;
	}

	if (((uint8)aBit & (uint8)BufferBit::DepthBit) != 0)
	{
		returningValue |= GL_DEPTH_BUFFER_BIT;
	}

	return returningValue;
}

GLenum GetEnumFromPrecision(EPrecisionType aPrecision)
{
  switch (aPrecision)
  {
  case EPrecisionType::RGB_F_16Bit:
    return GL_RGB16F;
    break;
  case EPrecisionType::RGB_F_32Bit:
    return GL_RGB32F;
    break;

  case EPrecisionType::RGB_4Bit:
    return GL_RGB4;
  case EPrecisionType::RGB_8Bit:
    return GL_RGB8;
  case EPrecisionType::RGB_10Bit:
    return GL_RGB10; 
  case EPrecisionType::RGB_12Bit:
      return GL_RGB12;


  case EPrecisionType::RGBA_F_16Bit:
    return GL_RGBA16F;
    break;
  case EPrecisionType::RGBA_F_32Bit:
    return GL_RGBA32F;
    break;

  case EPrecisionType::RGBA_2Bit:
    return GL_RGBA2;
    break;
  case EPrecisionType::RGBA_4Bit:
    return GL_RGBA4;
  case EPrecisionType::RGBA_8Bit:
    return GL_RGBA8;
  case EPrecisionType::RGBA_12Bit:
    return GL_RGBA12; 
  case EPrecisionType::RGBA_16Bit:
      return GL_RGBA16;

    break; 
    InvalidDefaultCase

  }
}


GLenum GetDataTypeEnumFromPrecision(EPrecisionType aType)
{
  switch (aType)
  {
  case EPrecisionType::RGB_F_16Bit:
  case EPrecisionType::RGB_F_32Bit:
  case EPrecisionType::RGBA_F_16Bit:
  case EPrecisionType::RGBA_F_32Bit:
    return GL_FLOAT;
    break;
  case EPrecisionType::RGB_4Bit:
  case EPrecisionType::RGB_8Bit:
  case EPrecisionType::RGB_10Bit:
  case EPrecisionType::RGB_12Bit:
  case EPrecisionType::RGBA_2Bit:
  case EPrecisionType::RGBA_4Bit:
  case EPrecisionType::RGBA_8Bit:
  case EPrecisionType::RGBA_12Bit:
  case EPrecisionType::RGBA_16Bit:
    return GL_UNSIGNED_BYTE;
    break;
    InvalidDefaultCase
  }

}
GLenum GetEnumFromImageFormat(EImageFormat aFormat)
{
  switch (aFormat)
  {
  case EImageFormat::RGB:
    return GL_RGB;
    break;
  case EImageFormat::RGBA:
    return GL_RGBA;
    break;
  default:
    break;
  }
}

GLenum GetEnumFromTextureParameter(ETextureParameter aParameter)
{
  switch (aParameter)
  {
  case MinFilter:
    return GL_TEXTURE_MIN_FILTER;
    break;
  case MagFilter:
    return GL_TEXTURE_MAG_FILTER;
    break;
  case Nearest:
    return GL_NEAREST;
    break;    
    InvalidDefaultCase

  }
}

GLenum GetEnumFromTextureID(ETextureID aID)
{
  switch (aID)
  {
  case Texture0:
    return GL_TEXTURE0;
    break;
  case Texture1:
    return GL_TEXTURE1;
    break;
  case Texture2:
    return GL_TEXTURE2;
    break;
  case Texture3:
    return GL_TEXTURE3;
    break;
  case Texture4:
    return GL_TEXTURE4;
    break;
  case Texture5:
    return GL_TEXTURE5;
    break;
  case Texture6:
    return GL_TEXTURE6;
    break;
  case Texture7:
    return GL_TEXTURE7;
    break;
  case Texture8:
    return GL_TEXTURE8;
    break;
  case Texture9:
    return GL_TEXTURE9;
    break;
    InvalidDefaultCase
  }
}

GLenum GetEnumFromAttachment(EBufferAttachment aAttachment)
{
  switch (aAttachment)
  {
  case Attachment0:
    return GL_COLOR_ATTACHMENT0;
    break;
  case Attachment1:
    return GL_COLOR_ATTACHMENT1;
    break;
  case Attachment2:
    return GL_COLOR_ATTACHMENT2;
    break;
  case Attachment3:
    return GL_COLOR_ATTACHMENT3;
    break;
  case Attachment4:
    return GL_COLOR_ATTACHMENT4;
    break;
  case Attachment5:
    return GL_COLOR_ATTACHMENT5;
    break;
  case Attachment6:
    return GL_COLOR_ATTACHMENT6;
    break;
  case Attachment7:
    return GL_COLOR_ATTACHMENT7;
    break;
  case Attachment8:
    return GL_COLOR_ATTACHMENT8;
    break;
  case Attachment9:
    return GL_COLOR_ATTACHMENT9;
    break;
  case Attachment10:
    return GL_COLOR_ATTACHMENT10;
    break;
  case Attachment11:
    return GL_COLOR_ATTACHMENT11;
    break;
  case Attachment12:
    return GL_COLOR_ATTACHMENT12;
    break;
  case Attachment13:
    return GL_COLOR_ATTACHMENT13;
    break;
  case Attachment14:
    return GL_COLOR_ATTACHMENT14;
    break;
  default:
    break;
  }
}

OpenGlGraphicsDevice::OpenGlGraphicsDevice() : IGraphicsDevice(EGraphicsDeviceType::OpenGL)
{

}

OpenGlGraphicsDevice::~OpenGlGraphicsDevice()
{
	ShutDown();
}

void OpenGlGraphicsDevice::Init()
{
	if (GLenum errCode = glewInit() != GLEW_OK)
	{
		Log::Error("Glew failed to initialize");
		BlueAssert(false);
	}

	Log::Info("Opengl Graphics device initialized");
	OpenGLResource r = {};
	mResources.emplace_back(std::move(r));
	glDepthFunc(GL_LESS);
}

void OpenGlGraphicsDevice::ShutDown()
{
	for (auto& resource : mResources)
	{
		DeleteResource(resource);
	}

	mResources.clear();
}

uint32 OpenGlGraphicsDevice::CreateGraphicsResource(EGraphicsResourceType aType)
{
	if (mFreeResources.size())
	{
		OpenGLResource* r = mFreeResources.front();
		mFreeResources.pop();

		r->resourceType = aType;
		CreateResource(*r);
		BlueAssert(glGetError() == 0);
		ASSERT_NO_GRAPHICS_ERROR();

		return r->id;
	}
	else
	{
		OpenGLResource r = {};
		r.resourceType = aType;
		CreateResource(r);
		r.id = (uint32)mResources.size();
		mResources.emplace_back(std::move(r));
		BlueAssert(glGetError() == 0);
		ASSERT_NO_GRAPHICS_ERROR();
		return r.id;
	}

}

void OpenGlGraphicsDevice::DeleteGraphicsResource(uint32& aResourceID)
{
	BlueAssert(aResourceID < mResources.size() && aResourceID);

	OpenGLResource* r = &mResources[aResourceID];
	DeleteResource(*r);
	mFreeResources.push(r);
	aResourceID = 0;
	ASSERT_NO_GRAPHICS_ERROR();
}

void OpenGlGraphicsDevice::UpdateResourceData(const uint32 aResourceID, size_t aOffset, void* aData, uint64 aDataSize, DataDescriptor* aDescriptors, uint32 aDescriptorCount)
{
	BlueAssert(aResourceID);
	BlueAssert(aResourceID < mResources.size());

	OpenGLResource& updatingResource = mResources[aResourceID];

	switch (updatingResource.resourceType)
	{
		case EGraphicsResourceType::ElementBuffer:
			UpdateElementBuffer(updatingResource, aData, aDataSize);
			break;

		case EGraphicsResourceType::VertexBuffer:
			UpdateVertexBuffer(updatingResource, aOffset, aData, aDataSize, aDescriptors, aDescriptorCount);
			break;
			InvalidDefaultCaseExtraStep(Log::Error("Tried updating an invalid resource"));
	}

	ASSERT_NO_GRAPHICS_ERROR();
}

void OpenGlGraphicsDevice::UpdateResourceData(const uint32 aResourceID, ubyte* aPixels, uint32 aWidth, uint32 aHeight, EPrecisionType aTexturePrecision, EImageFormat aPixelFormat, uint32 aMipMapLevel)
{
	BlueAssert(aResourceID);
	OpenGLResource& updatingResource = mResources[aResourceID];
	BlueAssert(updatingResource.resourceType == EGraphicsResourceType::Texture2D && aPixels && aWidth && aHeight);

  GLenum pixelFormat, textureFormat;
  pixelFormat = GetEnumFromImageFormat(aPixelFormat);
  textureFormat = GetEnumFromPrecision(aTexturePrecision);

	BindResource(updatingResource);
	glTexImage2D(GL_TEXTURE_2D, aMipMapLevel, texture
    0Format, aWidth, aHeight, 0, pixelFormat, GL_UNSIGNED_BYTE, aPixels);
  ASSERT_NO_GRAPHICS_ERROR();

	glGenerateMipmap(GL_TEXTURE_2D);
	UnBindResource(updatingResource);
	ASSERT_NO_GRAPHICS_ERROR();
}

void OpenGlGraphicsDevice::UpdateResourceData(const uint32 aResourceID, const uint32 aWidth, const uint32 aHeight, EPrecisionType aType)
{
  BlueAssert(aResourceID && aResourceID < mResources.size());
  BlueAssert(aWidth && aHeight);
  OpenGLResource& resource = mResources[aResourceID];

  BindResource(resource);
  glTexImage2D(GL_TEXTURE_2D, 0, GetEnumFromPrecision(aType), aWidth, aHeight, 0, GetEnumFromPrecision(aType), GetDataTypeEnumFromPrecision(aType), 0);
  UnBindResource(resource);
  ASSERT_NO_GRAPHICS_ERROR();
}

void OpenGlGraphicsDevice::UpdateResourceData(const uint32 aResourceID, const ETextureParameter aParameter, const ETextureParameter aValue)
{
  BlueAssert(aResourceID && aResourceID < mResources.size());
  GLenum parameter, value;
  parameter = GetEnumFromTextureParameter(aParameter);
  value = GetEnumFromTextureParameter(aValue);
  OpenGLResource& resource = mResources[aResourceID];

  BindResource(resource);
  glTextureParameteri(GL_TEXTURE_2D, parameter, value);
  UnBindResource(resource);
  
  ASSERT_NO_GRAPHICS_ERROR();
}

void OpenGlGraphicsDevice::UpdateResourceData(const uint32 aResourceID, char* aVertexShaderPath, char* aFragmentShaderPath)
{
	BlueAssert(aResourceID);
	OpenGLResource& updatingResource = mResources[aResourceID];
	BlueAssert(updatingResource.resourceType == EGraphicsResourceType::Shader);

	UpdateShader(updatingResource, aVertexShaderPath, aFragmentShaderPath);
	ASSERT_NO_GRAPHICS_ERROR();
}

void OpenGlGraphicsDevice::UpdateResourceData(const uint32 aResourceID, EBufferAttachment aAttachment)
{
  BlueAssert(aResourceID && aResourceID < mResources.size());
  OpenGLResource& resource = mResources[aResourceID];
  BlueAssert(resource.resourceType == EGraphicsResourceType::Texture2D);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GetEnumFromAttachment(aAttachment), GL_TEXTURE_2D, resource.lowLevelID, 0);  

  ASSERT_NO_GRAPHICS_ERROR();
}

void OpenGlGraphicsDevice::UpdateResourceData(const uint32 aResourceID, EBufferAttachment* aAttachments, const uint32 aCount)
{
  BlueAssert(aResourceID && aResourceID < mResources.size());
  OpenGLResource& resource = mResources[aResourceID];
  BlueAssert(resource.resourceType == EGraphicsResourceType::GBuffer);

  static GLenum attachments[EBufferAttachment::Count];

  for (uint32 i = 0; i < aCount; ++i)
  {
    attachments[i] = GetEnumFromAttachment(aAttachments[i]);
  }

  glDrawBuffers(aCount, attachments); 

  ASSERT_NO_GRAPHICS_ERROR();
}

inline GLenum GetGlEnumFromDrawMode(EDrawMode aMode)
{
	switch (aMode)
	{
		case EDrawMode::Triangles:
			return GL_TRIANGLES;
			break;

		case EDrawMode::Lines:
			return GL_LINES;
			break;

		case EDrawMode::TriangleFan:
			return GL_TRIANGLE_FAN;
			break;

		case EDrawMode::TriangleStrip:
			return GL_TRIANGLE_STRIP;
			break;

			InvalidDefaultCase;
	}

	return false;
}

void OpenGlGraphicsDevice::DrawBuffers(const EDrawMode aMode, const uint32 aFirst, const uint32 aCount)
{
	GLenum drawMode = GetGlEnumFromDrawMode(aMode);
	glDrawArrays(drawMode, aFirst, aCount);
	ASSERT_NO_GRAPHICS_ERROR();
}

void OpenGlGraphicsDevice::DrawBuffersInstanced(const EDrawMode aMode, const uint32 aFirst, const uint32 aCount)
{
	GLenum drawMode = GetGlEnumFromDrawMode(aMode);
	//glDrawArraysInstanced(drawMode, aFirst, aCount);
	ASSERT_NO_GRAPHICS_ERROR();
}

void OpenGlGraphicsDevice::DrawBuffersElements(const EDrawMode aMode, const uint32 aCount, void* aIndicies)
{
	GLenum drawMode = GetGlEnumFromDrawMode(aMode);
	glDrawElements(drawMode, aCount, GL_UNSIGNED_INT, aIndicies);
	ASSERT_NO_GRAPHICS_ERROR();
}

void OpenGlGraphicsDevice::ClearBuffer(BufferBit aBuffersToClear)
{
	glClear(GetGlEnumFromBufferBit(aBuffersToClear));
	ASSERT_NO_GRAPHICS_ERROR();
}

void OpenGlGraphicsDevice::SetClearColor(const glm::vec4 aColor)
{
	glClearColor(aColor.x, aColor.y, aColor.z, aColor.w);
}

void OpenGlGraphicsDevice::BindGraphicsResource(const uint32 aResourceID)
{
	BlueAssert(aResourceID < mResources.size());
	BlueAssert(aResourceID);

	OpenGLResource& bindingResource = mResources[aResourceID];

	BindResource(bindingResource);

	ASSERT_NO_GRAPHICS_ERROR();
}

void OpenGlGraphicsDevice::BindGraphicsResource(const uint32 aResourceID, const ETextureID aTextureID)
{
  BlueAssert(aResourceID && aResourceID < mResources.size());

  OpenGLResource& resource = mResources[aResourceID];

  glActiveTexture(GetEnumFromTextureID(aTextureID));
  ASSERT_NO_GRAPHICS_ERROR();
}

void OpenGlGraphicsDevice::UnbindGraphicsResource(const uint32 aResourceID)
{
	BlueAssert(aResourceID < mResources.size() && aResourceID);
	OpenGLResource& unbindingResource = mResources[aResourceID];

	UnBindResource(unbindingResource);

	ASSERT_NO_GRAPHICS_ERROR();
}

int32 OpenGlGraphicsDevice::GetShaderVariableLocation(uint32 aResourceID, char* aVarName)
{
	BlueAssert(aResourceID);
	BlueAssert(aResourceID < mResources.size());
	OpenGLResource& r = mResources[aResourceID];
	BlueAssert(r.resourceType == EGraphicsResourceType::Shader);
	return glGetUniformLocation(r.lowLevelID, aVarName);
}

int32 OpenGlGraphicsDevice::GetShaderVariableLocation(uint32 aResourceID, const char* aVarName)
{
	BlueAssert(aResourceID);
	BlueAssert(aResourceID < mResources.size());
	OpenGLResource& r = mResources[aResourceID];
	BlueAssert(r.resourceType == EGraphicsResourceType::Shader);
	return glGetUniformLocation(r.lowLevelID, aVarName);
}

void OpenGlGraphicsDevice::SetShaderVariable(uint32 aVarLoc, void* aVar, EVarType aVarType)
{
	float* data;

	switch (aVarType)
	{
		case EVarType::Float:
			glUniform1f(aVarLoc, (*(float*)aVar));
			break;

		case EVarType::Vector3:
			data = (float*)aVar;
			glUniform3f(aVarLoc, *data, *(data + 1), *(data + 2));
			break;

		case EVarType::Vector4:
			data = (float*)aVar;
			glUniform4f(aVarLoc, *data, *(data + 1), *(data + 2), *(data + 3));
			break;

		case EVarType::Matrix4x4:
			glUniformMatrix4fv(aVarLoc, 1, GL_FALSE, glm::value_ptr(*((glm::mat4*)aVar)));
			break;

			InvalidDefaultCase
	}

	ASSERT_NO_GRAPHICS_ERROR();
}

int GetGlEnumFromResourceType(EGraphicsResourceType aType)
{
	switch (aType)
	{
		case EGraphicsResourceType::VertexArrayBuffer  :
			return GL_VERTEX_ARRAY;
			break;

		case EGraphicsResourceType::VertexBuffer:
			return GL_ARRAY_BUFFER;
			break;

		case EGraphicsResourceType::ElementBuffer:
			return GL_ELEMENT_ARRAY_BUFFER;
			break;

		case EGraphicsResourceType::Texture2D:
			return GL_TEXTURE_2D;
			break;

		case EGraphicsResourceType::Shader:
			BlueAssert(false);
			return 0;
			break;

			break;
			InvalidDefaultCase
	}

	return 0;
}



void OpenGlGraphicsDevice::DeleteResource(OpenGLResource& aResource)
{
	static std::string baseString("Deleting Resource: ");
	//Verbose_Log(baseString + ResourceTypeToString(aResource.resourceType));

	switch (aResource.resourceType)
	{
		case EGraphicsResourceType::VertexArrayBuffer:
			glDeleteVertexArrays(1, &aResource.lowLevelID);

		case EGraphicsResourceType::VertexBuffer:
		case EGraphicsResourceType::ElementBuffer:
			glDeleteBuffers(1, &aResource.lowLevelID);
			break;

		case EGraphicsResourceType::Shader:
			glDeleteProgram(aResource.lowLevelID);
			aResource.lowLevelID = 0;
			break;

		case EGraphicsResourceType::Texture2D:
			glDeleteTextures(1, &aResource.lowLevelID);
			break;

			InvalidDefaultCase
	}

	aResource.resourceSizeGPU = 0;
}

void OpenGlGraphicsDevice::CreateResource(OpenGLResource& aResource)
{
	static std::string baseString("Creating Resource: ");
	//Verbose_Log(baseString + ResourceTypeToString(aResource.resourceType));

	switch (aResource.resourceType)
	{
		case EGraphicsResourceType::VertexArrayBuffer:
			glGenVertexArrays(1, &aResource.lowLevelID);
			break;

		case EGraphicsResourceType::VertexBuffer:
		case EGraphicsResourceType::ElementBuffer:
			glGenBuffers(1, &aResource.lowLevelID);
			break;

		case EGraphicsResourceType::GBuffer:
			glGenFramebuffers(1, &aResource.lowLevelID);
			break;

		case EGraphicsResourceType::Shader:
			aResource.lowLevelID = glCreateProgram();
			break;

		case EGraphicsResourceType::Texture2D:
			glGenTextures(1, &aResource.lowLevelID);
			break;

			InvalidDefaultCase
	}

}

void OpenGlGraphicsDevice::BindResource(OpenGLResource& aResource)
{
	switch (aResource.resourceType)
	{
		case EGraphicsResourceType::VertexBuffer:
			glBindBuffer(GL_ARRAY_BUFFER, aResource.lowLevelID);
			break;

		case EGraphicsResourceType::ElementBuffer:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, aResource.lowLevelID);
			break;

		case EGraphicsResourceType::VertexArrayBuffer:
			glBindVertexArray(aResource.lowLevelID);
			break;

		case EGraphicsResourceType::Shader:
			glUseProgram(aResource.lowLevelID);
			break;

		case EGraphicsResourceType::Texture2D:
			glBindTexture(GL_TEXTURE_2D, aResource.lowLevelID);
			break;

			InvalidDefaultCase
	}
}

void OpenGlGraphicsDevice::UnBindResource(OpenGLResource& aResource)
{
	switch (aResource.resourceType)
	{
		case EGraphicsResourceType::VertexBuffer:
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			break;

		case EGraphicsResourceType::ElementBuffer:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			break;

		case EGraphicsResourceType::VertexArrayBuffer:
			glBindVertexArray(0);
			break;

		case EGraphicsResourceType::Shader:
			glUseProgram(0);
			break;

		case EGraphicsResourceType::Texture2D:
			glBindTexture(GL_TEXTURE_2D, 0);
			break;

			InvalidDefaultCase
	}
}

uint32 LoadAndCompileShader(int32 aShaderType, char* aPath)
{
	std::string shaderSource;
	std::stringstream stringStream;
	std::ifstream file;
	file.open(aPath);

	if (!file.is_open())
	{
		Log::Error(std::string("File failed to open: ") + aPath);
		return 0;
	}

	stringStream << file.rdbuf();
	shaderSource = stringStream.str();

	uint32 shaderID = glCreateShader(aShaderType);
	const char* source = shaderSource.c_str();
	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);
	int32 success;
	char infoLog[1028];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shaderID, 1028, NULL, infoLog);
		std::cout << "SHADER COMPILE FAILED" << std::endl << infoLog << std::endl;
		return 0;
	}

	return shaderID;
}

void OpenGlGraphicsDevice::UpdateShader(OpenGLResource& aResource, char* aVertexPath, char* aFragmentPath)
{
	uint32 vertexShader = LoadAndCompileShader(GL_VERTEX_SHADER, aVertexPath);

	uint32 fragmentShader = LoadAndCompileShader(GL_FRAGMENT_SHADER, aFragmentPath);

	if (!vertexShader || !fragmentShader)
	{
		Log::Error("A shader failed to load");;
		return;
	}

	uint32 programID = aResource.lowLevelID;

	glAttachShader(programID, vertexShader);

	glAttachShader(programID, fragmentShader);

	glLinkProgram(programID);

	int32 success;
	glGetProgramiv(programID, GL_LINK_STATUS, &success);

	if (!success)
	{
		char infoLog[1028];
		glGetProgramInfoLog(programID, 1028, NULL, infoLog);
		std::cout << "PROGRAM FAILED TO LINK" << std::endl << infoLog << std::endl;
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void OpenGlGraphicsDevice::UpdateElementBuffer(OpenGLResource& aResource, void* aData, uint64 aDataSize)
{
	Verbose_Log("Updating ElementBuffer");
	BindResource(aResource);

	if (aResource.resourceSizeGPU <= aDataSize)
	{
		Verbose_Log("Reconstructing element buffer");
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, aDataSize, aData, GL_DYNAMIC_DRAW);
	}
	else
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, aDataSize, aData);
	}

	aResource.resourceSizeGPU = aDataSize;
	UnBindResource(aResource);
}

void OpenGlGraphicsDevice::UpdateVertexBuffer(OpenGLResource& aResource, size_t aOffset, void* aData, uint64 aDataSize, DataDescriptor* aDescriptors, uint32 aDescriptorCount)
{
	BindResource(aResource);

	if (aResource.resourceSizeGPU < aOffset + aDataSize || aResource.resourceSizeGPU == 0)
	{
		Verbose_Log("Reconstructing Vertex buffer");
		glBufferData(GL_ARRAY_BUFFER, aDataSize, aData, GL_DYNAMIC_DRAW);
		aResource.resourceSizeGPU = aDataSize;

		if (aDescriptors)
		{
			for (uint32 i = 0; i < aDescriptorCount; i++)
			{
				DataDescriptor* desc = &aDescriptors[i];

				if (desc != nullptr)
				{
					glEnableVertexAttribArray(desc->location);
					glVertexAttribPointer(desc->location, desc->count, GL_FLOAT, desc->normalized, desc->stride, (void*)(desc->offset));

					if (desc->instanced)
					{
						glVertexAttribDivisor(desc->location, desc->instanceCount);
					}
				}
			}
		}
	}
	else
	{
		glBufferSubData(GL_ARRAY_BUFFER, aOffset, aDataSize, aData);
	}

	UnBindResource(aResource);
}

