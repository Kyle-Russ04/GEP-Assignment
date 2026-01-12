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
	std::string meshFile = "curuthers/curuthers.obj";

	FILE* file = fopen(meshFile.c_str(), "r");
	if (file)
	{
		fclose(file);
		OnLoadMesh(meshFile);
	}
	else
	{
		std::cerr << "ERROR: Could not find mesh file: " << meshFile << std::endl;
		return;
	}
	if (_mesh)
	{
		_mesh->Draw();
	}
}
