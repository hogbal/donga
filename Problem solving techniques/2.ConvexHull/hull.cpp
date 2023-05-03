#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream inp("hull.inp");
ofstream out("hull.out");

typedef struct point
{
    int x;
    int y;
} point;

vector<point> p;
vector<point> hull;
int n;

int ccw2(point p, point q)
{
    return p.x * q.y - p.y * q.x;
}

int ccw(point r, point p, point q)
{
    p.x -= r.x;
    q.x -= r.x;
    p.y -= r.y;
    q.y -= r.y;
    return ccw2(p, q);
}

bool cmp(point a, point b)
{
    if (a.x == hull[0].x && a.y == hull[0].y)
        return true;
    if (b.x == hull[0].x && b.y == hull[0].y)
        return false;
    int res = ccw(hull[0], a, b);
    if (res > 0)
        return true;
    if (res < 0)
        return false;
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

void ConvexHull()
{
    int leftmost = 0;
    int result_idx = 0;
    for (int i = 1; i < n; i++)
    {
        if (p[i].x < p[result_idx].x || (p[i].x == p[result_idx].x && p[i].y < p[result_idx].y))
        {
            result_idx = i;
        }
        if (p[i].y < p[leftmost].y || (p[i].y == p[leftmost].y && p[i].x < p[leftmost].x))
        {
            leftmost = i;
        }
    }

    point start = p[result_idx];

    int current = leftmost;
    do
    {
        hull.push_back(p[current]);
        int next = (current + 1) % n;
        for (int i = 0; i < n; i++)
        {
            if (ccw(p[current], p[i], p[next]) > 0)
            {
                next = i;
            }
        }
        current = next;
    } while (current != leftmost);

    int size = hull.size();

    // 이미 hull[0]은 조건이 만족함.
    sort(hull.begin() + 1, hull.end(), cmp);

    result_idx = 0;
    for (int i = 0; i < size; i++)
    {
        if (hull[i].x == start.x && hull[i].y == start.y)
        {
            result_idx = i;
            break;
        }
    }

    out << size << endl;
    for (int i = result_idx; i < size; i++)
    {
        out << hull[i].x << " " << hull[i].y << endl;
    }
    for (int i = 0; i < result_idx; i++)
    {
        out << hull[i].x << " " << hull[i].y << endl;
    }
}

int main(void)
{
    inp >> n;
    p.resize(n);
    for (int i = 0; i < n; i++)
    {
        inp >> p[i].x >> p[i].y;
    }
    if (n > 2)
    {
        ConvexHull();
    }
    else
    {
        out << "0" << endl;
    }
}
