#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;

ifstream inp("eq.inp");
ofstream out("eq.out");

int ExtendedEuclid(int a, int b, int &x, int &y)
{
    int r1 = a, r2 = b, s1 = 1, s2 = 0, t1 = 0, t2 = 1;

    while (r2)
    {
        int q = r1 / r2;
        int r = r1 - (q * r2);
        int s = s1 - (q * s2);
        int t = t1 - (q * t2);

        r1 = r2;
        r2 = r;
        s1 = s2;
        s2 = s;
        t1 = t2;
        t2 = t;
    }

    x = s1;
    y = t1;

    return r1;
}

void diophantos(int a, int b, int c)
{
    int result, x, y, a0, b0, c0;
    int g = ExtendedEuclid(a, b, x, y);
    if (c % g != 0)
    {
        out << "-1" << endl;
        return;
    }

    a0 = a / g;
    b0 = b / g;
    c0 = c / g;

    int minValue = abs(x * (c / g)) + abs(y * (c / g));
    int max_num = a0;

    if (max_num < b0)
    {
        max_num = b0;
    }
    if (max_num < c0)
    {
        max_num = c0;
    }

    for (int i = -max_num; i <= max_num; i++)
    {
        // a0*x + b0*y = c0
        int temp_x = i;
        int temp_y = (c0 - (a0 * temp_x)) / b0;

        int value = abs(temp_x) + abs(temp_y);
        if (value < minValue && ((a0 * temp_x + b0 * temp_y) == c0))
        {
            minValue = value;
        }
    }

    out << minValue << endl;
}

int main(void)
{
    int T;
    inp >> T;

    for (int i = 0; i < T; i++)
    {
        int a, b, c;
        inp >> a >> b >> c;

        diophantos(a, b, c);
    }

    return 0;
}
