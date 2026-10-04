//
// Created by kristof on 9/16/26.
//

#include "include/Hex.hpp"

Hex::Hex(const int q, const int r) : q_(q), r_(r) {};

[[nodiscard]] int Hex::q() const { return q_; }
[[nodiscard]] int Hex::r() const { return r_; }
[[nodiscard]] int Hex::s() const { return -q_ - r_; }

[[nodiscard]] int Hex::distance(const Hex& other) const {
    return std::abs(q_ - other.q())
         + std::abs(q_ + r_ - other.q() - other.r())
         + std::abs(r_ - other.r());
}

bool Hex::operator==(const Hex& other) const {
    return q_ == other.q_ && r_ == other.r_;
}
