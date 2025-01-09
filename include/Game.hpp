#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <string>
#include "Button.hpp"

class Game {
private:
    sf::RenderWindow window;
    sf::Font font;
    std::unique_ptr<Button> workButton;
    std::unique_ptr<Button> hireButton;

    int clickCount;
    int workerCount;
    int precoTrabalhador;

    sf::Clock clock;

    sf::Text moneyText;
    sf::Text workersText;
    sf::Texture backgroundTexture;  
    sf::Sprite backgroundSprite;    

    void updateTexts();
    void handleEvents();
    void update();
    void render();

public:
    Game();
    ~Game() = default;
    void run();
};

#endif
