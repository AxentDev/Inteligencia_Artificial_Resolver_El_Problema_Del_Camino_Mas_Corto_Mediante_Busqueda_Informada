# -*- coding: utf-8 -*-
"""
Created on Tue Oct 29 16:00:11 2024

@author: gran_
"""
import heapq

# Grafo con las distancias entre ciudades basado en la tabla proporcionada
distancias = {
    'Tarragona': {'Bilbao': 419, 'Huesca': 177, 'Logroño': 340, 'Madrid': 424, 'Teruel': 216, 'Guadalajara': 374, 'Zaragoza': 187, 'Burgos': 432, 'Soria': 318, 'Cuenca': 308, 'Castellón': 167, 'Valencia': 229},
    'Bilbao': {'Tarragona': 419, 'Huesca': 242, 'Logroño': 97, 'Madrid': 323, 'Teruel': 358, 'Guadalajara': 293, 'Zaragoza': 246, 'Burgos': 119, 'Soria': 171, 'Cuenca': 361, 'Castellón': 436, 'Valencia': 473},
    'Huesca': {'Tarragona': 177, 'Bilbao': 242, 'Logroño': 172, 'Madrid': 335, 'Teruel': 207, 'Guadalajara': 284, 'Zaragoza': 67, 'Burgos': 272, 'Soria': 176, 'Cuenca': 267, 'Castellón': 240, 'Valencia': 296},
    'Logroño': {'Tarragona': 340, 'Bilbao': 97, 'Huesca': 172, 'Madrid': 251, 'Teruel': 261, 'Guadalajara': 212, 'Zaragoza': 157, 'Burgos': 103, 'Soria': 77, 'Cuenca': 138, 'Castellón': 314, 'Valencia': 375},
    'Madrid': {'Tarragona': 424, 'Bilbao': 323, 'Huesca': 335, 'Logroño': 251, 'Teruel': 220, 'Guadalajara': 51, 'Zaragoza': 273, 'Burgos': 214, 'Soria': 182, 'Cuenca': 138, 'Castellón': 302, 'Valencia': 332},
    'Teruel': {'Tarragona': 216, 'Bilbao': 358, 'Huesca': 207, 'Logroño': 261, 'Madrid': 220, 'Guadalajara': 176, 'Zaragoza': 146, 'Burgos': 310, 'Soria': 195, 'Cuenca': 93, 'Castellón': 278, 'Valencia': 115},
    'Guadalajara': {'Tarragona': 374, 'Bilbao': 293, 'Huesca': 284, 'Logroño': 212, 'Madrid': 51, 'Teruel': 176, 'Zaragoza': 221, 'Burgos': 212, 'Soria': 138, 'Cuenca': 106, 'Castellón': 273, 'Valencia': 270},
    'Zaragoza': {'Tarragona': 187, 'Bilbao': 246, 'Huesca': 67, 'Logroño': 157, 'Madrid': 273, 'Teruel': 146, 'Guadalajara': 221, 'Burgos': 245, 'Soria': 133, 'Cuenca': 204, 'Castellón': 198, 'Valencia': 246},
    'Burgos': {'Tarragona': 432, 'Bilbao': 119, 'Huesca': 272, 'Logroño': 103, 'Madrid': 214, 'Teruel': 310, 'Guadalajara': 212, 'Zaragoza': 245, 'Soria': 119, 'Cuenca': 284, 'Castellón': 402, 'Valencia': 424},
    'Soria': {'Tarragona': 318, 'Bilbao': 171, 'Huesca': 176, 'Logroño': 77, 'Madrid': 182, 'Teruel': 195, 'Guadalajara': 138, 'Zaragoza': 133, 'Burgos': 119, 'Cuenca': 178, 'Castellón': 291, 'Valencia': 311},
    'Cuenca': {'Tarragona': 308, 'Bilbao': 361, 'Huesca': 267, 'Logroño': 138, 'Madrid': 138, 'Teruel': 93, 'Guadalajara': 106, 'Zaragoza': 204, 'Burgos': 284, 'Soria': 178, 'Castellón': 164, 'Valencia': 63},
    'Castellón': {'Tarragona': 167, 'Bilbao': 436, 'Huesca': 240, 'Logroño': 314, 'Madrid': 302, 'Teruel': 278, 'Guadalajara': 273, 'Zaragoza': 198, 'Burgos': 402, 'Soria': 284, 'Cuenca': 164, 'Valencia': 63},
    'Valencia': {'Tarragona': 229, 'Bilbao': 473, 'Huesca': 296, 'Logroño': 375, 'Madrid': 332, 'Teruel': 115, 'Guadalajara': 270, 'Zaragoza': 246, 'Burgos': 424, 'Soria': 311, 'Cuenca': 63, 'Castellón': 63}
}

# Heurística aproximada (distancia en línea recta hasta Valencia)
heuristica = {
    'Tarragona': 229, 'Bilbao': 473, 'Huesca': 296, 'Logroño': 375, 'Madrid': 332,
    'Teruel': 115, 'Guadalajara': 270, 'Zaragoza': 246, 'Burgos': 424, 'Soria': 311,
    'Cuenca': 63, 'Castellón': 63, 'Valencia': 0
}

# Algoritmo Voraz (Greedy Best-First Search)
def busqueda_voraz(inicio, objetivo):
    frontera = [(heuristica[inicio], inicio, 0, [inicio])]  # (heurística, ciudad, distancia acumulada, camino)
    visitados = set()

    while frontera:
        heur, actual, distancia_acumulada, camino = heapq.heappop(frontera)

        if actual in visitados:
            continue
        visitados.add(actual)

        if actual == objetivo:
            return camino, distancia_acumulada

        # Expandir los vecinos de la ciudad actual
        for vecino, costo in distancias[actual].items():
            if vecino not in visitados:
                nueva_distancia = distancia_acumulada + costo
                # Añadir a la frontera con el nuevo camino y la distancia acumulada
                heapq.heappush(frontera, (heuristica[vecino], vecino, nueva_distancia, camino + [vecino]))

    return [], 0  # Si no se encuentra camino

# Ejecución del algoritmo Voraz
inicio = 'Logroño'
objetivo = 'Valencia'

camino_voraz, distancia_voraz = busqueda_voraz(inicio, objetivo)
print("Camino Voraz:", camino_voraz)
print("Distancia total Voraz:", distancia_voraz, "km")
