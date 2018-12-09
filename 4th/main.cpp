#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>

using namespace std;

class Record {
    string m_date;
    string m_thing;
public:
    Record() {
        
    }
    Record(string date, string thing) {
        m_date = date;
        m_thing = thing;
    }
    
    string getDate() {
        return m_date;
    }
    
    string toString() {
        return m_date + " " + m_thing;
    }
    
    bool isShiftStart() {
        return m_thing.substr(0, 5) == "Guard";
    }
    
    bool isSleep() {
        return m_thing.find("asleep") != std::string::npos;
    }
    
    bool isAwake() {
        return m_thing.find("wakes") != std::string::npos;
    }
    
    int getGuardId() {
        int first = m_thing.find("#");
        int second = m_thing.find("begin");
        return stoi(m_thing.substr(first + 1, second - first));
    }
    
    int getMinute() {
        int minutePtr = m_date.find(":");
        return stoi(m_date.substr(minutePtr + 1, 2));        
    }    
};

class Guard {
    int m_id;
    bool m_isAwake;
    Record m_sleepTime;
    int m_timeAsleep;
    int m_minutes[60];
public:
    Guard() {}
    Guard(int id) {
        m_id = id;
        m_isAwake = true;
        m_timeAsleep = 0;
        for (int i = 0; i < 60; i++) {
            m_minutes[i] = 0;
        }
    }
    
    void fallAsleep(Record record) {
        m_sleepTime = record;
    }
    
    void wakeUp(Record wakeRecord) {
//        cout << "Guard " << m_id << " sleeping between " << m_sleepTime.getMinute() << " and " << wakeRecord.getMinute() << "\n";
        for (int i = m_sleepTime.getMinute(); i < wakeRecord.getMinute(); i++) {
            m_minutes[i]++;
        }
    }
    
    int getId() {
        return m_id;
    }
    
    int minutesAsleep() {
        int count = 0;
        for (int i = 0; i < 60; i++) {
            if (m_minutes[i] > 0) {
                count += m_minutes[i];
            }
        }
        
        return count;
    }
    
    int * getMinutes() {
        return m_minutes;
    }
    
    int asleepCountDuringMinute(int minute) {
        return m_minutes[minute];
    }
    
    int mostCommonMinuteAsleep() {
        int minute = 0;
        int minuteCount = 0;
        for (int i = 0; i < 60; i++) {
            if (m_minutes[i] > minuteCount) {
                minute = i;
                minuteCount = m_minutes[i];
            }
        }
        
        return minute;
    }
    
    void outString() {
        cout << m_id << ": ";
        for (int i = 0; i < 60; i++) {
            cout << m_minutes[i] << "|";
        }
        cout << "\n";
    }
};

bool historySort (Record i, Record j) { return i.getDate() < j.getDate(); }

int main(int argc, char** argv) {  
    ifstream myfile ("data");
    
    vector<Record> history;
    
    if (myfile.good()) {
        string line;
        
        while (getline(myfile, line)) {
            // [1518-03-25 00:01] Guard #743 begins shift
            int datePtr = line.find("]");
            string date = line.substr(1, datePtr - 1);
            string thing = line.substr(datePtr + 2, line.size() - 1);
            history.push_back(Record(date, thing));
        }
        
        myfile.close();
    }
    
    std::sort(history.begin(), history.end(), historySort);
    
    map<int, Guard> guards;
    
    Guard currentGuard = Guard(-1);
    for (int i = 0; i < history.size(); i++) {
        Record tmpRec = history.at(i);
        
        if (tmpRec.isShiftStart()) {
            auto search = guards.find(tmpRec.getGuardId());
            if (search != guards.end()) {
                currentGuard = search->second;
            } else {
                currentGuard = Guard(tmpRec.getGuardId());
                guards.insert({tmpRec.getGuardId(), currentGuard});
            }
        } else if (tmpRec.isSleep()) {
            currentGuard.fallAsleep(tmpRec);
        } else if (tmpRec.isAwake()) {
            currentGuard.wakeUp(tmpRec);
        }
        guards.erase(currentGuard.getId());
        guards.insert({currentGuard.getId(), currentGuard});
    }
    
    map<int, Guard>::iterator it;
    for (it = guards.begin(); it != guards.end(); it++) {
        it->second.outString();
        cout << "Guard " << it->first << " was asleep for " << it->second.minutesAsleep() << " minutes most often " << it->second.mostCommonMinuteAsleep() << "\n";
    }
    
    int minuteSum[60];
    for (int i = 0; i < 60; i++) {
        minuteSum[i] = 0;
    }
    for (it = guards.begin(); it != guards.end(); it++) {
        int *minutes = it->second.getMinutes();
        for (int i = 0; i < 60; i++) {
            if (minutes[i] > 0) {
                minuteSum[i]++;
            }
        }
    }
    
    cout << "The number of guards asleep on any given minute\n";
    for (int i = 0; i < 60; i++) {
        cout << minuteSum[i] << "|";
    }
    cout << "\n";
    
    int greatestMinute = 0;
    int greatestMinuteSum = 0;
    for (int i = 0; i < 60; i++) {
        if (greatestMinuteSum < minuteSum[i]) {
            greatestMinuteSum = minuteSum[i];
            greatestMinute = i;
        }
    }
    cout << "Greatest minute: " << greatestMinute << " with a sum of " << greatestMinuteSum << "\n";
    
    for (int i = 0; i < 60; i++) {
        if (minuteSum[i] == greatestMinuteSum) {
            cout << "During minute " << i << " the following guards were asleep:\n";
            for (it = guards.begin(); it != guards.end(); it++) {
                cout << it->first << " for " << it->second.asleepCountDuringMinute(i) << " of those instances\n";
            }
        }
    }
    
//    int guardId = 0;
//    int maxSleepCount = 0;
//    for (it = guards.begin(); it != guards.end(); it++) {
//        int sleepCount = it->second.asleepCountDuringMinute(greatestMinute);
//        if (maxSleepCount < sleepCount) {
//            maxSleepCount = sleepCount;
//            guardId = it->first;
//        }
//    }        
//    cout << "The guard that contributed the most is " << guardId << " sleeping " << maxSleepCount << "\n";
  
    return 0;
}