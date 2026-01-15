#include "HUD.h"
#include <fstream>


using namespace ECS;


//void HUD::Initialise()
//{
//	if(hasInitialized)
//	{
//		return;
//	}
//	hasInitialized = true;
//	//initialising the text
//	if (TTF_Init() < 0)
//	{
//		std::cout << "Text initialised failed: " << TTF_GetError() << std::endl;
//	}
//
//	font = TTF_OpenFont("Minecraft.ttf", 24);
//	if (!font)
//	{
//		std::cout << "Font failed to initialise" << std::endl;
//	}
//}
//
//void HUD::DisplayScore()
//{
//	std::stringstream  Words;
//	Words << "Score: " << score;
//	const std::string text = Words.str();
//	//render the text to a surface
//	m_text = TTF_RenderText_Solid(font, text.c_str(), colour);
//	if(!m_text)
//	{
//		std::cout << "Text surface failed to initialise: " << TTF_GetError() << std::endl;
//	}
//	//create texture from surface
//	texture = SDL_CreateTextureFromSurface(renderer, m_text);
//	if(!texture)
//	{
//		std::cout << "Text texture failed to initialise: " << SDL_GetError() << std::endl;
//	}
//	//queery texture to renderer
//	SDL_Rect destination = { 25, 25, 125, 75 };
//	if(SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h) != 0)
//	{
//		std::cout << "Text texture query failed: " << SDL_GetError() << std::endl;
//		SDL_DestroyTexture(texture);
//		return;
//	}
//	SDL_RenderCopy(renderer, texture, NULL, &destination);
//	SDL_DestroyTexture(texture);
//}

void HUD::Load_Font()
{
    FT_Error error = FT_Init_FreeType(&ft);
    if (error)
    {
        throw std::runtime_error("Freetype init failed: " + std::to_string(error));
    }

    // Load font face
    error = FT_New_Face(ft, _path.c_str(), 0, &face);
    if (error)
    {
        std::cerr << "FT_New_Face error: " << error << std::endl;
        throw std::runtime_error("Failed to load font (Error: " + std::to_string(error) + ")");
    }

    // Ensure face is valid before setting size
    if (!face) {
        throw std::runtime_error("Font face is null!");
    }
    FT_Set_Pixel_Sizes(face, 0, 48); // Now safe to call
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Letters letter = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Letter.insert(std::pair<char, Letters>(c, letter));
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    face = nullptr;
    ft = nullptr;
    //release when done
}


void HUD::Render_Text(std::string text, float x, float y, float scale, glm::vec3 color)
{
    glDisable(GL_DEPTH_TEST); // Disable depth test for 2D text
    // ... rendering code ...
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Letters ch = Letter[*c];

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.texture_ID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph
        x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_DEPTH_TEST); // Re-enable if needed
}

void HUD::SetRenderBuffer()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //activate corresponding render state	
}

void HUD::load_data(const std::string& _vertex, const std::string& _fragment)
{
    std::ifstream file(_vertex.c_str());
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open VERTEX shader file: " + _vertex);
    }
    while (!file.eof())
    {
        std::string line;
        getline(file, line);
        vertex += line + '\n';
    }
    //stores the vertex into the string file in class

    std::ifstream file2(_fragment.c_str());
    if (!file2.is_open())
    {
        throw std::exception();
        //throw std::runtime_error("Failed to open FRAGMENT shader file: " + _fragment);
    }
    while (!file2.eof())
    {
        std::string line;
        getline(file2, line);
        fragment += line + '\n';
    }

}

