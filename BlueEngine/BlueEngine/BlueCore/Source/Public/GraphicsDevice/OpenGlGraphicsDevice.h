#pragma once
#include "IGraphicsDevice.h"
#include <vector>
#include <queue>
namespace BlueCore
{
	class OpenGlGraphicsDevice : public IGraphicsDevice
	{
		public:
		virtual void Init() override;
		virtual void ShutDown() override;

		virtual uint32 CreateGraphicsResource(EGraphicsResourceType aType) override;
		virtual void DeleteGraphicsResource(uint32& aResourceID) override;
		virtual void BindGraphicsResource(const uint32 aResourceID) override;
		virtual void UnBindGraphicsResource(const uint32 aResourceID) override;

		virtual int32 GetShaderVariableLocation(uint32 aResourceID, char* aVarName)override;
		virtual int32 GetShaderVariableLocation(uint32 aResourceID, const char* aVarName) override;

		virtual void SetShaderVariable(uint32 aVarLoc, void* aVar, EVarType aVarType) override;

		virtual void UpdateResourceData(const uint32 aResourceID, char* aVertexShaderPath, char* aFragmentShaderPath) override;
		virtual void UpdateResourceData(const uint32 aResourceID, ubyte* aPixels, uint32 aWidth, uint32 aHeight, ImageFormat aImageFormat, ImageFormat aSavingFormat, uint32 aMipMapLevel) override;
		virtual void UpdateResourceData(const uint32 aResourceID, size_t aOffset, void* aData, uint64 aDataSize, DataDescriptor* aDescriptors = nullptr, uint32 aDescriptorCount = 0) override;

		virtual void DrawBuffers(const EDrawMode aMode, const uint32 aFirst, const uint32 aCount) override;
		virtual void DrawBuffersInstanced(const EDrawMode aMode, const uint32 aFirst, const uint32 aCount) override;

		virtual void DrawBuffersElements(const EDrawMode aMode, const uint32 aCount, void* aIndicies = nullptr) override;

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
}