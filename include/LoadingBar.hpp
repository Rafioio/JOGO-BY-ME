#ifndef LOADING_BAR_HPP
#define LOADING_BAR_HPP

#include <SFML/Graphics.hpp>

class LoadingBar {
public:
    // Construtor para inicializar a posição, tamanho e cores
    LoadingBar(float x, float y, float width, float height);

    // Atualiza o progresso da barra com base no tempo e na velocidade
    void update(float deltaTime, float speed);
    bool isComplete() const;
    void draw(sf::RenderWindow& window);
    void reset();
    void startLoading();
    bool barrazerada() const;

private:
    sf::RectangleShape barBackground; // Fundo da barra
    sf::RectangleShape loadingBar;    // Parte da barra que se preenche
    float barWidth;  // Largura total da barra
    float barHeight; // Altura da barra
    float loadingProgress; // Progresso do carregamento
    bool isLoading;
};

#endif // LOADING_BAR_HPP
