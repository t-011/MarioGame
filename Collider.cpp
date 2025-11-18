//
// Created by tariq on 11/18/2025.
//

#include "Collider.h"

#include <algorithm>
#include <iostream>
#include <utility>

Collider::Collider(sf::Sprite& sprite)
    : body(sprite)
{}

/*
 * Caller pushes other by push value (0 to 1) if collision detected.
 * 0 = max push.
 * 1 = no push.
 */
bool Collider::resolveCollision(Collider& other, float push) {
    sf::FloatRect bounds = body.getGlobalBounds();
    sf::FloatRect otherBounds = other.body.getGlobalBounds();

    if (!bounds.findIntersection(otherBounds)) {
        return false;
    }

    float overlapX = std::min(bounds.position.x + bounds.size.x, otherBounds.position.x + otherBounds.size.x)
                   - std::max(bounds.position.x, otherBounds.position.x);
    float overlapY = std::min(bounds.position.y + bounds.size.y, otherBounds.position.y + otherBounds.size.y)
                   - std::max(bounds.position.y, otherBounds.position.y);

    if (overlapX < overlapY) {
        float moveX = (bounds.position.x < otherBounds.position.x ? -overlapX : overlapX);
        body.move({moveX * push, 0.f});
        other.body.move({-moveX * (1.f - push), 0.f});
    } else {
        float moveY = (bounds.position.y < otherBounds.position.y ? -overlapY : overlapY);
        body.move({0.f, moveY * push});
        other.body.move({0.f, -moveY * (1.f - push)});
    }

    return true;
}





