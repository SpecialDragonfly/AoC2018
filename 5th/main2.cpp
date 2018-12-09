#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

class Foo {
private:
    char m_letter;
    char m_upperLetter;
    bool m_first = true;
    char m_previous;
    vector<char> m_values;
public:
    Foo(char letter) {
        m_letter = letter;
        m_upperLetter = toupper(letter);
    }
    
    void handle(char input) {
        if (input == m_letter || input == m_upperLetter) {
            return;
        }
        
        if (m_first) {
            m_previous = input;
            m_first = false;
            return;
        }
        
        // Dealing with the same characters
        bool skip = false;
        if (toupper(m_previous) == toupper(input)) {
            if (input != m_previous && toupper(input) == m_previous) {
                skip = true;
            } else if (input != m_previous && input == toupper(m_previous)) {
                skip = true;
            }
        }
        if (skip == false) {
            m_values.push_back(m_previous);
            m_previous = input;
        } else {
            m_previous = m_values.back();
            m_values.pop_back();
        }
    }
    
    bool first() {
        return m_first;
    }
    
    char letter() {
        return m_letter;
    }
    
    int size() {
        return m_values.size();
    }
    
    void output() {
        for (int i = 0; i < m_values.size(); i++) {
            cout << m_values.at(i);
        }
    }
};

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
    char ch;
    fstream fin("data", fstream::in);
    vector<Foo> checks;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for( char c : alphabet) {
        //do something
        checks.push_back(Foo(c));
    }

    while (fin >> noskipws >> ch) {
        for (int i = 0; i < checks.size(); i++) {
            checks.at(i).handle(ch);
        }
    }
    
    for (Foo check : checks) {
        cout << check.letter() << ": " << check.size() << "\n";
//        check.output();
//        cout << "\n";
    }
      
    return 0;
}