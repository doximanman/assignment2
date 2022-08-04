//
// Created by kalo3 on 27-Jul-22.
//

#ifndef ASS1_POINT_HPP
#define ASS1_POINT_HPP

#include <ostream>
#include "vector"
using namespace std;
namespace Geometry {
    /**
     * General, any dimensional spacial point - holds a set of coordinates and can provide
     * any of them at will.
     */
    class Point {
    private:
        /**
         * vector of doubles instead of *double,
         * easier to work with and manage.
         */
        vector<double> _coordinates;
    public:
        /**
         * the dimension of the point (number of coordinates).
         */
        const int dimension;
        /**
         * normal constructor
         * @param coordinates given coordinates
         */
        explicit Point(const vector<double>& coordinates);
        /**
         * move constructor
         * @param other
         */
        Point(Point&& other);
        /**
         * copy constructor
         * @param other point to copy from.
         */
        Point(const Point& other);
        Point operator=(const Point& other);
        Point operator=(Point&& other);
        ~Point();
        /**
         * @param position
         * @return the position-th coordinate of the point.
         */
        double at(int position) const;
    };
}
/**
 * @return prints the point in the form (x1,x2,...,xn)
 */
ostream& operator<<(ostream &os, const Geometry::Point &a);
#endif //ASS1_POINT_HPP
