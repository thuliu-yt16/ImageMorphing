#include "graph.h"
#include <cassert>
namespace Triangulation{
    Graph::Graph(){
        points.clear();
        image = NULL;
        testCount = 0;
    }
    void Graph::setImage(Image* image){
        this -> image = image;
    }
    void Graph::removeEdge(Point* p1, Point* p2){
        assert(p1 != p2);
        assert(p1 -> del(p2));
        assert(p2 -> del(p1));
    }
    void Graph::addEdge(Point* p1, Point* p2){
        assert(p1 != p2);
        p1 -> add(p2);
        p2 -> add(p1);
    }
    void Graph::removePoint(Point* p){
        assert(p -> nb.size() == 0);
        for(vector<Point*>::iterator it = points.begin(); it != points.end(); it ++){
            if(*it == p){
                points.erase(it);
                return;
            }
        }
        delete p;
    }
    void Graph::addPoint(Point* p){
        p -> disturb();
        points.push_back(p);
    }
    Point* Graph::addPoint(double x, double y, int name){
        Point* p = new Point(x, y, name);
        p -> disturb();
        points.push_back(p);
        return p;
    }
    Graph::~Graph(){
        for(Point* p: points){
            delete p;
        }
        points.clear();
        vector<Point*>().swap(points);
    }
    void Graph::DelaunayTriangulation(){
        sort(points.begin(), points.end(), pointCompare);
        cout << points.size() << endl;
        for(vector<Point*>::iterator it = points.begin(); it + 1 != points.end(); it++){
            Point* p1 = *it;
            Point* p2 = *(it + 1);
            assert(p1 -> x != p2 -> x || p1 -> y != p2 -> y);
        }
        triangulation(0, points.size());
    }
    void Graph::triangulation(int l, int r){
        printf("divide: [%d, %d)\n", l, r);
        if(l + 1>= r) return;
        if(l + 2 == r){
            Point* p1 = points[l];
            Point* p2 = points[l + 1];
            drawLine(p1, p2, RED);
            addEdge(p1, p2);
            return;
        }
        if(l + 3 == r){
            Point* p1 = points[l];
            Point* p2 = points[l + 1];
            Point* p3 = points[l + 2];
            drawLine(p1, p2, RED);
            drawLine(p1, p3, RED);
            drawLine(p2, p3, RED);
            addEdge(p1, p2);
            addEdge(p2, p3);
            addEdge(p1, p3);
            return;
        }
        int m = (l + r) >> 1;
        triangulation(l, m); // l ~ m - 1
        triangulation(m, r); // m ~ r - 1
        // for(int i = l; i < r; i ++){
        //     points[i] -> print();
        // }
        vector<pair<Point*, Point*> > edges;
        edges.clear();
        // find base
        Point* base_l = points[m - 1];
        Point* base_r = points[m];
        while(true){
            bool base = true;
            for(Point* nb_l : base_l -> nb){
                if(nb_l -> belowLine(base_l, base_r)){
                    base = false;
                    base_l = nb_l;
                    break;
                }
            }
            if(!base) continue;
            for(Point* nb_r : base_r -> nb){
                if(nb_r -> belowLine(base_l, base_r)){
                    base = false;
                    base_r = nb_r;
                    break;
                }
            }
            if(base) break;
        }
        drawLine(base_l, base_r, RED);
        edges.push_back(make_pair(base_l, base_r));
        // expand to top
        // int cnt = 0;
        while(true){
            // cnt ++;
            bool top = true;
            for(Point* nb_l : base_l -> nb){
                if(!(nb_l -> belowLine(base_l, base_r))){
                    top = false;
                    break;
                }
            }
            for(Point* nb_r:base_r -> nb){
                if(!(nb_r -> belowLine(base_l, base_r))){
                    top = false;
                    break;
                }
            }

            // printf("left : ");base_l -> print();
            // printf("right: ");base_r -> print();
            if(top) break;
            // printf("%d: top: ", cnt);
            // cout << top << endl;
            for(Point* nb_l: base_l -> nb){
                nb_l -> getAngle(base_l, base_r, false); 
            }
            sort(base_l -> nb.begin(), base_l -> nb.end(), clockwise);
            for(Point* nb_r: base_r -> nb){
                nb_r -> getAngle(base_l, base_r, true); 
            }
            sort(base_r -> nb.begin(), base_r -> nb.end(), clockwise);
            // printf("left clock: \n");
            // for(Point* nb_l: base_l -> nb){
            //     nb_l -> print();
            //     printf("cos: %.4f\n", nb_l -> cosAngle);
            //     cout << nb_l -> isAbove << endl;
            // }
            // printf("right clock: \n");
            // for(Point* nb_r: base_r -> nb){
            //     nb_r -> print();
            //     printf("cos: %.4f\n", nb_r -> cosAngle);
            //     cout << nb_r -> isAbove << endl;
            // }
            Point* choice_l = NULL;
            Point* choice_r = NULL;
            for(vector<Point*>::iterator it = base_l -> nb.begin(); it != base_l -> nb.end();){
                Point* potential = *it;
                bool above = potential -> isAbove;
                if(!above) break;
                if(it + 1 == base_l -> nb.end()){
                    choice_l = potential; 
                    break;
                }
                Point* next_potential = *(it + 1);
                if(!(next_potential -> inCircumscribedCircle(base_l, base_r, potential))){
                    choice_l = potential;
                    break;
                }
                drawLine(potential, base_l, WHITE);
                potential -> del(base_l);
                it = base_l -> nb.erase(it);
            }
            for(vector<Point*>::iterator it = base_r -> nb.begin(); it != base_r -> nb.end();){
                Point* potential = *it;
                bool above = potential -> isAbove;
                if(!above) break;
                if(it + 1 == base_r -> nb.end()){
                    choice_r = potential; 
                    break;
                }
                Point* next_potential = *(it + 1);
                if(!(next_potential -> inCircumscribedCircle(base_l, base_r, potential))){
                    choice_r = potential;
                    break;
                }
                drawLine(potential, base_r, WHITE);
                potential -> del(base_r);
                it = base_r -> nb.erase(it);
            }
            assert(choice_l != NULL || choice_r != NULL);
            if(choice_l == NULL){
                edges.push_back(make_pair(base_l, choice_r));
                drawLine(base_l, choice_r, RED);
                base_r = choice_r;
            }
            else if(choice_r == NULL){
                edges.push_back(make_pair(base_r, choice_l));
                drawLine(base_r, choice_l, RED);
                base_l = choice_l;
            }
            else{
                if(choice_l -> inCircumscribedCircle(base_l, base_r, choice_r)){
                    edges.push_back(make_pair(base_r, choice_l));
                    drawLine(base_r, choice_l, RED);
                    base_l = choice_l;
                }
                else{
                    edges.push_back(make_pair(base_l, choice_r));
                    drawLine(base_l, choice_r, RED);
                    base_r = choice_r;
                }
            }
        }
        for(pair<Point*, Point*> e: edges){
            addEdge(e.first, e.second);
        }
        edges.clear();
        vector<pair<Point*, Point*> >().swap(edges);
    }
    void Graph::drawLine(Point* p1, Point* p2, Color color){
        return;
        // if(image){
        //     testCount += 1;
        //     image -> drawLine(p1, p2, color);
        //     string s1 = "test";
        //     s1 += to_string(testCount);
        //     s1 += ".png";
        //     image -> save_png(s1.c_str());
        // }
    }
    void Graph::getTriangles(vector<Triangle*>& triangles){
        triangles.clear();
        int psize = points.size();
        for(int i = 0; i < psize; i ++){
            Point* p0 = points[i];
            for(int j = i + 1; j < psize; j ++){
                Point* p1 = points[j];
                if(p0 -> connect(p1)){
                    for(int k = j + 1; k < psize; k ++){
                        Point* p2 = points[k];
                        if(p1 -> connect(p2) && p2 -> connect(p0)){
                            triangles.push_back(new Triangle(p0, p1, p2));
                        }
                    }
                }
            }
        }
    }
}