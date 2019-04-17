#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include "point.h"
#include "graph.h"
#include "image.h"
#include "triangle.h"
using namespace std;
using namespace Triangulation;
void readMark(const char* fname, Graph* g){
    ifstream fp(fname);
    string name;
    int x, y;
    for(int i = 0; i < FEATURE_POINTS; i ++){
        fp >> name >> y >> x;
        g -> addPoint(x, y, i);
    }
    assert(g -> points.size() == FEATURE_POINTS);
}
void test(){
    Graph* sourceMark = new Graph();
    readMark("source1_unique.txt", sourceMark);
    // Graph* t = new Graph();
    // int height = 270;
    // t -> addPoint(50,0);
    // t -> addPoint(0,50);
    // t -> addPoint(51,98);
    // t -> addPoint(51,152);
    // t -> addPoint(100,49);
    // t -> addPoint(151,150);
    // t -> addPoint(201,99);
    // t -> addPoint(249,0);
    // t -> addPoint(260,50);
    // t -> addPoint(250,150);
    // t -> setImage(board);
    // t -> DelaunayTriangulation();
    Image* source = new Image("source1.png");
    int w = source -> w;
    int h = source -> h;
    sourceMark -> addPoint(0, 0, FEATURE_POINTS);
    sourceMark -> addPoint(w - 1, 0, FEATURE_POINTS + 1);
    sourceMark -> addPoint(0, h - 1, FEATURE_POINTS + 2);
    sourceMark -> addPoint(w - 1, h - 1, FEATURE_POINTS + 3);
    Image* board = new Image(w, h);
    sourceMark -> setImage(board);
    sourceMark -> DelaunayTriangulation();
}
int main(){
    srand(unsigned(time(NULL)));
    Graph* sourceMark = new Graph();
    Graph* targetMark = new Graph();
    Graph* midMark = new Graph();
    readMark("source2_unique.txt", sourceMark);
    readMark("target2_unique.txt", targetMark);
    Image* source = new Image("source2.png");
    Image* target = new Image("target2.png");
    int w = source -> w;
    int h = source -> h;
    sourceMark -> addPoint(0, 0, FEATURE_POINTS);
    sourceMark -> addPoint(w - 1, 0, FEATURE_POINTS + 1);
    sourceMark -> addPoint(0, h - 1, FEATURE_POINTS + 2);
    sourceMark -> addPoint(w - 1, h - 1, FEATURE_POINTS + 3);
    targetMark -> addPoint(0, 0, FEATURE_POINTS);
    targetMark -> addPoint(w - 1, 0, FEATURE_POINTS + 1);
    targetMark -> addPoint(0, h - 1, FEATURE_POINTS + 2);
    targetMark -> addPoint(w - 1, h - 1, FEATURE_POINTS + 3);

    double rate = 0.6;
    for(int i = 0; i < POINT_SET_SIZE; i ++){
        Point* p1 = sourceMark -> points[i];
        Point* p2 = targetMark -> points[i];
        Point* p = new Point(p1 -> x * rate + (1 - rate) * p2 -> x, p1 -> y * rate + (1 - rate) * p2 -> y, i);
        midMark -> addPoint(p);
    }
    printf("Triangulation...\n");
    Image* board = new Image(w, h);
    midMark -> setImage(board);
    midMark -> DelaunayTriangulation();

    vector<Triangle*> triangles, sourceTriangles, targetTriangles;
    printf("Getting Triangles...\n");
    midMark -> getTriangles(triangles);
    sourceTriangles.clear();
    targetTriangles.clear();
    printf("Triangles: %d\n", triangles.size());
    for(Triangle* t: triangles){
        int ia = t -> a -> name;
        int ib = t -> b -> name;
        int ic = t -> c -> name;
        sourceTriangles.push_back(new Triangle(sourceMark -> points[ia], sourceMark -> points[ib], sourceMark -> points[ic]));
        targetTriangles.push_back(new Triangle(targetMark -> points[ia], targetMark -> points[ib], targetMark -> points[ic]));
    }
    Image* mid = new Image(w, h);
    Point p(0, 0, 0);
    Point temp(0, 0, 0);
    Vector3 weight;
    int tris = triangles.size();
    printf("Drawing...\n");
    for(int i = 0; i < w; i ++){
        for(int j = 0; j < h; j ++){
            p.x = i;p.y = j;
            for(int k = 0; k < tris; k ++){
                if(triangles[k] -> contains(&p, weight)){
                    sourceTriangles[k] -> getCoordinate(weight, &temp);
                    Color sc = source -> getPixel(temp);
                    targetTriangles[k] -> getCoordinate(weight, &temp);
                    Color tc = target -> getPixel(temp);
                    mid -> drawPixel(i, j, rate * sc + (1 - rate) * tc);
                    break;
                }
            }
        }
    }
    mid -> save_png("morph2.png");
    printf("Done\n");

    // Image* source = new Image("target2.png");
    // int w = source -> w;
    // int h = source -> h;

    // Graph* sourceMark = new Graph();
    // readMark("target2_unique.txt", sourceMark);
    // sourceMark -> addPoint(0, 0, FEATURE_POINTS);
    // sourceMark -> addPoint(w - 1, 0, FEATURE_POINTS + 1);
    // sourceMark -> addPoint(0, h - 1, FEATURE_POINTS + 2);
    // sourceMark -> addPoint(w - 1, h - 1, FEATURE_POINTS + 3);

    // for(int i = 0; i < POINT_SET_SIZE; i ++){
    //     source -> drawPixel(*(sourceMark -> points[i]), Color(255,0,0));
    // }
    // source -> save_png("target2_mark.png");

    return 0;
}
