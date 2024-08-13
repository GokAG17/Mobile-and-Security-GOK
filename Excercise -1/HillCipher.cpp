#include <iostream>
#include <vector>
#include <string>

using namespace std;

void getKeyMatrix(string key, vector<vector<int>>& keyMatrix, int n) {
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            keyMatrix[i][j] = (key[k]) % 65;
            k++;
        }
    }
}

void encrypt(vector<vector<int>>& keyMatrix, string& message, string& cipherText, int n) {
    vector<int> messageVector(n);

    for (int i = 0; i < message.length(); i += n) {
        for (int j = 0; j < n; j++) {
            messageVector[j] = message[i + j] % 65;
        }

        vector<int> cipherVector(n, 0);

        for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++) {
                cipherVector[x] += keyMatrix[x][y] * messageVector[y];
            }
            cipherVector[x] = cipherVector[x] % 26;
        }

        for (int j = 0; j < n; j++) {
            cipherText += cipherVector[j] + 65;
        }
    }
}

void decrypt(vector<vector<int>>& inverseKeyMatrix, string& cipherText, string& decryptedText, int n) {
    vector<int> cipherVector(n);

    for (int i = 0; i < cipherText.length(); i += n) {
        for (int j = 0; j < n; j++) {
            cipherVector[j] = cipherText[i + j] % 65;
        }

        vector<int> decryptedVector(n, 0);

        for (int x = 0; x < n; x++) {
            for (int y = 0; y < n; y++) {
                decryptedVector[x] += inverseKeyMatrix[x][y] * cipherVector[y];
            }
            decryptedVector[x] = decryptedVector[x] % 26;
        }

        for (int j = 0; j < n; j++) {
            decryptedText += decryptedVector[j] + 65;
        }
    }
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return 1; 
}

void getCofactorMatrix(vector<vector<int>>& matrix, vector<vector<int>>& cofactorMatrix, int p, int q, int n) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                cofactorMatrix[i][j++] = matrix[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinant(vector<vector<int>>& matrix, int n) {
    if (n == 1)
        return matrix[0][0];

    int det = 0;
    vector<vector<int>> cofactorMatrix(n, vector<int>(n));

    int sign = 1;
    for (int i = 0; i < n; i++) {
        getCofactorMatrix(matrix, cofactorMatrix, 0, i, n);
        det += sign * matrix[0][i] * determinant(cofactorMatrix, n - 1);
        sign = -sign;
    }
    return det;
}

void adjoint(vector<vector<int>>& matrix, vector<vector<int>>& adjMatrix, int n) {
    if (n == 1) {
        adjMatrix[0][0] = 1;
        return;
    }

    int sign = 1;
    vector<vector<int>> cofactorMatrix(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            getCofactorMatrix(matrix, cofactorMatrix, i, j, n);
            sign = ((i + j) % 2 == 0) ? 1 : -1;
            adjMatrix[j][i] = (sign * determinant(cofactorMatrix, n - 1)) % 26;
            if (adjMatrix[j][i] < 0) {
                adjMatrix[j][i] += 26;
            }
        }
    }
}

bool inverseKeyMatrix(vector<vector<int>>& matrix, vector<vector<int>>& invMatrix, int n) {
    int det = determinant(matrix, n);
    int invDet = modInverse(det, 26);
    if (invDet == -1)
        return false;

    vector<vector<int>> adjMatrix(n, vector<int>(n));
    adjoint(matrix, adjMatrix, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            invMatrix[i][j] = (adjMatrix[i][j] * invDet) % 26;
            if (invMatrix[i][j] < 0) {
                invMatrix[i][j] += 26;
            }
        }
    }
    return true;
}

int main() {
    int n;

    cout << "Enter the size of the key matrix (n x n): ";
    cin >> n;

    string key;
    cout << "Enter the key (length should be " << n * n << "): ";
    cin >> key;

    vector<vector<int>> keyMatrix(n, vector<int>(n));
    getKeyMatrix(key, keyMatrix, n);

    string message;
    cout << "Enter the message to be encrypted (uppercase, length multiple of " << n << "): ";
    cin >> message;

    string cipherText;
    encrypt(keyMatrix, message, cipherText, n);
    cout << "Encrypted Text: " << cipherText << endl;

    vector<vector<int>> invKeyMatrix(n, vector<int>(n));
    if (!inverseKeyMatrix(keyMatrix, invKeyMatrix, n)) {
        cout << "Inverse of the key matrix does not exist. Cannot decrypt." << endl;
        return 1;
    }

    string decryptedText;
    decrypt(invKeyMatrix, cipherText, decryptedText, n);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
