#pragma once
#include "BlueCore/Core/Types.h"
#include "BlueCore/Core/Defines.h"

namespace Blue
{
	class ArchiveObject;
	class   ISerializable
	{
	public:
		ISerializable();
		virtual ~ISerializable();

		virtual void OnSerialize(ArchiveObject* const  aArchive) const = 0;
		virtual void OnDeserialize(ArchiveObject* const aArchive) = 0;
	};
}