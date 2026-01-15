#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Material.h"
#include "glew.h"
#include <string>

namespace ECS
{
	struct MeshRenderer : ECS::Component
	{
	protected:

		// OpenGL Vertex Array Object
		GLuint _VAO;

		// Number of vertices in the mesh
		unsigned int _numVertices;

		std::unique_ptr<ECS::Mesh> _mesh;
		std::unique_ptr<ECS::Material> _material;
		

	public:
		std::string texturePath;
		std::string vertPath;
		std::string fragPath;
		void OnLoadMesh(const std::string& filename);
		void Draw();

		virtual void OnDraw() override
		{
			Draw();
		}
		void SetTexturePath( std::string _textpath);
		void SetVertexShaderPath(std::string _vertpath);
		void SetFragmentShaderPath(std::string _fragpath);
	};

}