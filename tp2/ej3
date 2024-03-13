#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
int a;
int vertices;
vector<tuple<int,int,int,int>> aristas;
long long D;
long long R;

struct DSU {
    DSU(int n){
        padre = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
        tamano = vector<int>(n,1);
    }

    int find(int v){
        while(padre[v] != v) v = padre[v];
        return v;
    }

    void unite(int u, int v){
        u = find(u); v = find(v);
        if(tamano[u] < tamano[v]) swap(u,v);
        //ahora u es al menos tan grande como v
        padre[v] = u;
        tamano[u] += tamano[v];
    }

    vector<int> padre;
    vector<int> tamano;

    //tamano[v] <= n
    //INV: si padre[v] != v entonces tamano[padre[v]] >= 2*tamano[v]
};

long double kruskal(vector<tuple<long double,int,int,int,int>>& E, int n){
    long double res = 0;
    sort(E.begin(),E.end(),greater<>());
    DSU dsu(n);

    int aristas = 0;
    for(auto tupla : E){
        //u y v estan en distinta cc?
        if(dsu.find(get<3>(tupla)) != dsu.find(get<4>(tupla))){
            dsu.unite(get<3>(tupla),get<4>(tupla));
            res += get<0>(tupla);
            aristas++;
            D += get<1>(tupla);
            R += get<2>(tupla);
        }
        if(aristas == n-1) break;
    }

    return res;
}

// a/b > c/d


int main() {
    int cantidadTest;
    cin >> cantidadTest;

    for (int i = 0; i < cantidadTest ; ++i) {
        cin >> vertices >> a;

        aristas={};



        for (int j = 0; j < a; ++j) {
            int v;
            int u;
            int di;
            int ri;

            cin >> u >> v >> di >> ri;

            aristas.push_back(make_tuple(di,ri,u,v));
        }



        long double cota =0;
        long double cotainf = 0;

        for (int j = 0; j < aristas.size(); ++j) {
            cota += get<0>(aristas[j]);
        }
        long double epsilon = 1e-8;
        long double c = cota/(long double) 2;
        long double res;
        int cont = 0;
        while (true){
            cont++;
            if(cont == 50){
                break;
            }
            D = 0;
            R = 0;

            //cout << c <<" " << cota-cotainf<<" " << epsilon<< " " << cota << " " << cotainf << "\n";
            vector<tuple<long double,int,int,int,int>> aristasC = {};
            for (int j = 0; j < aristas.size(); ++j) {
                long double peso = (long double)get<0>(aristas[j]) - (c* (long double)get<1>(aristas[j]));
                tuple<long double,int,int,int,int> temp = make_tuple(peso,get<0>(aristas[j]),get<1>(aristas[j]), get<2>(aristas[j]),get<3>(aristas[j]));
                aristasC.push_back(temp);
            }
            res = kruskal(aristasC,vertices);
            if (res>=0){
                cotainf = c;
                c = (cota+cotainf)/(long double) 2;

            }else{
                cota = c;
                c = (cota + cotainf)/(long double) 2;
            }

        }

        cout << D << " " << R << endl;

    }

}
