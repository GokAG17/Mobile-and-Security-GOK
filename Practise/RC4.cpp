#include <bits/stdc++.h>
using namespace std;

void ksa(vector<int> &key, vector<int> &s)
{
    int n = key.size();
    for (int i = 0; i < 256; i++)
    {
        s[i] = i;
    }
    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + s[i] + key[i % n]) % 256;
        swap(s[i], s[j]);
    }
}

int prga(vector<int> &s, int &i, int &j)
{
    i = (i + 1) % 256;
    j = (j + s[i]) % 256;
    swap(s[i], s[j]);
    return s[(s[i] + s[j] % 256)];
}

string RC4(string plaintext, string key)
{
    vector<int> s(256);
    vector<int> keyByte(key.begin(), key.end());

    ksa(keyByte, s);

    int i = 0;
    int j = 0;
    string ciphertext = "";
    for (char a : plaintext)
    {
        int x = prga(s, i, j);
        ciphertext += a ^ x;
    }
    return ciphertext;
}

int main()
{
    string key;
    cout << "Enter the key : ";
    cin >> key;
    string plaintext;
    cout << "Enter the plain text : ";
    cin.ignore();
    getline(cin, plaintext);

    string ciphertext = RC4(plaintext, key);
    for (unsigned char c : ciphertext)
    {
        printf("%02x ", c);
    }
    cout << endl;

    string decrypted = RC4(ciphertext, key);
    cout << "Decrypted Text : " << decrypted << endl;
    return 0;
}