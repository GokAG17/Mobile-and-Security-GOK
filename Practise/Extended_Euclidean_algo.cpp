#include <bits/stdc++.h>
using namespace std;

int extendedgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int main()
{
    int a, b, x, y;
    cout << "Enter the value of a : ";
    cin >> a;
    cout << "Enter the value of b : ";
    cin >> b;
    int gcd = extendedgcd(a, b, x, y);
    cout << "GCD of a and b is : " << gcd << endl;
    cout << "The value of x and y are : " << x << " and " << y << endl;
    return 0;
}