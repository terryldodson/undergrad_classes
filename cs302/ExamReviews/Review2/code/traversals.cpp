#include <queue>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

template <typename Tkey>
void bfs(int source) {
    queue<int> Q;
    vector<bool> visited;
    Q.push(source);

    visited.assign(V.size(), false);

    while (!Q.empty()) {
        int i = Q.front();
        Q.pop();

        if (!visited[i]) {
            visited[i] = true;
            for (int k = 0; k < E[i].size(); k++)
                Q.push(E[i][k]);
        }
    }
}

template<typename Tkey>
void dfs(int source) {
    stack<int> S;
    vector<bool> visited;
    S.push(source);

    visited.assign(V.size(), false);

    while (!S.empty()) {
        int i = S.top();
        S.pop();

        if (!visited[i]) {
            visited[i] = true;
            for (int k = 0; k < E[i].size(); k++)
                S.push(E[i][k]);
        }
    }
}

