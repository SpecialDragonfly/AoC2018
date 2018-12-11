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
    vector<Node> m_next;
    vector<Node> m_previous;
    bool m_handled;
    Node(){};
    Node(string id) {
        m_id = id;
    }
    string getId() const {
        return m_id;
    }
    void addNext(Node &next) {
        m_next.push_back(next);
    }
    void addPrerequisite(Node &previous) {
        m_previous.push_back(previous);
    }
    vector<Node> options() {
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

    Node& operator = (const Node& node) {
        m_id = node.m_id;
        m_next.clear();
        m_previous.clear();
        for (int i = 0; i < node.m_next.size(); i++) {
            m_next.push_back(node.m_next.at(i));
        }
        for (int i = 0; i < node.m_previous.size(); i++) {
            m_previous.push_back(node.m_previous.at(i));
        }
        
        return *this;
    }
};

void outputNodeVector(vector<Node> vec) {
    for (int i = 0; i < vec.size(); i++) {
        cout << vec.at(i).getId();
    }
    cout << "\n";
}

int main(int argc, char** argv) {  
    ifstream myfile ("data2");
    
    if (myfile.good()) {
        string line;
        
        vector<string> ids;
        vector<string> nextIds;
        map<string, Node> nodes;
        while (getline(myfile, line)) {
            // pieces[1] before pieces[2]
            regex pieces_regex(".*?Step ([A-Za-z]+) .*?step ([A-Za-z]+) .*$");
            smatch pieces_match;
            if (std::regex_match(line, pieces_match, pieces_regex)) {
                auto id = pieces_match[1];
                auto next = pieces_match[2];
                
                ids.push_back(id);
                nextIds.push_back(next);
                
                Node currentNode;
                Node nextNode;
                
                // Get the id node
                if (nodes.find(id) == nodes.end()) {
                    currentNode = Node(id);
                    nodes.insert({id, currentNode});
                }
                
                // Get the 'next' node
                if (nodes.find(next) == nodes.end()) {
                    nextNode = Node(next);
                    nodes.insert({next, nextNode});
                }
                
                nodes.at(id).addNext(nextNode);
                nodes.at(next).addPrerequisite(currentNode);                
            }
        }
        
        // Get the starting node
        // The node that exists in the list of ids that doesn't exist in the
        // list of 'nextIds' is our first Node.
        std::vector<string> v(ids.size());
        std::vector<string>::iterator it;
        
        auto last = std::unique(ids.begin(), ids.end());
        ids.erase(last, ids.end());
        
        last = std::unique(nextIds.begin(), nextIds.end());
        nextIds.erase(last, nextIds.end());
        
        std::sort(ids.begin(), ids.end());
        std::sort(nextIds.begin(), nextIds.end());
        it=std::set_difference (ids.begin(), ids.end(), nextIds.begin(), nextIds.end(), v.begin());
        
        // Get that first node.
        Node firstElement = nodes[v.at(0)];
        
        vector<Node> currentOptions;
        currentOptions.push_back(firstElement);

        vector<Node> newOptions;
        // For each node essentially.
        for (int count = 0; count < nodes.size(); count++) {
            cout << "Before sorting\n";
            outputNodeVector(currentOptions);
            // Sort our current options (because alphabetical order)
            std::sort(currentOptions.begin(), currentOptions.end());
            
            // We only want the unique options
            auto tmpIt = std::unique(currentOptions.begin(), currentOptions.end());
            currentOptions.erase(tmpIt, currentOptions.end());
            
            // Get the first one in the list
            Node nextElement = currentOptions.at(0);
            
            // What is it?
            cout << "Next: " << nextElement.getId() << "\n";
            
            // Remove it from the list
            currentOptions.erase(currentOptions.begin());
            cout << "After erasing: \n";
            outputNodeVector(currentOptions);
            
            // What are the options from that node?
            newOptions = nodes[nextElement.getId()].options();
            for (int i = 0; i < newOptions.size(); i++) {
                cout << "Adding " << newOptions.at(i).getId() << " to the list\n";
                currentOptions.push_back(newOptions.at(i));
            }
            cout << "New list: \n";
            outputNodeVector(currentOptions);
        }
        
        myfile.close();
    }
      
    return 0;
}