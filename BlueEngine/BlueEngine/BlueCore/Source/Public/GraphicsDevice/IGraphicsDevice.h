#pragma once
#include "Core/Types.h"
#include "Core/Defines.h"
#include "Core/NonCopyable.h"

#include <glm/vec4.hpp>

#define  ASSERT_GRAPHICS_ERROR 1

#if ASSERT_GRAPHICS_ERROR
	#ifndef ASSERT_NO_GRAPHICS_ERROR
		#define ASSERT_NO_GRAPHICS_ERROR()if(GLenum err = glGetError()){Blue::Log::Error(std::to_string((int)err)); Blue::Log::Flush(); BlueAssert(false);}
	#endif
#else
	#define ASSERT_NO_GRAPHICS_ERROR()if(GLenum err = glGetError()){Blue::Log::Error(std::to_string((int)err)); Blue::Log::Flush();}
#endif

namespace Blue
{
	enum class EGraphicsDeviceType : uint8
	{
		OpenGL = BlueBit(0),
		Vulkan = BlueBit(1),
		D3D11 = BlueBit(2),
		D3D12 = BlueBit(3),
		UnIdentified = BlueBit(7)
	};

	enum class EGraphicsResourceType : uint32
	{
		VertexArrayBuffer = 0,
		VertexBuffer = 1,
		ElementBuffer = 2,
		GBuffer = 4,
		Texture2D = 5,
		Shader = 6,
		Count
	};

	enum class EVarType : uint8
	{
		Float = 0,
		Vector3,
		Vector4,
		Matrix4x4,
		Count
	};

	enum class EDrawMode : uint8
	{
		Triangles,
		TriangleStrip,
		TriangleFan,
		Lines,
		Count
	};

	enum class BufferBit : uint8
	{
		DepthBit = BlueBit(0),
		Color = BlueBit(1),
	};

	enum class EPrecisionType : uint8
	{
		RGB_F_16Bit,
		RGB_F_32Bit,
		RGB_4Bit,
		RGB_8Bit,
		RGB_10Bit,
		RGB_12Bit,

		RGBA_F_16Bit,
		RGBA_F_32Bit,
		RGBA_2Bit,
		RGBA_4Bit,
		RGBA_8Bit,
		RGBA_12Bit,
		RGBA_16Bit,

	};



	enum class EImageFormat : uint8
	{
		RGB = 0,
		RGBA
	};


	enum EBufferAttachment : uint8
	{
		Attachment0,
		Attachment1,
		Attachment2,
		Attachment3,
		Attachment4,
		Attachment5,
		Attachment6,
		Attachment7,
		Attachment8,
		Attachment9,
		Attachment10,
		Attachment11,
		Attachment12,
		Attachment13,
		Attachment14,
		Count
	};

	enum ETextureID : uint8
	{
		Texture0,
		Texture1,
		Texture2,
		Texture3,
		Texture4,
		Texture5,
		Texture6,
		Texture7,
		Texture8,
		Texture9
	};

	enum ETextureParameter : uint8
	{
		MinFilter,
		MagFilter,
		Nearest
	};

	struct DataDescriptor;
	class IGraphicsDevice : public NonCopyable
	{
	public:
		IGraphicsDevice(EGraphicsDeviceType aType);

		virtual void Init() = 0;
		virtual void ShutDown() = 0;

		virtual uint32 CreateGraphicsResource(EGraphicsResourceType aType) = 0;
		virtual void DeleteGraphicsResource(uint32& aResourceID) = 0;
		virtual void BindGraphicsResource(const uint32 aResourceID) = 0;
		virtual void BindGraphicsResource(const uint32 aResourceID, const ETextureID aTextureID) = 0;
		virtual void UnbindGraphicsResource(const uint32 aResourceID) = 0;

		virtual int32 GetShaderVariableLocation(uint32 aResourceID, char* aVarName) = 0;
		virtual int32 GetShaderVariableLocation(uint32 aResourceID, const char* aVarName) = 0;

		virtual void SetShaderVariable(uint32 aVarLoc, void* aVar, EVarType aVarType) = 0;

		virtual void UpdateResourceData(const uint32 aResourceID, size_t aOffset, void* aData, uint64 aDataSize, DataDescriptor* aDescriptors = nullptr, uint32 aDescriptorCount = 0) = 0;
		virtual void UpdateResourceData(const uint32 aResourceID, ubyte* aPixels, const uint32 aWidth, const uint32 aHeight, EPrecisionType aTexturePrecision, EImageFormat aPixelFormat, uint32 aMipMapLevel) = 0;
		virtual void UpdateResourceData(const uint32 aResourceID, const uint32 aWidth, const uint32 aHeight, EPrecisionType aType) = 0;
		virtual void UpdateResourceData(const uint32 aResourceID, const ETextureParameter aParameter, const ETextureParameter aValue) = 0;
		virtual void UpdateResourceData(const uint32 aResourceID, char* aVertexShaderPath, char* aFragmentShaderPath) = 0;
		virtual void UpdateResourceData(const uint32 aResourceID, EBufferAttachment aAttachments) = 0;
		virtual void UpdateResourceData(const uint32 aResourceID, EBufferAttachment* aAttachments, const uint32 aCount) = 0;


		virtual void DrawBuffers(const EDrawMode aMode, const uint32 aFirst, const uint32 aCount) = 0;
		virtual void DrawBuffersInstanced(const EDrawMode aMode, const uint32 aFirst, const uint32 aCount) = 0;
		virtual void DrawBuffersElements(const EDrawMode aMode, const uint32 aCount, void* aIndicies = nullptr) = 0;

		virtual void ClearBuffer(const BufferBit aBitToClear) = 0;

		virtual void SetClearColor(const glm::vec4 aColor) = 0;

		static IGraphicsDevice* GetCurrentGraphicsDevice()
		{
			return mCurrentGraphicsDevice;
		}
	protected:

	private:
		friend class GraphicsDeviceFactory;
		static IGraphicsDevice* mCurrentGraphicsDevice;
		EGraphicsDeviceType mGraphicsType;

	};
}