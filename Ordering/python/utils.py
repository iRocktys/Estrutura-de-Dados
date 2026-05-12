import time

import matplotlib.pyplot as plt
import numpy as np


def gerar_amostras(tamanho):
    crescente = np.arange(tamanho, dtype=np.int32)
    aleatorio = np.random.randint(0, tamanho * 10, size=tamanho, dtype=np.int32)
    decrescente = np.arange(tamanho, 0, -1, dtype=np.int32)
    return crescente, aleatorio, decrescente


def rodar_bateria(funcao, amostras):
    tempos = []
    comps = []

    for amostra in amostras:
        arr_copy = amostra.copy()
        inicio = time.perf_counter()
        c = funcao(arr_copy)
        fim = time.perf_counter()

        tempos.append((fim - inicio) * 1000)
        comps.append(c)

    return tempos, comps


def comparar_desempenho(nome, f_c, f_py, tamanhos=None):
    if tamanhos is None:
        tamanhos = [1000, 2000, 4000]

    res = {
        'C': {
            'Tempos': {'Crescente': [], 'Aleatório': [], 'Decrescente': []},
            'Comps': {'Crescente': [], 'Aleatório': [], 'Decrescente': []},
        },
        'Python': {
            'Tempos': {'Crescente': [], 'Aleatório': [], 'Decrescente': []},
            'Comps': {'Crescente': [], 'Aleatório': [], 'Decrescente': []},
        },
    }

    casos = ['Crescente', 'Aleatório', 'Decrescente']
    baterias = [('C', f_c), ('Python', f_py)]

    for n in tamanhos:
        amostras = gerar_amostras(n)

        for linguagem, funcao in baterias:
            tempos, comparacoes = rodar_bateria(funcao, amostras)

            for i, caso in enumerate(casos):
                res[linguagem]['Tempos'][caso].append(tempos[i])
                res[linguagem]['Comps'][caso].append(comparacoes[i])

    plotar_graficos_dinamico(nome, tamanhos, res)


def plotar_graficos_dinamico(nome, tamanhos, res):
    fig, axs = plt.subplots(2, 2, figsize=(16, 12))
    fig.suptitle(nome, fontsize=20, fontweight='bold')

    estilos = {
        'Crescente': {'color': 'green'},
        'Aleatório': {'color': 'orange'},
        'Decrescente': {'color': 'red'},
    }
    casos = ['Crescente', 'Aleatório', 'Decrescente']
    config = [('C', 'C', 0), ('Python', 'Python', 1)]

    for titulo, key, row in config:
        for caso in casos:
            axs[row, 0].plot(tamanhos, res[key]['Tempos'][caso], label=caso, **estilos[caso])
        axs[row, 0].set_title(f'Tempo {titulo}')
        axs[row, 0].set_xlabel('Tamanho da entrada')
        axs[row, 0].set_ylabel('Tempo (ms)')
        axs[row, 0].grid(True)
        axs[row, 0].legend()

        for caso in casos:
            axs[row, 1].plot(tamanhos, res[key]['Comps'][caso], label=caso, **estilos[caso])
        axs[row, 1].set_title(f'Comparações {titulo}')
        axs[row, 1].set_xlabel('Tamanho da entrada')
        axs[row, 1].set_ylabel('Comparações')
        axs[row, 1].grid(True)
        axs[row, 1].legend()

    plt.tight_layout(rect=[0, 0.03, 1, 0.96])
    plt.show()
