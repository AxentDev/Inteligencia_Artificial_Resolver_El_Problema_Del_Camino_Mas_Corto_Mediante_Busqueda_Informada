#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <set>

using namespace std;

// Estructura para representar un nodo en la frontera
struct Node {
    string city;
    int distance;
    int heuristic;
    vector<string> path; // Para almacenar el camino

    bool operator<(const Node& other) const {
        return heuristic > other.heuristic; // menor prioridad para menores heurísticas
    }
};

// Grafo con las distancias entre ciudades
unordered_map<string, unordered_map<string, int>> distancias = {
    {"Tarragona", {{"Bilbao", 419}, {"Huesca", 177}, {"Logroño", 340}, {"Madrid", 424}, {"Teruel", 216}, {"Guadalajara", 374}, {"Zaragoza", 187}, {"Burgos", 432}, {"Soria", 318}, {"Cuenca", 308}, {"Castellón", 167}, {"Valencia", 229}}},
    {"Bilbao", {{"Tarragona", 419}, {"Huesca", 242}, {"Logroño", 97}, {"Madrid", 323}, {"Teruel", 358}, {"Guadalajara", 293}, {"Zaragoza", 246}, {"Burgos", 119}, {"Soria", 171}, {"Cuenca", 361}, {"Castellón", 436}, {"Valencia", 473}}},
    {"Huesca", {{"Tarragona", 177}, {"Bilbao", 242}, {"Logroño", 172}, {"Madrid", 335}, {"Teruel", 207}, {"Guadalajara", 284}, {"Zaragoza", 67}, {"Burgos", 272}, {"Soria", 176}, {"Cuenca", 267}, {"Castellón", 240}, {"Valencia", 296}}},
    {"Logroño", {{"Tarragona", 340}, {"Bilbao", 97}, {"Huesca", 172}, {"Madrid", 251}, {"Teruel", 261}, {"Guadalajara", 212}, {"Zaragoza", 157}, {"Burgos", 103}, {"Soria", 77}, {"Cuenca", 138}, {"Castellón", 314}, {"Valencia", 375}}},
    {"Madrid", {{"Tarragona", 424}, {"Bilbao", 323}, {"Huesca", 335}, {"Logroño", 251}, {"Teruel", 220}, {"Guadalajara", 51}, {"Zaragoza", 273}, {"Burgos", 214}, {"Soria", 182}, {"Cuenca", 138}, {"Castellón", 302}, {"Valencia", 332}}},
    // Añadir el resto de las ciudades...
};

// Heurística aproximada
unordered_map<string, int> heuristica = {
    {"Tarragona", 229}, {"Bilbao", 473}, {"Huesca", 296}, {"Logroño", 375}, {"Madrid", 332},
    {"Teruel", 115}, {"Guadalajara", 270}, {"Zaragoza", 246}, {"Burgos", 424}, {"Soria", 311},
    {"Cuenca", 63}, {"Castellón", 63}, {"Valencia", 0}
};

// Algoritmo Voraz
pair<vector<string>, int> busqueda_voraz(const string& inicio, const string& objetivo) {
    priority_queue<Node> frontera;
    set<string> visitados;

    frontera.push({inicio, 0, heuristica[inicio], {inicio}}); // Incluir el camino

    while (!frontera.empty()) {
        Node actual = frontera.top();
        frontera.pop();

        if (visitados.count(actual.city)) {
            continue;
        }
        visitados.insert(actual.city);

        // Si se encuentra el objetivo
        if (actual.city == objetivo) {
            return {actual.path, actual.distance}; // Devuelve el camino y la distancia
        }

        // Expandir vecinos
        for (const auto& vecino : distancias[actual.city]) {
            if (!visitados.count(vecino.first)) {
                int nueva_distancia = actual.distance + vecino.second;
                vector<string> nuevo_camino = actual.path; // Crear una copia del camino actual
                nuevo_camino.push_back(vecino.first); // Añadir el vecino al nuevo camino
                frontera.push({vecino.first, nueva_distancia, heuristica[vecino.first], nuevo_camino});
            }
        }
    }

    return {{}, 0}; // Si no se encuentra camino
}

int main() {
    string inicio = "Logroño";
    string objetivo = "Valencia";

    auto resultado = busqueda_voraz(inicio, objetivo);
    vector<string> camino = resultado.first;
    int distancia = resultado.second;

    cout << "Camino Voraz: ";
    for (const auto& ciudad : camino) {
        cout << ciudad << " ";
    }
    cout << "\nDistancia total Voraz: " << distancia << " km" << endl;

    return 0;
}

