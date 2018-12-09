#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

class Point {
    int m_x;
    int m_y;
    bool m_isInfinite = false;
public:
    Point(int x, int y) {
        m_x = x;
        m_y = y;
    }
    string coords() {
        stringstream ss;
        ss << "(" << m_x << ", " << m_y << ")";
        return ss.str();
    }
    
    void output() {
        cout << "(" << m_x << ", " << m_y << ") Is Infinite: " << (m_isInfinite ? "Y" : "N") << "\n";
    }
    int x() {
        return m_x;
    }
    int y() {
        return m_y;
    }
    int distanceFrom(int x, int y) {
        return abs(x-m_x) + abs(y-m_y);
    }
    void setAsInfinite() {
        m_isInfinite = true;
    }
};

class Coord {
    int m_x;
    int m_y;
    bool m_found;
    Point m_owner;
    map<Point, int> m_distances;
public:
    Coord(int x, int y) {
        m_x = x; 
        m_y = y;
    }
    void getDistances(vector<Point> points) {
        for (int i = 0; i < points.size(); i++) {
            m_distances.insert(
                {
                    points.at(i), 
                    points.at(i).distanceFrom(m_x, m_y)
                }
            );    
        }
    }
};

class Space {
    vector<Point> m_points;
    vector<Coord> m_coords;
public:
    Space(){}
    void addPoint(Point point) {
        m_points.push_back(point);
    }
    void calc() {
        int top = 999999999; // 0 ---------------- 99999
        int bottom = -1;
        int left = 99999999;
        int right = -1;
        for (int i = 0; i < m_points.size(); i++) {
            Point p = m_points.at(i);
            if (p.y() < top) {
                top = p.y();
            }
            if (p.y() > bottom) {
                bottom = p.y();
            }
            if (p.x() < left) {
                left = p.x();
            }
            if (p.x() > right) {
                right = p.x();
            }
        }
        
        for (int i = left; i < right; i++) {
            for (int j = top; j < bottom; j++) {
                Coord c = Coord(i, j);
                m_coords.push_back(c);
            }
        }
        for (int i = 0; i < m_coords.size(); i++) {
            m_coords.at(i).getDistances(m_points);
        }
    }
    void output() {
        for (int i = 0; i < m_points.size(); i++) {
            m_points.at(i).output();
        }
    }
};

int main(int argc, char** argv) {  
    ifstream myfile ("data2");
    
    if (myfile.good()) {
        string line;
        
        Space space;
        while (getline(myfile, line)) {
            // 67, 191
            int x = stoi(line.substr(0, line.find(",")));
            int y = stoi(line.substr(line.find(",") + 1, line.length()));
            Point p = Point(x, y);
            space.addPoint(p);
        }
        space.calc();
        space.output();
        
        myfile.close();
    }
      
    return 0;
}