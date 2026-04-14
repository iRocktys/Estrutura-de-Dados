def bubble_sort(arr):
    comparacoes = 0
    n = len(arr)
    for i in range(n - 1, 0, -1):
        for j in range(0, i):
            comparacoes += 1
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    return comparacoes

def insertion_sort(arr):
    comparacoes = 0
    n = len(arr)
    for i in range(1, n):
        aux = arr[i]
        j = i - 1
        while j >= 0:
            comparacoes += 1
            if aux < arr[j]:
                arr[j + 1] = arr[j]
                j -= 1
            else:
                break
        arr[j + 1] = aux
    return comparacoes

def selection_sort(arr):
    comparacoes = 0
    n = len(arr)
    for i in range(n - 1):
        min_idx = i
        for j in range(i + 1, n):
            comparacoes += 1
            if arr[j] < arr[min_idx]:
                min_idx = j
        if i != min_idx:
            arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return comparacoes

def merge_sort(arr):
    comparacoes = [0] 
    def _merge_sort(vetor, comeco, fim):
        if comeco < fim:
            meio = (comeco + fim) // 2
            _merge_sort(vetor, comeco, meio)
            _merge_sort(vetor, meio + 1, fim)
            _merge(vetor, comeco, meio, fim)

    def _merge(vetor, comeco, meio, fim):
        com1, com2 = comeco, meio + 1
        vetAux = []
        while com1 <= meio and com2 <= fim:
            comparacoes[0] += 1
            if vetor[com1] < vetor[com2]:
                vetAux.append(vetor[com1])
                com1 += 1
            else:
                vetAux.append(vetor[com2])
                com2 += 1
        while com1 <= meio:
            vetAux.append(vetor[com1])
            com1 += 1
        while com2 <= fim:
            vetAux.append(vetor[com2])
            com2 += 1
        for i in range(len(vetAux)):
            vetor[comeco + i] = vetAux[i]

    _merge_sort(arr, 0, len(arr) - 1)
    return comparacoes[0]

def quick_sort(arr):
    comparacoes = [0]
    def _quick_sort(vetor, left, right):
        i, j = left, right
        x = vetor[(left + right) // 2]
        while i <= j:
            while vetor[i] < x and i < right:
                comparacoes[0] += 1
                i += 1
            comparacoes[0] += 1
            
            while vetor[j] > x and j > left:
                comparacoes[0] += 1
                j -= 1
            comparacoes[0] += 1
            
            if i <= j:
                vetor[i], vetor[j] = vetor[j], vetor[i]
                i += 1
                j -= 1
        if j > left:
            _quick_sort(vetor, left, j)
        if i < right:
            _quick_sort(vetor, i, right)
            
    _quick_sort(arr, 0, len(arr) - 1)
    return comparacoes[0]