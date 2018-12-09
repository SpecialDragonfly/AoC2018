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
#include <map>
#include <iterator>
#include <unordered_set>

using namespace std;

int distance(string first, string second) {
    int diff = 0;
    for (int i = 0; i < first.size(); i++) {
        if (first.at(i) != second.at(i)) {
            diff++;
        }
    }
    
    return diff;
}

string sameCharacters(string first, string second) {
    string result = "";
    
    for (int i= 0; i < first.size(); i++) {
        if (first.at(i) == second.at(i)) {
            result.push_back(first.at(i));
        }
    }
    
    return result;
}

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
    
    // Combine the lists.
    std::unordered_set<string> tmpList (twoEqual.begin(), twoEqual.end());
    for (int i = 0; i < threeEqual.size(); i++) {
        // Will automatically remove duplicates
        tmpList.insert(threeEqual.at(i));
    }

    cout << "Final list contains " << tmpList.size() << " elements." << "\n";
    
    vector<string> finalList (tmpList.begin(), tmpList.end());
    
    int counter = 0;
    for (int i = 0; i < finalList.size(); i++) {
        string firstElement = finalList.at(i);
        for (int j = i + 1; j < finalList.size(); j++) {
            string secondElement = finalList.at(j);
            int dist = distance(firstElement, secondElement);
            if (dist == 1) {
                cout << firstElement << " differed from " << secondElement << " by " << dist << "\n";
                cout << sameCharacters(firstElement, secondElement) << "\n";
            }
            counter++;
        }
    }
    
    cout << "Will make " << counter << " comparisons" << "\n";
    
    /*
     * Combine the lists of twoEqual and threeEqual
     * for ($i = 0; i < count(list)
     *   for ($j = $i + 1, $j < count(list)
     *     if (difference between count[$i] and count[$j] is 1 - save it.
     */
    
    /*
     * return array_intersect(box1, box2)
     */
    
    return 0;
}
