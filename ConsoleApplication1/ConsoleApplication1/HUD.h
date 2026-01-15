#pragma once

#include "Component.h"
#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <GLM/ext.hpp>
#include <SDL/SDL.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <map>
#include <sstream>
#include <string>
#include <iostream>



namespace ECS
{
	struct HUD : Component
	{
	public:

		void Load_Font();
		void Render_Text(std::string text, float x, float y, float scale, glm::vec3 color);

		struct Letters {
			unsigned int texture_ID; //id of glyph texture
			glm::ivec2 size; //size of glyph
			glm::ivec2 bearing; //offset from baseline
			unsigned int advance; //offset to next glyph
		};
		std::map<char, Letters> Letter;
		int score{ 0 };

	private:
		GLuint VAO;
		GLuint VBO;
		FT_Library ft;
		FT_Face face;
		std::string _path = "Text/arial.ttf";
		void SetRenderBuffer();
		void load_data(const std::string& _vertex, const std::string& _fragment);

		std::string vertex;
		std::string fragment;

	};

}