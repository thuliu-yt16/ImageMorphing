#include "triangle.h"
Triangle::Triangle(Point* a, Point* b, Point* c):a(a), b(b), c(c){
    xa = a -> x;
    xb = b -> x;
    xc = c -> x;
    ya = a -> y;
    yb = b -> y;
    yc = c -> y;
    S2 = xa * (yb - yc) + ya * (xc - xb) + xb * yc - yb * xc;
}

bool Triangle::contains(Point* p, Vector3& weight){
    weight = gravityCoordinate(p);
    return weight.x > 0 && weight.y > 0 && weight.z > 0;
}
Vector3 Triangle::gravityCoordinate(Point* p){
    double xp = p -> x;
    double yp = p -> y;
    double PBC = xp * (yb - yc) + yp * (xc - xb) + xb * yc - yb * xc;
    double PCA = xp * (yc - ya) + yp * (xa - xc) + xc * ya - yc * xa;
    // double PAB = xp * (ya - yb) + yp * (xb - xa) + xa * yb - ya * xb;
    double u = PBC / S2;
    double v = PCA / S2;
    double w = 1 - u - v;
    return Vector3(u, v, w);
}
void Triangle::getCoordinate(const Vector3& weight, Point* p){
    p -> x = weight.Dot(Vector3(xa, xb, xc));
    p -> y = weight.Dot(Vector3(ya, yb, yc));
}