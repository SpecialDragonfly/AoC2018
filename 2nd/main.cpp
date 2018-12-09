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

/*
 * 
 */
int main(int argc, char** argv) {  
    vector<string> twoEqual;
    vector<string> threeEqual;
    
    ifstream myfile ("data");
    
    if (myfile.good()) {
        string line;
        
        while (getline(myfile, line)) {
            std::map<char, int> counts;
            for (int i = 0; i < line.size(); i++) {
                std::pair<std::map<char,int>::iterator, bool> ret;
                ret = counts.insert(std::pair<char, int>(line.at(i), 1));
                if (ret.second == false) {
                    counts[line.at(i)]++;
                }
            }
            
            bool inTwo = false;
            bool inThree = false;
            map<char, int>::iterator it;
            for ( it = counts.begin(); it != counts.end(); it++ )
            {
                if (it->second == 2 && inTwo == false) {
                    inTwo = true;
                }
                if (it->second == 3 && inThree == false) {
                    inThree = true;
                }
            }
            if (inTwo) {
                twoEqual.push_back(line);
            }
            if (inThree) {
                threeEqual.push_back(line);
            }
        }

        myfile.close();
    }
    cout << "Result: " << twoEqual.size() * threeEqual.size() << "\n";
    
    return 0;
}