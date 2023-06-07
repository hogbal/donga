#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ifstream inp("eq.inp");
ofstream out("eq.out");

// 확장 유클리드 알고리즘
int extendedGCD(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

// 일차 디오판토스 방정식 해 구하기
bool linearDiophantine(int a, int b, int c, int &x, int &y)
{
    int gcd = extendedGCD(a, b, x, y);

    if (c % gcd != 0)
        return false;

    x *= c / gcd;
    y *= c / gcd;

    return true;
}

int main()
{
    int T;
    inp >> T;

    for (int i = 0; i < T; i++)
    {
        int a, b, c;
        inp >> a >> b >> c;

        int x = 0, y = 0;
        int minSum = abs(c / a) + abs(c / b);
        bool foundSolution = false;

        for (int j = -minSum; j <= minSum; j++)
        {
            int tempX = j;
            int tempY = (c - (a * j)) / b;

            if ((a * tempX) + (b * tempY) == c)
            {
                if (!foundSolution || (abs(tempX) + abs(tempY) < abs(x) + abs(y)))
                {
                    foundSolution = true;
                    x = tempX;
                    y = tempY;
                }
            }
        }

        if (foundSolution && (a * x) + (b * y) == c)
            out << abs(x) + abs(y) << endl;
        else
            out << -1 << endl;
    }

    return 0;
}