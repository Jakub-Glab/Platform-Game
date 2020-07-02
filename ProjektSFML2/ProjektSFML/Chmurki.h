#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
using namespace std;
class RuchomySprite :public sf::Sprite
{
public:
    RuchomySprite() :Sprite() {};
    virtual ~RuchomySprite() = default;
    virtual void Animuj(const sf::Time& elapsed) = 0;
    virtual void Animuj2(const sf::Time& elapsed) = 0;
};
class Duch : public RuchomySprite
{
private:

    sf::Texture texture;
    void AddTexture(const std::string& filename) {
        texture.loadFromFile(filename);
        this->setTexture(texture);
        int i = rand() % 2;
        if (i == 0)
        {
            vx = 50.0f;

        }
        else
        {
            vx = -50.0f;
        }
        vy = 0.0f;
    };

public:
    float vx;
    float vy;
    Duch(const std::string& filename) :RuchomySprite() { this->AddTexture(filename); };
    void Animuj(const sf::Time& elapsed) {
        this->move(vx * elapsed.asSeconds(), vy * elapsed.asSeconds());
        
        if (this->getGlobalBounds().left <= 0)
        {
            this->setPosition(3800.0f, this->getPosition().y);
        }
        if (this->getGlobalBounds().left + this->getGlobalBounds().width >= 3800)
        {
            this->setPosition(70.0f, this->getPosition().y);
            vx = 50.0f;
        }
    }
    void Animuj2(const sf::Time& elapsed) {
        vx = -50.0f;
        this->move(vx * elapsed.asSeconds(), vy * elapsed.asSeconds());

        srand(time(NULL));
        int x = rand() % 10 + 100;
        if (this->getPosition().x < -250)
        {
            this->setPosition(680.0f, x);
        }
       
    }
   




};

