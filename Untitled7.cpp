#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>
#include <string>

using namespace std;

// Grafo con las distancias entre ciudades basado en la tabla proporcionada
unordered_map<string, unordered_map<string, int>> distancias = {
    {"Tarragona", {{"Bilbao", 419}, {"Huesca", 177}, {"Logro�o", 340}, {"Madrid", 424}, {"Teruel", 216}, {"Guadalajara", 374}, {"Zaragoza", 187}, {"Burgos", 432}, {"Soria", 318}, {"Cuenca", 308}, {"Castell�n", 167}, {"Valencia", 229}}},
    {"Bilbao", {{"Tarragona", 419}, {"Huesca", 242}, {"Logro�o", 97}, {"Madrid", 323}, {"Teruel", 358}, {"Guadalajara", 293}, {"Zaragoza", 246}, {"Burgos", 119}, {"Soria", 171}, {"Cuenca", 361}, {"Castell�n", 436}, {"Valencia", 473}}},
    {"Huesca", {{"Tarragona", 177}, {"Bilbao", 242}, {"Logro�o", 172}, {"Madrid", 335}, {"Teruel", 207}, {"Guadalajara", 284}, {"Zaragoza", 67}, {"Burgos", 272}, {"Soria", 176}, {"Cuenca", 267}, {"Castell�n", 240}, {"Valencia", 296}}},
    {"Logro�o", {{"Tarragona", 340}, {"Bilbao", 97}, {"Huesca", 172}, {"Madrid", 251}, {"Teruel", 261}, {"Guadalajara", 212}, {"Zaragoza", 157}, {"Burgos", 103}, {"Soria", 77}, {"Cuenca", 138}, {"Castell�n", 314}, {"Valencia", 375}}},
    {"Madrid", {{"Tarragona", 424}, {"Bilbao", 323}, {"Huesca", 335}, {"Logro�o", 251}, {"Teruel", 220}, {"Guadalajara", 51}, {"Zaragoza", 273}, {"Burgos", 214}, {"Soria", 182}, {"Cuenca", 138}, {"Castell�n", 302}, {"Valencia", 332}}},
    {"Teruel", {{"Tarragona", 216}, {"Bilbao", 358}, {"Huesca", 207}, {"Logro�o", 261}, {"Madrid", 220}, {"Guadalajara", 176}, {"Zaragoza", 146}, {"Burgos", 310}, {"Soria", 195}, {"Cuenca", 93}, {"Castell�n", 278}, {"Valencia", 115}}},
    {"Guadalajara", {{"Tarragona", 374}, {"Bilbao", 293}, {"Huesca", 284}, {"Logro�o", 212}, {"Madrid", 51}, {"Teruel", 176}, {"Zaragoza", 221}, {"Burgos", 212}, {"Soria", 138}, {"Cuenca", 106}, {"Castell�n", 273}, {"Valencia", 270}}},
    {"Zaragoza", {{"Tarragona", 187}, {"Bilbao", 246}, {"Huesca", 67}, {"Logro�o", 157}, {"Madrid", 273}, {"Teruel", 146}, {"Guadalajara", 221}, {"Burgos", 245}, {"Soria", 133}, {"Cuenca", 204}, {"Castell�n", 198}, {"Valencia", 246}}},
    {"Burgos", {{"Tarragona", 432}, {"Bilbao", 119}, {"Huesca", 272}, {"Logro�o", 103}, {"Madrid", 214}, {"Teruel", 310}, {"Guadalajara", 212}, {"Zaragoza", 245}, {"Soria", 119}, {"Cuenca", 284}, {"Castell�n", 402}, {"Valencia", 424}}},
    {"Soria", {{"Tarragona", 318}, {"Bilbao", 171}, {"Huesca", 176}, {"Logro�o", 77}, {"Madrid", 182}, {"Teruel", 195}, {"Guadalajara", 138}, {"Zaragoza", 133}, {"Burgos", 119}, {"Cuenca", 178}, {"Castell�n", 291}, {"Valencia", 311}}},
    {"Cuenca", {{"Tarragona", 308}, {"Bilbao", 361}, {"Huesca", 267}, {"Logro�o", 138}, {"Madrid", 138}, {"Teruel", 93}, {"Guadalajara", 106}, {"Zaragoza", 204}, {"Burgos", 284}, {"Soria", 178}, {"Castell�n", 164}, {"Valencia", 63}}},
    {"Castell�n", {{"Tarragona", 167}, {"Bilbao", 436}, {"Huesca", 240}, {"Logro�o", 314}, {"Madrid", 302}, {"Teruel", 278}, {"Guadalajara", 273}, {"Zaragoza", 198}, {"Burgos", 402}, {"Soria", 284}, {"Cuenca", 164}, {"Valencia", 63}}},
    {"Valencia", {{"Tarragona", 229}, {"Bilbao", 473}, {"Huesca", 296}, {"Logro�o", 375}, {"Madrid", 332}, {"Teruel", 115}, {"Guadalajara", 270}, {"Zaragoza", 246}, {"Burgos", 424}, {"Soria", 311}, {"Cuenca", 63}, {"Castell�n", 63}}}
};

// Heur�stica aproximada (distancia en l�nea recta hasta Valencia)
unordered_map<string, int> heuristica = {
    {"Tarragona", 229}, {"Bilbao", 473}, {"Huesca", 296}, {"Logro�o", 375}, {"Madrid", 332},
    {"Teruel", 115}, {"Guadalajara", 270}, {"Zaragoza", 246}, {"Burgos", 424}, {"Soria", 311},
    {"Cuenca", 63}, {"Castell�n", 63}, {"Valencia", 0}
};

// Algoritmo Voraz (Greedy Best-First Search)
pair<vector<string>, int> busqueda_voraz(const string &inicio, const string &objetivo) {
    priority_queue<tuple<int, string, int, vector<string>>, vector<tuple<int, string, int, vector<string>>>, greater<tuple<int, string, int, vector<string>>>> frontera; // (heur�stica, ciudad, distancia acumulada, camino)
    set<string> visitados;

    frontera.push(make_tuple(heuristica[inicio], inicio, 0, vector<string>{inicio}));

    while (!frontera.empty()) {
        auto [heur, actual, distancia_acumulada, camino] = frontera.top();
        frontera.pop();

        if (visitados.count(actual)) {
            continue;
        }
        visitados.insert(actual);

        if (actual == objetivo) {
            return {camino, distancia_acumulada};
        }

        // Expandir los vecinos de la ciudad actual
        for (const auto &vecino : distancias[actual]) {
            if (visitados.count(vecino.first) == 0) {
                int nueva_distancia = distancia_acumulada + vecino.second;
                // A�adir a la frontera con el nuevo camino y la distancia acumulada
                frontera.push(make_tuple(heuristica[vecino.first], vecino.first, nueva_distancia, camino + vector<string>{vecino.first}));
            }
        }
    }
    return {{}, 0};  // Si no se encuentra camino
}

// Ejecuci�n del algoritmo Voraz
int main() {
    string inicio = "Logro�o";
    string objetivo = "Valencia";

    auto [camino_voraz, distancia_voraz] = busqueda_voraz(inicio, objetivo);
    cout << "Camino Voraz: ";
    for (const auto &ciudad : camino_voraz) {
        cout << ciudad << (ciudad != objetivo ? " -> " : "");
    }
    cout << endl;
    cout << "Distancia total Voraz: " << distancia_voraz << " km" << endl;

    return 0;
}

