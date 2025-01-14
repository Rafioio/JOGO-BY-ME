#include "../include/Loja.hpp"
#include "../include/Globals.hpp"

Shop::Shop()
    : shopWindow(sf::VideoMode(600, 600), "Loja"){
    if (!font.loadFromFile("assets/fonts/PIXEARG_.TTF")) {
        throw std::runtime_error("Erro ao carregar a fonte!");
    }
    if (!lojaTexture.loadFromFile("assets/textures/loja.jpg")) {
        throw std::runtime_error("Erro ao carregar a imagem de fundo!");
    }

    lojaSprite.setTexture(lojaTexture);
    lojaSprite.setScale(0.35f, 0.35f);

    buyStraightPlus = std::make_unique<Button>(10, 50, 200, 100, sf::Color::White, "Espinafre", font);
    buyTimePlus = std::make_unique<Button>(10, 350, 200, 100, sf::Color::White, "Gasolina", font);
    buyWorkerPlus = std::make_unique<Button>(10, 200, 200, 100, sf::Color::White, "Enxada", font);

    moneyText.setFont(font);
    moneyText.setCharacterSize(24);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setPosition(10, 10);

    updateMoneyText(); // Atualiza o texto do contador

    precoTaxaSpeedText.setFont(font);
    precoTaxaSpeedText.setCharacterSize(24);
    precoTaxaSpeedText.setFillColor(sf::Color::Black);
    precoTaxaSpeedText.setPosition(220, 380);
    precoTaxaSpeedText.setCharacterSize(32);

    precoTaxaStraghtText.setFont(font);
    precoTaxaStraghtText.setCharacterSize(24);
    precoTaxaStraghtText.setFillColor(sf::Color::Black);
    precoTaxaStraghtText.setPosition(220, 80);
    precoTaxaStraghtText.setCharacterSize(32);

    precoTaxaWorkerText.setFont(font);
    precoTaxaWorkerText.setCharacterSize(24);
    precoTaxaWorkerText.setFillColor(sf::Color::Black);
    precoTaxaWorkerText.setPosition(220, 230);
    precoTaxaWorkerText.setCharacterSize(32);
}

void Shop::updateTexts() {
    moneyText.setString("Dinheiro: " + std::to_string(clickCount));
    precoTaxaSpeedText.setString("Valor: " + std::to_string(precoTaxaSpeed));
    precoTaxaStraghtText.setString("Valor: " + std::to_string(precoTaxaStraght));
    precoTaxaWorkerText.setString("Valor: " + std::to_string(precoTaxaWorker));
}
void Shop::updateMoneyText() {
    moneyText.setString("Dinheiro: " + std::to_string(clickCount));
}
void Shop::handleEvents() {
    sf::Event event;
    while (shopWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            shopWindow.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(shopWindow);

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

void Shop::run() {
    while (shopWindow.isOpen()) {
        handleEvents();
        render();
    }
}

void Shop::render() {
    updateTexts();
    shopWindow.clear();
    shopWindow.draw(lojaSprite);// Exibe o texto do dinheiro
    buyStraightPlus->draw(shopWindow);
    buyTimePlus->draw(shopWindow);
    buyWorkerPlus->draw(shopWindow);
    shopWindow.draw(precoTaxaSpeedText);
    shopWindow.draw(precoTaxaStraghtText);
    shopWindow.draw(precoTaxaWorkerText);
    shopWindow.display();
}