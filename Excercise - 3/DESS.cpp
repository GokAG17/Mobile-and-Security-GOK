#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

// Permutation tables (IP, FP, Expansion, P, S-Boxes)
int IP[] = { 58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
             62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
             57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
             61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7 };

int FP[] = { 40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
             38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
             36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
             34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25 };

// Expansion table for function f
int E[] = { 32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13,
            12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23,
            24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 };

// Permutation table used after S-boxes
int P[] = { 16, 7, 20, 21, 29, 12, 28, 17,
            1, 15, 23, 26, 5, 18, 31, 10,
            2, 8, 24, 14, 32, 27, 3, 9,
            19, 13, 30, 6, 22, 11, 4, 25 };

// S-box tables
int S_BOX[8][4][16] = {
    // S1
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
    // S2
    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
    // S3
    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
    // S4
    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
    // S5
    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
    // S6
    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
    // S7
    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 6, 8, 15, 2},
     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
     {6, 11, 13, 0, 5, 14, 7, 15, 3, 9, 8, 10, 12, 2, 4, 1}},
    // S8
    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 11, 6, 0, 3, 5}}};

// Key schedule (round keys)
vector<vector<int>> generateRoundKeys(vector<int> key) {
    vector<vector<int>> roundKeys(16, vector<int>(48));
    // This function will generate 16 round keys from the original key
    // You need to implement key scheduling (PC1, rotation, PC2) here
    return roundKeys;
}

vector<int> permute(vector<int> block, int* table, int size) {
    vector<int> result(size);
    for (int i = 0; i < size; ++i) {
        result[i] = block[table[i] - 1];
    }
    return result;
}

vector<int> xorVector(vector<int> a, vector<int> b) {
    for (int i = 0; i < a.size(); ++i) {
        a[i] ^= b[i];
    }
    return a;
}

vector<int> sBoxSubstitution(vector<int> input) {
    vector<int> output(32);
    for (int i = 0; i < 8; ++i) {
        vector<int> block(input.begin() + i * 6, input.begin() + (i + 1) * 6);
        int row = (block[0] << 1) | block[5];
        int col = (block[1] << 3) | (block[2] << 2) | (block[3] << 1) | block[4];
        int val = S_BOX[i][row][col];
        for (int j = 0; j < 4; ++j) {
            output[i * 4 + j] = (val >> (3 - j)) & 1;
        }
    }
    return output;
}

vector<int> feistelFunction(vector<int> right, vector<int> key) {
    vector<int> expanded = permute(right, E, 48);
    vector<int> xorResult = xorVector(expanded, key);
    vector<int> sBoxResult = sBoxSubstitution(xorResult);
    return permute(sBoxResult, P, 32);
}

vector<int> desRound(vector<int> left, vector<int> right, vector<int> key) {
    vector<int> newRight = xorVector(left, feistelFunction(right, key));
    return {right, newRight};
}

vector<int> desEncrypt(vector<int> block, vector<vector<int>> roundKeys) {
    vector<int> permutedBlock = permute(block, IP, 64);
    vector<int> left(permutedBlock.begin(), permutedBlock.begin() + 32);
    vector<int> right(permutedBlock.begin() + 32, permutedBlock.end());

    for (int i = 0; i < 16; ++i) {
        vector<int> result = desRound(left, right, roundKeys[i]);
        left = result[0];
        right = result[1];
    }

    vector<int> preOutput = left;
    left = right;
    right = preOutput;

    return permute(left + right, FP, 64);
}

vector<int> desDecrypt(vector<int> block, vector<vector<int>> roundKeys) {
    // Reverse the order of the round keys for decryption
    vector<vector<int>> reversedRoundKeys(roundKeys.rbegin(), roundKeys.rend());
    return desEncrypt(block, reversedRoundKeys);
}

int main() {
    vector<int> key = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Replace with actual key bits
    vector<vector<int>> roundKeys = generateRoundKeys(key);

    vector<int> plaintext = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Replace with actual plaintext bits

    vector<int> ciphertext = desEncrypt(plaintext, roundKeys);
    vector<int> decryptedText = desDecrypt(ciphertext, roundKeys);

    // Print ciphertext and decrypted text for verification
    cout << "Ciphertext: ";
    for (int bit : ciphertext) cout << bit;
    cout << endl;

    cout << "Decrypted Text: ";
    for (int bit : decryptedText) cout << bit;
    cout << endl;

    return 0;
}
