//
// Created by kristof on 9/16/26.
//

#ifndef HEXARENASERVER_COORDINATE_HPP
#define HEXARENASERVER_COORDINATE_HPP

class Coordinate {
public:
    Coordinate(double x, double y);

    [[nodiscard]] double x() const;
    [[nodiscard]] double y() const;

    [[nodiscard]] double distance(const Coordinate& other) const;

private:
    double x_;
    double y_;
};

#endif //HEXARENASERVER_COORDINATE_HPP
