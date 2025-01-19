#include "../include/Inferno.hpp"
#include "../include/Globals.hpp"

Inferno::Inferno()
    : infernoWindow(sf::VideoMode(600, 600), "inferno"){
    if (!font.loadFromFile("assets/fonts/PIXEARG_.TTF")) {
        throw std::runtime_error("Erro ao carregar a fonte!");
    }
    if (!infernoTexture.loadFromFile("assets/textures/inferno.jpg")) {
        throw std::runtime_error("Erro ao carregar a imagem de fundo!");
    }

    infernoSprite.setTexture(infernoTexture);
    infernoSprite.setScale(0.35f, 0.35f);
    sf::Vector2u windowSize = infernoWindow.getSize();

        infernoSprite.setScale(
        static_cast<float>(windowSize.x) / infernoTexture.getSize().x,  // Largura
        static_cast<float>(windowSize.y) / infernoTexture.getSize().y   // Altura
    );
    buyStraightPlus = std::make_unique<Button>(10, 50, 200, 100, sf::Color::White, "Peste", font);
    buyTimePlus = std::make_unique<Button>(10, 350, 200, 100, sf::Color::White, "Bomba-H", font);
    buyWorkerPlus = std::make_unique<Button>(10, 200, 200, 100, sf::Color::White, "Escravizar", font);

    moneyText.setFont(font);
    moneyText.setCharacterSize(24);
    moneyText.setFillColor(sf::Color::Red);
    moneyText.setPosition(10, 10);

    updateMoneyText(); // Atualiza o texto do contador

    precoTaxaSpeedText.setFont(font);
    precoTaxaSpeedText.setCharacterSize(24);
    precoTaxaSpeedText.setFillColor(sf::Color::White);
    precoTaxaSpeedText.setPosition(220, 380);
    precoTaxaSpeedText.setCharacterSize(32);

    precoTaxaStraghtText.setFont(font);
    precoTaxaStraghtText.setCharacterSize(24);
    precoTaxaStraghtText.setFillColor(sf::Color::White);
    precoTaxaStraghtText.setPosition(220, 80);
    precoTaxaStraghtText.setCharacterSize(32);

    precoTaxaWorkerText.setFont(font);
    precoTaxaWorkerText.setCharacterSize(24);
    precoTaxaWorkerText.setFillColor(sf::Color::White);
    precoTaxaWorkerText.setPosition(220, 230);
    precoTaxaWorkerText.setCharacterSize(32);
}

void Inferno::updateTexts() {
    moneyText.setString("Dinheiro: " + std::to_string(clickCount));
    precoTaxaSpeedText.setString("Valor: " + std::to_string(precoTaxaSpeed));
    precoTaxaStraghtText.setString("Valor: " + std::to_string(precoTaxaStraght));
    precoTaxaWorkerText.setString("Valor: " + std::to_string(precoTaxaWorker));
}
void Inferno::updateMoneyText() {
    moneyText.setString("Dinheiro: " + std::to_string(clickCount));
}
void Inferno::handleEvents() {
    sf::Event event;
    while (infernoWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            infernoWindow.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(infernoWindow);

            if (buyStraightPlus->isClicked(mousePos) && clickCount >= precoTaxaStraght) {
                clickCount -= precoTaxaStraght; // Deduz o custo
                taxaStraght++;
                precoTaxaStraght = static_cast<int>(precoTaxaStraght * 1.5);
                updateMoneyText(); // Atualiza o texto do contador
            }

            if (buyTimePlus->isClicked(mousePos) && clickCount >= precoTaxaSpeed) {
                clickCount -= precoTaxaSpeed;
                taxaSpeed += 50;
                precoTaxaSpeed = static_cast<int>(precoTaxaSpeed * 1.5);
                updateMoneyText();
            }

            if (buyWorkerPlus->isClicked(mousePos) && clickCount >= precoTaxaWorker) {
                clickCount -= precoTaxaWorker;
                taxaWorker++;
                precoTaxaWorker = static_cast<int>(precoTaxaWorker * 1.5);
                updateMoneyText();
            }
        }
    }
}

void Inferno::run() {
    while (infernoWindow.isOpen()) {
        handleEvents();
        render();
    }
}

void Inferno::render() {
    updateTexts();
    infernoWindow.clear();
    infernoWindow.draw(infernoSprite);// Exibe o texto do dinheiro
    buyStraightPlus->draw(infernoWindow);
    buyTimePlus->draw(infernoWindow);
    buyWorkerPlus->draw(infernoWindow);
    infernoWindow.draw(precoTaxaSpeedText);
    infernoWindow.draw(precoTaxaStraghtText);
    infernoWindow.draw(precoTaxaWorkerText);
    infernoWindow.display();
}