#pragma once
#include "Core/Defines.h"

enum class FullScreenLayer
{
	Game = BlueBit(0),
	HUD = BlueBit(1),
	Effect = BlueBit(2)
};

enum class TranslucencyType
{
	Opaque = BlueBit(0),
	Translucent = BlueBit(1)
};

enum class ViewportLayer
{
	Skybox = BlueBit(0),
	World = BlueBit(1),
	Effects = BlueBit(2),
	HUD = BlueBit(3),
};