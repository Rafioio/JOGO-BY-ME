#include "../include/Game.hpp"

Game::Game()
    : window(sf::VideoMode(800, 600), "Clicker"),
      clickCount(0), workerCount(0), precoTrabalhador(10),
      loadingBar(100.f, 500.f, 600.f, 30.f) {
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

void Game::update() {
    if (loadingBar.isComplete()) {
            loadingBar.reset();  // Reseta a barra
            clickCount++;
    }
    float deltaTime = clock.restart().asSeconds();  // Calcula o tempo entre atualizações

    // Atualiza a barra de carregamento
    loadingBar.update(deltaTime, 1000.f);  // Aumenta o progresso da barra

    if (workerClock.getElapsedTime().asSeconds() >= 1.0f) {
        clickCount += workerCount;
        workerClock.restart();
    }
    updateTexts();
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (workButton->isClicked(mousePos) && loadingBar.barrazerada()) {
                loadingBar.startLoading();
            }
        
            if (hireButton->isClicked(mousePos) && clickCount >= precoTrabalhador) {
                clickCount -= precoTrabalhador;
                workerCount++;
                precoTrabalhador = static_cast<int>(precoTrabalhador * 1.5);
            }
        }
    }
}



void Game::render() {
    window.clear();
    window.draw(backgroundSprite);
    loadingBar.draw(window);
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
