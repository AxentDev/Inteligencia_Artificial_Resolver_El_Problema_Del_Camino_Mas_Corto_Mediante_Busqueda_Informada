#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

struct Nodo {
    string ciudad;
    int costo;
    int heuristica;

    bool operator>(const Nodo &n) const {
        return (costo + heuristica) > (n.costo + n.heuristica);
    }
};

pair<vector<string>, int> aStar(const string &inicio, const string &objetivo,
                                 const unordered_map<string, unordered_map<string, int>> &distancias,
                                 const unordered_map<string, int> &heuristica) {
    priority_queue<Nodo, vector<Nodo>, greater<Nodo>> frontera;
    unordered_map<string, string> cameFrom;
    unordered_map<string, int> costoAcumulado;
    vector<string> camino;

    frontera.push({inicio, 0, heuristica.at(inicio)});
    costoAcumulado[inicio] = 0;

    while (!frontera.empty()) {
        Nodo actual = frontera.top();
        frontera.pop();

        if (actual.ciudad == objetivo) {
            string ciudad = objetivo;
            while (ciudad != inicio) {
                camino.insert(camino.begin(), ciudad);
                ciudad = cameFrom[ciudad];
            }
            camino.insert(camino.begin(), inicio);
            return {camino, costoAcumulado[objetivo]};
        }

        for (const auto &vecino : distancias.at(actual.ciudad)) {
            int nuevoCosto = costoAcumulado[actual.ciudad] + vecino.second;

            if (costoAcumulado.find(vecino.first) == costoAcumulado.end() ||
                nuevoCosto < costoAcumulado[vecino.first]) {
                costoAcumulado[vecino.first] = nuevoCosto;
                cameFrom[vecino.first] = actual.ciudad;
                frontera.push({vecino.first, nuevoCosto, heuristica.at(vecino.first)});
            }
        }
    }

    return {{}, 0};
}

int main() {
    unordered_map<string, unordered_map<string, int>> distancias = {
        {"Tarragona", {{"Bilbao", 419}, {"Huesca", 177}, {"Logroño", 340}, {"Madrid", 424}, {"Teruel", 216}, {"Guadalajara", 374}, {"Zaragoza", 187}, {"Burgos", 432}, {"Soria", 318}, {"Cuenca", 308}, {"Castellón", 167}, {"Valencia", 229}}},
        // Agrega el resto de las ciudades aquí
    };

    unordered_map<string, int> heuristica = {
        {"Tarragona", 229}, {"Bilbao", 473}, {"Huesca", 296}, {"Logroño", 375}, {"Madrid", 332},
        {"Teruel", 115}, {"Guadalajara", 270}, {"Zaragoza", 246}, {"Burgos", 424}, {"Soria", 311},
        {"Cuenca", 63}, {"Castellón", 63}, {"Valencia", 0}
    };

    string inicio = "Logroño";
    string objetivo = "Valencia";

    auto [camino, distanciaTotal] = aStar(inicio, objetivo, distancias, heuristica);

    cout << "Camino A*: ";
    for (const auto &ciudad : camino) {
        cout << ciudad << (ciudad != objetivo ? " -> " : "");
    }
    cout << endl;
    cout << "Distancia total: " << distanciaTotal << " km" << endl;

    return 0;
}

