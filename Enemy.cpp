//
// Created by tariq on 11/20/2025.
//

#include "Enemy.h"

Enemy::Enemy(TextureManager &textureManager, float speed)
    : body(textureManager.getTexture(pTexture::ENEMY)), speed(speed), collider(body, Collider::CollidingObject::ENEMY)
{
    body.setScale({.04f, .04f});

    sf::FloatRect bounds = body.getLocalBounds();
    body.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
}

void Enemy::update(float deltaTime) {

    constexpr float GRAVITY = 981.f;
    velocity.x = 0.f;

    if (direction == FACE_RIGHT) {
        velocity.x += speed;
    }
    else {
        velocity.x -= speed;
    }
    velocity.y += GRAVITY * deltaTime;

    body.move(velocity * deltaTime);
}

void Enemy::draw(sf::RenderWindow &window) const {
    window.draw(body);
}

void Enemy::onCollision(Collider::CollisionResult &cr) {

    if (cr.normal.x < 0.0f) {
        direction = FACE_LEFT;
        velocity.x = 0.0f;
    }
    else if (cr.normal.x > 0.0f) {
        direction = FACE_RIGHT;
        velocity.x = 0.0f;
    }
    if (cr.normal.y > 0.0f && cr.object == Collider::CollidingObject::PLAYER) {
        isDead = true;
    }
    velocity.y = 0.0f;

}

void Enemy::setPosition(sf::Vector2f position) {
    body.setPosition(position);
}




