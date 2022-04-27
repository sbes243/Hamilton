#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

void printcamino(vector<int> camino) {
    cout << "\nEs un camino Hamiltoniano\n";
    for (int i = 0; i < camino.size(); i++)
        cout << camino[i] << " ";

    cout << camino[0] << " ";
    cout << endl;
};

vector<string> split(const string& sentence, char param) {
    string parte;
    vector<string> separate;
    stringstream x(sentence);
    while (getline(x, parte, param)) {
        separate.push_back(parte);
    }
    return separate;
}

bool posible(int v, vector<vector<bool>> grafo,
    vector<int> camino, int pos)
{

    if (grafo[camino[pos - 1]][v] == 0)
        return false;

    for (int i = 0; i < pos; i++)
        if (camino[i] == v)
            return false;

    return true;
}

bool hamiltonrecur(vector<vector<bool>> grafo,
    vector<int> &camino, int pos)
{

    if (pos == grafo.size())
    {

        if (grafo[camino[pos - 1]][camino[0]] == 1)
            return true;
        else
            return false;
    }


    for (int v = 1; v < grafo.size(); v++)
    {

        if (posible(v, grafo, camino, pos))
        {
            camino[pos] = v;

            if (hamiltonrecur(grafo, camino, pos + 1) == true)
                return true;

            camino[pos] = -1;
        }
    }


    return false;
}

bool circuito(vector<vector<bool>> grafo)
{

    vector<int> camino;
    for (int i = 0; i < grafo.size(); i++) {
        camino.push_back(-1);
    }

    camino[0] = 0;
    if (hamiltonrecur(grafo, camino, 1) == false)
    {
        cout << "\nNo es camino Hamiltoniano";
        return false;
    }
    printcamino(camino);
    return true;
}

int main()
{
    ifstream mymatrix("matriz.txt");
    vector<string> a;
    string line;
    vector<vector<bool>> camin;
    while (getline(mymatrix, line)) {
        vector<string> separate = split(line, ' ');
        vector<bool> linea;
        for (int i = 0; i < separate.size(); i++) {
            string g = separate[i];
            linea.push_back(stoi(g));
        }
        camin.push_back(linea);
        linea.empty();
        a.push_back(line);
    }

   
    circuito(camin);

    return 0;
}