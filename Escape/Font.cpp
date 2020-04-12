#include "Font.h"

void Font::loadFont(std::string const& fontName, unsigned int textSize) {
	this->fontName = fontName;

	font.loadFromFile(fontName);

	// Generates the font texture with all the chars in the charset
	for (char letter: charSet) { font.getGlyph(letter, textSize, false); }

	const sf::Texture & temp = font.getTexture(textSize);
	FontTexture fontTexture;
	fontTexture.texture = temp.copyToImage();
	fontTexture.textureSize = fontTexture.texture.getSize().x;
	loadedTextSizes.insert(std::make_pair(textSize, fontTexture));
}

FontTexture& Font::getFont(unsigned int textSize) {
	if (fontName == "") { std::cout << "ERROR WITH FONT NAME!\n"; }

	if (loadedTextSizes.find(textSize) == loadedTextSizes.end()) { loadFont(fontName, textSize); }

	return loadedTextSizes.at(textSize);
}

sf::Glyph Font::getGlyph(char letter, unsigned int textSize) {
	return font.getGlyph(letter, textSize, false);
}
