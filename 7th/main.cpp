#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
#include <regex>

using namespace std;

class Node {
public:
    string m_id;
    vector<string> m_next;
    vector<string> m_previous;
    bool m_handled;
    Node(){};
    Node(string id) {
        m_id = id;
    }
    string getId() const {
        return m_id;
    }
    void addNext(string next) {
        m_next.push_back(next);
    }
    void addPrerequisite(string previous) {
        m_previous.push_back(previous);
    }
    vector<string> options() {
        return m_next;
    }
    void setHandled() {
        m_handled = true;
    }
    bool isHandled() {
        return m_handled;
    }
    bool operator < (const Node& node) const
    {
        return (m_id < node.m_id);
    }
    bool operator == (const Node& node) const
    {
        return (m_id < node.getId());
    }
};

int main(int argc, char** argv) {  
    ifstream myfile ("data2");
    
    if (myfile.good()) {
        string line;
        
        vector<string> ids;
        vector<string> next;
        map<string, Node> nodes;
        while (getline(myfile, line)) {
            // pieces[1] before pieces[2]
            regex pieces_regex(".*?Step ([A-Za-z]+) .*?step ([A-Za-z]+) .*$");
            smatch pieces_match;
            if (std::regex_match(line, pieces_match, pieces_regex)) {
                ids.push_back(pieces_match[1]);
                next.push_back(pieces_match[2]);
                if (nodes.find(pieces_match[1]) == nodes.end()) {
                    Node node = Node(pieces_match[1]);
                    node.addNext(pieces_match[2]);
                    nodes.insert({pieces_match[1], node});
                } else {
                    nodes.at(pieces_match[1]).addNext(pieces_match[2]);
                }
                if (nodes.find(pieces_match[2]) == nodes.end()) {
                    Node node = Node(pieces_match[2]);
                    node.addPrerequisite(pieces_match[1]);
                    nodes.insert({pieces_match[2], node});
                } else {
                    nodes.at(pieces_match[2]).addPrerequisite(pieces_match[1]);
                }
            }
        }
        
        std::vector<string> v(ids.size());
        std::vector<string>::iterator it;
        
        auto last = std::unique(ids.begin(), ids.end());
        ids.erase(last, ids.end());
        
        last = std::unique(next.begin(), next.end());
        next.erase(last, next.end());
        
        std::sort(ids.begin(), ids.end());
        std::sort(next.begin(), next.end());
        it=std::set_difference (ids.begin(), ids.end(), next.begin(), next.end(), v.begin());
        
        Node firstElement = nodes[v.at(0)];
        
        vector<Node> currentOptions;
        currentOptions.push_back(firstElement);

        vector<Node> newOptions;
        for (int count = 0; count < nodes.size(); count++) {
            std::sort(currentOptions.begin(), currentOptions.end());
            last = std::unique(currentOptions.begin(), currentOptions.end());
            //currentOptions.erase(last, currentOptions.end());               
            
            
//            string nextElement = currentOptions.at(0);
//            cout << "Next: " << nextElement << "\n";
//            currentOptions.erase(currentOptions.begin());
//            cout << "After erasing: \n";
//            for (int i = 0; i < currentOptions.size(); i++) {
//                cout << currentOptions.at(i);
//            }
//            cout << "\n";
//            newOptions = nodes[nextElement].options();
//            for (int i = 0; i < newOptions.size(); i++) {
//                currentOptions.push_back(newOptions.at(i));
//            }
        }
        
        myfile.close();
    }
      
    return 0;
}