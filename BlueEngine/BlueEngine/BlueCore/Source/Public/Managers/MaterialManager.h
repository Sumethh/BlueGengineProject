#pragma once
#include <vector>
#include "Core/NonCopyable.h"
#include "Core/Types.h"

class Material;
class MaterialManager : NonCopyable
{
	public:
	enum EDefaultMaterial : uint32
	{
		Default = 0,
		Debug,
		DebugInstanced,
		Count
	};

	Material* CreateMaterial();


	inline Material* GetMaterial(uint32 aMatIndex) { return mMaterials[aMatIndex]; }

	static inline MaterialManager* GI()
	{
		if (!mInstance)
		{
			mInstance = new MaterialManager();
		}

		return mInstance;
	}

	private:
	void CreateDefaultMaterials();
	MaterialManager();
	~MaterialManager();
	static MaterialManager* mInstance;
	std::vector<Material*> mMaterials;
};
