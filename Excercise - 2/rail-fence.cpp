//cipher attack on rail fence
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string railFenceDecrypt(string ciphertext, int numRails) {
    // Create a matrix to place the characters according to the rail pattern
    vector<vector<char>> rail(numRails, vector<char>(ciphertext.length(), '\n'));
    
    // Mark the places in the matrix with '*'
    bool dir_down = false;
    int row = 0, col = 0;

    for (int i = 0; i < ciphertext.length(); i++) {
        if (row == 0 || row == numRails - 1)
            dir_down = !dir_down;

        rail[row][col++] = '*';

        dir_down ? row++ : row--;
    }

    // Fill the marked places with characters from the ciphertext
    int index = 0;
    for (int i = 0; i < numRails; i++) {
        for (int j = 0; j < ciphertext.length(); j++) {
            if (rail[i][j] == '*' && index < ciphertext.length()) {
                rail[i][j] = ciphertext[index++];
            }
        }
    }

    // Now read the matrix to construct the plaintext
    string result;
    row = 0, col = 0;
    dir_down = false;

    for (int i = 0; i < ciphertext.length(); i++) {
        if (row == 0 || row == numRails - 1)
            dir_down = !dir_down;

        result.push_back(rail[row][col++]);

        dir_down ? row++ : row--;
    }

    return result;
}

int main() {
    string ciphertext = "WECRLTEERDSOEEFEAOCAIVDEN";
    
    // Try all possible keys (number of rails)
    for (int key = 2; key < ciphertext.length(); key++) {
        string decrypted_text = railFenceDecrypt(ciphertext, key);
        cout << "Key " << key << ": " << decrypted_text << endl;
    }

    return 0;
}
