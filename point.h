#ifndef POINT_H
#define POINT_H
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include "point.h"
#include "defs.h"
#include <cassert>
#include <iostream>
using namespace std;
namespace Triangulation{
    class Point{
    public:
        double x;
        double y;
        double cosAngle;
        bool isAbove;
        int name;
        vector<Point*> nb;
        Point(double x, double y, int name);
        void disturb();
        void add(Point* p);
        bool del(Point* p);
        bool connect(Point* p);
        ~Point();
        bool belowLine(Point* a, Point* b);
        void getAngle(Point* a, Point* b, bool right);
        bool inCircumscribedCircle(Point* a, Point* b, Point* c);
        void print();
    };
    bool clockwise(Point* a, Point* b);
    bool pointCompare(Point* a, Point* b);
    double sqrDistance(Point* a, Point* b);
}
#endif
