//
// Created by kristof on 9/16/26.
//

#include "include/Coordinate.hpp"

#include <cmath>

Coordinate::Coordinate(const double x, const double y) : x_(x), y_(y) {};

[[nodiscard]] double Coordinate::x() const { return x_; }
[[nodiscard]] double Coordinate::y() const { return y_; }

[[nodiscard]] double Coordinate::distance(const Coordinate& other) const noexcept(true) {
    return std::hypot(x_ - other.x(), y_ - other.y());
}

[[nodiscard]] bool Coordinate::operator==(const Coordinate &other) const {
    return x_ == other.x_ && y_ == other.y_;
}
