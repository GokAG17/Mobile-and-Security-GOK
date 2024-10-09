#include <bits/stdc++.h>
using namespace std;

int gcdeuclidean(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main()
{
    int a, b;
    cout << "Enter the value of a : ";
    cin >> a;
    cout << "Enter the value of b : ";
    cin >> b;
    int gcd = gcdeuclidean(a, b);
    cout << "GCD of a and b is : " << gcd << endl;
    return 0;
}