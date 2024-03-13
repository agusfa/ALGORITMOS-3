#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int tamanio;


int INF = 1e7;

vector<vector<int>> tablero;

//Edmonds-Karp algoritm

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
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
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
    vector<int> parent(adj.size());
    int new_flow;

    while ((new_flow = bfs(s, t, parent))) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}



int main() {
    int cantTest;
    cin >> cantTest;

    for (int i = 0; i < cantTest; ++i) {

        cin >> tamanio;

        if (tamanio == 0){
            cout << 0 << "\n";
            continue;
        }

        tablero.resize(tamanio);
        for (int j = 0; j < tamanio; ++j) {
            tablero[j].resize(tamanio);
        }

        for (int j = 0; j < tamanio; ++j) {
            for (int k = 0; k < tamanio; ++k) {
                cin >> tablero[j][k];

            }
        }

        //calculamos la cantidad de filas en base a los espacios rotos
        int cantFilas = 0;
        for (int j = 0; j < tamanio; ++j) {

            int unos = 0;
            for (int k = 0; k < tamanio; ++k) {
                if (tablero[j][k] == 1){
                    if ((k!=0 and k!=(tamanio - 1)) and tablero[j][k - 1] != 1){
                        cantFilas++;
                    }
                    unos++;

                }
                if (k == tamanio - 1 and unos < tamanio){
                    cantFilas++;
                }

            }
        }

        //el vector de adyacencias va a estar numerado:
        //de 0 a cantFilas -1 son todas las filas del tablero
        //de cantFilas hasta el final -2 son todas las columnas
        //los ultimos dos son S y T
        adj.resize(cantFilas);
        for (int j = 0; j < cantFilas; ++j) {
            adj[j] = {};
        }


        vector<int> columnas(tamanio); // cada posicion del vector representa que columna hay que asignarle a cada fila
        //se acutaliza cada vez que nos encontramos con un 1
        for (int j = 0; j < tamanio; ++j) {
            columnas[j] = j;
        }


        int fila = 0;
        for (int j = 0; j < tamanio; ++j) {
            int unos = 0;
            for (int k = 0; k < tamanio; ++k) {
                if (tablero[j][k] == 1){
                    if ((k != 0 and k!=(tamanio - 1)) and tablero[j][k - 1] != 1){
                        fila++;
                    }
                    //para asegurarnos que no se pisen las numeracion de las columnas
                    //acutalizamos al numero de columna mayor + 1
                    //en algunos test quedan varias columnas vacias que no se usan
                    columnas[k] = *max_element(columnas.begin(),columnas.end()) +1;
                    unos++;

                }else if (tablero[j][k] == 0){

                    adj[fila].push_back(cantFilas + columnas[k]);

                }
            }
            if (unos < tamanio){
                fila++;
            }

        }

        //Añadimos los nodos que representan las columnas
        for (int j = 0; j <= *max_element(columnas.begin(),columnas.end()); ++j) {
            adj.push_back({});
        }

        //añadimos la vuelta de los nodos de columna a los nodos de fila
        for (int j = 0; j <cantFilas; ++j) {
            for (int k = 0; k < adj[j].size(); ++k) {
                int c = adj[j][k];
                adj[c].push_back(j);

            }
        }


//Añadimos el nodo S y sus aristas
        adj.push_back({});
        for (int j = 0; j < cantFilas; ++j) {
            adj[adj.size()-1].push_back(j);
            adj[j].push_back(adj.size()-1);
        }
        //Añadimos el nodo T y sus aristas
        adj.push_back({});
        for (int j = cantFilas; j < adj.size()-2; ++j) {
            adj[j].push_back(adj.size()-1);
            adj[adj.size()-1].push_back(j);
        }

        //Armamos la matriz de capacidades
        capacity.resize(adj.size());
        for (int j = 0; j < adj.size(); ++j) {
            capacity[j].resize(adj.size());
        }

        for (int j = 0; j < capacity.size()-1; ++j) {
            for (int k = 0; k < capacity.size(); ++k) {
                if(k == capacity.size()-2){
                    capacity[j][k] = 0;
                }else{capacity[j][k] = 1;}
            }
        }

        for (int j = cantFilas; j < adj.size()-2; ++j) {
            for (int k = 0; k < adj[j].size(); ++k) {
                if (adj[j][k] != adj.size()-1){
                    capacity[j][k] = 0;
                }
            }
        }

        //aristas de vuelta de una fila a S
        for (int j = 0; j < cantFilas; ++j) {
            capacity[j][adj.size()-2] = 0;
        }

        //aristas de vuelta de T a las columnas
        for (int j = cantFilas; j < adj.size()-2; ++j) {
            capacity[adj.size()-1][j] = 0;
        }

        for (int j = 0; j < adj.size(); ++j) {
            for (int k = 0; k < adj[j].size(); ++k) {
                cout << j << " " << adj[j][k] << " " << capacity[j][k] << "\n";
            }
        }

        int res = maxflow(adj.size()-2,adj.size()-1);
        cout << res << "\n";
    }
}
