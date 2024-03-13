#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


using namespace std;


int cantidadTest ;
int n ;
vector<double> tiempos ;
double mod = (pow(10,9)+7);
vector<double> descontentos ;



bool actualEsMenor(const pair<double,double>& a, const pair<double,double>& b){

    // actual < anterior
    // a/c < b/d <=> ad < bc
    double aPord = a.first * b.second;
    double bPorc = b.first * a.second;
    return aPord < bPorc;


}


int aux () {
    vector<pair<double, double>> datos(n);
    for (int i = 0; i < tiempos.size(); i++) {
        pair<double, double> tupla = make_pair(descontentos[i], tiempos[i]);

        datos[i] = tupla;
    }

    //sort(coef.begin(), coef.end());

    for (int i = 0; i < n; ++i) {

        pair<double, double> actual = datos[i];
        int j = i - 1;

        while (actualEsMenor(actual, datos[j]) and j >= 0) {
            datos[j + 1] = datos[j];
            j--;
        }
        datos[j + 1] = actual;

    }

    double res = 0;
    double minutos = 0;

    for (int i = n - 1; i >= 0; --i) {

        minutos += datos[i].second;
        double temp = datos[i].first * minutos;
        res += fmod(temp, mod);
    }
        res = fmod(res,mod);
        return res;

}


//100000 100000
//10000 20000


int main() {
    cin >> cantidadTest;
    for(int j = 0; j<cantidadTest; j++){
        cin >> n;

        tiempos.resize(n);
        descontentos.resize(n);
        for(int i=0; i<n; i++){
            double tiempo;
            cin >> tiempo;
            tiempos[i] = fmod(tiempo,mod);
        }

        for(int i=0; i<n; i++){
            double molestia;
            cin >> molestia;
            descontentos[i] = fmod(molestia,mod);
        }

        int res = aux();
        cout << res << "\n";

    }



}