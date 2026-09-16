//
// Created by kristof on 9/16/26.
//

#include "include/Coordinate.hpp"

#include <cmath>

Coordinate::Coordinate(const double x, const double y) : x_(x), y_(y) {};

double Coordinate::x() const { return x_; }
double Coordinate::y() const { return y_; }

double Coordinate::distance(const Coordinate& other) const {
    return std::sqrt(
        std::pow(std::abs(x_ - other.x()), 2)
        + std::pow(std::abs(y_ - other.y()), 2)
    );
}