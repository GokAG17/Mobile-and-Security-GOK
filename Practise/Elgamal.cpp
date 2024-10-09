#include <bits/stdc++.h>
using namespace std;

long long modInverse(long long a, long long b)
{
    a = a % b;
    for (long long i = 1; i < b; i++)
    {
        if ((a * i) % b == 1)
        {
            return i;
        }
    }
    return -1;
}

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

void generatekey(long long &p, long long &g, long long &x, long long &y)
{
    p = 23;
    g = 5;
    x = rand() % (p - 2) + 1;
    y = modExp(g, x, p);
}

pair<long long, long long> encrypt(long long pt, long long g, long long p, long long y)
{
    long long k = rand() % (p - 2) + 1;
    long long c1 = modExp(g, k, p);
    long long c2 = pt * modExp(y, k, p);
    return {c1, c2};
}

long long decrypt(pair<long long, long long> ct, long long x, long long p)
{
    long long c1 = ct.first;
    long long c2 = ct.second;
    long long s = modExp(c1, x, p);
    long long sin = modInverse(s, p);
    return (c2 * sin) % p;
}

int main()
{
    srand(time(0));
    long long p, g, x, y;
    generatekey(p, g, x, y);
    cout << "Public Key : p = " << p << " g = " << g << " y = " << y << endl;
    cout << "Private Key : x = " << x << endl;
    long long plaintext;
    cout << "Enter the Plain text : ";
    cin >> plaintext;
    pair<long long, long long> cipher = encrypt(plaintext, g, p, y);
    cout << "Cipher c1 : " << cipher.first << " , c2 : " << cipher.second << endl;
    long long decrypted = decrypt(cipher, x, p);
    cout << "Decrypted Text : " << decrypted << endl;
    return 0;
}