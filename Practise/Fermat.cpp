#include <bits/stdc++.h>
using namespace std;

long long modExp(long long base, long long exp, long long mod)
{
    long long res = 1;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

long long fermat(long long a, long long p)
{
    return modExp(a, p - 1, p);
}

int main()
{
    long long a, p;
    cout << "Enter the value of a : ";
    cin >> a;
    cout << "Enter the value of b : ";
    cin >> p;
    if (a % p == 0)
    {
        cout << "Inverse not Exist " << endl;
    }
    else
    {
        long long inv = fermat(a, p);
        cout << " Modular Inverse is : " << inv << endl;
    }
    return 0;
}