


#include "Player.h"

#include <cmath>

#include "Collider.h"

Player::Player(TextureManager& textureManager, float switchTime, float speed, float jumpHeight)
    : currTexture(pTexture::IDLE), body(textureManager.getTexture(currTexture)), animation(textureManager, switchTime),
        speed(speed), textureManager(textureManager), collider(body, Collider::CollidingObject::PLAYER), jumpHeight(jumpHeight)
{
    body.setTextureRect(animation.rect);

    sf::FloatRect bounds = body.getLocalBounds();
    body.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
}

void Player::update(const float deltaTime) {

    constexpr float GRAVITY = 981.f;
    velocity.x = 0.f; // needed

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
        velocity.x -= speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
        velocity.x += speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) && canJump) {
        canJump = false;

        velocity.y = -sqrtf(2.0f * GRAVITY * jumpHeight);
    }



    velocity.y += GRAVITY * deltaTime;

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
        if (cr.object == Collider::CollidingObject::TILE) {
            // collision on left
            velocity.x = 0.0;
        }
        else if (cr.object == Collider::CollidingObject::ENEMY) {
            isDead = true;
        }
    }
    // collision on right
    else if (cr.normal.x > 0.f) {
        if (cr.object == Collider::CollidingObject::TILE) {
            velocity.x = 0.0;
        }
        else if (cr.object == Collider::CollidingObject::ENEMY) {
            velocity.x = 0.0;
            isDead = true;
        }
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
