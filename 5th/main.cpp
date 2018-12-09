#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

void showVector(vector<char> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec.at(i);
    }
}

int main(int argc, char** argv) {  
    
    // a => A, A => a
    // not A => A or a => a
    // if (uppercase(char) == uppercase(previousChar)) // we're dealing with the same characters
    // if (char != previousChar && uppercase(char) == previousChar) // a => A
    // if (char != previousChar && char == uppercase(previousChar) // A => a
    char previousChar;
    char ch;
    fstream fin("data", fstream::in);
    vector<char> values;
    bool first = true;
    while (fin >> noskipws >> ch) {
        if (first) {
            previousChar = ch;
            //cout << "---\n";
            //showVector(values);
            //cout << "---\n";
            first = false;
            continue;
        }
        
        // Dealing with the same characters
        bool skip = false;
        if (toupper(previousChar) == toupper(ch)) {
            if (ch != previousChar && toupper(ch) == previousChar) {
                // skip
                skip = true;
                //cout << "skipping because " << ch << "/" << previousChar << "\n";
            } else if (ch != previousChar && ch == toupper(previousChar)) {
                // skip
                skip = true;
                //cout << "skipping because " << ch << "/" << previousChar << "\n";
            } else {
                //cout << "Found: " << ch << "/" << previousChar << "\n";
            }
        }
        if (skip == false) {
            //cout << "No skip\n";
            values.push_back(previousChar);
            previousChar = ch;
            //showVector(values);
            //cout << "\n";
        } else {
            //cout << "Annihilation! " << previousChar << "/" << ch << "\n";
            previousChar = values.back();
            //cout << "Previous character now " << previousChar << "\n";
            values.pop_back();
            //showVector(values);
            //cout << "\n";
            // previous character and this one annihilate each other.
            // new previous Char is whatever was last on the 
        }
    }
    
    cout << "Polymer size: " << values.size() << "\n";
      
    return 0;
}