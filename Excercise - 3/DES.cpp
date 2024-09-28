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
     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
    // S8
    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}
};

// Function to perform the initial/final permutation
bitset<64> permute(bitset<64> input, int* table, int n) {
    bitset<64> output;
    for (int i = 0; i < n; i++) {
        output[n - i - 1] = input[64 - table[i]];
    }
    return output;
}

// Expand 32-bit half-block to 48-bit using expansion table
bitset<48> expand(bitset<32> halfBlock) {
    bitset<48> expandedBlock;
    for (int i = 0; i < 48; i++) {
        expandedBlock[47 - i] = halfBlock[32 - E[i]];
    }
    return expandedBlock;
}

// Function f in the DES Feistel structure
bitset<32> functionF(bitset<32> R, bitset<48> K) {
    // Step 1: Expansion of R
    bitset<48> expandedR = expand(R);

    // Step 2: XOR with the key
    expandedR ^= K;

    // Step 3: Substitution using S-boxes
    bitset<32> substituted;
    for (int i = 0; i < 8; i++) {
        bitset<6> chunk;
        for (int j = 0; j < 6; j++) {
            chunk[5 - j] = expandedR[47 - (6 * i + j)];
        }
        int row = (chunk[5] << 1) | chunk[0];
        int col = (chunk[4] << 3) | (chunk[3] << 2) | (chunk[2] << 1) | chunk[1];
        int sboxValue = S_BOX[i][row][col];
        bitset<4> sboxOutput(sboxValue);

        // Map the 4 bits from S-box to the output
        for (int j = 0; j < 4; j++) {
            substituted[31 - (4 * i + j)] = sboxOutput[3 - j];
        }
    }

    // Step 4: Permutation P on substituted block
    bitset<32> permutedBlock;
    for (int i = 0; i < 32; i++) {
        permutedBlock[31 - i] = substituted[32 - P[i]];
    }

    return permutedBlock;
}

// Left circular shift for key scheduling
bitset<28> leftShift(bitset<28> halfKey, int shifts) {
    return (halfKey << shifts) | (halfKey >> (28 - shifts));
}

// Generate round keys for 16 rounds
vector<bitset<48>> generateKeys(bitset<64> key) {
    // Key Permuted Choice 1
    int PC1[] = { 57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
                  10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
                  63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
                  14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4 };

    // Key Permuted Choice 2
    int PC2[] = { 14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4,
                  26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40,
                  51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32 };

    // Left shifts for each round
    int shifts[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

    // Apply PC1 to the key
    bitset<56> permutedKey;
    for (int i = 0; i < 56; i++) {
        permutedKey[55 - i] = key[64 - PC1[i]];
    }

    // Split into left and right halves
    bitset<28> C, D;
    for (int i = 0; i < 28; i++) {
        C[i] = permutedKey[i + 28];
        D[i] = permutedKey[i];
    }

    // Generate 16 round keys
    vector<bitset<48>> roundKeys;
    for (int round = 0; round < 16; round++) {
        // Left shift both halves
        C = leftShift(C, shifts[round]);
        D = leftShift(D, shifts[round]);

        // Combine the halves and apply PC2
        bitset<56> combinedKey;
        for (int i = 0; i < 28; i++) {
            combinedKey[i] = D[i];
            combinedKey[i + 28] = C[i];
        }

        // Apply PC2 to generate round key
        bitset<48> roundKey;
        for (int i = 0; i < 48; i++) {
            roundKey[47 - i] = combinedKey[56 - PC2[i]];
        }
        roundKeys.push_back(roundKey);
    }

    return roundKeys;
}

// DES encryption
bitset<64> desEncrypt(bitset<64> plaintext, vector<bitset<48>> roundKeys) {
    // Step 1: Initial Permutation
    bitset<64> permutedText = permute(plaintext, IP, 64);

    // Step 2: Split into left and right halves
    bitset<32> L, R;
    for (int i = 0; i < 32; i++) {
        L[i] = permutedText[i + 32];
        R[i] = permutedText[i];
    }

    // Step 3: 16 rounds of Feistel structure
    for (int round = 0; round < 16; round++) {
        bitset<32> newR = L ^ functionF(R, roundKeys[round]);
        L = R;
        R = newR;
    }

    // Step 4: Combine the halves and apply Final Permutation
    bitset<64> combined;
    for (int i = 0; i < 32; i++) {
        combined[i + 32] = L[i];
        combined[i] = R[i];
    }
    return permute(combined, FP, 64);
}

int main() {
    bitset<64> plaintext(0x0123456789ABCDEF);  // Example 64-bit plaintext
    bitset<64> key(0x133457799BBCDFF1);       // Example 64-bit key

    // Generate round keys
    vector<bitset<48>> roundKeys = generateKeys(key);

    // Encrypt the plaintext using DES
    bitset<64> ciphertext = desEncrypt(plaintext, roundKeys);

    cout << "Ciphertext: " << hex << ciphertext.to_ullong() << endl;

    return 0;
}
