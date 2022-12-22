#include "Digraph.h"

int main() {
    Digraph<char> d;
    d.read(cin);
    cout << "The Digraph's ";
    d.display(cout);
    cout << endl;

    int start, destination;
    char response;
    do {
        cout << "Start: ";
        cin >> start;
        cout << "Destination: ";
        cin >>destination;
        vector<int> path = d.shortestPath(start, destination);
        if (!path.empty()) {
            cout << "Shortest path is:\n";
            for (int k = path.size() - 1; k > 0; --k) {
                cout << setw(3) << path[k] << " " << d.data(path[k]) << endl;
                cout << "    |\n"
                     << "    v\n";
            }
            cout << setw(3) << destination << " " << d.data(destination) << endl;
        }
        cout << "\nMore (Y or N)?";
        cin >> response;
    } while (response == 'y' || response == 'Y');
    return 0;
}

/*
6
A 3
1 4
2 12
4 4
B 3
0 2
2 6
3 8
C 2
1 6
3 14
D 2
0 12
4 4
E 1
3 10
F 2
4 6
3 20
 */