#include "Digraph.h"

int main() {
    Digraph<int> d;
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
        cout << "Shortest path is:\n";
        for (int k = path.size() - 1; k > 0; --k) {
            cout << setw(3) << path[k] << " " << d.data(path[k]) << endl;
            cout << "    |\n"
                 << "    v\n";
        }
        cout << setw(3) << destination << " " << d.data(destination) << endl;
        cout << "\nMore (Y or N)?";
        cin >> response;
    } while (response == 'y' || response == 'Y');
    return 0;
}
/*
5
0 3
1 5
2 3
4 2
1 2
2 2
3 6
2 2
1 1
3 2
3 0
4 3
1 6
2 10
3 4
 */