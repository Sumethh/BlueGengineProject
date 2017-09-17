#pragma once

#include "BlueCore/Core/Types.h"
#include "BlueCore/Core/NonCopyable.h"
#include "BlueCore/Graphics/Light.h"
#include <string>
#include <glm/vec4.hpp>
#include <vector>
#define MAX_LIGHTS 32

namespace Blue
{
	class Shader;
	class Texture2D;
	class Material : public NonCopyable
	{
	public:

		Material(uint32 aMaterialID);
		~Material();

		void Bind(bool aBindShader = true);
		void SetDataForDrawing(Shader* aShader = nullptr);
		void UnBind(bool aUnbindShader = true);
		inline void SetDiffuseColor(glm::vec4 aColor)
		{
			mDiffuseColor = aColor;
		}
		inline void SetAmbientColor(glm::vec4 aColor)
		{
			mAmbientColor = aColor;
		}
		inline void SetSpecularPower(float aSpec)
		{
			mSpecular = aSpec;
		}
		inline void SetShader(Shader* aShader)
		{
			mShader = aShader;
		}
		inline Shader* GetShader()
		{
			return mShader;
		}
		inline void SetTexture(Texture2D* aTexture)
		{
			mTexture = aTexture;
		}
		uint32 GetID() const
		{
			return mId;
		}
		uint32 GetShaderVariableLoc(const char* aVariable);
		bool HasAlpha()const;

		bool IsBound()const;

	private:
		std::string mName;
		glm::vec4 mDiffuseColor;
		glm::vec4 mAmbientColor;
		float mSpecular;
		uint32 mId;
		Texture2D* mTexture;
		Shader* mShader;

		bool mBound;
	};
}