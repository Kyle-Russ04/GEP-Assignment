#pragma once
#include <GLM/glm.hpp>
#include <SDL/SDL.h>
#include "glew.h"
#include "Resource.h"
#include <string>


namespace ECS
{

	struct Material
	{
		Material();
		~Material();

		bool LoadShaders(std::string vertFilename, std::string fragFilename);
		// Loads a .bmp from file
		unsigned int LoadTexture(std::string filename);
		bool CheckShaderCompiled(GLint shader);
		void SetMatrices(glm::mat4 modelMatrix, glm::mat4 invModelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix);
		void Apply();

		// The OpenGL shader program handle
		int _shaderProgram;

		// Locations of Uniforms in the vertex shader
		int _shaderModelMatLocation;
		int _shaderInvModelMatLocation;
		int _shaderViewMatLocation;
		int _shaderProjMatLocation;

		// Location of Uniforms in the fragment shader
		int _shaderDiffuseColLocation, _shaderEmissiveColLocation, _shaderSpecularColLocation;
		int _shaderWSLightPosLocation;
		int _shaderTex1SamplerLocation;

		// Local store of material properties to be sent to the shader
		glm::vec3 _emissiveColour;
		glm::vec3 _diffuseColour;
		glm::vec3 _specularColour;
		glm::vec3 _lightPosition;

		//allow for user to change the material properties
		void SetEmissiveColour(glm::vec3 colour) { _emissiveColour = colour; }
		void SetDiffuseColour(glm::vec3 colour) { _diffuseColour = colour; }
		void SetSpecularColour(glm::vec3 colour) { _specularColour = colour; }
		void SetLightPosition(glm::vec3 position) { _lightPosition = position; }

		glm::vec3 GetEmissiveColour() const { return _emissiveColour; }
		glm::vec3 GetDiffuseColour() const { return _diffuseColour; }
		glm::vec3 GetSpecularColour() const { return _specularColour; }
		glm::vec3 GetLightPosition() const { return _lightPosition; }

		// OpenGL handle for the texture
		unsigned int _texture1;

	};

}