/* 
 * File:   main2.cpp
 * Author: dominic
 *
 * Created on 30 November 2018, 15:53
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {  
    vector<int> frequencyChanges;
    vector<int> frequencies;
    
    ifstream myfile ("data");

    if (myfile.good()) {
        string line;
        int linevalue;
        while (getline(myfile, line)) {
            std::size_t pos = line.find("+");
            if (pos != std::string::npos) {
                line = line.replace(pos, 1, "");
            }
            linevalue = std::stoi(line);
            frequencyChanges.push_back(linevalue);
        }

        myfile.close();
    }
    
    int offset = 0;
    frequencies.push_back(offset);
    bool found = false;
    cout << "Number of frequency changes: " << frequencyChanges.size() << "\n";
    while (!found) {
        for (int i = 0; i < frequencyChanges.size(); i++) {
            offset += frequencyChanges.at(i);
            if (std::find(frequencies.begin(), frequencies.end(), offset) != frequencies.end()) {
                found = true;
                cout << "Found duplicate frequency: " << offset << "\n";
                break;
            } else {
                frequencies.push_back(offset);
            }
        }
        cout << "Iterated frequencies. Frequencies:" << frequencies.size() << " Current offset " << offset << "\n";
    }
    
    return 0;
}