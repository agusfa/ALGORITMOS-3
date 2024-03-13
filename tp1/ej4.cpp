#include <iostream>
#include <vector>
using namespace std;

int n;
int puestos;
vector<int> posiciones;
vector<vector<vector<int>>> memo;

vector<int> padres;



//calcula el costo ente prove j y prove i
int arreglarSuma(int i, int j){
    int costo = 0;
    int dist1;
    int dist2;
    for(int k = j+1; k < i;k++){
        dist1 = abs(posiciones[k]-posiciones[j]);
        dist2 = abs(posiciones[k]-posiciones[i]);
        costo += min(dist1,dist2);
    }
    return costo;
}

//calcula el costo entre 0-i con las prove = padres+i
int costoHasta(int i){
    int costo = 0;
    if (padres.empty()){
        return arreglarSuma( i,0);
    }
    costo += arreglarSuma(padres[0],0 );
    for (int j = 0; j < padres.size()-1; ++j) {
        costo += arreglarSuma(padres[j+1], padres[j]);
    }
    costo += arreglarSuma(i,padres[padres.size()-1]);
    return costo;
}

int costoEntre(int i, int j){
    int costo = 0;
    for (int k = 0; k < i; ++k) {
        costo += posiciones[k] - posiciones[j];
    }
    return costo;
}



int aux(int i, int k, int j){


    if ( i<puestos+1 and j<puestos+1 and k>=0 and  memo[i][k][j] != -1 ){
        return memo[i][k][j];
    }

    //ya puse todas las prove
    if (k==0){
        long  temp = 0;
        for (int l = i; l < puestos+1; ++l) {
            temp += abs(posiciones[l] - posiciones[j]);
        }
        if(i<puestos+1 and j<puestos+1){
            memo[i][k][j] = temp;
        }

        return temp;
    }

    if (i > puestos){
        return 1e9;
    }

    //quedan menos puestos que prove por poner
    if (puestos+1-i < k){
        memo[i][k][j] = 1000000000;
        return 1000000000;

    }

    int poner = aux(i+1,k-1, i) + arreglarSuma(i,j);
    int noPoner = aux(i+1, k, j);

    int res = min(poner , noPoner);

    memo[i][k][j] = res;

    return res;

}


int main() {

    int cantTest;
    cin >> cantTest;
    for (int t = 0; t < cantTest; t++) {
        cin >> puestos >> n;
        posiciones.resize(puestos + 1);
        posiciones[0] = 1e9;
        for (int j = 1; j < puestos + 1; j++) {
            cin >> posiciones[j];
        }

        memo.resize(puestos + 1);
        for (int i = 0; i < puestos + 1; ++i) {
            memo[i].resize(n + 1);
            for (int k = 0; k < n + 1; ++k) {
                memo[i][k].resize(puestos + 1);
            }
        }


        for (int i = 0; i < puestos + 1; ++i) {
            for (int j = 0; j < n + 1; ++j) {
                for (int k = 0; k < puestos + 1; ++k) {
                    memo[i][j][k] = -1;
                }

            }
        }




        padres = {};
        int res = aux(1, n, 0);

        int k = n;
        int i = 1;
        int j = 0;
        while (k > 0) {
            if (i == puestos) {
                //estoy en la ultima posicion y me queda una prove por poner
                padres.push_back(i);
                k--;
            } else if (memo[i + 1][k][j] == -1) {
                padres.push_back(i);
                i++;
                k--;
                j++;
            }  else if (memo[i + 1][k][j] >= memo[i + 1][k - 1][i] + arreglarSuma(i,j)) {
                //no poner >= poner
                padres.push_back(i);
                i++;
                k--;
                j = i-1;
            } else {
                //no poner < poner
                i++;

            }

        }

        cout << res << "\n";

/*
        for (int i = 0; i < puestos+1; ++i) {
            for (int j = 0; j < n+1; ++j) {
                for (int k = 0; k < puestos+1; ++k) {
                    cout << memo[i][j][k] << " ";
                }
                cout << "//";
            }
            cout << "\n";
        }

*/
        for(int l = 0; l < padres.size(); l++){
            cout << posiciones[padres[l]];
            if (l < padres.size()-1){
                cout << " ";
            }
        }
        cout << "\n";



    }




}
