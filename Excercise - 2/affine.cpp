//cryptographic attack on cipher text by affine cipher
//date:26/8/2024
#include <iostream>
#include <string>
using namespace std;

// Function to compute the greatest common divisor (GCD) using the Euclidean algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to encrypt a message using the Affine Cipher
string encryptMessage(string msg, int a, int b) {
    string cipher = "";
    for (int i = 0; i < msg.length(); i++) {
        if (msg[i] != ' ') {
            if (isupper(msg[i]))
                cipher += (char)((((a * (msg[i] - 'A')) + b) % 26) + 'A');
            else if (islower(msg[i]))
                cipher += (char)((((a * (msg[i] - 'a')) + b) % 26) + 'a');
        } else {
            cipher += msg[i];
        }
    }
    return cipher;
}

// Function to decrypt a message using the Affine Cipher
string decryptCipher(string cipher, int a, int b) {
    string msg = "";
    int a_inv = 0;
    int flag = 0;

    // Find a_inv (multiplicative inverse of a modulo 26)
    for (int i = 0; i < 26; i++) {
        flag = (a * i) % 26;
        if (flag == 1) {
            a_inv = i;
            break;
        }
    }

    for (int i = 0; i < cipher.length(); i++) {
        if (cipher[i] != ' ') {
            if (isupper(cipher[i]))
                msg += (char)(((a_inv * ((cipher[i] - 'A' - b + 26)) % 26)) + 'A');
            else if (islower(cipher[i]))
                msg += (char)(((a_inv * ((cipher[i] - 'a' - b + 26)) % 26)) + 'a');
        } else {
            msg += cipher[i];
        }
    }

    return msg;
}

// Function to perform brute-force attack on Affine Cipher
void performAffineAttack(string cipherText) {
    cout << "Attempting all possible key pairs (a, b):\n";

    // Try all values of 'a' and 'b'
    for (int a = 1; a < 26; a++) {
        if (gcd(a, 26) == 1) // 'a' must be coprime with 26
        {
            for (int b = 0; b < 26; b++) {
                string decryptedText = decryptCipher(cipherText, a, b);
                cout << "a = " << a << ", b = " << b << ": " << decryptedText << endl;
            }
        }
    }
}

int main() {
    string msg;
    int a, b;

    cout << "Enter the value of a: ";
    cin >> a;
    cout << "Enter the value of b: ";
    cin >> b;
    cin.ignore();
    cout << "Enter the plain text: ";
    getline(cin, msg);

    string cipherText = encryptMessage(msg, a, b);
    cout << "Cipher Text is : " << cipherText << endl;

    cout << "Plain Text is: " << decryptCipher(cipherText, a, b) << endl;

    performAffineAttack(cipherText);

    return 0;
}
