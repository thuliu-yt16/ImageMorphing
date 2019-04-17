#include "point.h"
namespace Triangulation{
    Point::Point(double x, double y, int name):x(x), y(y), name(name){
        nb.clear();
        cosAngle = 0;
    }
    void Point::add(Point* p){
        nb.push_back(p);
    }
    bool Point::del(Point* p){
        for(vector<Point*>::iterator it = nb.begin(); it != nb.end(); it++){
            if(*it == p){
                nb.erase(it);
                return true;
            }
        }
        return false;
    }
    void Point::disturb(){
        double N = 1;
        x += -N / 2 + RAND(N);
        y += -N / 2 + RAND(N);
    }
    Point::~Point(){ nb.clear(); vector<Point*>().swap(nb); }
    bool Point::belowLine(Point* a, Point* b){
        assert(this != a && this != b);
        assert(a -> x <= b -> x);
        // if(a -> x > b -> x) swap(a, b);
        double v1x = b -> x - a -> x;
        double v1y = b -> y - a -> y;
        double v2x = b -> x - x;
        double v2y = b -> y - y;
        double cross = v1x * v2y - v1y * v2x;
        return cross > 0;
    }
    void Point::getAngle(Point* a, Point* b, bool right){
        // calculate cos of this-a-b angle
        isAbove = !belowLine(a, b);
        if(right)
            swap(a, b);
        double a2 = sqrDistance(this, a);
        double b2 = sqrDistance(a, b);
        double c2 = sqrDistance(this, b);
        cosAngle = (a2 + b2 - c2) / 2 / sqrt(a2 * b2);
        assert(cosAngle != -1 && cosAngle != 1);
    }
    bool Point::inCircumscribedCircle(Point* a, Point* b, Point* c){
        double x1 = a -> x;
        double y1 = a -> y;
        double x2 = b -> x;
        double y2 = b -> y;
        double x3 = c -> x;
        double y3 = c -> y;
        double la = sqrt(sqrDistance(c, b));
        double lb = sqrt(sqrDistance(a, c));
        double lc = sqrt(sqrDistance(a, b));
        double p = (la + lb + lc) * 0.5;
        double S = sqrt(p * (p - la) * (p - lb) * (p - lc));
        double r = la * lb * lc / 4 / S;
        double t1 = x1 * x1 + y1 * y1;
        double t2 = x2 * x2 + y2 * y2;
        double t3 = x3 * x3 + y3 * y3;
        double temp = x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2;
        if(temp == 0) return true;
        double ox = (t2 * y3 + t1 * y2 + t3 * y1 - t2 * y1 - t3 * y2 - t1 * y3) / temp / 2;
        double oy = (t3 * x2 + t2 * x1 + t1 * x3 - t1 * x2 - t2 * x3 - t3 * x1) / temp / 2;
        double dis2 = (x - ox) * (x - ox) + (y - oy) * (y - oy) - r * r;
        return dis2 < 0;
    }
    void Point::print(){
        printf("Point: (%.1f, %.1f)\n", x, y);
    }

    bool pointCompare(Point* a, Point* b){
        if(a -> x < b -> x)
            return true;
        if(a -> x > b -> x)
            return false;
        if(a -> y < b -> y)
            return true;
        if(a -> y > b -> y)
            return false;
        return true;
    }
    bool clockwise(Point* a, Point* b){
        if(a -> isAbove && b -> isAbove){
            return a -> cosAngle > b -> cosAngle;
        }
        if(a -> isAbove && !(b -> isAbove)){
            return true;
        }
        if(!(a -> isAbove) && b -> isAbove){
            return false;
        }
        if(!(a -> isAbove) && !(b -> isAbove)){
            return a -> cosAngle < b -> cosAngle;
        }
    }
    double sqrDistance(Point* a, Point* b){
        double dx = a -> x - b -> x;
        double dy = a -> y - b -> y;
        return dx * dx + dy * dy;
    }
    bool Point::connect(Point* p){
        for(Point* b: nb){
            if(b == p) return true;
        }
        return false;
    }
}
