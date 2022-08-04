//
// Created by kalo3 on 27-Jul-22.
//

#ifndef ASS1_MANHATTANDISTANCE_HPP
#define ASS1_MANHATTANDISTANCE_HPP

#include "Distance.hpp"

namespace Geometry {
    class ManhattanDistance : public Distance {
    public:
        /**
        * Assumes p1 and p2 are of the same dimension.
        * @return Manhattan distance - sum of the absolute values of the differences between the points' coordinates.
        */
        double distance(Point p1, Point p2) override;
    };
}

#endif //ASS1_MANHATTANDISTANCE_HPP
