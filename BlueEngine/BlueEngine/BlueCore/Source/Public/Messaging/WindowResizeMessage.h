#pragma once

#include "IMessage.h"


struct WindowResizeMessage : public IMessage
{
	uint32 windowWidth;
	uint32 windowHeight;
};