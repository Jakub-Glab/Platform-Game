#pragma once
#include "Animacje.h"
#include <iostream>
#include <SFML\Graphics.hpp>
class Coin {
public:
    Coin(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f newPos);
    ~Coin();
    void Draw(sf::RenderWindow& window);

    sf::FloatRect getGlobalBounds() {
        return ects.getGlobalBounds();
    }

    
    void Update(float deltaTime);
    sf::RectangleShape ects;
private:
    
    Animation animation;
    bool faceRight;
    unsigned int row;
};




