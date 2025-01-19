#include "../include/Button.hpp"

Button::Button(float x, float y, float width, float height, const sf::Color& color, const std::string& label, sf::Font& font) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    // Centraliza o texto no botão
    text.setPosition(
        x + (width - text.getGlobalBounds().width) / 2.f,
        y + (height - text.getGlobalBounds().height) / 2.f
    );
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

bool Button::isClicked(const sf::Vector2i& mousePos) {
    return shape.getGlobalBounds().contains(mousePos.x, mousePos.y);
}


void Button::setText(const std::string& label) {
    text.setString(label);

    // Recalcula a posição para centralizar o texto no botão
    text.setPosition(
        shape.getPosition().x + (shape.getSize().x - text.getGlobalBounds().width) / 2.f,
        shape.getPosition().y + (shape.getSize().y - text.getGlobalBounds().height) / 2.f
    );
}
