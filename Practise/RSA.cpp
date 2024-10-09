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

int modInverse(int a, int b)
{
    a = a % b;
    for (int i = 1; i < b; i++)
    {
        if ((a * i) % b == 1)
        {
            return i;
        }
    }
    return -1;
}

void generatekey(int &e, int &d, int phi)
{
    e = 2;
    while (gcd(e, phi) != 1)
    {
        e++;
    }
    d = modInverse(e, phi);
}

long long encrypt(int plaintext, int e, int n)
{
    return modExp(plaintext, e, n);
}

long long decrypt(long long ciphertext, int d, int n)
{
    return modExp(ciphertext, d, n);
}

int main()
{
    int p, q, e, d;
    cout << "Enter the value of p : ";
    cin >> p;
    cout << "Enter the value of q : ";
    cin >> q;
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    cout << "The value of euler totient fucntion : " << phi << endl;
    generatekey(e, d, phi);
    cout << "The Public Key : e = " << e << ", n = " << n << endl;
    cout << "The Private Key : d = " << d << ", n = " << n << endl;
    int plaintext;
    cout << "Enter the plain text : ";
    cin >> plaintext;
    long long encrypttxt = encrypt(plaintext, e, n);
    cout << "Encrypted Text : " << encrypttxt << endl;
    long long decrypttxt = decrypt(encrypttxt, d, n);
    cout << "Decrypted Text : " << decrypttxt << endl;
    return 0;
}