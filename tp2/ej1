#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int bases;
int enlaces;
int U,V;
vector<vector<int>> aristas;



vector<pair<int,int>> aux(){
    vector<pair<int,int>> res;
    for(int i= 0;i< aristas.size();i++){
        if (aristas[i].size() == 2){
            for (int j = 0; j < aristas[i].size(); ++j) {
                int n = aristas[i][j];
                if(aristas[i][j] < i and aristas[n].size() == 2){
                    continue;
                }
                res.push_back({min(i,n),max(i,n)});
            }
        }
    }
    return res;
}

int main() {

    int ctest;
    cin >> ctest;
    for (int i = 0; i < ctest; ++i) {
        cin >> bases >> enlaces;

        aristas.resize(bases);
        for (auto & arista : aristas) {
            arista = {};
        }
        for (int j = 0; j < enlaces; ++j) {
            cin >> U >> V;
            aristas[U].push_back(V);
            aristas[V].push_back(U);
        }


        vector<pair<int,int>> res = aux();
        sort(res.begin(), res.end());
        cout << res.size() << "\n";
        for (auto & re : res) {
            cout << re.first << " " << re.second << "\n";
        }
    }

    return 0;
}


