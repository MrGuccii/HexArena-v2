//
// Created by kristof on 9/15/26.
//

#include "include/Player.hpp"

Player::Player(const float x, const float y) : id(next_id++), speed(DEFAULT_SPEED), x(x), y(y), dx(0), dy(0) {}

void Player::move() {
    this->x += this->dx * static_cast<float>(this->speed);
    this->y += this->dy * static_cast<float>(this->speed);
}

void Player::set_direction(const float target_dx, const float target_dy) {
    if (target_dx < 0) this->dx = 0;
    if (target_dx > 1) this->dx = 1;
    if (target_dy < 0) this->dy = 0;
    if (target_dy > 1) this->dy = 1;
}
