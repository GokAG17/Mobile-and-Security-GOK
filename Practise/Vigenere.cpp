#include <bits/stdc++.h>
using namespace std;
string generate(string pt, string k)
{
    int n = pt.size();
    int m = k.size();
    for (int i = 0; i < n - m; i++)
    {
        k += k[i % m];
    }
    return k;
}

string encrypt(string pt, string k)
{
    int n = pt.size();
    string ct = "";
    for (int i = 0; i < n; i++)
    {
        char x = (pt[i] + k[i]) % 26;
        x += 'A';
        ct += x;
    }
    return ct;
}

string decrypt(string pt, string k)
{
    int n = pt.size();
    string ct = "";
    for (int i = 0; i < n; i++)
    {
        char x = (pt[i] - k[i] + 26) % 26;
        x += 'A';
        ct += x;
    }
    return ct;
}

int main()
{
    string plaintext;
    string key;
    cout << "Enter the plain text : ";
    getline(cin, plaintext);
    cout << "Enter the Key : ";
    getline(cin, key);
    key = generate(plaintext, key);
    string encrypted = encrypt(plaintext, key);
    cout << "Encrypted Text : " << encrypted << endl;
    string decrypted = decrypt(encrypted, key);
    cout << "Decrypted Text : " << decrypted << endl;
    return 0;
}