#pragma once

#include "Font.h"
#include "State.h"
#include "Program.h"
#include "GLWindow.h"

#include <vector>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Text {
	public:
		Text(GLWindow& window);

		void createText(glm::vec2 textPosition, unsigned int characterSize, Font* font, std::string text);
		void setText(std::string newText);
		void render();

	private:
		GLWindow& window;

		std::vector<float> vertices;
		unsigned int VAO, VBO, texture;

		float cursorPosition;
		unsigned int characterSize;
		float baseLineX, baseLineY;

		FontTexture* fontTexture;
		Font* textFont;
		std::unique_ptr<Program> program = nullptr;
};

