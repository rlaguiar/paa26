#include<math.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
 
#define TAM 10
#define PRINTABLE false

// número de trocas, pode ser usado em quase todos os algoritmos
unsigned long long int numTrocas;

// número de repetições e IFs, usados em algoritmos iterativos
unsigned long long int countExt;
unsigned long long int countInt;
unsigned long long int countIf; // não se aplica no inserion sort

// para o merge e quick
unsigned long long int numChamRec;
unsigned long long int numChamAux; // para as funções merge e partition
unsigned long long int tamPilha;
unsigned long long int tamMaxPilha;
unsigned long long int sumSizeSubVectors; // apenas para o merge

void zerarContadores() {
    countExt = countInt = countIf = numTrocas = 0;
    numChamRec = numChamAux = tamPilha = tamMaxPilha = sumSizeSubVectors = 0;
}

void swap(double *a, double *b){
    double temp = *a;
    *a = *b;
    *b = temp;
    numTrocas++;
}

void preencherAleatorio(double *v){
    for(int i=0; i<TAM; i++){
        v[i] = (double) rand() / RAND_MAX;
    }
}

void preencherOrdenado(double *v){
    v[0] = (double) rand() / RAND_MAX;
    for(int i=1; i<TAM; i++){
        v[i] = v[i-1] + (double) rand() / RAND_MAX;
    }
}

void preencherInversamente(double *v){
    preencherOrdenado(v);
    for(int i=0; i<TAM/2; i++){
        swap(&v[i], &v[TAM-1-i]);
    }
}

void preencherPoucosValores(double *v) {
    int numValores = (int) log2(TAM) + 1;
    double *dict = malloc(numValores * sizeof(double));
    for (int i = 0; i < numValores; i++) dict[i] = (double) rand() / RAND_MAX;
    for (int i = 0; i < TAM; i++) v[i] = dict[rand() % numValores];
    free(dict);
}

void preencherQuaseOrdenado(double *v) {
    preencherOrdenado(v);
    int num_trocas = (int) sqrt(TAM); 
    for (int i = 0; i < num_trocas; i++) {
        int idx1 = rand() % TAM;
        int idx2 = rand() % TAM;
        swap(&v[idx1], &v[idx2]);
    }
}

void imprimirVetor(double *v){
    if(!PRINTABLE) return;
    for(int i=0; i<TAM; i++){
        printf("%.2f\t", v[i]);
    }
    printf("\n");
}

void insertionSort(double *v){
    if(v==NULL) exit(1);
    int i, j;
    for(i=1; i<TAM; i++){
        countExt++;
        double chave = v[i];
        j=i-1;
        while(j>=0 && chave<v[j]) {
            v[j+1] = v[j];
            j--;
            countInt++;
        }
        v[j+1] = chave;
    }
}

void selectionSort(double *v) {
    // TODO: colocar aqui a versão tradicional do seletcionSort
    // TODO: utilizar a função swap que já está neste código,
    // até mesmo porque ela já conta o número de trocas.
    // utilizar os outros contadores globais para ordenação iterativa.
}

void bubbleSort(double *v) {
    for (int i = 0; i < TAM - 1; i++) {
        countExt++;
        for (int j = 0; j < TAM - 1; j++) {
            countInt++;             
            if (v[j] > v[j + 1]) {
                countIf++; 
                swap(&v[j], &v[j + 1]); 
            }
        }
    }
}

void merge(double *v, int p, int q, int r) {
    int nEsq = q - p + 1;
    int nDir = r - q;
    
    sumSizeSubVectors += nEsq + nDir;

    double *vetorEsq = malloc(nEsq*sizeof(double));
    double *vetorDir = malloc(nDir*sizeof(double));

    for (int i = 0; i < nEsq; i++) vetorEsq[i] = v[p + i];
    for (int j = 0; j < nDir; j++) vetorDir[j] = v[q + 1 + j];

    int i = 0, j = 0, k = p;

    while (i < nEsq && j < nDir)
        v[k++] = (vetorEsq[i] <= vetorDir[j]) ? vetorEsq[i++] : vetorDir[j++];
    
    while (i < nEsq) v[k++] = vetorEsq[i++];
    while (j < nDir) v[k++] = vetorDir[j++];

    free(vetorEsq);
    free(vetorDir);
}

void mergeSort(double *v, int p, int r) {
    
    numChamRec +=2 ;
    tamPilha++;
    if (tamPilha > tamMaxPilha) tamMaxPilha = tamPilha;
    
    if (p < r) {
        int q = p + (r - p) / 2;
        mergeSort(v, p, q);
        mergeSort(v, q + 1, r);
        merge(v, p, q, r);
        numChamAux++;
    }
    tamPilha--;
}

void mergeSortCaller(double *v){
    mergeSort(v, 0, TAM-1);
}

int partition(double *v, int p, int r) {
    double pivot = v[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (v[j] <= pivot) {
            i++;
            swap(&v[i], &v[j]);
        }
    }
    swap(&v[i + 1], &v[r]);
    return i + 1;
}

void quickSort(double *v, int p, int r) {
    numChamRec += 2;
    tamPilha++;
    if (tamPilha > tamMaxPilha) tamMaxPilha = tamPilha;
    if (p < r) {
        int q = partition(v, p, r);
        numChamAux++;
        quickSort(v, p, q - 1);
        quickSort(v, q + 1, r);
    }
    tamPilha--;
}

void quickSortCaller(double *v) {
    quickSort(v, 0, TAM - 1);
}

int main(){
    srand(time(NULL));
    clock_t inicio, fim;
    double tempo;
    double *vetor = malloc (TAM * sizeof(double));
    preencherInversamente(vetor);
    
    imprimirVetor(vetor);
    
    zerarContadores();
    inicio = clock();
    quickSortCaller(vetor);
    fim = clock();
    
    tempo = (double)(fim-inicio)/CLOCKS_PER_SEC;
    imprimirVetor(vetor);
    free(vetor);
    
    // métricas para os iterativos:
    // algumas podem não ser válidas para todos os algoritmos
    printf("\n\nlaço externo: %llu", countExt);
    printf("\nlaço interno: %llu", countInt);
    printf("\nnum ifs: %llu", countIf);
    
    // métricas para os recursivos:
    // algumas podem não ser válidas para todos os algoritmos
    printf("\n\nnum chamadas recursivas: %llu", numChamRec);
    printf("\nnum chamadas merge/partition: %llu", numChamAux);
    printf("\nsoma de tamanho dos vetores: %llu", sumSizeSubVectors);
    // printf("\ntamanho da pilha: %llu", tamPilha); apenas para testes
    printf("\ntamanho max da pilha: %llu", tamMaxPilha);
    
    // válido para quase todos os algoritmos
    printf("\n\nnúmero de trocas: %llu", numTrocas);

    // válido para todos os algoritmos
    printf("\n\ntempo em sec: %.4f", tempo);

    return 0;
}