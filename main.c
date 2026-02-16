#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// aqui foi definido a estrutura
typedef struct {
    char algoritmo[20];
    int tamanho;
    double tempo;
    long long comparacoes;
    long long movimentacoes;
} Resultado;

// aqui vai ser o preenchimento que vai ser feito de forma decrescente 
void preencherDecrescente(int vetor[], int tamanho) {
	int i;
    for (i = 0; i < tamanho; i++) {
        vetor[i] = tamanho - i;
    }
}

// aqui é o algoritmo buuble para poder fazer a ordenação dos numeros
void bubbleSort(int vetor[], int tamanho, long long *comparacoes, long long *movimentacoes) {
	int i, j;
	
    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            (*comparacoes)++;
            if (vetor[j] > vetor[j + 1]) {
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                (*movimentacoes) += 3;
            }
        }
    }
}


// aqui praticamente a mesma coisa mas so que no algoritimo bubble
void selectionSort(int vetor[], int tamanho, long long *comparacoes, long long *movimentacoes) {
	int i, j;
	
    for (i = 0; i < tamanho - 1; i++) {
        int min = i;

        for (j = i + 1; j < tamanho; j++) {
            (*comparacoes)++;
            if (vetor[j] < vetor[min]) {
                min = j;
            }
        }

        if (min != i) {
            int temp = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = temp;
            (*movimentacoes) += 3;
        }
    }
}


// aqui vai ser executado o bubble e contar o tempo que foi necessario
Resultado executarBubble(int tamanho) {
    Resultado r;
    int *vetor = (int *)malloc(tamanho * sizeof(int));
    long long comparacoes = 0, movimentacoes = 0;
    clock_t inicio, fim;

    preencherDecrescente(vetor, tamanho);

    inicio = clock();
    bubbleSort(vetor, tamanho, &comparacoes, &movimentacoes);
    fim = clock();

    strcpy(r.algoritmo, "Bubble Sort");
    r.tamanho = tamanho;
    r.tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;
    r.comparacoes = comparacoes;
    r.movimentacoes = movimentacoes;

    free(vetor);
    return r;
}

// a mesma coisa que antes mas so que em selection
Resultado executarSelection(int tamanho) {
    Resultado r;
    int *vetor = (int *)malloc(tamanho * sizeof(int));
    long long comparacoes = 0, movimentacoes = 0;
    clock_t inicio, fim;

    preencherDecrescente(vetor, tamanho);

    inicio = clock();
    selectionSort(vetor, tamanho, &comparacoes, &movimentacoes);
    fim = clock();

    strcpy(r.algoritmo, "Selection Sort");
    r.tamanho = tamanho;
    r.tempo = (double)(fim - inicio) * 1000 / CLOCKS_PER_SEC;
    r.comparacoes = comparacoes;
    r.movimentacoes = movimentacoes;

    free(vetor);
    return r;
}

int main() {

    int tamanhos[] = {100, 1000, 10000}, i;
    Resultado resultados[6];
    int k = 0;

    // aqui vai executar o algoritimo bubble
    for (i = 0; i < 3; i++) {
        resultados[k++] = executarBubble(tamanhos[i]);
    }

    // e aqui vai executar o selection
    for (i = 0; i < 3; i++) {
        resultados[k++] = executarSelection(tamanhos[i]);
    }

    // aqui vai ser responsavel por inmprimir a tabela 
    printf("\n---------------------------------------------------------------------------------------------\n");
    printf("| %-15s | %-8s | %-12s | %-15s | %-15s |\n",
           "Algoritmo", "Tamanho", "Tempo (ms)", "Comparacoes", "Movimentacoes");
    printf("---------------------------------------------------------------------------------------------\n");

    for (i = 0; i < 6; i++) {
        printf("| %-15s | %-8d | %-12.3f | %-15lld | %-15lld |\n",
               resultados[i].algoritmo,
               resultados[i].tamanho,
               resultados[i].tempo,
               resultados[i].comparacoes,
               resultados[i].movimentacoes);
    }

    printf("---------------------------------------------------------------------------------------------\n");

    return 0;
}
