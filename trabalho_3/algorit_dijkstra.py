import sys

def dijkstra(graph, start):
    # Inicializa as estruturas de dados
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    visited = set()

    while len(visited) < len(graph):
        # Encontra o nó com a menor distância ainda não visitado
        min_distance = float('inf')
        min_node = None
        for node in graph:
            if node not in visited and distances[node] < min_distance:
                min_distance = distances[node]
                min_node = node

        if min_node is None:
            break

        visited.add(min_node)

        # Atualiza as distâncias dos vizinhos do nó atual
        for neighbor, weight in graph[min_node]:
            distance = distances[min_node] + weight
            if distance < distances[neighbor]:
                distances[neighbor] = distance

    return distances


def parse_tgf(file):
    graph = {}
    edges_started = False

    with open(file, 'r') as f:
        for line in f:
            line = line.strip()
            if line == '#':
                edges_started = True
                continue

            if edges_started:
                source, target, weight = map(int, line.split())
                if source not in graph:
                    graph[source] = []
                graph[source].append((target, weight))
            else:
                node, _ = line.split()
                node = int(node)
                if node not in graph:
                    graph[node] = []

    return graph


# Arquivo TGF fornecido
tgf_file = 'robot.tgf'

# Parse do arquivo TGF para obter o grafo
graph = parse_tgf(tgf_file)

# Nó de partida para calcular o caminho mínimo
start_node = 1

# Executa o algoritmo de Dijkstra
distances = dijkstra(graph, start_node)

# Imprime as distâncias mínimas a partir do nó de partida
for node, distance in distances.items():
    print(f'Distância mínima de {start_node} para {node}: {distance}')
