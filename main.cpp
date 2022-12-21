#include <map>
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>
#include "Heap/Heap.h"

using namespace std;

template<typename DataType>
class Digraph {
public:
    DataType data(int k) const;

    void read(istream &in);

    void display(ostream &out);

    vector<int> shortestPath(int start, int destination);

private:
    class VertesInfo {
    public:
        DataType data;
        map<int, int> adjacencyList;
    };

    vector<VertesInfo> myAdjacencyLists;
};

template<typename DataType>
DataType Digraph<DataType>::data(int k) const {
    return myAdjacencyLists[k].data;
}

template<typename DataType>
void Digraph<DataType>::read(istream &in) {
    Digraph<DataType>::VertesInfo vi;
    int n, vertex, dis, m;
    myAdjacencyLists.push_back(vi);
    in >> m;
    while (m--) {
        in >> vi.data;
        in >> n;
        map<int, int> adjList;
        for (int i = 0; i < n; ++i) {
            in >> vertex >> dis;
            adjList.insert(pair<int, int>(vertex, dis));
        }
        vi.adjacencyList = adjList;
        myAdjacencyLists.push_back(vi);
    }
}

template<typename DataType>
void Digraph<DataType>::display(ostream &out) {
    out << "Adjacency-List Representation: \n";
    for (int i = 1; i < myAdjacencyLists.size(); ++i) {
        if (myAdjacencyLists[i].adjacencyList.empty()) {
            out << i << ": " << myAdjacencyLists[i].data << endl;
            continue;
        }
        out << i << ": " << myAdjacencyLists[i].data << "-";
        for (auto iter = myAdjacencyLists[i].adjacencyList.begin();
             iter != myAdjacencyLists[i].adjacencyList.end(); ++iter) {
            if (iter == myAdjacencyLists[i].adjacencyList.begin()) {
                out << iter->first;
            } else {
                out << "     " << iter->first;
            }
            out << endl;
        }
    }
}

template<typename DataType>
vector<int> Digraph<DataType>::shortestPath(int start, int destination) {
    int n = myAdjacencyLists.size();
    vector<int> distLabel(n, -1), predLabel(n);
    distLabel[start] = 0;
    int distance = 0, vertex;
    Heap<int> vertexQueue;
    vertexQueue.add(start);
    while (distLabel[destination] < 0 && !vertexQueue.empty()) {
        vertex = vertexQueue.top();
        vertexQueue.removeTop();
        if (distLabel[vertex] > distance) {
            distance++;
        }
        for (auto iter = myAdjacencyLists[vertex].adjacencyList.begin();
             iter != myAdjacencyLists[vertex].adjacencyList.end(); ++iter) {
            if (distLabel[iter->first] < 0) {
                distLabel[iter->first] = distance + iter->second;
                predLabel[iter->first] = vertex;
                vertexQueue.add(iter->first);
            }
        }
    }
    distance++;
    vector<int> path(distance + 1);
    if (distLabel[destination] < 0) {
        cout << "Destination not reachable from start vertex\n";
    } else {
        path[distance] = destination;
        for (int k = distance - 1; k >= 0; --k) {
            path[k] = predLabel[path[k + 1]];
        }
    }
    return path;
}

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
        for (int k = 0; k < path.size() - 1; ++k) {
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