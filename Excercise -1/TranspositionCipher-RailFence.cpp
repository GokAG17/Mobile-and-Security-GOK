#include <iostream>
#include <string>
#include <vector>

using namespace std;

string encryptRailFence(string text, int key)
{
    if (key <= 1)
        return text;

    vector<string> rail(key);
    int dir = 1, row = 0;

    for (char c : text)
    {
        rail[row] += c;
        row += dir;
        if (row == 0 || row == key - 1)
            dir *= -1;
    }

    string cipherText;
    for (const auto &line : rail)
    {
        cipherText += line;
    }

    return cipherText;
}

string decryptRailFence(string cipherText, int key)
{
    if (key <= 1)
        return cipherText;

    int n = cipherText.size();
    vector<string> rail(key, string(n, '\n'));

    int dir = 1, row = 0;
    int index = 0;

    // Mark the positions on the rail matrix
    for (int i = 0; i < n; i++)
    {
        rail[row][i] = '*';
        row += dir;
        if (row == 0 || row == key - 1)
            dir *= -1;
    }

    // Place characters in the positions marked
    for (int r = 0; r < key; r++)
    {
        for (int i = 0; i < n; i++)
        {
            if (rail[r][i] == '*' && index < n)
            {
                rail[r][i] = cipherText[index++];
            }
        }
    }

    string plainText;
    row = 0, dir = 1;

    // Read the matrix to reconstruct the plaintext
    for (int i = 0; i < n; i++)
    {
        plainText += rail[row][i];
        row += dir;
        if (row == 0 || row == key - 1)
            dir *= -1;
    }

    return plainText;
}

int main()
{
    string text;
    int key;

    cout << "Enter the text to be encrypted: ";
    getline(cin, text);

    cout << "Enter the key (number of rails): ";
    cin >> key;

    string encrypted = encryptRailFence(text, key);
    cout << "Encrypted Text: " << encrypted << endl;

    string decrypted = decryptRailFence(encrypted, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
