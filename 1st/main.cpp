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

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {  
    vector<int> numbers;
    
    ifstream myfile ("data");
    
    int offset = 0;
    if (myfile.good()) {
        string line;
        int linevalue;
        while (getline(myfile, line)) {
            std::size_t pos = line.find("+");
            if (pos != std::string::npos) {
                line = line.replace(pos, 1, "");
            }
            linevalue = std::stoi(line);
            offset += linevalue;
        }

        myfile.close();
    }
    cout << "Final offset: " << offset << "\n";
    
    return 0;
}