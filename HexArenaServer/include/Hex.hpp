//
// Created by kristof on 9/16/26.
//

#ifndef HEXARENASERVER_HEX_HPP
#define HEXARENASERVER_HEX_HPP
#include <cmath>

// Axial hexagonal coordinate system
class Hex {
public:
    Hex(int q, int r);

    [[nodiscard]] int s() const;
    [[nodiscard]] int q() const;
    [[nodiscard]] int r() const;

    [[nodiscard]] int distance(const Hex& other) const;

private:
    int q_;
    int r_;
};

#endif //HEXARENASERVER_HEX_HPP
