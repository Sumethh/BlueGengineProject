#pragma once
#include "IGraphicsDevice.h"
#include <vector>
#include <queue>

class OpenGlGraphicsDevice : public IGraphicsDevice
{
	public:
	void Init() override;
	void ShutDown() override;

	uint32 CreateGraphicsResource(EGraphicsResourceType aType) override;
	void DeleteGraphicsResource(uint32& aResourceID) override;
	void BindGraphicsResource(const uint32 aResourceID) override;
	void UnBindGraphicsResource(const uint32 aResourceID) override;

	int32 GetShaderVariableLocation(uint32 aResourceID, char* aVarName)override;
	int32 GetShaderVariableLocation(uint32 aResourceID, const char* aVarName) override;

	void SetShaderVariable(uint32 aVarLoc, void* aVar, EVarType aVarType) override;

	void UpdateResourceData(const uint32 aResourceID, char* aVertexShaderPath, char* aFragmentShaderPath) override;
	void UpdateResourceData(const uint32 aResourceID, ubyte* aPixels, uint32 aWidth, uint32 aHeight, ImageFormat aImageFormat, ImageFormat aSavingFormat, uint32 aMipMapLevel) override;
	void UpdateResourceData(const uint32 aResourceID, size_t aOffset, void* aData, uint64 aDataSize, DataDescriptor* aDescriptors = nullptr, uint32 aDescriptorCount = 0) override;

	void DrawBuffers(const EDrawMode aMode, const uint32 aFirst, const uint32 aCount) override;
	void DrawBuffersInstanced(const EDrawMode aMode, const uint32 aFirst, const uint32 aCount) override;

	void DrawBuffersElements(const EDrawMode aMode, const uint32 aCount, void* aIndicies = nullptr) override;

	void ClearBuffer(const BufferBit aBufferToClear) override;
	void SetClearColor(const glm::vec4 aColor) override;
	private:
	friend class GraphicsDeviceFactory;
	OpenGlGraphicsDevice();
	~OpenGlGraphicsDevice();

	struct OpenGLResource
	{
		uint32 lowLevelID;
		uint32 id;
		EGraphicsResourceType resourceType;
		uint64 resourceSizeGPU;
	};

	void DeleteResource(OpenGLResource& aResource);
	void CreateResource(OpenGLResource& aResource);
	void BindResource(OpenGLResource& aResource);
	void UnBindResource(OpenGLResource& aResource);

	void UpdateShader(OpenGLResource& aResource, char* aVertexPath, char* aFragmentPath);

	void UpdateElementBuffer(OpenGLResource& aResource, void* aData, uint64 aDataSize);
	void UpdateVertexBuffer(OpenGLResource& aResource, size_t aOffset, void* aData, uint64 aDataSize, DataDescriptor* aDescriptors = nullptr, uint32 aDescriptorCount = 0);

	std::vector<OpenGLResource> mResources;
	std::queue<OpenGLResource*> mFreeResources;
};
