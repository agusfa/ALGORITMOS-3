#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;

int esquinas;
int calles;
int personas;
int carga;
//vector<tuple<int,int,int>> mapa;


int INF = 1e9;

//Edmonds-Karp algorithm
vector<vector<int>> capPersonas;
vector<vector<int>> capacity;
vector<vector<int>> adj;

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
            if (parent[next] == -1 && (capPersonas[cur][next])) {
                parent[next] = cur;
                int new_flow = min(flow, (capPersonas[cur][next]));
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
    vector<int> parent(esquinas);
    int new_flow;

    while ((new_flow = bfs(s, t, parent))) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capPersonas[prev][cur] -= new_flow;
            capPersonas[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}



int main() {
    int cantTest;
    cin >> cantTest;


    for (int i = 0; i < cantTest; ++i) {

        cin >> esquinas >> calles >> personas;

        adj.resize(esquinas);

        capacity.resize(esquinas);
        capPersonas.resize(esquinas);
        for (int j = 0; j < esquinas; ++j) {
            adj[j] = {};
            capacity[j].resize(esquinas);
            capPersonas[j].resize(esquinas);
        }

        for (int j = 0; j < esquinas; ++j) {
            for (int k = 0; k < esquinas; ++k) {
                capacity[j][k] = 0;
            }
        }
        int ctotal = 0;
        for (int j = 0; j < calles; ++j) {
            int v, w, c;
            cin >> v >> w >> c;
            capacity[v-1][w-1] = c;
            adj[v-1].push_back(w-1);
            ctotal += c;

        }

        int sup = ctotal+1;
        int inf = 0;
        carga = ((sup+inf)/2);
        while(sup-inf >1){

            for (int j = 0; j < esquinas; ++j) {
                for (int k = 0; k < esquinas; ++k) {
                    capPersonas[j][k] = capacity[j][k] / carga;
                }
            }
            int flujo = maxflow(0,esquinas-1);
            //cout << flujo * carga << " " << cont << " " << carga << "\n";
            if (flujo >= personas){

                inf = carga;
                carga = (sup + inf) / 2;

            }else{
                sup = carga;
                carga = (sup + inf) / 2;
            }


        }

       // cout << cargaMax * personas << " ";
       // cout << sup * personas << " " << inf * personas<< " " << carga* personas;
        cout << inf * personas << "\n";

    }

}
