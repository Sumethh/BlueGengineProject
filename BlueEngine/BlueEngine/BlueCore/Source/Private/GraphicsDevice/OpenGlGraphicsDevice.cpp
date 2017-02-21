#include "GraphicsDevice/OpenGlGraphicsDevice.h"
#include "Core/Log.h"
#include "GraphicsDevice/DataDescriptor.h"

#include <gl/glew.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>


int GetGlEnumFromBufferBit(BufferBit aBit)
{
	int returningValue = 0;

	if (((uint8)aBit & (uint8)BufferBit::Color) != 0)
	{
		returningValue |= GL_COLOR_BUFFER_BIT;
	}

	if (((uint8)aBit & (uint8)BufferBit::DepthBit) != 0)
	{
		returningValue |= GL_DEPTH_BITS;
	}

	return returningValue;
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
		Log::LogError("Glew failed to initialize");
		BlueAssert(false);
	}

	Log::LogInfo("Opengl Graphics device initialized");
	OpenGLResource r = {};
	mResources.emplace_back(std::move(r));
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
		CHECK_FOR_GRAPHIC_ERROR();

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
		CHECK_FOR_GRAPHIC_ERROR();
		return r.id;
	}

}

void OpenGlGraphicsDevice::DeleteGraphicsResource(uint32& aResourceID)
{
	BlueAssert(aResourceID < mResources.size());
	BlueAssert(aResourceID);

	OpenGLResource* r = &mResources[aResourceID];
	DeleteResource(*r);
	mFreeResources.push(r);
	aResourceID = 0;
	CHECK_FOR_GRAPHIC_ERROR();
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

		default:
			Log::LogError("Tried updating an invalid resource");
			BlueAssert(false);
			break;
	}

	CHECK_FOR_GRAPHIC_ERROR();
}

void OpenGlGraphicsDevice::UpdateResourceData(const uint32 aResourceID, char* aVertexShaderPath, char* aFragmentShaderPath)
{
	BlueAssert(aResourceID);
	OpenGLResource& updatingResource = mResources[aResourceID];
	BlueAssert(updatingResource.resourceType == EGraphicsResourceType::Shader);

	UpdateShader(updatingResource, aVertexShaderPath, aFragmentShaderPath);
	CHECK_FOR_GRAPHIC_ERROR();
}

void OpenGlGraphicsDevice::UpdateResourceData(const uint32 aResourceID, ubyte* aPixels, uint32 aWidth, uint32 aHeight, ImageFormat aImageFormat, ImageFormat aSavingFormat, uint32 aMipMapLevel)
{
	BlueAssert(aResourceID);
	OpenGLResource& updatingResource = mResources[aResourceID];
	BlueAssert(updatingResource.resourceType == EGraphicsResourceType::Texture2D && aPixels && aWidth && aHeight);

	uint32 imageFormat, storingFormat;

	if (aImageFormat == ImageFormat::RGB)
	{
		imageFormat = GL_RGB;
	}
	else
	{
		imageFormat = GL_RGBA;
	}

	if (aSavingFormat == ImageFormat::RGB)
	{
		storingFormat = GL_RGB;
	}
	else
	{
		storingFormat = GL_RGBA;
	}

	BindResource(updatingResource);
	glTexImage2D(GL_TEXTURE_2D, aMipMapLevel, imageFormat, aWidth, aHeight, 0, storingFormat, GL_UNSIGNED_BYTE, aPixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	UnBindResource(updatingResource);
	CHECK_FOR_GRAPHIC_ERROR();
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

		default:
			BlueAssert(false);
			return false;

			break;
	}
}

void OpenGlGraphicsDevice::DrawBuffers(const EDrawMode aMode, const uint32 aFirst, const uint32 aCount)
{
	GLenum drawMode = GetGlEnumFromDrawMode(aMode);
	glDrawArrays(drawMode, aFirst, aCount);
	CHECK_FOR_GRAPHIC_ERROR();
}

void OpenGlGraphicsDevice::DrawBuffersInstanced(const EDrawMode aMode, const uint32 aFirst, const uint32 aCount)
{
	GLenum drawMode = GetGlEnumFromDrawMode(aMode);
	//glDrawArraysInstanced(drawMode, aFirst, aCount);
	CHECK_FOR_GRAPHIC_ERROR();
}

void OpenGlGraphicsDevice::DrawBuffersElements(const EDrawMode aMode, const uint32 aCount, void* aIndicies)
{
	GLenum drawMode = GetGlEnumFromDrawMode(aMode);
	glDrawElements(drawMode, aCount, GL_UNSIGNED_INT, aIndicies);
	CHECK_FOR_GRAPHIC_ERROR();
}

void OpenGlGraphicsDevice::ClearBuffer(BufferBit aBuffersToClear)
{
	glClear(GetGlEnumFromBufferBit(aBuffersToClear));
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

	CHECK_FOR_GRAPHIC_ERROR();
}

void OpenGlGraphicsDevice::UnBindGraphicsResource(const uint32 aResourceID)
{
	BlueAssert(aResourceID < mResources.size());
	BlueAssert(aResourceID);
	OpenGLResource& unbindingResource = mResources[aResourceID];

	UnBindResource(unbindingResource);

	CHECK_FOR_GRAPHIC_ERROR();
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
			glUniformMatrix4fv(aVarLoc, 1, GL_FALSE, (float*)aVar);
			break;

		default:
			break;
	}

	CHECK_FOR_GRAPHIC_ERROR();
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

		case EGraphicsResourceType::Count:
			BlueAssert(false);
			return 0;
			break;

		default:
			BlueAssert(false);
			return 0;
			break;
	}
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


		default:
			break;
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

		case EGraphicsResourceType::Shader:
			aResource.lowLevelID = glCreateProgram();
			break;

		case EGraphicsResourceType::Texture2D:
			glGenTextures(1, &aResource.lowLevelID);
			break;

		default:
			break;
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

		default:
			break;
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

		default:
			break;
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
		Log::LogError(std::string("File failed to open: ") + aPath);
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
		Log::LogError("A shader failed to load");;
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

