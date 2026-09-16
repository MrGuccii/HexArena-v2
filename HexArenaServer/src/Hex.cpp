//
// Created by kristof on 9/16/26.
//

#include "include/Hex.hpp"

Hex::Hex(const int q, const int r) : q_(q), r_(r) {};

int Hex::q() const { return q_; }
int Hex::r() const { return r_; }
int Hex::s() const { return -q_ - r_; }

int Hex::distance(const Hex& other) const {
    return std::abs(q_ - other.q())
         + std::abs(q_ + r_ - other.q() - other.r())
         + std::abs(r_ - other.r());
}
