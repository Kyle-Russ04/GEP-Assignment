#pragma once


#include <GLM/glm.hpp>
#include <SDL/SDL.h>
#include "glew.h"
#include "Resource.h"
#include <string>

namespace ECS
{

	struct Mesh : Resource
	{
	public:
		void Draw()
		{
			// Activate the VAO
			glBindVertexArray(_VAO);

			// Tell OpenGL to draw it
			// Must specify the type of geometry to draw and the number of vertices
			glDrawArrays(GL_TRIANGLES, 0, _numVertices);

			// Unbind VAO
			glBindVertexArray(0);
		};
		void LoadOBJ(std::string filename);

		unsigned int _numVertices = 0;
		GLuint _VAO = 0;

	};

}