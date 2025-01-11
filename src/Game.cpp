#include "../include/Game.hpp"

Game::Game()
    : window(sf::VideoMode(800, 600), "Clicker"),
      clickCount(0), workerCount(0), precoTrabalhador(10) {
    // Carrega a fonte
    if (!font.loadFromFile("assets/fonts/PIXEARG_.TTF")) {
        throw std::runtime_error("Erro ao carregar a fonte!");
    }

    // Carrega a textura de fundo
    if (!backgroundTexture.loadFromFile("assets/textures/Fazenda.jpg")) {
        throw std::runtime_error("Erro ao carregar a imagem de fundo!");
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Configuração do botão "Trabalhar"
    workButton = std::make_unique<Button>(10, 50, 200, 100, sf::Color::Green, "Trabalhar", font);

    // Configuração do botão "Contratar"
    hireButton = std::make_unique<Button>(10, 200, 200, 100, sf::Color::Yellow, "Contratar: 10", font);

    // Configuração dos textos
    moneyText.setFont(font);
    moneyText.setCharacterSize(24);
    moneyText.setFillColor(sf::Color::Black);
    moneyText.setPosition(350, 50);

    workersText.setFont(font);
    workersText.setCharacterSize(24);
    workersText.setFillColor(sf::Color::Black);
    workersText.setPosition(350, 100);

    updateTexts();
}

void Game::updateTexts() {
    moneyText.setString("Dinheiro: " + std::to_string(clickCount));
    workersText.setString("Lucro/seg: " + std::to_string(workerCount));
    hireButton->setText("Contratar: " + std::to_string(precoTrabalhador));
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (workButton->isClicked(mousePos)) {
                clickCount++;
            }

            if (hireButton->isClicked(mousePos) && clickCount >= precoTrabalhador) {
                clickCount -= precoTrabalhador;
                workerCount++;
                precoTrabalhador = static_cast<int>(precoTrabalhador * 1.5);
            }
        }
    }
}

void Game::update() {
    if (clock.getElapsedTime().asSeconds() >= 1.0f) {
        clickCount += workerCount;
        clock.restart();
    }
    updateTexts();
}

void Game::render() {
    window.clear();
    window.draw(backgroundSprite);
    workButton->draw(window);
    hireButton->draw(window);
    window.draw(moneyText);
    window.draw(workersText);
    window.display();
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}
