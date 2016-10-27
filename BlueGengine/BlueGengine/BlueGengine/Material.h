#pragma once

#include "Types.h"
#include "NonCopyable.h"
#include <string>
#include <glm/vec4.hpp>
namespace BlueGengine
{
	class Shader;
	class Texture;
	class Material : public NonCopyable
	{
		public:
		enum TextureType
		{
			Diffuse,
			SpecularMap,
			NormalMap
		};


		Material(uint32 a_materialID);
		~Material();


		void PrepareForDrawing();
		void Unprep();
		inline void SetDiffuseColor(glm::vec4 a_color) { m_diffuseColor = a_color; }
		inline void SetAmbientColor(glm::vec4 a_color) { m_ambientColor = a_color; }
		inline void SetSpecularPower(float a_spec) { m_specular = a_spec; }

		inline void SetShader(Shader* a_shader) { m_shader = a_shader; }
		inline void SetTexture(Texture* a_texture) { m_texture = a_texture; }
		//TODO change this so it gets an id from a material manager
		uint32 GetID() const { return m_id; }
		Shader* m_shader;
		private:
		std::string m_name;
		glm::vec4 m_diffuseColor;
		glm::vec4 m_ambientColor;
		float m_specular;
		uint32 m_id;
		Texture* m_texture;
	};
}
