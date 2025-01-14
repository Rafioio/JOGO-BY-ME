#ifndef SHOP_HPP
#define SHOP_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include "Button.hpp"

class Shop {
public:
    Shop();
    void run();
    void handleEvents();
    void update();
    void render();

private:
    std::unique_ptr<Button> buyWorkerPlus;
    std::unique_ptr<Button> buyTimePlus;
    std::unique_ptr<Button> buyStraightPlus;
    sf::RenderWindow shopWindow;
    sf::Font font;
    sf::Texture lojaTexture;
    sf::Sprite lojaSprite;
    
    sf::Text moneyText;
    sf::Text precoTaxaSpeedText;
    sf::Text precoTaxaStraghtText;
    sf::Text precoTaxaWorkerText;

    void updateMoneyText();
    void updateTexts();
};

#endif // SHOP_HPP
