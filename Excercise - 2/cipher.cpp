
//crypto attack on caser cipher's cipher text
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to decrypt a Caesar cipher with a given shift
string decryptCaesar(const string &ciphertext, int shift) {
    string plaintext = "";
    for (char c : ciphertext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char decryptedChar = (c - base - shift + 26) % 26 + base;
            plaintext += decryptedChar;
        } else {
            plaintext += c;
        }
    }
    return plaintext;
}

// Function to perform cryptanalysis on the Caesar cipher
void performCryptanalysis(const string &ciphertext) {
    cout << "Trying all possible shifts (0-25):\n";
    for (int shift = 0; shift < 26; ++shift) {
        string decryptedText = decryptCaesar(ciphertext, shift);
        cout << "Shift " << shift << ": " << decryptedText << endl;
    }
}

int main() {
    string ciphertext;
    
    cout << "Enter the ciphertext (only letters and spaces are considered): ";
    getline(cin, ciphertext);
    
    performCryptanalysis(ciphertext);
    
    return 0;
}
