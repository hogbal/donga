#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

ifstream inp("rectangle.inp");
ofstream out("rectangle.out");

int N;

typedef struct {
    long long x;
    long long y;
}Point;

typedef struct {
    long long x;
    long long y;
    long long len;
    int point1;
    int point2;
}Point_Center;

bool cmp(const Point_Center &p1, const Point_Center &p2) {
    if(p1.len != p2.len) return p1.len < p2.len;
    if(p1.x != p2.x) return p1.x < p2.x;
    return p1.y < p2.y;
}

void rectangle(){
    Point *p = new Point[N];
    Point_Center *pc = new Point_Center[N*N];
    
    for(int i=0;i<N;i++) {
        inp >> p[i].x >> p[i].y;
    }
    
    int index = 0;
    for(int i=0;i<N;i++) {
        for(int j=i+1;j<N;j++) {
            pc[index].x = p[i].x+p[j].x;
            pc[index].y = p[i].y+p[j].y;
            pc[index].len = pow(p[j].x-p[i].x,2)+pow(p[j].y-p[i].y,2);
            pc[index].point1 = i; pc[index].point2 = j;
            index++;
        }
    }
    
    sort(pc,pc+index,cmp);
    
    long long area = 0;
    for(int i=0;i<index;i++) {
        int j=i+1;
        while(pc[i].x==pc[j].x&&pc[i].y==pc[j].y&&pc[i].len==pc[j].len){
            int index1 = pc[i].point1;
            int index2 = pc[i].point2;
            int index3 = pc[j].point1;
            int index4 = pc[j].point2;
            long long cmp_area = abs(p[index1].x*(p[index2].y-p[index3].y)+p[index2].x*(p[index3].y-p[index1].y)+p[index3].x*(p[index1].y-p[index2].y))+ abs(p[index1].x*(p[index2].y-p[index4].y)+p[index2].x*(p[index4].y-p[index1].y)+p[index4].x*(p[index1].y-p[index2].y));
            
            if(area < cmp_area) {
                area = cmp_area;
            }
            j++;
        }
        /*
        for(int j=i+1;j<index;j++) {
            if(pc[i].x==pc[j].x&&pc[i].y==pc[j].y&&pc[i].len==pc[j].len) {
                int index1 = pc[i].point1;
                int index2 = pc[i].point2;
                int index3 = pc[j].point1;
                int index4 = pc[j].point2;
                double cmp_area = abs(p[index1].x*(p[index2].y-p[index3].y)+p[index2].x*(p[index3].y-p[index1].y)+p[index3].x*(p[index1].y-p[index2].y))+ abs(p[index1].x*(p[index2].y-p[index4].y)+p[index2].x*(p[index4].y-p[index1].y)+p[index4].x*(p[index1].y-p[index2].y));
                
                if(area < cmp_area) {
                    area = cmp_area;
                }
            }
         */
    }
    out << area/2 << endl;
}

int main(void) {
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++) {
        inp >> N;
        rectangle();
    }
}
