#include "MeshRenderer.h"

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
	std::cout << "Drawing Mesh Renderer Component" << std::endl;
	//This needs:
	//The model matrix from the transform component
	//add methods in Entity to query other components
	//The view and projection matrices from the camera component
	//store current camera in core, then retrieve from there
	//finally send matrices to shader then draw

	//project relative path to mesh

	if(!_mesh)
	{
		std::cerr << "ERROR: Could not find mesh file for MeshRenderer" << std::endl;
		return;
	}

	if (!_material)
	{
		_material = std::make_unique<ECS::Material>();
		const std::string vertPath = "shaders/basic.vert";
		const std::string fragPath = "shaders/basic.frag";
		if (!_material->LoadShaders(vertPath, fragPath))
		{
			std::cerr << "ERROR: Could not find material for MeshRenderer" << std::endl;
			return;
		}
		_material->SetDiffuseColour(glm::vec3(0.8f, 0.8f, 0.8f));
		_material->SetEmissiveColour(glm::vec3(0.0f));
		_material->SetSpecularColour(glm::vec3(0.2f));
	}

	glm::mat4 modelMatrix = glm::mat4(1.0f); // Identity matrix as placeholder

	if (_mesh)
	{
		_mesh->Draw();
	}
}
