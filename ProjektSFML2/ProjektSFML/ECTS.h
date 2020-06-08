#pragma once
#include "Animacje.h"
#include <iostream>
#include <SFML\Graphics.hpp>
class Coin {
public:
    Coin(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    ~Coin();
    void Draw(sf::RenderWindow& window);

    sf::FloatRect getGlobalBounds() {
        return coin.getGlobalBounds();
    }

    void setPos(sf::Vector2f newPos) {
        coin.setPosition(newPos);
    }
    void Update(float deltaTime);
private:
    sf::RectangleShape coin;
    Animation animation;
    bool faceRight;
    unsigned int row;
};




