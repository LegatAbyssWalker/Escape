#pragma once

#include "SFML/Graphics.hpp"

#include "State.h"

#include <iostream>
#include <string>
#include <map>

struct FontTexture {
	sf::Image texture;
	int textureSize = 0;
};

class Font {
	public:
		Font() = default;
		
		void loadFont(std::string const& fontName, unsigned int textSize);

		FontTexture& getFont(unsigned int textSize);
		sf::Glyph getGlyph(char letter, unsigned int textSize);

	private:
		std::string fontName = "";
		sf::Font font;

		const std::string charSet = "()[]{}<>!§$%&=?,.-;:_#*+~0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		std::map<int, FontTexture> loadedTextSizes;
};

