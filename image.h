#ifndef IMAGE_H
#define IMAGE_H
#include "vector3.h"
#include "point.h"
#include "triangle.h"
namespace Triangulation{
    class Image{
    public:
        int w;
        int h;
        int n;
        unsigned char* pixel;
        Image(int _w, int _h);
        Image(const char* fname);
        void save_png(const char* fname) const ;
        void drawPixel(int x,int y,Color color);
        void drawPixel(Point p, Color color);
        // void show(const char* fname) const;
        Color getPixel(int x,int y) const;
        Color getPixel(Point p) const;
        ~Image();
        void drawLine(double x0, double y0, double x1, double y1, Color color);
        void drawLine(Point* a, Point* b, Color color);
    private:
        void line(int x0, int y0, int x1, int y1, Color color);
    };
}
#endif