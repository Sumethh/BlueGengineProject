#pragma once

#include "IMessage.h"


namespace Blue
{
	struct WindowResizeMessage : public IMessage
	{
		uint32 windowWidth;
		uint32 windowHeight;
	};
}