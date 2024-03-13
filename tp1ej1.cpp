#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <tuple>

using namespace std;

int cantTests;
int rows;
int cols;
vector<vector<string>> matriz;



int aux(int i,int j,string pos, set<tuple<int ,int>> camino){

    int res = 0;

    if (i== rows or j == cols or i == -1 or j == -1){
        return 1000;
    }

    if (matriz[i][j] == "#"){
        return 1000;
    }

    if (i== rows -1 and j == cols-1){
        return 0;
    }

    tuple<int, int> tupla(i,j);
    if(camino.count(tupla) == 1){
        return 1000;
    }else{
        camino.insert(tupla);
    }

    if (matriz[i][j] == "+"){
        if (pos == "arriba"){
            res = min(1+ aux(i,j-1,"derecha", camino), min(1+ aux(i,j+1,"izquierda", camino), 1+ aux(i+1,j,"arriba", camino)));
        }

        if (pos == "abajo"){
            res = min(1+ aux(i,j-1,"derecha", camino), min(1+ aux(i,j+1,"izquierda", camino), 1+ aux(i-1,j,"abajo", camino)));
        }

        if (pos == "izquierda"){
            res = min(1+ aux(i+1,j,"arriba",camino), min(1+ aux(i,j+1,"izquierda",camino), 1+ aux(i-1,j,"abajo", camino)));
        }

        if (pos == "derecha"){
            res = min(1+ aux(i+1,j,"arriba",camino), min(1+ aux(i,j-1,"derecha",camino), 1+ aux(i-1,j,"abajo", camino)));
        }

    }

    if (matriz[i][j] == "L"){
        if (pos == "arriba"){
            res = min(1 + aux(i,j+1,"izquierda",camino),1 + aux(i,j-1,"derecha", camino));
        }
        if (pos == "derecha"){
            res = min(1 + aux(i+1,j,"arriba",camino),1 + aux(i-1,j,"abajo", camino));
        }
        if (pos == "izquierda"){
            res = min(1 + aux(i+1,j,"arriba",camino),1 + aux(i-1,j,"abajo", camino));
        }
        if (pos == "abajo"){
            res = min(1 + aux(i,j+1,"izquierda",camino),1 + aux(i,j-1,"derecha", camino));
        }
    }

    if(matriz[i][j] == "I"){
        if(pos == "arriba"){
            res = 1 + aux(i+1,j,"arriba",camino);
        }
        if(pos == "abajo"){
            res = 1 + aux(i-1,j,"abajo",camino);
        }
        if(pos == "derecha"){
            res = 1 + aux(i,j-1,"derecha", camino);
        }
        if(pos == "izquierda"){
            res = 1 + aux(i,j+1,"izquierda",camino);
        }
    }
    camino.erase(tupla);
    return res;
}



int aux2(int i,int j,string pos, set<tuple<int ,int>> camino){

    tuple<int, int> tupla(i,j);

    int res = 0;


    if (i== rows -1 and j == cols-1){
        return 0;
    }

    if (i== rows or j == cols or i == -1 or j == -1){
        return -1000;
    }

    if (matriz[i][j] == "#"){
        return -1000;
    }

    if(camino.count(tupla) == 1){
        return -1000;
    }else{
        camino.insert(tupla);
    }

    if (matriz[i][j] == "+"){
        if (pos == "arriba"){
            res = max(1+ aux2(i,j-1,"derecha", camino), max(1+ aux2(i,j+1,"izquierda", camino), 1+ aux2(i+1,j,"arriba", camino)));
        }

        if (pos == "abajo"){
            res = max(1+ aux2(i,j-1,"derecha", camino), max(1+ aux2(i,j+1,"izquierda", camino), 1+ aux2(i-1,j,"abajo", camino)));
        }

        if (pos == "izquierda"){
            res = max(1+ aux2(i+1,j,"arriba",camino), max(1+ aux2(i,j+1,"izquierda",camino), 1+ aux2(i-1,j,"abajo", camino)));
        }

        if (pos == "derecha"){
            res = max(1+ aux2(i+1,j,"arriba",camino), max(1+ aux2(i,j-1,"derecha",camino), 1+ aux2(i-1,j,"abajo", camino)));
        }

    }

    if (matriz[i][j] == "L"){
        if (pos == "arriba"){
            res = max(1 + aux2(i,j+1,"izquierda",camino),1 + aux2(i,j-1,"derecha", camino));
        }
        if (pos == "derecha"){
            res = max(1 + aux2(i+1,j,"arriba",camino),1 + aux2(i-1,j,"abajo", camino));
        }
        if (pos == "izquierda"){
            res = max(1 + aux2(i+1,j,"arriba",camino),1 + aux2(i-1,j,"abajo", camino));
        }
        if (pos == "abajo"){
            res = max(1 + aux2(i,j+1,"izquierda",camino),1 + aux2(i,j-1,"derecha", camino));
        }
    }

    if(matriz[i][j] == "I"){
        if(pos == "arriba"){
            res = 1 + aux2(i+1,j,"arriba",camino);
        }
        if(pos == "abajo"){
            res = 1 + aux2(i-1,j,"abajo",camino);
        }
        if(pos == "derecha"){
            res = 1 + aux2(i,j-1,"derecha", camino);
        }
        if(pos == "izquierda"){
            res = 1 + aux2(i,j+1,"izquierda",camino);
        }
    }
    camino.erase(tupla);
    return res;
}




int main() {


    //cout << "Ingrese cantidad de tests: ";
    cin >> cantTests;


    for(int i = 0; i<cantTests; i++){
        //cout << "Ingrese el numero de filas y columnas: ";
        cin >> rows >> cols;

        matriz.resize(rows,vector<string>(cols));
        for(int i = 0; i<rows;i++){
            matriz[i].resize(cols," ");
        }

        //cout << "Ingrese los elementos de la matriz por filas:" << endl;

        // Llenar la matriz con valores ingresados por el usuario
        for (int i = 0; i < rows; i++) {
            cout << "Fila " << i + 1 << ": ";
            for (int j = 0; j < cols; j++) {
                cin >> matriz[i][j];
            }
        }

        set<tuple<int, int>> camino;
        int resMin = min(aux(0, 0,  "arriba",camino), aux(0, 0,  "izquierda",camino));
        int resMax = max(aux2(0, 0,  "arriba",camino), aux2(0, 0,  "izquierda",camino));


        string res;
        if(resMin >= 1000){
            res = "IMPOSIBLE";
            cout << res <<"\n";
        }else{
            res = "POSIBLE";
            cout << res << " "<< resMin << " "<< resMax <<"\n";
        }



    }


    return 0;
}
