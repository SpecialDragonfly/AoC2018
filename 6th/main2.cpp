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
    bool distanceSum(vector<Point> points) {
        int max = 10000;
        int currentCount = 0;
        for (int i = 0; i < points.size(); i++) {
            int dist = points.at(i).distanceFrom(m_x, m_y);
            if (currentCount + dist >= max) {
                return false;
            }
            currentCount += dist;
        }
        //cout << "Valid point " << toString() << " dist: " << currentCount << "\n";
        return true;
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
        
        int regionCount = 0;
        for (int i = left; i <= right; i++) {
            for (int j = top; j <= bottom; j++) {
                Coord c = Coord(i, j);
                if (c.distanceSum(m_points)) {
                    regionCount++;
                }
            }
        }
        cout << "Region size: " << regionCount << "\n";
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
        
        myfile.close();
    }
      
    return 0;
}