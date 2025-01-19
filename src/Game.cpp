#include "../include/Game.hpp"
#include "../include/Globals.hpp"
#include <thread>
#include <iomanip> 

Game::Game()
    : window(sf::VideoMode(800, 600), "Fazenda"),
      workerCount(0), precoTrabalhador(10),
      loadingBar(100.f, 500.f, 600.f, 30.f) {
    // Carrega a fonte
    if (!font.loadFromFile("assets/fonts/PIXEARG_.TTF")) {
        throw std::runtime_error("Erro ao carregar a fonte!");
    }

    // Carrega a textura de fundo
    if (!fazendaTexture.loadFromFile("assets/textures/Fazenda.jpg")) {
        throw std::runtime_error("Erro ao carregar a imagem de fundo!");
    }
    fazendaSprite.setTexture(fazendaTexture);

    // Configuração dos botões
    workButton = std::make_unique<Button>(10, 50, 200, 100, sf::Color::Green, "Trabalhar", font);
    shopButton = std::make_unique<Button>(10, 350, 200, 100, sf::Color::Blue, "50 RS", font);
    hireButton = std::make_unique<Button>(10, 200, 200, 100, sf::Color::Yellow, "Contratar: 10", font);
    infernoButton = std::make_unique<Button>(300, 350, 200, 100, sf::Color::Red, "10000 RS", font);

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
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << clickCount; // Limita a 2 casas decimais
    moneyText.setString("Dinheiro: " + ss.str());
    workersText.setString("Quantidade de Camaradas: " + std::to_string(workerCount));
    hireButton->setText("Contratar: " + std::to_string(precoTrabalhador));
}

void Game::update() {
    if (loadingBar.isComplete()) {
        loadingBar.reset();  // Reseta a barra
        clickCount += taxaStraght * taxaStraght / 4;
    }

    float deltaTime = clock.restart().asSeconds();
    loadingBar.update(deltaTime, taxaSpeed);

    if (workerClock.getElapsedTime().asSeconds() >= 1.0f) {
        clickCount += workerCount * taxaWorker;
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
            
            if (shopButton->isClicked(mousePos) && !shopButtonClicked) {
                if(clickCount>=50){
                    clickCount -= 50;
                    shopButton->setText("Loja");
                    std::thread shopThread([&]() {
                        Shop shop;
                        shop.run();
                        
                    });
                    shopThread.detach();
                    shopButtonClicked = true;
                }}
            else if (shopButton->isClicked(mousePos) && shopButtonClicked) {
                std::thread shopThread([&]() {
                    Shop shop;
                    shop.run();
                        
                });
                shopThread.detach();

            }

            if (infernoButton->isClicked(mousePos) && !infernoButtonClicked) {
                if(clickCount>=10000){
                    clickCount -= 10000;
                    infernoButton->setText("Inferno");
                    std::thread infernoThread([&]() {
                        Inferno inferno;
                        inferno.run();
                        
                    });
                    infernoThread.detach();
                    infernoButtonClicked = true;
                }}
            else if (infernoButton->isClicked(mousePos) && infernoButtonClicked) {
                std::thread infernoThread([&]() {
                    Inferno inferno;
                    inferno.run();
                        
                });
                infernoThread.detach();

            }
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
    window.clear(sf::Color(139, 69, 19));
    window.draw(fazendaSprite);
    shopButton->draw(window);
    loadingBar.draw(window);
    workButton->draw(window);
    hireButton->draw(window);
    infernoButton->draw(window);
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
