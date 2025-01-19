#ifndef Inferno_HPP
#define Inferno_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include "Button.hpp"

class Inferno {
public:
    Inferno();
    void run();
    void handleEvents();
    void update();
    void render();

private:
    std::unique_ptr<Button> buyWorkerPlus;
    std::unique_ptr<Button> buyTimePlus;
    std::unique_ptr<Button> buyStraightPlus;
    sf::RenderWindow infernoWindow;
    sf::Font font;
    sf::Texture infernoTexture;
    sf::Sprite infernoSprite;
    
    sf::Text moneyText;
    sf::Text precoTaxaSpeedText;
    sf::Text precoTaxaStraghtText;
    sf::Text precoTaxaWorkerText;

    void updateMoneyText();
    void updateTexts();
};

#endif // SHOP_HPP
