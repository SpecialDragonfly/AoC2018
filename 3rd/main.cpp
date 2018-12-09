/* 
 * File:   main.cpp
 * Author: dominic
 *
 * Created on 30 November 2018, 15:53
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iterator>

using namespace std;

// A claim like #123 @ 3,2: 5x4
vector<int> getIndex(string line)
{
    int firstPtr = 0;
    int secondPtr = line.find("@");
    
    string ideaNumber = line.substr(firstPtr, secondPtr - firstPtr);
    ideaNumber.erase(ideaNumber.find_last_not_of(" \n\r\t")+1);
    
    firstPtr = secondPtr + 1;
    secondPtr = line.find(",");
    
    int xValue = stoi(line.substr(firstPtr, secondPtr - firstPtr));
    
    firstPtr = secondPtr + 1;
    secondPtr = line.find(":");
    
    int yValue = stoi(line.substr(firstPtr, secondPtr - firstPtr));
    
    firstPtr = secondPtr + 1;
    secondPtr = line.find("x");
    
    int width = stoi(line.substr(firstPtr, secondPtr - firstPtr));
    
    firstPtr = secondPtr + 1;
    secondPtr = line.length();
    
    int height = stoi(line.substr(firstPtr, secondPtr - firstPtr));
    
    cout << ideaNumber << "@" << xValue << "," << yValue << ": " << width << "x" << height << "\n";
    
    vector<int> numbers;
    for (int i = xValue; i < xValue + width; i++) {
        for (int j = yValue; j < yValue + height; j++) {
            int index = j * 1000 + i;
            numbers.push_back(index);
        }
    }
    
    return numbers;
}

int main(int argc, char** argv) {  
    ifstream myfile ("data");
    
    int positions[1000000];
    
    for (int i=0; i<1000000; i++) {
        positions[i] = 0;    // Initialize all elements to zero.
    }
    
    if (myfile.good()) {
        string line;
        
        while (getline(myfile, line)) {
            vector<int> values = getIndex(line);
            for (int i = 0; i < values.size(); i++) {
                positions[values.at(i)]++;
            }
        }
        
        int counter = 0;
        for (int i = 0; i < 1000000; i++) {
            if (positions[i] > 1) {
                counter++;
            }
        }

        cout << "final count: " << counter << "\n";
        
        myfile.clear();
        myfile.seekg(0);
        while (getline(myfile, line)) {
            cout << line << "\n";
            vector<int> values = getIndex(line);
            bool overlap = false;
            for (int i = 0; i < values.size(); i++) {
                if (positions[values.at(i)] > 1) {
                    overlap = true;
                    break;
                }
            }
            if (overlap == false) {
                cout << "found it!" << "\n";
                break;
            }
        }

        myfile.close();
    }
    
    return 0;
}