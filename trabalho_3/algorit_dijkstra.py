import sys

def dijkstra(grafo, partida):
    # inicializa as estruturas 
    distancias = {no: float('inf') for no in grafo}
    distancias[partida] = 0
    visitados = set()

    while len(visitados) < len(grafo):
        # aqui vai encontrar o nó com a menor distância ainda não visitado
        menor_distancia = float('inf')
        no_menor = None
        for no in grafo:
            if no not in visitados and distancias[no] < menor_distancia:
                menor_distancia = distancias[no]
                no_menor = no

        if no_menor is None:
            break

        visitados.add(no_menor)

        # vai atualiza as distâncias dos vizinhos do nó atual
        for vizinho, peso in grafo[no_menor]:
            distancia = distancias[no_menor] + peso
            if distancia < distancias[vizinho]:
                distancias[vizinho] = distancia

    return distancias


def parse_tgf(arquivo):
    grafo = {}
    arestas_iniciadas = False

    with open(arquivo, 'r') as f:
        for linha in f:
            linha = linha.strip()
            if linha == '#':
                arestas_iniciadas = True
                continue

            if arestas_iniciadas:
                origem, destino, peso = map(int, linha.split())
                if origem not in grafo:
                    grafo[origem] = []
                grafo[origem].append((destino, peso))
            else:
                no, _ = linha.split()
                no = int(no)
                if no not in grafo:
                    grafo[no] = []

    return grafo


# arquivo TGF fornecido
arquivo_tgf = r'c:\Users\SAMSUNG\Desktop\EstruturaDeDados\trabalho_3\robot.tgf'

# parse do arquivo TGF para obter o grafo
grafo = parse_tgf(arquivo_tgf)

# nó de partida para calcular o caminho mínimo
no_partida = 1

# vai executa o algoritmo 
distancias = dijkstra(grafo, no_partida)

# imprime as distâncias mínimas a partir do nó de partida
for no, distancia in distancias.items():
    print(f'Distância mínima de {no_partida} para {no}: {distancia}')
