#include <bits/stdc++.h>

using namespace std;

string padText(const string &text, int keyLength) {
    string paddedText = text;
    int extraChars = text.length() % keyLength;
    if (extraChars != 0) {
        paddedText.append(keyLength - extraChars, 'X');  
    }
    return paddedText;
}

string encrypt(string text, string key) {
    int keyLength = key.length();
    text = padText(text, keyLength);

    int numRows = text.length() / keyLength;
    vector<string> grid(numRows, string(keyLength, ' '));

    for (int i = 0; i < text.length(); i++) {
        grid[i / keyLength][i % keyLength] = text[i];
    }

    vector<int> order(keyLength);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) { return key[i] < key[j]; });

    string cipherText;
    for (int col : order) {
        for (int row = 0; row < numRows; row++) {
            cipherText += grid[row][col];
        }
    }

    return cipherText;
}

string decrypt(string cipherText, string key) {
    int keyLength = key.length();
    int numRows = cipherText.length() / keyLength;
    vector<string> grid(numRows, string(keyLength, ' '));

    vector<int> order(keyLength);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) { return key[i] < key[j]; });


    int index = 0;
    for (int col : order) {
        for (int row = 0; row < numRows; row++) {
            grid[row][col] = cipherText[index++];
        }
    }

    string plainText;
    for (int row = 0; row < numRows; row++) {
        plainText += grid[row];
    }

    plainText.erase(remove(plainText.begin(), plainText.end(), 'X'), plainText.end());

    return plainText;
}

int main() {
    string text, key;

    cout << "Enter the text to be encrypted: ";
    getline(cin, text);
    
    cout << "Enter the key (a word): ";
    getline(cin, key);

    string encrypted = encrypt(text, key);
    cout << "Encrypted Text: " << encrypted << endl;

    string decrypted = decrypt(encrypted, key);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
