<<<<<<< HEAD
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int mod26(int x) {
    return (x % 26 + 26) % 26;
}

int determinant(const vector<vector<int>>& matrix) {
    return mod26(matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}

int multiplicativeInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; 
}

vector<vector<int>> inverseKeyMatrix(const vector<vector<int>>& keyMatrix) {
    int det = determinant(keyMatrix);
    int invDet = multiplicativeInverse(det, 26);

    if (invDet == -1) {
        cout << "Key matrix is not invertible (no modular inverse for determinant)." << endl;
        exit(1);
    }

    vector<vector<int>> invMatrix(2, vector<int>(2));
    invMatrix[0][0] = mod26(keyMatrix[1][1] * invDet);
    invMatrix[0][1] = mod26(-keyMatrix[0][1] * invDet);
    invMatrix[1][0] = mod26(-keyMatrix[1][0] * invDet);
    invMatrix[1][1] = mod26(keyMatrix[0][0] * invDet);

    return invMatrix;
}

vector<vector<int>> getKeyMatrix(const string& key) {
    vector<vector<int>> keyMatrix(2, vector<int>(2));
    int k = 0;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            keyMatrix[i][j] = (key[k] % 65);
            ++k;
        }
    }

    return keyMatrix;
}

string hillCipher(const string& input, const vector<vector<int>>& matrix) {
    int n = input.length();
    string output = "";

    for (int i = 0; i < n; i += 2) {
        int x = input[i] % 65;
        int y = (i + 1 < n) ? input[i + 1] % 65 : 23; // 23 is 'X' in 0-based alphabet

        int c1 = mod26(matrix[0][0] * x + matrix[0][1] * y);
        int c2 = mod26(matrix[1][0] * x + matrix[1][1] * y);

        output += c1 + 65;
        output += c2 + 65;
    }

    return output;
}

int main() {
    string plaintext, key;

    cout << "Enter a 2x2 key matrix (4 letters): ";
    cin >> key;
    
    if (key.length() != 4) {
        cout << "Key must be 4 characters long." << endl;
        return 1;
    }

    cout << "Enter the plaintext: ";
    cin >> plaintext;

    // Pad plaintext if odd length
    if (plaintext.length() % 2 != 0) {
        plaintext += 'X'; // Pad with 'X'
    }

    vector<vector<int>> keyMatrix = getKeyMatrix(key);
    string ciphertext = hillCipher(plaintext, keyMatrix);

    cout << "Ciphertext: " << ciphertext << endl;

    // Attempt to get the inverse of the key matrix
    vector<vector<int>> invKeyMatrix = inverseKeyMatrix(keyMatrix);
    string decryptedtext = hillCipher(ciphertext, invKeyMatrix);

    // Remove padding if it was added
    if (plaintext.length() % 2 != 0 && decryptedtext.back() == 'X') {
        decryptedtext.pop_back();
    }

    cout << "Decrypted text: " << decryptedtext << endl;

    return 0;
}
=======
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int mod26(int x) {
    return (x % 26 + 26) % 26;
}

int determinant(const vector<vector<int>>& matrix) {
    return mod26(matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}

int multiplicativeInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; 
}

vector<vector<int>> inverseKeyMatrix(const vector<vector<int>>& keyMatrix) {
    int det = determinant(keyMatrix);
    int invDet = multiplicativeInverse(det, 26);

    if (invDet == -1) {
        cout << "Key matrix is not invertible (no modular inverse for determinant)." << endl;
        exit(1);
    }

    vector<vector<int>> invMatrix(2, vector<int>(2));
    invMatrix[0][0] = mod26(keyMatrix[1][1] * invDet);
    invMatrix[0][1] = mod26(-keyMatrix[0][1] * invDet);
    invMatrix[1][0] = mod26(-keyMatrix[1][0] * invDet);
    invMatrix[1][1] = mod26(keyMatrix[0][0] * invDet);

    return invMatrix;
}

vector<vector<int>> getKeyMatrix(const string& key) {
    vector<vector<int>> keyMatrix(2, vector<int>(2));
    int k = 0;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            keyMatrix[i][j] = (key[k] % 65);
            ++k;
        }
    }

    return keyMatrix;
}

string hillCipher(const string& input, const vector<vector<int>>& matrix) {
    int n = input.length();
    string output = "";

    for (int i = 0; i < n; i += 2) {
        int x = input[i] % 65;
        int y = (i + 1 < n) ? input[i + 1] % 65 : 23; // 23 is 'X' in 0-based alphabet

        int c1 = mod26(matrix[0][0] * x + matrix[0][1] * y);
        int c2 = mod26(matrix[1][0] * x + matrix[1][1] * y);

        output += c1 + 65;
        output += c2 + 65;
    }

    return output;
}

int main() {
    string plaintext, key;

    cout << "Enter a 2x2 key matrix (4 letters): ";
    cin >> key;
    
    if (key.length() != 4) {
        cout << "Key must be 4 characters long." << endl;
        return 1;
    }

    cout << "Enter the plaintext: ";
    cin >> plaintext;

    // Pad plaintext if odd length
    if (plaintext.length() % 2 != 0) {
        plaintext += 'X'; // Pad with 'X'
    }

    vector<vector<int>> keyMatrix = getKeyMatrix(key);
    string ciphertext = hillCipher(plaintext, keyMatrix);

    cout << "Ciphertext: " << ciphertext << endl;

    // Attempt to get the inverse of the key matrix
    vector<vector<int>> invKeyMatrix = inverseKeyMatrix(keyMatrix);
    string decryptedtext = hillCipher(ciphertext, invKeyMatrix);

    // Remove padding if it was added
    if (plaintext.length() % 2 != 0 && decryptedtext.back() == 'X') {
        decryptedtext.pop_back();
    }

    cout << "Decrypted text: " << decryptedtext << endl;

    return 0;
}
>>>>>>> b0aa8f66028e64bd629d882caa60d856db00d28c
