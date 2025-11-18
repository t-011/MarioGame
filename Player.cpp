


#include "Player.h"

Player::Player(TextureManager& textureManager, float switchTime, float speed)
    : currTexture(pTexture::IDLE), body(textureManager.getTexture(currTexture)), animation(textureManager, switchTime),
        speed(speed), textureManager(textureManager), collider(body)
{
    body.setTextureRect(animation.rect);

    sf::FloatRect bounds = body.getLocalBounds();
    body.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
}

void Player::update(const float deltaTime) {
    sf::Vector2f movement{};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
        movement.x -= speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
        movement.x += speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) {
        movement.y -= speed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) {
        movement.y += speed * deltaTime;
    }

    if (movement.x == 0.f) {
        currTexture = pTexture::IDLE; // Idle animation
    }
    else {
        currTexture = pTexture::RUN;

        if (movement.x < 0.f) {
            body.setScale({-1.f, 1.f}); // faces opposite direction
        }
        else {
            body.setScale({1.f, 1.f});
        }
    }

    body.setTexture(textureManager.getTexture(currTexture));
    animation.update(currTexture, deltaTime);
    body.setTextureRect(animation.rect);

    sf::FloatRect bounds = body.getLocalBounds();
    body.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

    body.move(movement);
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(body);
}

void Player::setPosition(const sf::Vector2f position) {
    body.setPosition(position);
}

sf::Vector2f Player::getPosition() const {
    return body.getPosition();
}
