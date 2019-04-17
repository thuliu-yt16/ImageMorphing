#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include "point.h"
#include "defs.h"
#include "image.h"
#include "triangle.h"
using namespace std;
namespace Triangulation{
    #define RED (Color(255,0,0))
    #define WHITE (Color(255,255,255))
    class Graph{
    public:
        Graph();
        ~Graph();
        vector<Point*> points;
        Image* image;
        int testCount;
        void removeEdge(Point* p1, Point* p2);
        void addEdge(Point* p1, Point* p2);
        void removePoint(Point* p);
        void addPoint(Point* p);
        Point* addPoint(double x, double y, int name);
        void DelaunayTriangulation();
        void triangulation(int l, int r);
        void setImage(Image* image);
        void drawLine(Point* p1, Point* p2, Color color);
        void getTriangles(vector<Triangle*>& triangles);
    };
}


#endif
