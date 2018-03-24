#include "BlueCore/Graphics/RenderCommands.h"
#include <glm/glm.hpp>
namespace Blue
{
	template<typename T>
	constexpr inline EVarType ConvertToVarType()
	{
		BlueAssert(false);
		return EVarType::Count;
	}
#pragma region ConvertTypes
	template<>
	constexpr inline EVarType ConvertToVarType<float>()
	{
		return EVarType::Float;
	}
	template<>
	constexpr inline EVarType ConvertToVarType<int32>()
	{
		return EVarType::Int;
	}
	template<>
	constexpr inline EVarType ConvertToVarType<glm::vec3>()
	{
		return EVarType::Vector3;
	}
	template<>
	constexpr inline EVarType ConvertToVarType<glm::vec4>()
	{
		return EVarType::Vector4;
	}
	template<>
	constexpr inline EVarType ConvertToVarType<glm::mat4>() 
	{
		return EVarType::Matrix4x4;
	}
#pragma endregion ConvertTypes

	void DispatchDrawCommand(void * aData)
	{
		
	}
	DispatchFunction DrawCommand::dispatchFunction = DispatchFunction(&DispatchDrawCommand);


	template<typename T>
	void DispatchSetShaderVariableCommand(void* aData)
	{
		BlueAssert(aData);
		SetShaderVariableCommand<T> command = reinterpret_cast<SetShaderVariableCommand<T>*>(aData);
		IGraphicsDevice* graphicsDevice = IGraphicsDevice::GetCurrentGraphicsDevice();
		int32 location = graphicsDevice->GetShaderVariableLocation(command->shaderID, command->variableName);
		BlueAssert(location != -1);
		graphicsDevice->SetShaderVariable(location, static_cast<void*>(&(command->variable)), ConvertToVarType<T>());
	}
	template <typename T>
	DispatchFunction SetShaderVariableCommand<T>::dispatchFunction = DispatchFunction(&DispatchSetShaderVariableCommand<T>);

}
