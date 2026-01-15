#include "MeshRenderer.h"
#include "Transform.h"
#include "Entity.h"
#include "Core.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

using namespace ECS;

void MeshRenderer::OnLoadMesh(const std::string& filename)
{
	_mesh = std::make_unique<ECS::Mesh>();
	_mesh->LoadOBJ(filename);
	_VAO = _mesh->_VAO;
	_numVertices = _mesh->_numVertices;
}
// Draws the mesh - must have shaders applied for this to display!
void MeshRenderer::Draw()
{
	// MeshRenderer-specific draw logic
	//This needs:
	//The model matrix from the transform component
	//add methods in Entity to query other components
	//The view and projection matrices from the camera component
	//store current camera in core, then retrieve from there
	//finally send matrices to shader then draw

	//project relative path to mesh

	if (!_mesh)
	{
		std::cerr << "ERROR: Could not find mesh file for MeshRenderer" << std::endl;
		return;
	}

	if (!_material)
	{
		_material = std::make_unique<ECS::Material>();

		if (!_material->LoadShaders(vertPath, fragPath))
		{
			std::cerr << "ERROR: Could not find material for MeshRenderer" << std::endl;
			return;
		}
		//_material->SetDiffuseColour(glm::vec3(0.8f, 0.8f, 0.8f));
		//_material->SetEmissiveColour(glm::vec3(0.0f));
		//_material->SetSpecularColour(glm::vec3(0.2f));
	}

	unsigned int textureID = _material->LoadTexture(texturePath);
	if (textureID != 0)
	{
		_material->_texture1 = textureID;
	}


	glm::mat4 modelMatrix = glm::mat4(1.0f); // Identity matrix as placeholder


	// Build model matrix from Transform component if present
	glm::mat4 modelMat = glm::mat4(1.0f);
	if (auto ent = GetEntity())
	{
		auto transform = ent->GetComponent<Transform>();
		if (transform)
		{
			// Transform currently exposes position only; use it if available
			glm::vec3 pos = transform->GetPosition();
			modelMat = glm::translate(glm::mat4(1.0f), pos);
			// TODO: incorporate rotation/scale when Transform exposes them
		}
	}

	// Inverse model matrix
	glm::mat4 invModel = glm::inverse(modelMat);

	// Build view and projection (fallbacks if no camera system is present)
	glm::mat4 viewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f),   // eye
		glm::vec3(0.0f, 0.0f, 0.0f),   // center
		glm::vec3(0.0f, 1.0f, 0.0f));  // up

	glm::mat4 projMat = glm::mat4(1.0f);
	// attempt to get window aspect from Core if possible
	float aspect = 1.0f;
	if (auto ent = GetEntity())
	{
		if (auto core = ent->GetCore())
		{
			SDL_Window* window = core->m_window;
			if (window)
			{
				int w = 1, h = 1;
				SDL_GetWindowSize(window, &w, &h);
				if (h != 0) aspect = static_cast<float>(w) / static_cast<float>(h);
			}
		}
	}
	projMat = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);

	// Send matrices to material and activate shader + textures
	_material->SetMatrices(modelMat, invModel, viewMat, projMat);
	_material->Apply();


	if (_mesh)
	{
		_mesh->Draw();
	}
}

void MeshRenderer::SetTexturePath(std::string _textpath)
{
	texturePath = _textpath;
}

void MeshRenderer::SetVertexShaderPath(std::string _vertpath)
{
	vertPath = _vertpath;
}

void MeshRenderer::SetFragmentShaderPath(std::string _fragpath)
{
	fragPath = _fragpath;
}
