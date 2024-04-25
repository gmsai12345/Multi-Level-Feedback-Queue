#include <iostream>
#include <queue>
using namespace std;

class Process {
public:
    int arrTi, procTi, burTi, waTi, tuArTi, name;

    Process(int arrival, int burst, int pname) : arrTi(arrival), procTi(burst), burTi(burst), name(pname), waTi(0), tuArTi(0) {}

    // Operator overloading for comparison
    bool operator>(const Process& p) const {
        return arrTi > p.arrTi;
    }
};

class CompareBurst {
public:
    bool operator()(const Process& p1, const Process& p2) const {
        return p1.burTi > p2.burTi;
    }
};

int main() {
    int totTi = 0, totWaTi = 0, procnum, totTuArTi = 0;
    priority_queue<Process, vector<Process>, greater<Process>> queue8;
    priority_queue<Process, vector<Process>, CompareBurst> queue16;
    priority_queue<Process, vector<Process>, CompareBurst> queuesjf;

    cout << "Enter The Number Of Processes: ";
    cin >> procnum;
    for (int i = 1; i <= procnum; i++) {
        int arrival, burst;
        cout << "Enter process " << i << " arrival-time: ";
        cin >> arrival;
        cout << "Enter process " << i << " burst-time: ";
        cin >> burst;
        Process temp(arrival, burst, i);
        queue8.push(temp);
    }

    while (!queue8.empty() || !queue16.empty() || !queuesjf.empty()) {
        if (!queue8.empty()) {
            Process temp = queue8.top();
            queue8.pop();
            int tempTime = min(temp.procTi, 8);
            temp.procTi -= tempTime;
            totTi += tempTime;
            temp.waTi = max(0, totTi - temp.arrTi - temp.burTi);
            temp.tuArTi = temp.waTi + temp.burTi;
            if (temp.procTi <= 0) {
                cout << "Process " << temp.name << " has finished with waiting time: " << temp.waTi << " and turnaround time: " << temp.tuArTi << " From Queue 8\n";
                totTuArTi += temp.tuArTi;
                totWaTi += temp.waTi;
            } else {
                queue16.push(temp);
            }
        }

        if (!queue16.empty()) {
            Process temp = queue16.top();
            queue16.pop();
            int tempTime = min(temp.procTi, 16);
            temp.procTi -= tempTime;
            totTi += tempTime;
            temp.waTi = max(0, totTi - temp.arrTi - temp.burTi);
            temp.tuArTi = temp.waTi + temp.burTi;
            if (temp.procTi <= 0) {
                cout << "Process " << temp.name << " finished with waiting time: " << temp.waTi << " and turnaround time: " << temp.tuArTi << " From Queue 16\n";
                totTuArTi += temp.tuArTi;
                totWaTi += temp.waTi;
            } else {
                queuesjf.push(temp);
            }
        }

        if (!queuesjf.empty()) {
            Process temp = queuesjf.top();
            queuesjf.pop();
            totTi += temp.procTi;
            temp.waTi = max(0, totTi - temp.arrTi - temp.burTi);
            temp.tuArTi = temp.waTi + temp.burTi;
            cout << "Process " << temp.name << "  finished with waiting time: " << temp.waTi << " and turnaround time: " << temp.tuArTi << " From Queue Shortest Job First Queue\n";
            totTuArTi += temp.tuArTi;
            totWaTi += temp.waTi;
        }
    }

    cout << "The total waiting time: " << totWaTi << endl;
    cout << "Total turnaround time: " << totTuArTi << endl;
    cout << "The average waiting time is: " << (totWaTi) / procnum << endl;
    cout << "The average turnaround time is: " << (totTuArTi) / procnum << endl;

    return 0;
}
