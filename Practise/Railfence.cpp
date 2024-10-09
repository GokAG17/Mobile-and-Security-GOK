#include <bits/stdc++.h>
using namespace std;

string encrypt(string s, int key)
{
    int n = s.size();
    if (key <= 1)
    {
        return s;
    }
    vector<string> rail(key);
    int dir = 1;
    int row = 0;
    for (char a : s)
    {
        rail[row].push_back(a);
        row += dir;
        if (row == 0 || row == key - 1)
        {
            dir *= -1;
        }
    }
    string cipher;
    for (auto a : rail)
    {
        cipher += a;
    }
    return cipher;
}

string decrypt(string s, int key)
{
    if (key <= 1)
    {
        return s;
    }
    int n = s.size();
    vector<string> rail(key, string(n, '\n'));
    int dir = 1;
    int row = 0;
    for (int i = 0; i < n; i++)
    {
        rail[row][i] = '*';
        row += dir;
        if (row == 0 || row == key - 1)
        {
            dir *= -1;
        }
    }
    int index = 0;
    for (int r = 0; r < key; r++)
    {
        for (int i = 0; i < n; i++)
        {
            if (rail[r][i] == '*' && index < n)
            {
                rail[r][i] = s[index++];
            }
        }
    }
    string plaintext;
    row = 0;
    dir = 1;
    for (int i = 0; i < n; i++)
    {
        plaintext += rail[row][i];
        row += dir;
        if (row == 0 || row == key - 1)
        {
            dir *= -1;
        }
    }
    return plaintext;
}

int main()
{
    string s;
    int l;
    cout << "Enter the string for Encryption : ";
    getline(cin, s);
    cout << "Enter the key len : ";
    cin >> l;
    string encrypted = encrypt(s, l);
    cout << "Encrypted Text : " << encrypted << endl;
    string decrypted = decrypt(encrypted, l);
    cout << "Decrypted Text : " << decrypted << endl;
    return 0;
}