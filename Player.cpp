


#include "Player.h"

#include <cmath>

#include "Collider.h"

Player::Player(TextureManager& textureManager, float switchTime, float speed, float jumpHeight)
    : currTexture(pTexture::IDLE), body(textureManager.getTexture(currTexture)), animation(textureManager, switchTime),
        speed(speed), textureManager(textureManager), collider(body), jumpHeight(jumpHeight)
{
    body.setTextureRect(animation.rect);

    sf::FloatRect bounds = body.getLocalBounds();
    body.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
}

void Player::update(const float deltaTime) {

    velocity.x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
        velocity.x -= speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
        velocity.x += speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) && canJump
            && (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A) || true)) {
        canJump = false;

        velocity.y = -sqrtf(2.0f * 981.f * jumpHeight);
    }



    velocity.y += 981.f * deltaTime;

    if (velocity.x == 0.f) {
        currTexture = pTexture::IDLE; // Idle animation
    }
    else {
        currTexture = pTexture::RUN;

        if (velocity.x < 0.f) {
            body.setScale({-1.f, 1.f}); // faces opposite direction
        }
        else {
            body.setScale({1.f, 1.f});
        }
    }

    body.setTexture(textureManager.getTexture(currTexture));
    animation.update(currTexture, deltaTime);
    body.setTextureRect(animation.rect);

    // sf::FloatRect bounds = body.getLocalBounds();
    // body.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});

    body.move(velocity * deltaTime);
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(body);
}

void Player::onCollision(Collider::CollisionResult& cr) {

    if (cr.normal.x < 0.f) {
        // collision on left
        velocity.x = 0.0;
    }
    else if (cr.normal.x > 0.f) {
        // collision on right
        velocity.x = 0.0;
    }
    if (cr.normal.y < 0.f) {
        // collision on bottom
        canJump = true;
        velocity.y = 0.0;
    }
    else if (cr.normal.y > 0.f) {
        // collision on top
        velocity.y = 0.0;
    }

}

void Player::setPosition(const sf::Vector2f position) {
    body.setPosition(position);
}

sf::Vector2f Player::getPosition() const {
    return body.getPosition();
}
