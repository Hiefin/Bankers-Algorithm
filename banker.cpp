#include <iostream>
#include <fstream>
using namespace std;

int main() {
    const int P = 5; // # of processes
    const int R = 3; // # of resources

    int total[R];      // total of each resource
    int alloc[P][R];   // matrix of allocated resources for each process
    int maxNeed[P][R]; // matrix ofmaximum resources processes may need
    int need[P][R];    // matrix of remaining resources
    int available[R];  // available resources

    ifstream file("input.txt");
    if (!file) {
        cout << "Can't open file\n";
        return 1;
    }

    // read in all resources and puts A,B,C into total array
    for (int j = 0; j < R; j++)
        file >> total[j];

    // read in allocation matrix from input.txt
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            file >> alloc[i][j];

    // read in maximum matrix from input.txt
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            file >> maxNeed[i][j];

    file.close();       // done with calculations from input.txt

    // find available resources
    for (int j = 0; j < R; j++) {
        int sum = 0;
        for (int i = 0; i < P; i++)
            sum += alloc[i][j];
        available[j] = total[j] - sum;
    }

    // find need matrix
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maxNeed[i][j] - alloc[i][j];

    // Find if in safe state
    bool finished[P] = {false};
    int safeSeq[P];
    int count = 0;

    while (count < P) {
        bool found = false;

        for (int i = 0; i < P; i++) {
            if (!finished[i]) {
                bool canRun = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > available[j]) { // if needs cant be fuffilled by available resources breaks and tries the next process
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    for (int j = 0; j < R; j++)
                        available[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finished[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "System is NOT in a safe state.\n";
            return 0;
        }
    }

    // Print if found /= false
    cout << "System is in a safe state.\nSafe sequence: < ";
    for (int i = 0; i < P; i++)
        cout << "P" << safeSeq[i] << " ";
    cout << ">\n";

    return 0;
}
