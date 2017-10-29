#pragma once
#include "IGraphicsDevice.h"
#include <vector>
#include <queue>

namespace Blue
{
	class OpenGlGraphicsDevice : public IGraphicsDevice
	{
	public:
		void Init() override;
		void ShutDown() override;

		GraphicsDeviceResourceID CreateGraphicsResource(EGraphicsResourceType aType) override;
		void DeleteGraphicsResource(GraphicsDeviceResourceID& aResourceID) override;
		void BindGraphicsResource(const GraphicsDeviceResourceID aResourceID) override;
		void BindGraphicsResource(const GraphicsDeviceResourceID aResourceID, const ETextureID aTextureID) override;
		void UnbindGraphicsResource(const GraphicsDeviceResourceID aResourceID) override;

		int32 GetShaderVariableLocation(uint32 aResourceID, char* aVarName)override;
		int32 GetShaderVariableLocation(uint32 aResourceID, const char* aVarName) override;

		void SetShaderVariable(uint32 aVarLoc, void* aVar, EVarType aVarType) override;

		void UpdateResourceData(const GraphicsDeviceResourceID aResourceID, size_t aOffset, void* aData, uint64 aDataSize, DataDescriptor* aDescriptors = nullptr, uint32 aDescriptorCount = 0) override;
		void UpdateResourceData(const GraphicsDeviceResourceID aResourceID, ubyte* aPixels, const uint32 aWidth, const uint32 aHeight, EPrecisionType aTexturePrecision, EImageFormat aPixelFormat, EDataType aTextureDataType, uint32 aMipMapLevel) override;
		void UpdateResourceData(const GraphicsDeviceResourceID aResourceID, const uint32 aWidth, const uint32 aHeight, EPrecisionType aType) override;
		void UpdateResourceData(const GraphicsDeviceResourceID aResourceID, const ETextureParameter aParameter, const ETextureParameter aValue) override;
		void UpdateResourceData(const GraphicsDeviceResourceID aResourceID, const std::string& aVertexShaderPath, const std::string& aFragmentShaderPath) override;
		void UpdateResourceData(const GraphicsDeviceResourceID aResourceID, EBufferAttachment aAttachment) override;
		void UpdateResourceData(const GraphicsDeviceResourceID aResourceID, EBufferAttachment* aAttachments, const uint32 aCount) override;
		void UpdateResourceData(const GraphicsDeviceResourceID aResourceID, ERenderBufferType aType, EBufferAttachment aAttachment, const uint32 aWidth, const uint32 aHeight);

		void BlitFramebuffers(const GraphicsDeviceResourceID aReadResourceID, const GraphicsDeviceResourceID aWritingResourceID, IntRect aReadResourceRect, IntRect aWriteResourceRect, EBufferBit aDataToCopy);

		void DrawBuffers(const EDrawMode aMode, const uint32 aFirst, const uint32 aCount) override;
		void DrawBuffersInstanced(const EDrawMode aMode, const uint32 aFirst, const uint32 aCount) override;
		void DrawBuffersElements(const EDrawMode aMode, const uint32 aCount, void* aIndicies = nullptr) override;

		void ClearBuffer(const EBufferBit aBufferToClear) override;

		void SetClearColor(const glm::vec4 aColor) override;

		void Disable()override;
		void Enable() override;
		void OnWindowResize(struct WindowResizeMessage* aMessage);

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

		void UpdateShader(OpenGLResource& aResource, const std::string& aVertexPath, const std::string& aFragmentPath);

		void UpdateElementBuffer(OpenGLResource& aResource, void* aData, uint64 aDataSize);
		void UpdateVertexBuffer(OpenGLResource& aResource, size_t aOffset, void* aData, uint64 aDataSize, DataDescriptor* aDescriptors = nullptr, uint32 aDescriptorCount = 0);

		std::vector<OpenGLResource> mResources;
		std::queue<OpenGLResource*> mFreeResources;
	};
}