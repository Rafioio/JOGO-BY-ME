#include "../include/Loja.hpp"
#include "../include/Globals.hpp"

Shop::Shop()
    : shopWindow(sf::VideoMode(600, 600), "Loja") {
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
}

void Shop::updateMoneyText() {
    moneyText.setString("Dinheiro: " + std::to_string(clickCount)); // Atualiza o texto com o valor atual
}
void Shop::update() {
    updateMoneyText();  // Atualiza o texto de dinheiro constantemente
}

void Shop::handleEvents() {
    sf::Event event;
    while (shopWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            shopWindow.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(shopWindow);

            if (buyStraightPlus->isClicked(mousePos) && clickCount >= 10) {
                clickCount -= 10; // Deduz o custo
                taxaStraght++;
                updateMoneyText(); // Atualiza o texto do contador
            }

            if (buyTimePlus->isClicked(mousePos) && clickCount >= 10) {
                clickCount -= 10;
                taxaSpeed += 50;
                updateMoneyText();
            }

            if (buyWorkerPlus->isClicked(mousePos) && clickCount >= 10) {
                clickCount -= 10;
                taxaWorker++;
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
    shopWindow.clear();
    shopWindow.draw(lojaSprite);
    shopWindow.draw(moneyText); // Exibe o texto do dinheiro
    buyStraightPlus->draw(shopWindow);
    buyTimePlus->draw(shopWindow);
    buyWorkerPlus->draw(shopWindow);
    shopWindow.display();
}
