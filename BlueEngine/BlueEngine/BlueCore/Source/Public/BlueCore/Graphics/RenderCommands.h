#pragma once
#include "BlueCore/Core/Types.h"
#include "BlueCore/GraphicsDevice/IGraphicsDevice.h"
#include "BlueCore/Core/IDelegate.h"

namespace Blue
{
	typedef SimpleDelegate<void, void*> DispatchFunction;

	struct SubmittedCommand
	{	
		DispatchFunction* dispatch = nullptr;
		void* data = nullptr;
	};

	struct DrawCommand
	{
		static DispatchFunction dispatchFunction;

		uint32 bufferID = 0;
		uint32 indexCount = 0;
		uint32 firstIndex = 0;
		EDrawMode drawMode = EDrawMode::Triangles;
	};

	template <typename T>
	struct SetShaderVariableCommand
	{
		static DispatchFunction dispatchFunction;

		char* variableName;
		GraphicsDeviceResourceID shaderID;
		T variable;
	};
}