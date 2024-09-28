//crypto attack on mono alphabetic cipher's cipher text

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<char, int> analyzeFrequency(const string &text) {
    map<char, int> freq;
    for (char c : text) {
        if (isalpha(c)) {
            c = toupper(c);
            freq[c]++;
        }
    }
    return freq;
}

vector<pair<char, int>> sortByFrequency(const map<char, int> &freq) {
    vector<pair<char, int>> sortedFreq(freq.begin(), freq.end());
    sort(sortedFreq.begin(), sortedFreq.end(), [](const pair<char, int> &a, const pair<char, int> &b) {
        return a.second > b.second;
    });
    return sortedFreq;
}

void printFrequencies(const map<char, int> &freq) {
    cout << "Letter frequencies:\n";
    for (const auto &pair : freq) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

void performFrequencyAnalysis(const string &ciphertext) {
    map<char, int> freq = analyzeFrequency(ciphertext);
    vector<pair<char, int>> sortedFreq = sortByFrequency(freq);
    
    printFrequencies(freq);

    cout << "\nSuggested substitutions (most common letters in English):\n";
    const string commonLetters = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    
    for (size_t i = 0; i < sortedFreq.size(); ++i) {
        if (i < commonLetters.size()) {
            cout << sortedFreq[i].first << " -> " << commonLetters[i] << endl;
        }
    }
}

int main() {
    string ciphertext;
    
    cout << "Enter the ciphertext (letters and spaces only): ";
    getline(cin, ciphertext);
    
    performFrequencyAnalysis(ciphertext);
    
    return 0;
}
