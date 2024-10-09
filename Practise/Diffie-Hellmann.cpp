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

int genPrimitiveRoot(int p)
{
    for (long long g = 2; g < p; g++)
    {
        bool isprim = true;
        for (long long i = 1; i < p - 1; i++)
        {
            if (modExp(g, i, p) == 1)
            {
                isprim = false;
                break;
            }
        }
        if (isprim)
        {
            return g;
        }
    }
    return -1;
}

void diffiehellman()
{
    int p = 23;
    int g = 9;

    // long long private_a = rand() % (p - 2) + 1;
    // long long private_b = rand() % (p - 2) + 1;

    long long private_a = 4;
    long long private_b = 3;

    long long public_a = modExp(g, private_a, p);
    long long public_b = modExp(g, private_b, p);

    long long shared_a = modExp(public_b, private_a, p);
    long long shared_b = modExp(public_a, private_b, p);

    cout << "Prime Number : " << p << endl;
    cout << "Primitive root modulo of p : " << g << endl;
    cout << "Private Key A : " << private_a << endl;
    cout << "Public Key A : " << public_a << endl;
    cout << "Private Key B : " << private_b << endl;
    cout << "Public Key B : " << public_b << endl;
    cout << "Shared Key A : " << shared_a << endl;
    cout << "Shared Key B : " << shared_b << endl;
}

int main()
{
    srand(time(0));
    diffiehellman();
    return 0;
}