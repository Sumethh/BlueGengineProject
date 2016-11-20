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
	class Texture;
	class Material : public NonCopyable
	{
		public:

		Material(uint32 aMaterialID);
		~Material();

		void Bind();
		void SetDataForDrawing();
		void Unprep();
		inline void SetDiffuseColor(glm::vec4 aColor) { mDiffuseColor = aColor; }
		inline void SetAmbientColor(glm::vec4 aColor) { mAmbientColor = aColor; }
		inline void SetSpecularPower(float aSpec) { mSpecular = aSpec; }
		inline void SetShader(Shader* aShader) { m_shader = aShader; }
		inline void SetTexture(Texture* aTexture) { mTexture = aTexture; }

		uint32 GetID() const { return mId; }
		Shader* m_shader;

		uint32 GetShaderVariableLoc(const char* aVariable);

		void SetPointLightData(std::vector<Light*>& aLights);

		private:
		void CalculateAllLightInformation();
		std::string mName;
		glm::vec4 mDiffuseColor;
		glm::vec4 mAmbientColor;
		float mSpecular;
		uint32 mId;
		Texture* mTexture;

	};
}
