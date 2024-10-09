#include <bits/stdc++.h>
using namespace std;

int modInverse(int a, int b)
{
    a = a % b;
    for (int x = 1; x < b; x++)
    {
        if ((a * x) % b == 1)
        {
            return x;
        }
    }
    return -1;
}

char enchar(char s, int a, int b)
{
    if (isupper(s))
    {
        return char(((a * (s - 'A') + b) % 26) + 'A');
    }
    else if (islower(s))
    {
        return char(((a * (s - 'a') + b) % 26) + 'a');
    }
    return s;
}

char dechar(char s, int a, int b)
{
    int ain = modInverse(a, 26);
    if (ain == -1)
    {
        cout << "Modular Inverse does not exist" << endl;
        exit(1);
    }
    if (isupper(s))
    {
        return char(((ain * ((s - 'A') - b + 26)) % 26) + 'A');
    }
    else if (islower(s))
    {
        return char(((ain * ((s - 'a') - b + 26)) % 26) + 'a');
    }
    return s;
}

string encrypt(string s, int a, int b)
{
    string res = "";
    for (char ch : s)
    {
        res += enchar(ch, a, b);
    }
    return res;
}

string decrypt(string s, int a, int b)
{
    string res = "";
    for (char ch : s)
    {
        res += dechar(ch, a, b);
    }
    return res;
}

int main()
{
    string s;
    int a, b;
    cout << "Enter the string fro encryption : ";
    getline(cin, s);
    cout << "Enter the value of a (coprime) : ";
    cin >> a;
    cout << "Enter the value of b :";
    cin >> b;
    if (modInverse(a, 26) == -1)
    {
        cout << " a not coprime with 26 , Enter valid number";
        return 1;
    }
    string encryptedtext = encrypt(s, a, b);
    cout << "Encrypted Text : " << encryptedtext << endl;
    string decryptedtext = decrypt(encryptedtext, a, b);
    cout << "Decrypted Text : " << decryptedtext << endl;
    return 0;
}