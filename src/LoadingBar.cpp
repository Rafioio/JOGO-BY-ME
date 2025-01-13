#include "../include/LoadingBar.hpp"
#include <iostream>
// Construtor para inicializar a posição, tamanho e cores
LoadingBar::LoadingBar(float x, float y, float width, float height)
    : barWidth(width), barHeight(height), loadingProgress(0.f), isLoading(false) {

    // Configurando o fundo da barra
    barBackground.setSize(sf::Vector2f(barWidth, barHeight));
    barBackground.setPosition(x, y);
    barBackground.setFillColor(sf::Color::Black); // Cor do fundo da barra

    // Configurando a barra de carregamento (inicialmente vazia)
    loadingBar.setSize(sf::Vector2f(0.f, barHeight));  // A barra começa com largura 0
    loadingBar.setPosition(x, y);
    loadingBar.setFillColor(sf::Color::Green); // Cor da parte carregada da barra
}

// Implementação do método startLoading
void LoadingBar::startLoading() {
    isLoading = true;
    loadingProgress = 0.f;  // Começa o carregamento
}

bool LoadingBar::isComplete() const {
    return loadingProgress >= barWidth;  // Verifica se o progresso alcançou o limite
    
}

void LoadingBar::reset() {

    loadingProgress = 0.f;
}
bool LoadingBar::barrazerada() const {
    return loadingProgress == 0;
}
// Atualiza o progresso da barra com base no deltaTime e speed
void LoadingBar::update(float deltaTime, float speed) {
     // Teste com valor fixo para ver a barra preenchend
    if (isLoading) {
        loadingProgress += speed * deltaTime;
        if (loadingProgress >= barWidth) {
            loadingProgress = barWidth;
            isLoading = false;
        }
        loadingBar.setSize(sf::Vector2f(loadingProgress, barHeight));
    }

    // Debug: Verifique o progresso da barra

}



// Desenha a barra na janela
void LoadingBar::draw(sf::RenderWindow& window) {
    window.draw(barBackground); // Desenha o fundo da barra
    window.draw(loadingBar);    // Desenha a parte carregada da barra
}
