#pragma once
#include "Core/Types.h"
#include "Core/Defines.h"

class ArchiveObject;
class   ISerializable
{
	public:
	ISerializable();
	virtual ~ISerializable();

	virtual void OnSerialize(ArchiveObject* const  aArchive) const = 0;
	virtual void OnDeserialize(ArchiveObject* const aArchive) = 0;
};
