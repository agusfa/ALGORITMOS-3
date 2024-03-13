#include <iostream>
#include <vector>



using namespace std;

int cantTests;
int n;
int total;
vector<int> datos;
vector<char> respuesta;
int numMax;
vector<vector<int>> memo;



bool aux(int i, int monto, int inicial){
    if(i == inicial){
        i++;
    }
    if(i==n and monto==total){
        return true;
    }else if (i==n and monto!=total){
        return false;
    }

    if(inicial == 0 and memo[i][(monto + numMax) / 100] == 20000000){
        return true;
    }else if(inicial == 0 and memo[i][(monto + numMax) / 100] == -20000000){
        return false;
    }

    if (memo[i][(monto + numMax)/100] == inicial){
        return true;
    }else if (memo[i][(monto + numMax)/100] == -inicial){
        return false;
    }

    bool negativo = aux(i+1, monto-datos[i],inicial);
    bool positivo = aux(i+1, monto+datos[i],inicial);


    if (inicial == 0){
        if (positivo or negativo) {
            memo[i][(monto + numMax) / 100] = 20000000;
        } else {
            memo[i][(monto + numMax) / 100] = -20000000;
        }
    }else {
        if (positivo or negativo) {
            memo[i][(monto + numMax) / 100] = inicial;
        } else {
            memo[i][(monto + numMax) / 100] = -inicial;
        }
    }

    if (positivo or negativo){
        return true;
    }else{
        return false;
    }
}




int main() {
    cin >> cantTests;
    for(int i = 0;i<cantTests;i++){
        cin >> n >> total;
        datos.resize(n);
        for(int j = 0;j<n;j++){
            cin >> datos[j];
        }

        respuesta.resize(n);
        memo.resize(n);
        numMax = 0;
        for(int k = 0; k<n; k++){
            numMax += datos[k];

        }

        for (int k = 0; k<n; k++){ //Le pongo el tamaño adecuado a la matriz
            memo[k].resize(2*numMax/100 + 1);
        }

        for(int k = 0 ; k<n; k++){
            for (int j = 0; j < (2*numMax/100 + 1); j++){
                memo[k][j] = -10000000;
            }
        }

        for(int k = 0; k<n;k++){
            bool positivo = aux(0,datos[k],k);
            bool negativo = aux(0,-datos[k],k);
            if (positivo and negativo){
                respuesta[k] = '?';
            } else if (positivo){
                respuesta[k] = '+';
            } else if(negativo){
                respuesta[k] = '-';
            }

        }


        for(int j = 0;j<n;j++){
            cout << respuesta[j];
            if(j == n-1){
                cout << "\n";
            }

        }
    }

    return 0;
}
