#pragma once
#include "Core/Types.h"
#include "Core/Defines.h"
#include "Core/NonCopyable.h"
#include "Graphics/ImageFormat.h"

namespace BlueCore
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
		Texture2D = 3,
		Shader = 4,

		Count
	};

	enum class EVarType : uint8
	{
		Float,
		Vector3,
		Vector4,
		Matrix4x4
	};

	enum class EDrawMode : uint8
	{
		Triangles,
		Lines,

	};

	//static char* ResourceTypeToString(EGraphicsResourceType aType)
	//{
	//	switch (aType)
	//	{
	//		case BlueGengine::EGraphicsResourceType::VertexArrayBuffer:
	//			return "Vertex Array Buffer";
	//
	//			break;
	//
	//		case BlueGengine::EGraphicsResourceType::VertexBuffer:
	//			return "Vertex Buffer";
	//
	//			break;
	//
	//		case BlueGengine::EGraphicsResourceType::ElementBuffer:
	//			return "Element Buffer";
	//
	//			break;
	//
	//		case BlueGengine::EGraphicsResourceType::Texture2D:
	//			return "Texture2D";
	//
	//			break;
	//
	//		case BlueGengine::EGraphicsResourceType::Shader:
	//			return "Shader";
	//
	//			break;
	//
	//		case BlueGengine::EGraphicsResourceType::Count:
	//			return "Count";
	//			break;
	//
	//		default:
	//			return "Undefined";
	//			break;
	//	}
	//}

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
		virtual void UnBindGraphicsResource(const uint32 aResourceID) = 0;

		virtual int32 GetShaderVariableLocation(uint32 aResourceID, char* aVarName) = 0;
		virtual int32 GetShaderVariableLocation(uint32 aResourceID, const char* aVarName) = 0;

		virtual void SetShaderVariable(uint32 aVarLoc, void* aVar, EVarType aVarType) = 0;

		virtual void UpdateResourceData(const uint32 aResourceID, size_t aOffset, void* aData, uint64 aDataSize, DataDescriptor* aDescriptors = nullptr, uint32 aDescriptorCount = 0) = 0;
		virtual void UpdateResourceData(const uint32 aResourceID, ubyte* aPixels, uint32 aWidth, uint32 aHeight, ImageFormat aPixleFormat, ImageFormat aSavingFormat, uint32 aMipMapLevel) = 0;
		virtual void UpdateResourceData(const uint32 aResourceID, char* aVertexShaderPath, char* aFragmentShaderPath) = 0;

		virtual void DrawBuffers(const EDrawMode aMode, const uint32 aFirst, const uint32 aCount) = 0;
		virtual void DrawBuffersInstanced(const EDrawMode aMode, const uint32 aFirst, const uint32 aCount) = 0;

		virtual void DrawBuffersElements(const EDrawMode aMode, const uint32 aCount, void* aIndicies = nullptr) = 0;


		static IGraphicsDevice* GetCurrentGraphicsDevice() { return mCurrentGraphicsDevice; }
		protected:

		private:
		friend class GraphicsDeviceFactory;
		static IGraphicsDevice* mCurrentGraphicsDevice;
		EGraphicsDeviceType mGraphicsType;

	};
}