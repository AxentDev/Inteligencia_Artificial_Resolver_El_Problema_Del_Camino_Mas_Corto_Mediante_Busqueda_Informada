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

    // Operador para la prioridad en la cola
    bool operator>(const Nodo &n) const {
        return (costo + heuristica) > (n.costo + n.heuristica);
    }
};

// Implementación del algoritmo A*
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
            // Reconstruir el camino
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
    unordered_map<string, unordered_map<string, int>> distancias;
    distancias["Logroño"] = {{"Soria", 77}, {"Guadalajara", 212}, {"Cuenca", 138}};
    distancias["Soria"] = {{"Logroño", 77}, {"Guadalajara", 138}};
    distancias["Guadalajara"] = {{"Logroño", 212}, {"Soria", 138}, {"Cuenca", 106}};
    distancias["Cuenca"] = {{"Guadalajara", 106}, {"Valencia", 63}};
    distancias["Valencia"] = {};  // Ciudad de destino sin vecinos

    // Heurísticas
    unordered_map<string, int> heuristica;
    heuristica["Logroño"] = 500;
    heuristica["Soria"] = 400;
    heuristica["Guadalajara"] = 300;
    heuristica["Cuenca"] = 100;
    heuristica["Valencia"] = 0;

    string inicio = "Logroño";
    string objetivo = "Valencia";

    vector<string> camino = aStar(inicio, objetivo, distancias, heuristica);

    // Mostrar resultado
    cout << "Camino A*: ";
    int totalKilometros = 0;  // Variable para acumular los kilómetros
    for (size_t i = 0; i < camino.size(); ++i) {
        cout << camino[i];
        if (i < camino.size() - 1) {
            // Sumar la distancia al total
            totalKilometros += distancias[camino[i]][camino[i + 1]];
            cout << " -> ";
        }
    }
    cout << endl;
    cout << "Kilómetros totales: " << totalKilometros << " km" << endl;  // Mostrar kilómetros totales

    return 0;
}

