#pragma once

#include "Types.h"
#include "NonCopyable.h"
#include <string>
#include <glm/vec4.hpp>
#include <vector>
#include "Light.h"
#define MAX_LIGHTS 32
namespace BlueGengine
{
	class Shader;
	class Texture2D;
	class Material : public NonCopyable
	{
		public:

		Material(uint32 aMaterialID);
		~Material();

		void Bind();
		void SetDataForDrawing();
		void UnBind();
		inline void SetDiffuseColor(glm::vec4 aColor) { mDiffuseColor = aColor; }
		inline void SetAmbientColor(glm::vec4 aColor) { mAmbientColor = aColor; }
		inline void SetSpecularPower(float aSpec) { mSpecular = aSpec; }
		inline void SetShader(Shader* aShader) { mShader = aShader; }
		inline Shader* GetShader() { return mShader; }
		inline void SetTexture(Texture2D* aTexture) { mTexture = aTexture; }
		uint32 GetID() const { return mId; }

		uint32 GetShaderVariableLoc(const char* aVariable);

		void SetPointLightData(std::vector<Light*>& aLights);

		private:
		std::string mName;
		glm::vec4 mDiffuseColor;
		glm::vec4 mAmbientColor;
		float mSpecular;
		uint32 mId;
		Texture2D* mTexture;
		Shader* mShader;

	};
}
