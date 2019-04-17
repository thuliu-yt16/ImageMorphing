#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include "defs.h"
#include "vector3.h"
using namespace Triangulation;
class Triangle{
    public:
        Point *a, *b, *c;
        double xa,xb,xc,ya,yb,yc;
        double S2;
        Triangle(Point* a, Point* b, Point* c);
        bool contains(Point* p, Vector3& weight);
        Vector3 gravityCoordinate(Point* p);
        void getCoordinate(const Vector3& weight, Point* p);
};
#endif