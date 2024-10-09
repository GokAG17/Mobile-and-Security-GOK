#include <bits/stdc++.h>
using namespace std;

string encryption(string s, int k)
{
    int n = s.size();
    string res = "";
    for (int i = 0; i < n; i++)
    {
        if (isupper(s[i]))
        {
            res += char(int(s[i] + k - 65) % 26 + 65);
        }
        else if (islower(s[i]))
        {
            res += char(int(s[i] + k - 97) % 26 + 97);
        }
        else
        {
            res += s[i];
        }
    }
    return res;
}

string decryption(string s, int k)
{
    string res = encryption(s, 26 - k);
    return res;
}

int main()
{
    string s;
    int k;
    cout << "Enter the String to encrypt : ";
    getline(cin, s);
    cout << "Enter the Key for encryption : ";
    cin >> k;
    string encrypted = encryption(s, k);
    cout << "Encrypted String : " << encrypted << endl;
    string decrypted = decryption(encrypted, k);
    cout << "Decrypted String :" << decrypted << endl;
    return 0;
}