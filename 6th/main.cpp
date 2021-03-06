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
    Point(){}
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
public:
    Coord(int x, int y) {
        m_x = x; 
        m_y = y;
    }
    string toString()
    {
        stringstream ss;
        ss << "(" << m_x << ", " << m_y << ")";
        return ss.str();   
    }
    bool getClosestTo(vector<Point> points, Point &p) {
        int minDistance = 999999999;
        for (int i = 0; i < points.size(); i++) {
            Point &point = points.at(i);
            
            int distance = point.distanceFrom(m_x, m_y);
            if (distance < minDistance) {
                minDistance = distance;
                p = point;
            }
        }
        int minCount = 0;
        for (int i = 0; i < points.size(); i++) {
            if (points.at(i).distanceFrom(m_x, m_y) == minDistance) {
                minCount++;
            } 
        }
        
        return minCount == 1;
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
        
        // So for each grid point, loop through all the test points, do the manhatten distance and 
        // if you don't get any equal ones add it to the list (I think you're using a vector)
        // for the closest test point
        
        map<string, int> territories;
        for (int i = 0; i < m_points.size(); i++) {
            territories.insert({m_points.at(i).coords(), 0});
        }
        for (int i = left; i <= right; i++) {
            for (int j = top; j <= bottom; j++) {
                Coord c = Coord(i, j);
                Point p = Point();
                bool found = c.getClosestTo(m_points, p);
                //cout << c.toString() << ": " << (found ? p.coords() : "no") << "\n";
                if (found) {
                    if (i == left || i == right || j == top || j == bottom) {
                        cout << p.coords() << " marked as infinite\n";
                        p.setAsInfinite();
                    } else {
                        territories.at(p.coords())++;
                    }
                }
            }
        }
        map<string, int>::iterator it;
        for (it = territories.begin(); it != territories.end(); it++) {
            cout << it->first << ": " << it->second << "\n";
        }
    }
    
    void output() {
        for (int i = 0; i < m_points.size(); i++) {
            m_points.at(i).output();
        }
    }
};

int main(int argc, char** argv) {  
    ifstream myfile ("data");
    
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