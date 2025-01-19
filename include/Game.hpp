#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <memory>
#include <string>
#include "Button.hpp"
#include "LoadingBar.hpp"
#include "Loja.hpp"
#include "Inferno.hpp"
 
class Game {
private:
    LoadingBar loadingBar;

    bool infernoButtonClicked = false;
    bool shopButtonClicked = false;
    sf::RenderWindow window;
    sf::Font font;
    std::unique_ptr<Button> workButton;
    std::unique_ptr<Button> hireButton;
    std::unique_ptr<Button> shopButton;
    std::unique_ptr<Button> infernoButton;

    int workerCount;
    int precoTrabalhador;

    sf::Clock clock;
    sf::Clock workerClock;

    sf::Text moneyText;
    sf::Text workersText;
    sf::Texture fazendaTexture;  
    sf::Sprite fazendaSprite;    

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
