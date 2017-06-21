#pragma once
#include "BlueCore/Core/Defines.h"

namespace Blue
{
	enum class EFullScreenLayer
	{
		Game = BlueBit(0),
		HUD = BlueBit(1),
		Effect = BlueBit(2)
	};


	enum class ETranslucencyType
	{
		Opaque = BlueBit(0),
		Translucent = BlueBit(1)
	};

	enum class EViewportLayer
	{
		Skybox = BlueBit(0),
		World = BlueBit(1),
		Effects = BlueBit(2),
		HUD = BlueBit(3),
	};
}