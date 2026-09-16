//
// Created by kristof on 9/15/26.
//

#ifndef HEXARENASERVER_PLAYER_HPP
#define HEXARENASERVER_PLAYER_HPP

#include <cstdint>

class Player {
public:
    Player(float x, float y);

    void move();

    void updateDirectionVector(float target_dx, float target_dy);
private:
    static uint32_t next_id;
    uint32_t id;
    float x;
    float y;
    float dx;
    float dy;
};


#endif //HEXARENASERVER_PLAYER_HPP
