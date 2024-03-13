#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int filas;
int columnas;
vector<vector<int>> tiempos;
pair<int,int> hospital;
pair<int,int> paciente;

vector<pair<int,int>> direcciones(pair<int, int> pos){
    vector<pair<int,int>> res;

    if (pos.first +1 < filas){
        res.push_back(make_pair(pos.first+1,pos.second));
    }
    if (pos.first-1 >= 0){
        res.push_back(make_pair(pos.first-1,pos.second));
    }
    if (pos.second +1 < columnas){
        res.push_back(make_pair(pos.first,pos.second+1));
    }
    if (pos.second-1 >= 0){
        res.push_back(make_pair(pos.first,pos.second-1));
    }
    return res;

}



int bfs (pair<int,int> inicio, int time){
    vector<vector<bool>> visitado(filas,vector<bool> (columnas,false));
    vector<vector<int>> distancia(filas,vector<int> (columnas));

    visitado[inicio.first][inicio.second] = true;
    distancia[inicio.first][inicio.second] = 0;

    queue<pair<int,int>> q;
    q.push(inicio);



    while (!q.empty()) {
        pair<int,int> v = q.front(); q.pop();

        for (auto pos : direcciones(v)) {
            if (!visitado[pos.first][pos.second] and (tiempos[pos.first][pos.second]==0 or time < tiempos[pos.first][pos.second]-1)) {

                visitado[pos.first][pos.second] = true;
                distancia[pos.first][pos.second] = distancia[v.first][v.second] + 1;
                q.push(pos);

            }
        }
        time++;
    }

    if ((inicio == hospital and !visitado[paciente.first][paciente.second]) or (inicio==paciente and !visitado[hospital.first][hospital.second])){
        return -1;
    }

    if (inicio == hospital){
        return distancia[paciente.first][paciente.second];
    }else{
        return distancia[hospital.first][hospital.second];
    }

}





int main() {
    int cantTest;
    cin >> cantTest;


    for (int i = 0; i < cantTest; ++i) {
        cin >> filas >> columnas;

        tiempos.resize(filas);
        for (int j = 0; j < filas; ++j) {
            tiempos[j].resize(columnas);
        }

        for (int j = 0; j < filas; ++j) {
            for (int k = 0; k < columnas; ++k) {
                cin >> tiempos[j][k];
            }
        }

        cin >> hospital.first >> hospital.second;

        cin >> paciente.first >> paciente.second;

        int ida = bfs(hospital,0);
        int vuelta = bfs(paciente,ida) ;


        if (ida==-1 or vuelta== -1){
            cout << "IMPOSIBLE" << "\n";
        }else{
            vuelta = vuelta + ida;
            cout << ida << " " << vuelta << "\n";
        }
    }
    return 0;
}





