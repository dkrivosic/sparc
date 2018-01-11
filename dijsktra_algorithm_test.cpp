#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int inf = 100000000;
vector<vector<pair<int, int> > > graph;

int main() {
    int n, m, x;
    cin >>n >>m >>x;
    vector<int> bio(n, 0);
    vector<int> dist(n, inf);
    vector<int> parent(n, -1);
    vector<pair<int, int> > vpii;

    graph.insert(graph.begin(), n, vpii);
    set<pair<int, int> > nearest;
    for(int i=0; i<n; i++) nearest.insert(make_pair(inf, i));
    int a, b, c;
    for(int i=0; i<m; i++) {
        cin >>a >>b >>c;
        graph[a].push_back(make_pair(b, c));
        graph[b].push_back(make_pair(a, c));
    }

    dist[x] = 0;
    nearest.erase(make_pair(inf, x));
    nearest.insert(make_pair(0, x));
    int distance, vertex;
    pair<int, int> pii;
    for(int i=0; i<n-1; i++) {
        distance = (nearest.begin())->first;
        vertex = (nearest.begin())->second;
        nearest.erase(nearest.begin());
        bio[vertex]=1;
        for(int j=0; j<graph[vertex].size(); j++) {
            if(!bio[graph[vertex][j].first]) {
                if(dist[graph[vertex][j].first] > distance + graph[vertex][j].second) {
                    pii = graph[vertex][j];
                    parent[pii.first]=vertex;
                    nearest.erase(make_pair(dist[pii.first], pii.first));
                    dist[pii.first] = distance + pii.second;
                    nearest.insert(make_pair(distance+pii.second, pii.first));
                }
            }
        }
    }

    for(int j=0; j<n; j++) {
        int x=parent[j];
        cout <<j << ' ';
        while(x!=-1) {
            cout <<x << ' ';
            x = parent[x];
        }
        cout << " -> distance: " << dist[j] <<endl;
    }
}
