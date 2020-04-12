#include "Text.h"


Text::Text(GLWindow& window)
    : window(window) {

    program = std::make_unique<Program>(TEXT_VERTEX_SHADER, TEXT_FRAGMENT_SHADER);
}

void Text::createText(glm::vec2 textPosition, unsigned int characterSize, Font* font, std::string text) {
    glGenTextures(1, &texture);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    baseLineX = textPosition.x;
    baseLineY = textPosition.y;
    vertices.clear();
    this->characterSize = characterSize;
    textFont = font;
    auto sizeTexure = textFont->getFont(this->characterSize).textureSize;

    cursorPosition = 0;
    sf::Vector2f posOnScreen = { baseLineX, baseLineY };
    vertices.clear();
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textFont->getFont(this->characterSize).texture.getSize().x,
        textFont->getFont(this->characterSize).texture.getSize().y,
        0, GL_RGBA, GL_UNSIGNED_BYTE, textFont->getFont(this->characterSize).texture.getPixelsPtr());

    glGenerateMipmap(GL_TEXTURE_2D);

    setText(text);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // Texture Coordinates
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

void Text::setText(std::string newText) {
    sf::Vector2f posOnScreen = { baseLineX, baseLineY };
    vertices.clear();
    for (char letter : newText) {
        sf::Glyph tempGlyph = textFont->getGlyph(letter, characterSize);
        int getTextureSize = textFont->getFont(characterSize).texture.getSize().x;
        float percTexture = 1.f / getTextureSize;

        sf::Vector2f topLeftCalculated = { tempGlyph.textureRect.left * percTexture,(tempGlyph.textureRect.top * percTexture) };
        sf::Vector2f widthHeightCalculated = { tempGlyph.textureRect.width * percTexture,tempGlyph.textureRect.height * percTexture };

        auto adjustedAdvance = (1.0f / window.getWindow().getSize().x) * tempGlyph.advance;
        auto adjustedheight  = (1.0f / window.getWindow().getSize().y) * tempGlyph.bounds.height;
        auto adjustedwidth   = (1.0f / window.getWindow().getSize().x) * tempGlyph.bounds.width;
        auto adjustedtop     = (1.0f / window.getWindow().getSize().y) * tempGlyph.bounds.top;


        std::vector<float> temp = {
            posOnScreen.x,  adjustedheight + posOnScreen.y, 0.0f,   topLeftCalculated.x, topLeftCalculated.y,
            posOnScreen.x, posOnScreen.y, 0.0f,   topLeftCalculated.x, topLeftCalculated.y + widthHeightCalculated.y,
            adjustedwidth + posOnScreen.x,posOnScreen.y, 0.0f,   topLeftCalculated.x + widthHeightCalculated.x, topLeftCalculated.y + widthHeightCalculated.y,
            adjustedwidth + posOnScreen.x,posOnScreen.y, 0.0f,   topLeftCalculated.x + widthHeightCalculated.x, topLeftCalculated.y + widthHeightCalculated.y,
            adjustedwidth + posOnScreen.x, adjustedheight + posOnScreen.y, 0.0f,   topLeftCalculated.x + widthHeightCalculated.x, topLeftCalculated.y,
            posOnScreen.x,adjustedheight + posOnScreen.y, 0.0f,  topLeftCalculated.x, topLeftCalculated.y
        };
        vertices.insert(vertices.end(), temp.begin(), temp.end());
        posOnScreen.x += adjustedAdvance;
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void Text::render() {
    program->useProgram();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);

    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
}
