#include <iostream>
#include <string>
#include <cctype>
using namespace std;


int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

char encryptChar(char ch, int a, int b) {
    if (isupper(ch)) {
        return char(((a * (ch - 'A') + b) % 26) + 'A');
    } else if (islower(ch)) {
        return char(((a * (ch - 'a') + b) % 26) + 'a');
    }
    return ch;
}

char decryptChar(char ch, int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        cout << "Modular inverse does not exist. Decryption is not possible." << endl;
        exit(1);
    }
    if (isupper(ch)) {
        return char(((a_inv * ((ch - 'A') - b + 26)) % 26) + 'A');
    } else if (islower(ch)) {
        return char(((a_inv * ((ch - 'a') - b + 26)) % 26) + 'a');
    }
    return ch;
}

string encrypt(string text, int a, int b) {
    string cipherText;
    for (char ch : text) {
        cipherText += encryptChar(ch, a, b);
    }
    return cipherText;
}

string decrypt(string cipherText, int a, int b) {
    string plainText;
    for (char ch : cipherText) {
        plainText += decryptChar(ch, a, b);
    }
    return plainText;
}

int main() {
    string text;
    int a, b;

    cout << "Enter the text to be encrypted: ";
    getline(cin, text);

    cout << "Enter the value for 'a' (should be coprime with 26): ";
    cin >> a;
    cout << "Enter the value for 'b': ";
    cin >> b;

    if (modInverse(a, 26) == -1) {
        cout << "'a' is not coprime with 26. Please enter a valid value." << endl;
        return 1;
    }

    string encrypted = encrypt(text, a, b);
    cout << "Encrypted Text: " << encrypted << endl;

    string decrypted = decrypt(encrypted, a, b);
    cout << "Decrypted Text: " << decrypted << endl;

    return 0;
}
