//
// Created by kalo3 on 27-Jul-22.
//

#ifndef ASS1_DISTANCE_HPP
#define ASS1_DISTANCE_HPP

#include "Point.hpp"

namespace Geometry {
    /**
     * Abstract class that requires has a distance function between
     * two points.
     */
    class Distance {
    public:
        /**
         * Assumes p1 and p2 are of the same dimension.
         * @return The distance between the points.
         */
        virtual double distance(Point p1,Point p2)=0;
    };
}
#endif //ASS1_DISTANCE_HPP
