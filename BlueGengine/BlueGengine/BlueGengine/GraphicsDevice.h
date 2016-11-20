#pragma once
#include "Types.h"
#include "Defines.h"
#include "NonCopyable.h"
namespace BlueGengine
{
	enum class EGraphicsDeviceType : uint8
	{
		OpenGL = BlueBit(0),
		Vulkan = BlueBit(1),
		D3D11 = BlueBit(2),
		D3D12 = BlueBit(3),
		UnIdentified = BlueBit(7)
	};

	class GraphicsDevice : public NonCopyable
	{
		public:



		protected:

		private:
		friend class GraphicsDeviceFactory;
		GraphicsDevice(EGraphicsDeviceType aType);
		EGraphicsDeviceType mGraphicsType;

	};
}