#include<bits/stdc++.h>
using namespace std;
const int INF = 4000;

vector<string> professors = {"Newton", "Euclid", "Gauss", "Euler", "Fahd", "Maryam"};
vector<string> classes = {"Calc 1", "Calc 2", "Linear Algebra", "Discrete Math", "Abstract ALgebra", "Real analysis",
 "Complex analysis", "Topology", "Differential geometry", "Partial differential equations", "Functional analysis", "Number theory", "Mathematical"};
vector<string> inverse_maps = {"source", "Newton", "Euclid", "Gauss", "Euler", "Fahd", "Maryam", "Calc 1", "Calc 2", "Linear Algebra", "Discrete Math", "Abstract ALgebra", "Real analysis",
 "Complex analysis", "Topology", "Differential geometry", "Partial differential equations", "Functional analysis", "Number theory", "Mathematical", "destination"};

int n = inverse_maps.size();

vector<vector<int>> affinity(n,vector<int>(n,0));
vector<vector<int>> residual(n,vector<int>(n,0));

map<string,int> maps;
vector<vector<int>> adj(n);

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
            if (parent[next] == -1 && residual[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, residual[cur][next]);
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
            residual[prev][cur] -= new_flow;
            residual[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

void init(){
    for(auto wordIndex = 0;wordIndex < n; wordIndex++){
        string word = inverse_maps[wordIndex];
        maps[word] = wordIndex;
    }

    // classes values
    affinity[maps["Calc 1"]][maps["destination"]] = 100;
    affinity[maps["Calc 2"]][maps["destination"]] = 100;
    affinity[maps["Linear Algebra"]][maps["destination"]] = 100;
    affinity[maps["Discrete Math"]][maps["destination"]] = 100;

    
    affinity[maps["Abstract ALgebra"]][maps["destination"]] = 70;
    affinity[maps["Real analysis"]][maps["destination"]] = 70;
    affinity[maps["Complex analysis"]][maps["destination"]] = 70;

    affinity[maps["Topology"]][maps["destination"]] = 40;
    affinity[maps["Differential geometry"]][maps["destination"]] = 40;
    affinity[maps["Partial differential equations"]][maps["destination"]] = 40;
    affinity[maps["Functional analysis"]][maps["destination"]] = 40;
    affinity[maps["Number theory"]][maps["destination"]] = 40;
    affinity[maps["Mathematical"]][maps["destination"]] = 40;

    // Newton's classes
    affinity[maps["Newton"]][maps["Calc 1"]] = 100;
    affinity[maps["Newton"]][maps["Calc 2"]] = 100;
    affinity[maps["Newton"]][maps["Linear Algebra"]] = 50;
    affinity[maps["Newton"]][maps["Discrete Math"]] = 50;
    affinity[maps["Newton"]][maps["Abstract ALgebra"]] = 50;
    affinity[maps["Newton"]][maps["Real analysis"]] = 50;
    affinity[maps["Newton"]][maps["Complex analysis"]] = 50;
    affinity[maps["Newton"]][maps["Functional analysis"]] = 50;

    // Euclid
    affinity[maps["Euclid"]][maps["Differential geometry"]] = 100;

    // Gauss    
    affinity[maps["Gauss"]][maps["Number theory"]] = 100;

    
    // Euler    
    affinity[maps["Euler"]][maps["Calc 1"]] = 50;
    affinity[maps["Euler"]][maps["Calc 2"]] = 50;
    affinity[maps["Euler"]][maps["Real analysis"]] = 100;
    affinity[maps["Euler"]][maps["Complex analysis"]] = 100;
    affinity[maps["Euler"]][maps["Functional analysis"]] = 100;
    
    // Fahd
    affinity[maps["Fahd"]][maps["Partial differential equations"]] = 100;

    // Maryam
    affinity[maps["Maryam"]][maps["Topology"]] = 100;

    // professor total value
    for(auto professor: professors){
        affinity[maps["source"]][maps[professor]] = 300;
    }

    residual = affinity;


    // initialize the adjacency list
    
    //source to professors
    for(auto professor:professors){
        adj[maps["source"]].push_back(maps[professor]);
    }

    //professors to courses
    for(auto professor: professors){
        for(auto course:classes){
            adj[maps[professor]].push_back(maps[course]);
        }
    }

    //courses to sink
    for(auto course:classes){
        adj[maps[course]].push_back(maps["destination"]);
    }

    
}

void display_assignemnts(){
    for(auto professor: professors){
        for(auto course:classes){
            int res = residual[maps[professor]][maps[course]];
            int flow = affinity[maps[professor]][maps[course]];
            if(flow > res){
                cout << professor << ": " << course << " -- " << flow << " vs " << res << endl;
            }
        }
    }
}

int main(){
    init();

    auto flow = maxflow(maps["source"],maps["destination"]);
    
    cout << flow << endl;
    display_assignemnts();

    return 0;
}