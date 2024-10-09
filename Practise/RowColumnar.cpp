#include <bits/stdc++.h>
using namespace std;

string padtext(string s, int key)
{
    string padtxt = s;
    int ext = s.size() % key;
    if (ext != 0)
    {
        padtxt.append(key - ext, 'X');
    }
    return padtxt;
}

string encrypt(string s, string k)
{
    int keylen = k.size();
    string ptxt = padtext(s, keylen);
    int numrow = ptxt.size() / keylen;
    vector<string> grid(numrow, string(keylen, ' '));
    for (int i = 0; i < ptxt.size(); i++)
    {
        grid[i / keylen][i % keylen] = ptxt[i];
    }
    vector<int> order(keylen);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j)
         { return k[i] < k[j]; });
    string cipher;
    for (int col : order)
    {
        for (int row = 0; row < numrow; row++)
        {
            cipher += grid[row][col];
        }
    }
    return cipher;
}

string decrypt(string s, string k)
{
    int klen = k.size();
    int numrow = s.size() / klen;
    vector<string> grid(numrow, string(klen, ' '));
    vector<int> order(klen);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j)
         { return k[i] < k[j]; });

    int index = 0;
    for (int col : order)
    {
        for (int i = 0; i < numrow; i++)
        {
            grid[i][col] = s[index++];
        }
    }
    string pt;
    for (int i = 0; i < numrow; i++)
    {
        pt += grid[i];
    }
    pt.erase(remove(pt.begin(), pt.end(), 'X'), pt.end());
    return pt;
}

int main()
{
    string s1, k;
    cout << "Enter the string for encryption : ";
    getline(cin, s1);
    cout << "Enter the string key : ";
    getline(cin, k);
    string encrypted = encrypt(s1, k);
    cout << "Encrypted Text : " << encrypted << endl;
    string decrypted = decrypt(encrypted, k);
    cout << "Decrypted Text : " << decrypted << endl;
    return 0;
}