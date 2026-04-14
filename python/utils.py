import matplotlib.pyplot as plt
import numpy as np
import time

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

def comparar_desempenho(nome, f_c, f_py, f_c_opt=None, tamanhos=[1000, 2000, 4000]):
    res = {
        'C': {'Tempos': {'Crescente': [], 'Aleatório': [], 'Decrescente': []}, 'Comps': {'Crescente': [], 'Aleatório': [], 'Decrescente': []}},
        'Py': {'Tempos': {'Crescente': [], 'Aleatório': [], 'Decrescente': []}, 'Comps': {'Crescente': [], 'Aleatório': [], 'Decrescente': []}}
    }
    
    if f_c_opt is not None:
        res['C_Opt'] = {'Tempos': {'Crescente': [], 'Aleatório': [], 'Decrescente': []}, 'Comps': {'Crescente': [], 'Aleatório': [], 'Decrescente': []}}

    for n in tamanhos:
        cresc, aleat, decresc = gerar_amostras(n)
        
        baterias = [('C', f_c, 'C'), ('Py', f_py, 'Py')]
        
        if f_c_opt is not None:
            baterias.insert(1, ('C Opt', f_c_opt, 'C_Opt'))
        
        for label, func, key in baterias:
            t, c = rodar_bateria(func, [cresc, aleat, decresc])
            res[key]['Tempos']['Crescente'].append(t[0])
            res[key]['Comps']['Crescente'].append(c[0])
            res[key]['Tempos']['Aleatório'].append(t[1])
            res[key]['Comps']['Aleatório'].append(c[1])
            res[key]['Tempos']['Decrescente'].append(t[2])
            res[key]['Comps']['Decrescente'].append(c[2])

    plotar_graficos_dinamico(nome, tamanhos, res, f_c_opt is not None)

def plotar_graficos_dinamico(nome, tamanhos, res, tem_otimizado):
    linhas = 3 if tem_otimizado else 2
    fig, axs = plt.subplots(linhas, 2, figsize=(16, 6 * linhas))
    fig.suptitle(nome, fontsize=20, fontweight='bold')
    
    estilos = {'Crescente': {'color': 'green'}, 'Aleatório': {'color': 'orange'}, 'Decrescente': {'color': 'red'}}
    casos = ['Crescente', 'Aleatório', 'Decrescente']
    
    config = [('C (Padrão)', 'C', 0)]
    if tem_otimizado:
        config.append(('C (Branchless)', 'C_Opt', 1))
        config.append(('Python', 'Py', 2))
    else:
        config.append(('Python', 'Py', 1))

    for titulo, key, row in config:
        for c in casos:
            axs[row, 0].plot(tamanhos, res[key]['Tempos'][c], label=c, **estilos[c])
        axs[row, 0].set_title(f'Tempo {titulo}')
        axs[row, 0].grid(True)
        axs[row, 0].legend()
        
        for c in casos:
            axs[row, 1].plot(tamanhos, res[key]['Comps'][c], label=c, **estilos[c])
        axs[row, 1].set_title(f'Comparações {titulo}')
        axs[row, 1].grid(True)
        axs[row, 1].legend()

    plt.tight_layout(rect=[0, 0.03, 1, 0.96])
    plt.show()