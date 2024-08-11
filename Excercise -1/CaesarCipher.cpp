#include <iostream>
#include <string>
using namespace std;

string caesarEncrypt(string text, int key)
{
    string res = "";
    for (int i = 0; i < text.size(); i++)
    {
        if (isupper(text[i]))
        {
            res += char(int(text[i] + key - 65) % 26 + 65);
        }
        else
        {
            res += char(int(text[i] + key - 97) % 26 + 97);
        }
    }
    return res;
}

string caesarDecrypt(string text, int key)
{
    return caesarEncrypt(text, 26 - key);
}

int main()
{
    string text;
    int key;
    cout << "Enter the text to encrypt : ";
    cin >> text;
    cout << "Enter the key to encrypt : ";
    cin >> key;
    string encrypted = caesarEncrypt(text, key);
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << caesarDecrypt(encrypted, key) << endl;
    return 0;
}
