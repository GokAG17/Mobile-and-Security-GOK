#include<bits/stdc++.h>

using namespace std;

void getKeyMatrix(string key, vector<vector<int>> &keyMatrix, int size) {
    int k = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            keyMatrix[i][j] = (key[k] - 'A') % 26;
            k++;
        }
    }
}

vector<int> multiplyMatrix(vector<vector<int>> &keyMatrix, vector<int> &messageVector, int size) {
    vector<int> cipherVector(size, 0);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cipherVector[i] += keyMatrix[i][j] * messageVector[j];
        }
        cipherVector[i] %= 26;  
    }
    return cipherVector;
}

string HillCipher(string message, string key) {
    int size = sqrt(key.length());
    vector<vector<int>> keyMatrix(size, vector<int>(size));
    
    getKeyMatrix(key, keyMatrix, size);

    while (message.length() % size != 0) {
        message += 'X';
    }

    string cipherText = "";
    
    for (int i = 0; i < message.length(); i += size) {
        vector<int> messageVector(size);
        for (int j = 0; j < size; j++) {
            messageVector[j] = (message[i + j] - 'A') % 26;
        }
        
        vector<int> cipherVector = multiplyMatrix(keyMatrix, messageVector, size);
        
        for (int j = 0; j < size; j++) {
            cipherText += (cipherVector[j] + 'A');
        }
    }

    return cipherText;
}

int main() {
    string message, key;

    cout << "Enter the message (uppercase letters only): ";
    getline(cin, message);

    cout << "Enter the key (uppercase letters only, must be a perfect square length): ";
    getline(cin, key);

    int size = sqrt(key.length());
    if (size * size != key.length()) {
        cout << "Invalid key length. The key length must be a perfect square (e.g., 4, 9, 16, ...)." << endl;
        return 1;
    }

    string cipherText = HillCipher(message, key);
    cout << "Encrypted Text: " << cipherText << endl;

    return 0;
}
