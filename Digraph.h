#include <map>
#include <vector>
#include <queue>
#include <iostream>
#include <iomanip>

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
    for (int i = 0; i < myAdjacencyLists.size(); ++i) {
        if (myAdjacencyLists[i].adjacencyList.empty()) {
            out << i << ": " << myAdjacencyLists[i].data << endl;
            continue;
        }
        out << i << ": " << myAdjacencyLists[i].data << "-";
        for (auto iter = myAdjacencyLists[i].adjacencyList.begin();
             iter != myAdjacencyLists[i].adjacencyList.end(); ++iter) {
            if (iter == myAdjacencyLists[i].adjacencyList.begin()) {
                out << myAdjacencyLists[iter->first].data;
            } else {
                out << "     " << myAdjacencyLists[iter->first].data;
            }
            out << endl;
        }
    }
}

template<typename DataType>
vector<int> Digraph<DataType>::shortestPath(int start, int destination) {
    int n = myAdjacencyLists.size();
    vector<int> distLabel(n, -1), predLabel(n, -1);
    vector<bool> flag(n, false);
    distLabel[start] = 0;
    int distance, vertex;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<> > vertexQueue;
    vertexQueue.push(pair<int, int>(0, start));
    while (!flag[destination] && !vertexQueue.empty()) {
        if (flag[vertexQueue.top().second]) {
            vertexQueue.pop();
            continue;
        }
        vertex = vertexQueue.top().second;
        distance = vertexQueue.top().first;
        flag[vertex] = true;
        vertexQueue.pop();
        for (auto iter = myAdjacencyLists[vertex].adjacencyList.begin();
             iter != myAdjacencyLists[vertex].adjacencyList.end(); ++iter) {
            if (!flag[iter->first] &&
                (predLabel[iter->first] < 0 || distLabel[iter->first] > distance + iter->second)) {
                distLabel[iter->first] = distance + iter->second;
                predLabel[iter->first] = vertex;
                vertexQueue.push(pair<int, int>(distance + iter->second, iter->first));
            }
        }
    }
    vector<int> path;
    if (distLabel[destination] < 0) {
        cout << "Destination not reachable from start vertex\n";
    } else {
        path.push_back(destination);
        int d = destination;
        while (predLabel[d] != -1) {
            path.push_back(predLabel[d]);
            d = predLabel[d];
        }
    }
    return path;
}