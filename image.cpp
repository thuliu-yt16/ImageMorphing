#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
namespace Triangulation{
    Image::Image(int _w, int _h):w(_w),h(_h){
        n = 3;
        pixel = new unsigned char[w * h * n];
        for(int i = 0; i < w * h * n; i ++){
            pixel[i] = 255;
        }
    }
    Image::Image(const char* fname){
        n = 3;
        pixel = stbi_load(fname, &w, &h, &n, 3);
    }
    void Image::save_png(const char* fname) const {
        stbi_write_png(fname, w, h, n, pixel, w * n);
    }
    void Image::drawPixel(int x, int y, Color color){
        pixel[n * (w * y + x)] = color.r;
        pixel[n * (w * y + x) + 1] = color.g;
        pixel[n * (w * y + x) + 2] = color.b;
    }
    // void Image::show(const char* fname) const{
    // }
    Color Image::getPixel(int x, int y) const{
        return Color(pixel[n * (w * y + x)], pixel[n * (w * y + x) + 1], pixel[n * (w * y + x) + 2]);
    }
    void Image::drawPixel(Point p, Color color){
        int x = p.x;
        int y = p.y;
        pixel[n * (w * y + x)] = (unsigned char)color.r;
        pixel[n * (w * y + x) + 1] = (unsigned char)color.g;
        pixel[n * (w * y + x) + 2] = (unsigned char)color.b;
    }
    Color Image::getPixel(Point p) const{
        int x = p.x;
        int y = p.y;
        return Color(pixel[n * (w * y + x)], pixel[n * (w * y + x) + 1], pixel[n * (w * y + x) + 2]);
    }
    void Image::drawLine(double x0, double y0, double x1, double y1, Color color){
        line(x0, y0, x1, y1, color);
    }
    void Image::drawLine(Point* a, Point* b, Color color){
        line(a -> x, a -> y, b -> x, b -> y, color);
    }
    void Image::line(int x0, int y0,int x1,int y1,Color color){
        bool swaped = false;
        if(abs(x1 - x0) < abs(y1 - y0)){
            swap(y0,x0);
            swap(y1,x1);
            swaped = true;
        }
        if(x0 > x1){
            swap(x0,x1);
            swap(y0,y1);
        }
        int x,y,dx,dy,e;
        dx = x1 - x0,dy = y1 - y0,e = -dx;
        x = x0,y = y0;
        for(int i=0;i<=dx;i++){
            swaped ? drawPixel(y,x,color) : drawPixel(x,y,color);
            x ++;
            e += 2 * abs(dy);
            if(e >= 0){
                dy >= 0 ? y ++ : y --;
                e -= 2 * dx;
            }
        }
    }
}