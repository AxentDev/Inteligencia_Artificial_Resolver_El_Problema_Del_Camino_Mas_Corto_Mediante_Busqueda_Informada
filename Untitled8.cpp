#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>

using namespace std;

struct Nodo {
    string ciudad;
    int costo;
    int heuristica;

    // Operador para la prioridad en la cola
    bool operator>(const Nodo &n) const {
        return (costo + heuristica) > (n.costo + n.heuristica);
    }
};

vector<string> aStar(const string &inicio, const string &objetivo,
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
            return camino;
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

    return camino; // Retorna un camino vacío si no se encuentra
}

int main() {
    // Grafo de distancias
    unordered_map<string, unordered_map<string, int>> distancias = {
        //... (tu grafo de distancias aquí)
    };

    // Heurísticas
    unordered_map<string, int> heuristica = {
        //... (tu heurística aquí)
    };

    string inicio = "Logroño";
    string objetivo = "Valencia";

    vector<string> camino = aStar(inicio, objetivo, distancias, heuristica);

    // Mostrar resultado
    cout << "Camino A*: ";
    for (const auto &ciudad : camino) {
        cout << ciudad << (ciudad != objetivo ? " -> " : "");
    }
    cout << endl;

    return 0;
}

