#include<bits/stdc++.h>
using namespace std;
const int INF = 4000;

int n;
vector<vector<int>> affinity;
vector<string> professors = {"Newton", "Euclid", "Gauss", "Euler", "Fahd", "Maryam"};
vector<string> classes = {"Calc 1", "Calc 2", "Linear Algebra", "Discrete Math", "Abstract ALgebra", "Real analysis",
 "Complex analysis", "Topology", "Differential geometry", "Partial differential equations", "Functional analysis", "Number theory", "Mathematical"};
vector<string> inverse_maps = {"Newton", "Euclid", "Gauss", "Euler", "Fahd", "Maryam", "Calc 1", "Calc 2", "Linear Algebra", "Discrete Math", "Abstract ALgebra", "Real analysis",
 "Complex analysis", "Topology", "Differential geometry", "Partial differential equations", "Functional analysis", "Number theory", "Mathematical"};


map<string,int> maps;
vector<vector<int>> adj(6, vector<int>(13));

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && affinity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, affinity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            affinity[prev][cur] -= new_flow;
            affinity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

void init(){
    for(auto wordIndex = 0;wordIndex < inverse_maps.size(); wordIndex++){
        string word = inverse_maps[wordIndex];
        maps[word] = wordIndex;
    }

    // Newton's classes
    adj[maps["Newton"]][maps["Calc 1"]] = 100;
    adj[maps["Newton"]][maps["Calc 2"]] = 100;
    adj[maps["Newton"]][maps["Linear Algebra"]] = 50;
    adj[maps["Newton"]][maps["Discrete Math"]] = 50;
    adj[maps["Newton"]][maps["Abstract ALgebra"]] = 50;
    adj[maps["Newton"]][maps["Real analysis"]] = 50;
    adj[maps["Newton"]][maps["Complex analysis"]] = 50;
    adj[maps["Newton"]][maps["Functional analysis"]] = 50;

    // Euclid
    adj[maps["Euclid"]][maps["Differential geometry"]] = 100;

    // Gauss    
    adj[maps["Gauss"]][maps["Number theory"]] = 100;

    
    // Euler    
    adj[maps["Euler"]][maps["Calc 1"]] = 50;
    adj[maps["Euler"]][maps["Calc 2"]] = 50;
    adj[maps["Euler"]][maps["Real analysis"]] = 100;
    adj[maps["Euler"]][maps["Complex analysis"]] = 100;
    adj[maps["Euler"]][maps["Functional analysis"]] = 100;
    
    // Fahd
    adj[maps["Fahd"]][maps["Partial differential equations"]] = 100;

    // Maryam
    adj[maps["Maryam"]][maps["Topology"]] = 100;

    
}

int main(){
    init();
    cout << "DONE" << endl;
    return 0;
}