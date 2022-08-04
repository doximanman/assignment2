//
// Created by kalo3 on 27-Jul-22.
//

#include "Point.hpp"

using namespace Geometry;
Point::Point(const vector<double>& coordinates):dimension((int)coordinates.size()),_coordinates(coordinates) {
}
Point::Point(const Point &other):dimension(other.dimension),_coordinates(other._coordinates) {
}
double Point::at(int position) const{
    return _coordinates.at(position);
}

ostream& operator<<(ostream &os, const Geometry::Point &a){
    os<<"(";
    for(int i=0;i<a.dimension-1;i++){
        os<<a.at(i)<<",";
    }
    return os<<a.at(a.dimension-1)<<") ";
}