#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int eulertotient(int n)
{
    int result = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
            {
                n /= i;
            }
            result -= result / i;
        }
    }
    if (n > 1)
    {
        result -= result / n;
    }
    return result;
}

long long modExp(long long base, long long exp, long long mod)
{
    long long result = 1;
    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main()
{
    int a, n;
    cout << "Enter the value of a (base) : ";
    cin >> a;
    cout << "Enter the value of n (modulus) : ";
    cin >> n;
    if (gcd(a, n) != 1)
    {
        cout << "Error: gcd(a,n) is not coprime." << endl;
        exit(1);
    }
    int phi = eulertotient(n);
    cout << "Euler Totient : " << phi << endl;
    int val = modExp(a, phi - 1, n);
    cout << "Mod Inverse of a and n : " << val << endl;
    return 0;
}