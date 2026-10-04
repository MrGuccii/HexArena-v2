//
// Created by kristof on 9/15/26.
//

#ifndef HEXARENASERVER_PLAYER_HPP
#define HEXARENASERVER_PLAYER_HPP

#include <cstdint>

#define DEFAULT_SPEED 5

class Player {
public:
    Player(float x, float y);

    void move();

    void set_direction(float target_dx, float target_dy);
private:
    static uint32_t next_id;
    uint32_t id;
    int8_t speed;
    float x;
    float y;
    float dx;
    float dy;
};


#endif //HEXARENASERVER_PLAYER_HPP
